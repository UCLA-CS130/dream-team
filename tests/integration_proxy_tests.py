#!/usr/bin/env python

import os, sys, subprocess, time, httplib, urllib

# Dynamically creates a config file for the test

def create_test_config(port_number, test_fname):
    port = 'port ' + port_number + ';\n'
    proxy = 'path /proxy ProxyHandler {\n\t host localhost;\n\tport 12497;\n\t}\n'
    root_path = 'path / StaticHandler {\n\t root integration_dir;\n\t}\n'
    config_file_content = port + proxy + root_path

    config_file = open(test_fname, 'w+')
    config_file.write(config_file_content)
    config_file.close

def create_test_file(port_number, test_fname, contents):
    config_file_content =  contents

    config_file = open(test_fname, 'w+')
    config_file.write(config_file_content)
    config_file.close

# Creates and sends the request; returns the httplib response object

def send_request(port_number, request_type, request_resource):
    print("Sending request to {} for {}".format(port_number, request_resource))
    conn = httplib.HTTPConnection('localhost:' + port_number)
    conn.request(request_type, request_resource)
    return conn.getresponse()

def get_http_version_string(r_version):
    http_version = 'HTTP/'
    if r_version == 10:
        http_version += '1.0'
    elif r_version == 11:
        http_version += '1.1'
    
    return http_version

def check_status_line(response_direct, response_proxy):
    status_line = get_http_version_string(response_direct.version) + ' ' + str(response_direct.status) \
                      + ' ' + response_direct.reason
    status_line_2 = get_http_version_string(response_proxy.version) + ' ' + str(response_proxy.status) \
                      + ' ' + response_proxy.reason
    return status_line == status_line_2

def check_resp_body(response_direct, response_proxy):
    r_body = response_direct.read()
    r_body_2 = response_proxy.read()
    return r_body == r_body_2

def is_result_same(response_direct, response_proxy):
    return check_status_line(response_direct, response_proxy) and check_resp_body(response_direct, response_proxy)

def main():
    port_number = '12497'
    port_number_2 = '12498'
    test_fname = 'integration_proxy_test_config'
    test_fname_2 = 'integration_proxy_test_config2'
    test_file_name = 'integration_proxy_test.txt'
    path_to_bin = os.getcwd() + '/bin'
    path_to_config_file = path_to_bin + '/' + test_fname
    path_to_config_file_2 = path_to_bin + '/' + test_fname_2
    path_to_test_file = path_to_bin + '/integration_dir/' + test_file_name
    test_file_contents = "test file"

    create_test_config(port_number, path_to_config_file)
    create_test_config(port_number_2, path_to_config_file_2)
    create_test_file(port_number, path_to_test_file, test_file_contents)
    
    test_files = []
    test_files.append(test_fname)
    test_files.append(test_fname_2)

    request_type = 'GET'
    request_resource = '/' + test_file_name
    request_type_2 = 'GET'
    request_resource_2 = '/proxy/' + test_file_name

    processes = []
    for file in test_files:
        running_server = subprocess.Popen(['./webserver', file], cwd=path_to_bin)
        processes.append(running_server)

    # Add a short delay to make sure the server is listening before the request is sent
    time.sleep(1)

    # Set up request parameters
    try:
        response = send_request(port_number, request_type, request_resource)  
        response_2 = send_request(port_number_2, request_type_2, request_resource_2)        
        if is_result_same(response, response_2):
            print("Result is the same")
            sys.exit(0)
        else:
            print("Result is different")
            sys.exit(1)
    except httplib.HTTPException as err:
        print err.reason
        sys.exit(1)
    finally:
#        os.remove(path_to_config_file)
        running_server.kill()

if __name__ == "__main__":
    main()

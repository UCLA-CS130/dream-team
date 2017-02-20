#!/usr/bin/env python

import os, sys, subprocess, time, httplib, urllib

# Dynamically creates a config file for the test

def create_test_config(port_number, root_dir, test_fname):
    port = 'port ' + port_number + ';\n'
    echo = 'path /echo EchoHandler {};\n'
    root_path = 'path / StaticHandler {\n\t root tests/test_file_dir/;\n\t}\n'
    config_file_content = port + echo + root_path

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

def check_status_line(response):
    status_line = get_http_version_string(response.version) + ' ' + str(response.status) \
                      + ' ' + response.reason
    expected_status_line = 'HTTP/1.1 200 OK'
    return status_line == expected_status_line

def check_resp_headers(response):
    r_headers = response.getheaders()
    expected_headers = [('content-type', 'text/plain')]
    return r_headers == expected_headers

def check_resp_body(port, response, request_type, request_resource):
    request_text = '\r\n' + request_type + ' ' + request_resource + ' HTTP/1.1\r\n'
    # These are included in the request by default
    request_text += 'Host: localhost:' + port + '\r\nAccept-Encoding: identity\r\n' 
    request_text += '\r\n' # Termination of body
    
    resp_str = response.read()

    print("Request")
    print(request_text)

    print("Response")
    print(resp_str)
    return request_text == resp_str

def is_echo_valid(port, response, request_type, request_resource):
    return check_status_line(response) and check_resp_headers(response) \
           and check_resp_body(port, response, request_type, request_resource)

def main():
    port_number = '6673'
    root_dir = 'hola'
    test_fname = 'integration_test_config'
    path_to_bin = os.getcwd() + '/bin'
    path_to_config_file = path_to_bin + '/' + test_fname
    
    create_test_config(port_number, root_dir, path_to_config_file)    
    running_server = subprocess.Popen(['./webserver', test_fname], cwd=path_to_bin)

    # Add a short delay to make sure the server is listening before the request is sent
    time.sleep(1)

    # Set up request parameters
    request_type = 'GET'
    request_resource = '/echo/some_resource'
    
    # TODO when needed: send custom headers and url parameters
    #request_params = urllib.urlencode({})
    #request_headers = {}

    try:
        response = send_request(port_number, request_type, request_resource)        
        if is_echo_valid(port_number, response, request_type, request_resource):
            print("Valid echo")
            sys.exit(0)
        else:
            print("Invalid echo")
            sys.exit(1)
    except httplib.HTTPException as err:
        print err.reason
        sys.exit(1)
    finally:
#        os.remove(path_to_config_file)
        running_server.kill()

if __name__ == "__main__":
    main()

#!/usr/bin/env python

import os, subprocess, urllib2, time

# Dynamically creates a config file for the test

def create_test_config(port_number, test_fname):
    config_file_content = 'server {\n\tlisten ' + port_number + ';\n}\n'
    config_file = open(test_fname, 'w+')
    config_file.write(config_file_content)
    config_file.close

# Creates and sends the request; returns the urllib2 response object

def send_request(port_number, request_headers):
    get_request = urllib2.Request('http://localhost:' + port_number, headers=request_headers)
    return urllib2.urlopen(get_request)

def check_echo_response(port_number, request_headers):
    

def main():
    port_number = '2001'
    test_fname = 'integration_test_config'
    
    create_test_config(port_number, test_fname)

    running_server = subprocess.Popen(['./webserver', test_fname])

    # Add a short delay to make sure the server is listening before the request is sent
    time.sleep(1)

    # Taken from http://stackoverflow.com/questions/385262/how-do-i-send-a-custom-header-with-urllib2-in-a-http-request
    request_headers = {
    "Accept-Language": "en-US,en;q=0.5",
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:40.0) Gecko/20100101 Firefox/40.0",
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
    "Referer": "http://thewebsite.com",
    "Connection": "keep-alive" 
    }

    try:
        response = send_request(port_number, request_headers)
        print response.getcode()
        print response.headers
        print response.read()
    except urllib2.URLError as err:
        print err.reason
        system.exit(1)
    finally:
        os.remove(test_fname)
        running_server.kill()

if __name__ == "__main__":
    main()

#!/usr/bin/env python

import os, subprocess, urllib2, time

# Create a config file for the test

#port_number = '2001'
#test_fname = 'integration_test_config'

#config_file_content = 'server {\n\tlisten ' + port_number + ';\n}\n'

#config_file = open(test_fname, 'w+')
#config_file.write(config_file_content)
#config_file.close

# Run the server

running_server = subprocess.Popen(['./webserver', 'config_file'])

# Create and send the request

#res = subprocess.check_output(['./test_get_request.sh'])

time.sleep(3)

#res = subprocess.check_output(['curl', 'http://localhost:2001'])# + port_number])

print urllib2.urlopen('http://localhost:2001').read()

time.sleep(3)
# Clean-up

#os.remove(test_fname)
running_server.kill()

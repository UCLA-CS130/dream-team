#!/usr/bin/env python

import os.path, subprocess, urllib

if not os.path.isfile("config_file"):
    print "The config file does not exist - aborting tests"
    sys.exit(1)

running_server = subprocess.Popen(['./webserver', 'config_file'])
response = urllib.urlopen('http://localhost:2001')

print response.read()

running_server.kill();

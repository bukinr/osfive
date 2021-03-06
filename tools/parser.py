#-
# Copyright (c) 2019 Ruslan Bukin <br@bsdpad.com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

import sys
import os

# merge dict b into dict a
def merge(a, b, path = None):
	if path is None:
		path = []
	for key in b:
		if key in a:
			if type(a[key]) == dict and type(b[key]) == dict:
				merge(a[key], b[key], path + [str(key)])
			elif a[key] == b[key]:
				# same leaf value
				pass
			else:
				# conflict, keep original value
				pass
		else:
			a[key] = b[key]
	return a

#
# Process the value
#
def proc(d, key, val):
	k = key.strip()
	v = val.strip()

	#print('proc: key "' + k + '" val "' + v + '"')

	if v.startswith('{'):
		f = {}
		proc0(f, v.strip("{}"))
		if k in d:
			merge(d[k], f)
			#for k1 in f:
			#	d[k][k1] = f[k1]
		else:
			d[k] = f
	elif v.startswith("'"):
		if k in d:
			d[k].append(v.strip("'"))
		else:
			d[k] = [v.strip("'")]
	else:
		spl = v.split()
		for s in spl:
			if k in d:
				d[k].append(s)
			else:
				d[k] = [s]

#
# Find the key value pair
# First word is key, everything else until ';' is value
#
def proc0(d, data):
	i = 0
	tmp = ''
	key = ''
	val = ''
	depth = 0

	#print("proc0 %s\n" % data)

	while i < len(data):
		c = data[i]

		if (c == '#' and depth == 0):
			# Single line comment
			while c != '\n':
				c = data[i]
				i += 1
			continue

		elif ((c == ';' or i == len(data) - 1) and depth == 0):
			if val == '':
				val = tmp
				tmp = ''
			if (key and val):
				proc(d, key, val)
				key = ''
				val = ''
			i += 1
			continue

		elif (c == '='):
			if tmp.strip() == '':
				i += 1
				continue

		elif (c == ' ' or c == '\t'):
			if key == '' and tmp.strip():
				key = tmp
				tmp = ''

		elif (c == '{'):
			depth += 1
		elif (c == '}'):
			depth -= 1

		tmp += c
		i += 1

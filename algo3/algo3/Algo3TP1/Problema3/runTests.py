#!/usr/bin/env python

import os,sys

# os.system("rm sarasa3")
for n in range(9, 10):
	print "n: ", n
	for k in range(n**2+1):
		print "k: ", k
		# for i in range(min(k, 10) + 1):
		for i in range(100):
			# print n,",",k,",",i
			os.system("./ej3 < casos/"+str(n)+"-"+str(k)+"-"+str(i) + " >> sarasa4")
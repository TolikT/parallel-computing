#!/usr/bin/python

import commands
import sys


if __name__ == '__main__':
	# stage build
	file_list = []
	ret = commands.getstatusoutput("make seq")
       	file_list.append(ret[1].split(" ")[-1])

	# stage run
	n1 = 20000
	n2 = 200000
	delta = int((n2 - n1) / 10)

	for bin_file in file_list:	
		with open('{name}-1.csv'.format(name=bin_file), 'w+') as log_file:
			for pntr in range(n1, n2+1, delta):
				log_file.write("{pntr},{result}\n".format(pntr=pntr,result=float(commands.getstatusoutput("./{name} {pntr} 1".format(name=bin_file, pntr=pntr))[1].split("\n")[-1])))

				log_file.flush()

		with open('{name}-4.csv'.format(name=bin_file), 'w+') as log_file:
			for pntr in range(n1, n2+1, delta):
				log_file.write("{pntr},{result}\n".format(pntr=pntr,result=float(commands.getstatusoutput("./{name} {pntr} 4".format(name=bin_file, pntr=pntr))[1].split("\n")[-1])))
				log_file.flush()
	sys.exit(0)

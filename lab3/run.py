#!/usr/bin/python

import commands
import sys


if __name__ == '__main__':
	# stage build
	file_list = []
	ret = commands.getstatusoutput("make seq")
       	file_list.append(ret[1].split(" ")[-1])

	for schedule in ("static", "dynamic", "guided"):
        	for chunk in (2**pwr for pwr in range(0,10)):
            		ret = commands.getstatusoutput("make seq SCHEDULE={} CHUNK={}".format(schedule, chunk))
			file_list.append(ret[1].split(" ")[-1])

	# stage run
	n1 = 2000
	n2 = 20000
	delta = int((n2 - n1) / 10)

	for bin_file in file_list:	
		with open('{name}-little.csv'.format(name=bin_file), 'w+') as log_file:
			for pntr in range(n1, n2+1, delta):
				log_file.write("{pntr},{result}\n".format(pntr=pntr,result=int(commands.getstatusoutput("./{name} {pntr}".format(name=bin_file, pntr=pntr))[1].split("\n")[-1])))

				log_file.flush()
	sys.exit(0)

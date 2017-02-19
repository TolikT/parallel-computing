import sys
import getopt
import commands

options, _ = getopt.getopt(sys.argv[1:], 't:p:', ['time=', 'program='])

for opt, arg in options:
	if opt in ('-t', '--time'):
        	time = arg
    	elif opt in ('-p', '--program'):
        	program_name = arg

i = 0
while True:
	i += 100
	if int(commands.getstatusoutput("/home/tikhoa/lab1/{name} {size}".format(name=program_name, size=i))[1]) >= int(time):
		print i
		break

sys.exit(0)


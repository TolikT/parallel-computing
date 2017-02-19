import sys
import getopt
import commands


if __name__ == '__main__':
	options, _ = getopt.getopt(sys.argv[1:], 't:p:i:', ['time=', 'program=', 'interval='])

	for opt, arg in options:
		if opt in ('-t', '--time'):
        		time = arg
    		elif opt in ('-p', '--program'):
        		program_name = arg
    		elif opt in ('-i', '--interval'):
        		interval = int(arg)

	i = 0
	while True:
		i += interval
		if int(commands.getstatusoutput("./{name} {size}".format(name=program_name, size=i))[1].split('\n')[-1]) >= int(time):
			print i
			break

	sys.exit(0)


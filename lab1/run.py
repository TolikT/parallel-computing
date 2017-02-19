import commands
import sys


if __name__ == '__main__':
	n1 = int(commands.getstatusoutput("python find_size_by_time.py --time=100 --program=lab1-seq --interval=10000")[1])
	print "n1={}".format(n1)
	n2 = int(commands.getstatusoutput("python find_size_by_time.py --time=10000 --program=lab1-seq --interval=100000")[1])
	print "n2={}".format(n2)

	delta = int((n2 - n1) / 10)

	with open('seq.csv', 'w+') as seq_file:
		for pontr in range(n1, n2+1, delta):
			seq_file.write("{pntr},{result}\n".format(pntr=pntr,result=int(commands.getstatusoutput("./lab1-seq {size}".format(pntr))[1])))
	
	for i in range(2,12):
		with open('par{num}.csv'.format(num=i), 'w+') as seq_file:
			for pontr in range(n1, n2+1, delta):
				seq_file.write("{pntr},{result}\n".format(pntr=pntr,result=int(commands.getstatusoutput("./lab1-par-{num} {size}".format(num=i, size=pntr))[1])))

	sys.exit(0)



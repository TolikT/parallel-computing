import commands
import sys


if __name__ == '__main__':
	#n1 = int(commands.getstatusoutput("python find_size_by_time.py --time=100 --program=lab1-seq --interval=10000")[1])
	#print "n1={}".format(n1)
	#n2 = int(commands.getstatusoutput("python find_size_by_time.py --time=10000 --program=lab1-seq --interval=100000")[1])
	#print "n2={}".format(n2)
	n1 = 20000
	n2 = 200000
	delta = int((n2 - n1) / 10)
	
	for opt in (2, 3, 's'):
		with open('seq-o{}.csv'.format(opt), 'w+') as seq_file:
			for pntr in range(n1, n2+1, delta):
				seq_file.write("{pntr},{result}\n".format(pntr=pntr,result=int(commands.getstatusoutput("./lab1-seq-o{opt} {size}".format(opt=opt, size=pntr))[1].split("\n")[-1])))
	
	with open('seq.csv', 'w+') as seq_file:
		print "seq_file:\n"
		for pntr in range(n1, n2+1, delta):
			seq_file.write("{pntr},{result}\n".format(pntr=pntr,result=int(commands.getstatusoutput("./lab1-seq {size}".format(size=pntr))[1].split("\n")[-1])))
	
	for i in range(2,12):
		with open('par{num}.csv'.format(num=i), 'w+') as par_file:
			for pntr in range(n1, n2+1, delta):
				par_file.write("{pntr},{result}\n".format(pntr=pntr,result=int(commands.getstatusoutput("./lab1-par-{num} {size}".format(num=i, size=pntr))[1].split("\n")[-1])))

	for i in range(2,12):
		with open('par-icc{num}.csv'.format(num=i), 'w+') as par_icc_file:
			for pntr in range(n1, n2+1, delta):
				par_icc_file.write("{pntr},{result}\n".format(pntr=pntr,result=int(commands.getstatusoutput("./lab1-icc-par-{num} {size}".format(num=i, size=pntr))[1].split("\n")[-1])))
	
	sys.exit(0)

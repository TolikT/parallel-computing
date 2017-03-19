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
	
	for i in range(3,4):
		with open('lab2-par{num}.csv'.format(num=i), 'w+') as par_file:
			for pntr in range(n1, n2+1, delta):
				par_file.write("{pntr},{result}\n".format(pntr=pntr,result=int(commands.getstatusoutput("./lab2-seq {n} {m}".format(n=pntr, m=i))[1].split("\n")[-1])))

				par_file.flush()
	sys.exit(0)

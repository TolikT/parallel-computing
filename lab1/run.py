import commands
import sys

n1 = int(commands.getstatusoutput("python script.py --time=100 --program=lab1-par-10")[1])
print "n1={}".format(n1)
n2 = int(commands.getstatusoutput("python script.py --time=10000 --program=lab1-par-10")[1])
print "n2={}".format(n2)

delta = int((n2 - n1) / 10)

with open('sec.txt', 'a') as seq_file:
	pntr = n1
	while pntr < n2:
		seq_file.write("{pntr},{result}\n".format(pntr=pntr,result=int(commands.getstatusoutput("python script.py --time={} --program=lab1-seq".format(pntr))[1])))
		pntr += delta


sys.exit(0)



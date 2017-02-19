import commands
import sys

n1 = int(commands.getstatusoutput("python find_size_by_time.py --time=100 --program=lab1-seq")[1])
print "n1={}".format(n1)
n2 = int(commands.getstatusoutput("python find_size_by_time.py --time=10000 --program=lab1-seq")[1])
print "n2={}".format(n2)

delta = int((n2 - n1) / 10)

with open('seq.csv', 'a') as seq_file:
	for pontr in range(n1, n2+1, delta):
		seq_file.write("{pntr},{result}\n".format(pntr=pntr,result=int(commands.getstatusoutput("./lab1-seq {size}".format(pntr))[1])))


sys.exit(0)



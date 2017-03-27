#!/usr/bin/python

import commands
import sys

file_list = []

# Step 1: Build
try:
        
    ret = commands.getstatusoutput("make seq")
    if (ret[0] != 0):
        raise IOError(ret[0], ret[1])
    for line in ret[1].split('\n'):
        file_list.append(line.split(' ')[-1])

except IOError as e:
    print "Error {}: {}".format(e.errno, e.strerror);
    exit(1)

n1 = 20000
n2 = 380000
# Step 2: run tests
delta = int((n2 - n1) / 20)
print delta
print file_list

for bin_file in file_list:
    with open('{}.csv'.format(bin_file), 'w+') as log_file:
        try:
            for n in range(n1, n2+1, delta):
                ret = commands.getstatusoutput('OMP_NESTED=true ./{} {}'.format(bin_file, n))
                if (ret[0] != 0):
                    raise IOError(ret[0], ret[1])

                log_file.write('{}'.format(n))
                for i in range(0,5):
                    log_file.write(',{}'.format(ret[1].split('\n')[i]))
                log_file.write('\n');
                log_file.flush()
        except IOError as e:
            print "Error {}: {}".format(e.errno, e.strerror);
            exit(1)

exit(0)

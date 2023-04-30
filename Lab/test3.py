import os
import subprocess
correct, hasexp,total = 0,0, 0
testfile='tests'

input_list = subprocess.getoutput('find ../'+testfile+'/*.cmm').split('\n')
for file_name in input_list:
    total += 1
    hasexp+=1
    std_file_name = file_name[0:12]+'.ir'
    std_file = open(std_file_name,'w')
    #print(['./parser',file_name,' > ',std_file_name])
    subprocess.run(['./parser',file_name],stdout=std_file,stderr=std_file)
    
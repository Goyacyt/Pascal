import os
import subprocess
correct, hasexp,total = 0,0, 0
RED="\033[1;31m"
NONE="\033[0m"
LBLUE="\033[1;36m"
PURPLE="\033[1;35m"
YELLOW="\033[1;33m"
GREEN="\033[1;42m"
def get_output(res_list):
    err = set()
    for res in res_list:
        if 'Error' not in res:
            break
        line = res.strip().split(' ')[5].strip(':')
        err.add(int(line))
    return err


def result_same(res_list1, res_list2):
    err1 = get_output(res_list1)
    err2 = get_output(res_list2)
    if len(err1) != len(err2):
        return False
    if len(err1.difference(err2)):
        return False
    return True


# subprocess.call(
#     args=['rm -rf /home/lyt/myfile/Pascal/Lab/normalTests_1/inputs/C-2.cmm'],shell=True)
# subprocess.call(
#     args=['rm -rf /home/lyt/myfile/Pascal/Lab/normalTests_1/expects/C-2.exp'], shell=True)
input_list = subprocess.getoutput('find ~/myfile/Pascal/Lab/Test2/inputs/*.cmm').split('\n')
for file_name in input_list:
    total += 1
    flag = True
    #print(file_name)
    std_file_name = file_name[:34]+'expects/'+file_name[41:-4]+'.exp'
    #print(RED+"std"+NONE,std_file_name)
    print(YELLOW+std_file_name[42:-4]+NONE)
    if os.path.exists(std_file_name):
        hasexp+=1
        std_file = open(std_file_name)
        std_res_list = std_file.readlines()
        res_list = subprocess.getoutput(
            '~/myfile/Pascal/Lab/Code/parser '+file_name).split('\n')
        #print('~/myfile/Pascal/Lab/Code/parser ' + file_name)
        if result_same(std_res_list, res_list) == False:
            print(RED+"!!test error"+NONE)
            print("my output:")
            subprocess.run(['/home/lyt/myfile/Pascal/Lab/Code/parser',file_name])
            std_file = open(std_file_name)
            std_res_list = std_file.readlines()
            print(NONE+"standard output:"+NONE)
            print(std_res_list)
        
        else:
            print(GREEN+"pass!"+NONE)
            print("my output:")
            subprocess.run(['/home/lyt/myfile/Pascal/Lab/Code/parser',file_name])
            std_file = open(std_file_name)
            std_res_list = std_file.readlines()
            print(NONE+"standard output:"+NONE)
            print(std_res_list)
            correct += 1
        #if correct < hasexp:
        #    break
    else:
        print(LBLUE+"not exit expect file:"+NONE,file_name)
    #     print(file_name,"should print err")
    #     subprocess.run(['/home/lyt/myfile/Pascal/Lab/Code/parser',file_name])
    #     print("\n")
    print("\n")

print(correct, hasexp,total)

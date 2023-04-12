import os
import subprocess
correct, hasexp,total = 0,0, 0

NONE="\033[0m"
RED="\033[1;41m"
LBLUE="\033[1;36m"
PURPLE="\033[1;35m"
YELLOW="\033[1;33m"
GREEN="\033[1;42m"
testfile='TestB'

def get_output(res_list):
    err = dict()
    for res in res_list:
        if 'Error' not in res:
            break
        res = res.strip().split(' ')
        if res[5].strip(':') not in err:
            err[res[5].strip(':')] = set()
        err[res[5].strip(':')].add(res[2])
    return err


def result_same(std_res, my_res):
    err_std = get_output(std_res)
    err_my = get_output(my_res)
    std_lines = set(err_std.keys())
    my_lines = set(err_my.keys())
    if len(std_lines.difference(my_lines)) or len(my_lines.difference(std_lines)):
        print("line diff")
        print("standard: ",err_std,", diff in:",std_lines.difference(my_lines))
        print("my: ",err_my,", diff in:",my_lines.difference(std_lines))
        return False
    for line in std_lines:
        if len(err_std[line].difference(err_my[line])):
            print("type diff in "+line)
            print(err_std[line])
            print(err_my[line])
            print(err_std[line].difference(err_my[line]))
            return False

    return True


# subprocess.call(
#     args=['rm -rf /home/lyt/myfile/Pascal/Lab/normalTests_1/inputs/C-2.cmm'],shell=True)
# subprocess.call(
#     args=['rm -rf /home/lyt/myfile/Pascal/Lab/normalTests_1/expects/C-2.exp'], shell=True)
input_list = subprocess.getoutput('find ~/myfile/Pascal/Lab/'+testfile+'/inputs/*.cmm').split('\n')
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
            #print(res_list)
            std_file = open(std_file_name)
            std_res_list = std_file.readlines()
            print(NONE+"standard output:"+NONE)
            print(std_res_list)
        
        else:
            print(GREEN+"pass!"+NONE)
            print("my output:")
            subprocess.run(['/home/lyt/myfile/Pascal/Lab/Code/parser',file_name])
            #print(res_list)
            std_file = open(std_file_name)
            std_res_list = std_file.readlines()
            print(NONE+"standard output:"+NONE)
            print(std_res_list)
            correct += 1
        #if correct < hasexp:
        #    break
    else:
        print(LBLUE+"miss expect file:"+NONE,file_name)
        print("my output:")
        subprocess.run(['/home/lyt/myfile/Pascal/Lab/Code/parser',file_name])
    print("\n")

print(correct, hasexp,total)

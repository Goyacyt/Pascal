import os
import subprocess
correct, hasexp,total = 0,0, 0


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
input_list = subprocess.getoutput('find ./normalTest_1/inputs/*.cmm').split('\n')

for file_name in input_list:
    total += 1
    flag = True

    std_file_name = file_name[:15]+'expects/'+file_name[22:-4]+'.exp'
    #print(std_file_name)
    if os.path.exists(std_file_name):
        hasexp+=1
        std_file = open(std_file_name)
        std_res_list = std_file.readlines()
        res_list = subprocess.getoutput(
            '/home/myfile/Pascal/Lab/Code/parser '+file_name).split('\n')
        #print('/home/myfile/Pascal/Lab/Code/parser ' + file_name)
        if result_same(std_res_list, res_list) == False:
            print("test error")
            subprocess.call(args=['cp', file_name,
                              '/home/myfile/Pascal/Lab/normalTest_1/inputs'])
            subprocess.call(args=['cp', std_file_name,
                              '/home/myfile/Pascal/Lab/normalTest_1/expects'])
            #print(sorted(list(get_output(std_res_list))))
            #print(sorted(list(get_output(res_list))))
        else:
         correct += 1
        #if correct < hasexp:
        #    break
    else:
        print(file_name,"should print err")
        subprocess.run(['./Code/parser',file_name])
        print("\n")

print(correct, hasexp,total)

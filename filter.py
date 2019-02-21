import os  
  
FILE_NAME = 'agorasdk.log'  

TAG1 = 'testpacketrate'
TAG2= 'testframerate'
TAG3= 'testjitter'
TAG4= 'testrtt'

size = os.path.getsize(FILE_NAME) / 1024 / 1024   
if  10   < size :  
    print("File too large , it will be take more time for to done.  \n")      
def fetch1():  
    fp = open(FILE_NAME)  
    fp_res = open("packetlost.txt","w")  
    str1 = 'zxh'  
    str2 = '}' 
    for line in fp:  
        #¹ýÂË   
        if line.find(TAG1) ==-1:  
            continue  
        if len(line) < 20:  
            continue  
          
        #Æ¥Åä  
        i1 = line.index(str1) +3  
        i2 = line.index(str2) +0  
        info = line[i1:i2]  
        fp_res.write(str(info)+"\n")
        print(info)
     
    fp.close()  
    fp_res.close()  
def fetch2():  
    fp = open(FILE_NAME)  
    fp_res = open("framelost.txt","w")  
    str1 = 'zxh'  
    str2 = '}' 
    for line in fp:  
        #¹ýÂË   
        if line.find(TAG2) ==-1:  
            continue  
        if len(line) < 20:  
            continue  
          
        #Æ¥Åä  
        i1 = line.index(str1) +3  
        i2 = line.index(str2) +0  
        info = line[i1:i2]  
        fp_res.write(str(info)+"\n")
        print(info)
     
    fp.close()  
    fp_res.close()

def fetch3():  
    fp = open(FILE_NAME)  
    fp_res = open("jitter.txt","w")  
    str1 = 'zxh'  
    str2 = '}' 
    for line in fp:  
        #¹ýÂË   
        if line.find(TAG3) ==-1:  
            continue  
        if len(line) < 20:  
            continue  
          
        #Æ¥Åä  
        i1 = line.index(str1) +3  
        i2 = line.index(str2) +0  
        info = line[i1:i2]  
        fp_res.write(str(info)+"\n")
        print(info)
     
    fp.close()  
    fp_res.close()

def fetch4():  
    fp = open(FILE_NAME)  
    fp_res = open("rtt.txt","w")  
    str1 = 'zxh'  
    str2 = '}' 
    for line in fp:  
        #¹ýÂË   
        if line.find(TAG4) ==-1:  
            continue  
        if len(line) < 20:  
            continue  
          
        #Æ¥Åä  
        i1 = line.index(str1) +3  
        i2 = line.index(str2) +0  
        info = line[i1:i2]  
        fp_res.write(str(info)+"\n")
        print(info)
     
    fp.close()  
    fp_res.close()
  
fetch1()  
fetch2()
fetch3()
fetch4() 

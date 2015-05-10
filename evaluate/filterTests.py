import os
import re
import subprocess

path = u"/home/boris/Projects/tests/"

def filterDirectory(directory):
    cnt = 0
    for fileName in os.listdir(directory):
        cnt += 1
        filePath = directory + "/" + fileName
        subprocess.call(['./readSIVALab', filePath, 'graph.in', '1'])

        graphFile = open('graph.in', 'r')
        n = graphFile.readline().split(' ')[3]
        graphFile.close()

        print (filePath + " " + n)
        if int(n) > 200:
            os.remove(filePath)
            print ("Removed")

    return cnt


if __name__ == '__main__':
    cnt = 0
    for directory in os.listdir(path):
        cnt += filterDirectory(path + directory)
    print (cnt)


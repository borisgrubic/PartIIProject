import os
import sys
import time
import shutil
import subprocess

output = "benchmarkResults"
path = "/home/boris/Projects/tests/"

def runProgram(program, callProgram, fout, n):
    start = int(round(time.time() * 1000))
    try:
        subp = subprocess.call(callProgram, timeout=240)
    except subprocess.TimeoutExpired:
        pass

    end = int(round(time.time() * 1000))
    sys.stderr.write("{0} finished in {1}ms\n".format(program, end - start))

    fout.write("({0}, {1})\n".format(n, (end - start) / 1000.0))

def runTestsDirectory(program, callProgram, directory, fout):
    fout.write('% {0}\n'.format(program))
    files = os.listdir(directory)
    files.sort()
    for fileName in files:
        filePath = directory + "/" + fileName
        sys.stderr.write("{0}\n".format(filePath))
        # subprocess.call(['./readSIVALab', filePath, 'graph.in', '1'])
        subprocess.call(['./readAdjMat', filePath, 'graph.in', '1'])
        # shutil.copyfile(filePath, 'graph.in')

        graphFile = open('graph.in', 'r')
        n = graphFile.readline().split(' ')[2]
        graphFile.close()

        runProgram(program, callProgram, fout, n)

    fout.write("\n")

if __name__ == '__main__':
    fout = open(output, "w")

    for directory in os.listdir(path):
        sys.stderr.write("Running tests for {0}\n".format(directory))
        fout.write("% {0}\n".format(directory))

        runTestsDirectory('nauty', ['./canonizeNauty', 'graph.in'], path + directory, fout)
        runTestsDirectory('bliss', ['./bliss', '-directed', '-v=0', 'graph.in'], path + directory, fout)
        runTestsDirectory('myProgram', ['./canonize', 'graph.in'], path + directory, fout)

        fout.write("\n")

    sys.stderr.write("Benchmark finished\n")
    fout.close()



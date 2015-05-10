import random
import subprocess
import time
import sys

def generateGraph(n, d, out):
    fileOut = open(out, 'w')
    random.seed(None)

    allEdges = []
    for v in range(n):
        allNodes = []
        for u in range(n):
            if u != v:
                allNodes.append(u)
        for i in range(min(d, n - 1)):
            idx = random.randint(0, len(allNodes) - 1)
            allEdges.append((v,allNodes.pop(idx)))

    m = random.randint(0, len(allEdges))
    edges = []
    for edgeId in range(m):
        idx = random.randint(0, len(allEdges) - 1);
        edges.append(allEdges.pop(idx))
     
    fileOut.write("p edge {} {}\n".format(n, m))
    for (u, v) in edges:
        fileOut.write("e {} {}\n".format(u, v))
    fileOut.close()

    sys.stderr.write("Graph with n = {0}, m = {1}, d = {2} has been created\n".format(n, m, d))

def runCanonization(inputFilename):
    start = int(round(time.time() * 1000))
    try:
        subp = subprocess.call(['../evaluate/canonizeNauty', inputFilename], timeout=120)
    except subprocess.TimeoutExpired:
        pass

    end = int(round(time.time() * 1000))
    sys.stderr.write("Canonization algorithm finished in {0}ms\n".format(end - start))
    return end - start


def evaluate(n, cnt, logFilename):
    sys.stderr.write("Evaluating for n = {0} and cnt = {1}\n".format(n, cnt))
    logFile = open(logFilename, 'a')

    sd = 1
    while sd*sd < n:
        sd += 1

    for d in [3, 5, 7, 9, sd, n]:
        totalTime = 0.0

        for testId in range(cnt):
            fileName = "graph{0}-{1}-{2}.in".format(n,d,testId)
            generateGraph(n, d, fileName)
            runtime = runCanonization(fileName)
            totalTime += runtime

            logFile.write("Runtime for test {0}: n = {1}, d = {2} is {3}ms\n".format(testId + 1, n, d, runtime))

        totalTime /= cnt
        sys.stderr.write("Finished evaluating for n = {0}, d = {1} with average time: {2}ms\n\n\n".format(n, d, totalTime))
        logFile.write("Average time for n = {0}, d = {1} is {2}ms\n\n".format(n, d, totalTime))

    logFile.close()
    

if __name__ == '__main__':
    sys.stderr.write("Evaluation started\n")

    for n in range(5, 61, 5):
        evaluate(n, 10, "outputFile")

    sys.stderr.write("Evaluation ended\n")

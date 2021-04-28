#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np
import glob
import os

logDirPath = os.getcwd() + "/log/"
results = {}

# traverse root directory, and list directories as dirs and files as files
for root, dirs, files in os.walk(logDirPath):
    for f in files:
        print("Processing: " + f)
        results[f] = {"size" : [], "rate" : []}
        filePath = os.path.join(root, f)
        with open(filePath, "r", encoding="utf-8") as search:
            for line in search:
                line = line.rstrip()
                if "size" in line:
                    size = line.split(":")[-1].lstrip()
                    if size.isnumeric():
                        results[f]["size"].append(int(line.split(":")[-1].lstrip()))
                    else:
                        results[f]["size"].append(None)

                if "rate" in line:
                    rate = line.split(":")[-1].lstrip().split("\t")[0]
                    if rate.isnumeric():
                        results[f]["rate"].append(int(line.split(":")[-1].lstrip().split("\t")[0]))
                    else:
                        results[f]["rate"].append(None)


print(results)

iterationNumber = 1

def extractStatistics(iterationNumber, rateResults):
    end = int(len(rateResults)/iterationNumber)
    print(end)
    avg = np.empty(end)
    minimum = np.empty(end)
    maximum = np.empty(end)
    for index in range(end):
        tempNpArray = np.asarray(rateResults)
        temp = tempNpArray[index*iterationNumber:index*iterationNumber + iterationNumber]
        avg[index] = np.mean(temp)
        minimum[index] = np.min(temp)
        maximum[index] = np.max(temp)

    print(avg)
    print(minimum)
    print(maximum)

    return avg, minimum, maximum

# shm
shmYAvg, shmYMin, shmYMax = extractStatistics(iterationNumber, results["shm"]["rate"])
shmX = np.asarray(results["shm"]["size"], dtype=np.int64)
shmX = np.unique(shmX)
plt.plot(shmX, shmYAvg, linestyle='-', marker='o', color="red", label="shm")
plt.scatter(shmX, shmYMin, marker='x', color="red")
plt.scatter(shmX, shmYMax, marker='x', color="red")

# mmap
mmapYAvg, mmapYMin, mmapYMax = extractStatistics(iterationNumber, results["mmap"]["rate"])
mmapX = np.asarray(results["mmap"]["size"], dtype=np.int64)
mmapX = np.unique(mmapX)
plt.plot(mmapX, mmapYAvg, linestyle='-', marker='o', color="darkred", label="mmap")
plt.scatter(mmapX, mmapYMin, marker='x', color="darkred")
plt.scatter(mmapX, mmapYMax, marker='x', color="darkred")

# domain
domainYAvg, domainYMin, domainYMax = extractStatistics(iterationNumber, results["domain"]["rate"])
domainX = np.asarray(results["domain"]["size"], dtype=np.int64)
domainX = np.unique(domainX)
plt.plot(domainX, domainYAvg, linestyle='-', marker='o', color="black", label="domain")
plt.scatter(domainX, domainYMin, marker='x', color="black")
plt.scatter(domainX, domainYMax, marker='x', color="black")

# fifo
fifoYAvg, fifoYMin, fifoYMax = extractStatistics(iterationNumber, results["fifo"]["rate"])
fifoX = np.asarray(results["fifo"]["size"], dtype=np.int64)
fifoX = np.unique(fifoX)
plt.plot(fifoX, fifoYAvg, linestyle='-', marker='o', color="yellow", label="fifo")
plt.scatter(fifoX, fifoYMin, marker='x', color="yellow")
plt.scatter(fifoX, fifoYMax, marker='x', color="yellow")

# mq (message size currently limited to 2kB)
# TODO: Investigate whether is possible to remove this limit
#mqYAvg, mqYMin, mqYMax = extractStatistics(iterationNumber, results["mq"]["rate"])
#mqX = np.asarray(results["mq"]["size"], dtype=np.int64)
#mqX = np.unique(mqX)
#plt.plot(mqX, mqYAvg, linestyle='-', marker='o', color="olive", label="mq")
#plt.scatter(mqX, mqYMin, marker='x', color="olive")
#plt.scatter(mqX, mqYMax, marker='x', color="olive")

# tcp
tcpYAvg, tcpYMin, tcpYMax = extractStatistics(iterationNumber, results["tcp"]["rate"])
tcpX = np.asarray(results["tcp"]["size"], dtype=np.int64)
tcpX = np.unique(tcpX)
plt.plot(tcpX, tcpYAvg, linestyle='-', marker='o', color="brown", label="tcp")
plt.scatter(tcpX, tcpYMin, marker='x', color="brown")
plt.scatter(tcpX, tcpYMax, marker='x', color="brown")

# zeromq
zeromqYAvg, zeromqYMin, zeromqYMax = extractStatistics(iterationNumber, results["zeromq"]["rate"])
zeromqX = np.asarray(results["zeromq"]["size"], dtype=np.int64)
zeromqX = np.unique(zeromqX)
plt.plot(zeromqX, zeromqYAvg, linestyle='-', marker='o', color="skyblue", label="zeromq")
plt.scatter(zeromqX, zeromqYMin, marker='x', color="skyblue")
plt.scatter(zeromqX, zeromqYMax, marker='x', color="skyblue")

# nanomsg
nanomsgYAvg, nanomsgYMin, nanomsgYMax = extractStatistics(iterationNumber, results["nanomsg"]["rate"])
nanomsgX = np.asarray(results["nanomsg"]["size"], dtype=np.int64)
nanomsgX = np.unique(nanomsgX)
plt.plot(nanomsgX, nanomsgYAvg, linestyle='-', marker='o', color="magenta", label="nanomsg")
plt.scatter(nanomsgX, nanomsgYMin, marker='x', color="magenta")
plt.scatter(nanomsgX, nanomsgYMax, marker='x', color="magenta")

# nng
nngYAvg, nngYMin, nngYMax = extractStatistics(iterationNumber, results["nng"]["rate"])
nngX = np.asarray(results["nng"]["size"], dtype=np.int64)
nngX = np.unique(nngX)
plt.plot(nngX, nngYAvg, linestyle='-', marker='o', color="orange", label="nng")
plt.scatter(nngX, nngYMin, marker='x', color="orange")
plt.scatter(nngX, nngYMax, marker='x', color="orange")

# dbus
dbusYAvg, dbusYMin, dbusYMax = extractStatistics(iterationNumber, results["dbus"]["rate"])
dbusX = np.asarray(results["dbus"]["size"], dtype=np.int64)
dbusX = np.unique(dbusX)
plt.plot(dbusX, dbusYAvg, linestyle='-', marker='o', color="blue", label="dbus")
plt.scatter(dbusX, dbusYMin, marker='x', color="blue")
plt.scatter(dbusX, dbusYMax, marker='x', color="blue")

# plot configuration
plt.title("Throughput", fontweight='bold')
plt.xscale("symlog")
plt.yscale("symlog")
plt.xlabel('Packet Size (Bytes)')
plt.ylabel('Message rate (messages/s)')
#plt.legend(loc="upper right")
plt.legend(loc="upper left")
plt.grid(True)
plt.savefig("benchmark.png", bbox_inches='tight', dpi=500)

plt.show()

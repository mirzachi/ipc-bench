#!/usr/bin/python3
import subprocess as sp
import psutil
import os
import time

# What to benchmark
technologies = ("shm", "mmap", "domain", "fifo", "tcp", "zeromq", "nanomsg", "nng", "dbus")
# Messages to send in one iteration
count = 1000
# Number of iterations
iterationsPerScenario = 100 
# Message sizes for sending
packetSizes = (1, 10, 100, 1000, 10000)
# Build folder of the benchmark executables
programPath =  "cmake-build-debug/source/"
# Where to output benchmark results
logFilePath = os.getcwd() + "/log"
# Wait between iterations in seconds
# In each iteration *count* messages is transmitted
# The timeout should be larger if *count* is larger
timeout = 1

for tech in technologies:
    print("Benchmarking IPC: " + tech)
    os.makedirs(os.path.dirname(logFilePath + "/" + tech), exist_ok=True)
    logFile = open(logFilePath + "/" + tech, "a+")
    for packetSize in packetSizes:
        print("Packet size: " + str(packetSize))
        logFile.write("**********\n")
        logFile.write("packetSize:" + str(packetSize) + "\n")
        logFile.write("**********\n")
        logFile.flush()
        time.sleep(1)
        for iteration in range(iterationsPerScenario):
            print("Iteration: " + str(iteration))
            logFile.write("----------\n")
            logFile.write("iteration: " + str(iteration) + "\n")
            logFile.write("----------\n")
            logFile.flush()
            time.sleep(1)
            while True:
                args = [programPath + tech + "/" + tech, "-c", str(count), "-s", str(packetSize)]
                process = sp.Popen(args, cwd=".", stdout=logFile, stderr=sp.STDOUT, start_new_session=True)
                try:
                    process.wait(10)
                except sp.TimeoutExpired:
                    args = ["pkill", "-9", "-x", tech]
                    sp.Popen(args, start_new_session=True)
                    args = ["pkill", "-9", "-x", tech + "-server"]
                    sp.Popen(args, start_new_session=True)
                    args = ["pkill", "-9", "-x", tech + "-client"]
                    sp.Popen(args, start_new_session=True)
                    print("Waiting on process took more than 10 seconds. Retrying!!!")
                    time.sleep(timeout)
                    continue
                else:
                    break
            time.sleep(timeout)



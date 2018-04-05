#! /usr/bin/env python
#coding:utf-8
import os, time
print('before the fork, my PID is',os.getpid())
if os.fork():
    print('Hello from the parent. My PID is',os.getpid())
else:
    print('Hello from the child. My PID is',os.getpid())
time.sleep(1)
print('Hello from both of us.')

# os.fork()
# Fork a child process. Return 0 in the child and the child’s process id in the parent. If an error occurs OSError is raised.
# Note that some platforms including FreeBSD <= 6.3 and Cygwin have known issues when using fork() from a thread.
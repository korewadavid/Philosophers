#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/wait.h>
#include <sys/types.h>

// 1. Multiple threads can exist inside a single process, threads also share memory
// Tradeoff: Issues when different threads modify the same variable since they share memory:



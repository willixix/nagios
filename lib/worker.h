#ifndef INCLUDE_worker_h__
#define INCLUDE_worker_h__
#include "iobroker.h"
#include "iocache.h"
#include "kvvec.h"
#include <errno.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
typedef struct iobuf
{
	int fd;
	unsigned int len;
	char *buf;
} iobuf;

#define next_wp next_cp
#define prev_wp prev_cp
typedef struct child_process {
	char *cmd;
	pid_t pid;
	int ret;
	struct timeval start;
	struct timeval stop;
	float runtime;
	struct rusage rusage;
	iobuf outstd;
	iobuf outerr;
	struct child_process *prev_cp, *next_cp;
} child_process;

typedef struct worker_process {
	int sd;
	pid_t pid; /* pid of this worker */
	unsigned int jobs, running;
	struct timeval start;
	struct worker_process *prev_wp, *next_wp;
} worker_process;

extern void enter_worker(int sd);
extern void die(const char *msg);

#endif /* INCLUDE_worker_h__ */

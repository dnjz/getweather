/*
 * trabalho.h
 *
 *  Created on: Apr 6, 2017
 *      Author: dnj
 */

#ifndef TRABALHO2_SO_H
#define TRABALHO2_SO_H
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct {

	pid_t pidChild;
	int pipefd[2];
	

} so_popen_t;

so_popen_t *so_popen(char *cmd[], char *mode);

int  so_pclose(so_popen_t *popen);

int so_pread(so_popen_t *popen, char * buf, ssize_t size);

int so_pwrite(so_popen_t *popen, char *buf, ssize_t size);

#endif

/*
 * trabalho.c
 *
 *  Created on: Apr 4, 2017
 *      Author: dnj
 */

#include "trabalho2_SO.h"

so_popen_t *so_popen(char *cmd[], char *mode){

//modes
	char read_buff[]="r";
	char write_buff[]="w";

	so_popen_t*popen=malloc(sizeof(so_popen_t));
	if (pipe(popen->pipefd) < 0) {
		perror("Error on pipe");
		return NULL;
	}

	pid_t pid=fork();

	if (pid < 0) {
		perror("Error on fork");
		return NULL;
	}

	else if (pid == 0){
		if(strcoll(mode,read_buff)==0){
			dup2(popen->pipefd[1], STDOUT_FILENO);
		}
		if(strcoll(mode,write_buff)==0){
			dup2(popen->pipefd[0], STDIN_FILENO);
		}
		close(popen->pipefd[0]);
		close(popen->pipefd[1]);
		close(popen->pipefd[1]);
		close(popen->pipefd[0]);
		execvp(cmd[0],cmd);
		printf("Error in exec");
	}
	
	else{
		popen->pidChild=getpid();
		if(strcoll(mode,read_buff)==0){
			close(popen->pipefd[1]);
		}
		if(strcoll(mode,write_buff)==0){
			close(popen->pipefd[0]);
		}
	}
	return popen;
}

int so_pclose(so_popen_t *popen){
	if( popen->pipefd[0] >= 0 ){
		close(popen->pipefd[0]);
	}
	if( popen->pipefd[1] >= 0 ){
		close(popen->pipefd[1]);
	}
return 0;
}

int so_pread(so_popen_t *popen, char * buf, ssize_t size){
	int nbytesr=read(popen->pipefd[0], buf, size );
	if(nbytesr < 0){
		perror("Error in read");
		return nbytesr;
	}
	else{
		return nbytesr;
	}
}
int so_pwrite(so_popen_t *popen, char *buf, ssize_t size){
	int nbytesw=write(popen->pipefd[1], buf, size );
	if(nbytesw < 0){
		perror("Error in write");
		return nbytesw;
	}
	else{
		return nbytesw;
	}
}



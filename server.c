#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include "shmdata.h"

int createServer(int port){
	//	int tcp_socket;
	struct sockaddr_in sockaddr;
	int lfd, cfd;
	pid_t pid;
	int n;
	char outbuff[128];
	char buff[128];
	int shm_id;
	//int row, col;
	//char *str, *p;

	//initBoard();
	//socket
	lfd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr.sin_family=AF_INET;
	sockaddr.sin_port=htons(port);
	sockaddr.sin_addr.s_addr=INADDR_ANY;

	//bind int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);

	if(bind(lfd, (const struct sockaddr *)&sockaddr, sizeof(struct sockaddr_in)) == -1){
		perror("Can't bind");
		exit(1);
	}

	//listen
	if(listen(lfd, 2) == -1){
		perror("Can't listen");
		exit(1);
	}

	void *shm = NULL;//分配的共享内存的原始首地址   
        struct shared_use_st *shared;//指向shm   
    	int shmid;//共享内存标识符 //创建共享内存   
    	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);
	shm = shmat(shmid, 0, 0);
	shared = (struct shared_use_st*)shm;   
    	shared->written = 0;

	while(1){

		if((cfd = accept(lfd, NULL, NULL)) == -1){
			perror("Can't accept.");
			exit(1);
		}
		pid = fork();
		if(pid == 0){
			signal(SIGCHLD, SIG_IGN);
			close(lfd);	
			write(cfd, "Please input row and col\r\n", 24);
			while(1){
				//signal(SIGCHLD, SIG_IGN);
				n = read(cfd, buff, sizeof(buff));      
        			strncpy(shared->text, buff, n);      //写完数据，设置written使共享内存段可读       
        			shared->written = 1;  
				//printf("%.*s\r", buff);
				//strcpy(outbuff, buff);
				write(cfd, shared->text, n);
				//printf("%s", outbuff);
				close(cfd);
				shared->written = 0;
				//signal(SIGCHLD, SIG_IGN);
				exit(0);
			}

		}
		else if (pid > 0){
			close(cfd);
		}
	}
}

main(int ac, char *av[]){
	//initBoard();
	//printChessBoard();
	createServer(atoi(av[1]));

}


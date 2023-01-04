#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <sys/types.h>          /* See NOTES */
#include <stdlib.h>
#include <string.h>
#include "chess.h"

int connectServer(char *ipaddr, int port){
	int tcp_socket;
	struct sockaddr_in sockaddr;

	//socket
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port);
	sockaddr.sin_addr.s_addr=inet_addr(ipaddr);

	//connect
	if(connect(tcp_socket, (const struct sockaddr *)&sockaddr, sizeof(struct sockaddr_in)) == -1){
		perror("Can't connect");
		exit(1);
	}

	return tcp_socket;
}

main(int ac, char *av[]){
	int tcp_socket;
	int n;
	char buf[512];
	int row, col;
	char *str, *p;
	int winner;
	int player;
	initBoard();

	tcp_socket = connectServer(av[1], atoi(av[2]));

	printf("Choose player number(1, 2): ");
	scanf("%d", &player);
	printf("You are player %d\r\n", player);
	while(1){
		printChessBoard();
		printf("Please input use , to split row and col:\r\n");
		scanf("%s", buf);
		write(tcp_socket, buf, sizeof(buf));
		n = read(tcp_socket, buf, sizeof(buf));
		str = buf;
		for(int i = 0; i < 2; i++){
			p = strsep(&str, ",");
			if(i == 0){
				row = atoi(p);
			}
			else{
				col = atoi(p);
			}
		}
		takeTurn(row, col);
		printChessBoard();
		if(hasWon(row, col) == 1){
			if(getNextPlayer() == Player1){
				winner = Player2;
			}
			else{
				winner = Player1;
			}
			
			if(winner = player){
				printf("Congratulations, player %d has won!!!\r\n", winner);
			}
			else{
				printf("Sorry, player %d has won!!!\r\n", winner);
			}
			exit(0);
		}
		close(tcp_socket);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
	pid_t serv_pid;
	int pipe_fd[2];
	char serv_ip[21];
	char test[100];
	int port_i;
	in_port_t serv_port;
	int sock;
	ssize_t bytes;
	if (argc == 1) {
		puts("ERROR: Must inlcude option -c for just client or -s for client and server");
	}
	else if (argc == 2) {
		if(strcmp(argv[1], "-c")==0) {
			printf("Please input IPv4 \n");
			scanf("%s", &serv_ip);
			printf("Please input Port \n");
			scanf("%d", &port_i);
			serv_port = port_i;
		}
		else if (strcmp(argv[1], "-s")==0) {
			puts("starting client and server");
			pipe(pipe_fd);
			serv_pid = fork();
			/*CHILD*/
			if (serv_pid == 0) {
				dup2(pipe_fd[1],STDOUT_FILENO);
				close(pipe_fd[0]);
				execl("./server", "server", NULL);
				exit(0);
			}
			/*PARENT*/
			printf("PID OF SERVER: %d \n", serv_pid);
			int temp = dup(0);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[1]);
			fflush(STDIN_FILENO);
			scanf("%s", &serv_ip);
			printf("The ip is  %s \n", serv_ip);
			scanf("%d", &port_i);
			printf("The port is %d \n", port_i);
			serv_port = port_i;
			dup2(temp, 0);
		}
		else puts("invalid option");
	}
	else {
		puts("too many arguments");
	}
	char message[64];
	puts("what is the password?");
	scanf("%s", &message);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0) {
		puts ("socket creation failed");
		exit(0);
	}
	
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	inet_pton(AF_INET, serv_ip, &server_address.sin_addr.s_addr);
	server_address.sin_port = htons(serv_port);
	connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	send(sock, message, sizeof(message), 0);
	char buffer[BUFSIZ];
	while(recv(sock, buffer, BUFSIZ - 1, 0) != 0) {
			puts(buffer);
		}
	puts("all data recieved");
	close(sock);
	
	return 0;
}


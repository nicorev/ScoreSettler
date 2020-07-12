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
	in_port_t port = 13043;
	puts("10.0.0.34");
	puts("13043");

	int server_sock;
	server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);

	bind(server_sock, (struct sockaddr*) &server_addr, sizeof(server_addr));
	listen(server_sock, 5);

	while(1) {
		struct sockaddr_in clnt_addr;
		socklen_t clnt_addr_len = sizeof(clnt_addr);
		int clnt_sock = accept(server_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_len);
		char clnt_name[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, clnt_name, sizeof(clnt_name));
		char buffer[BUFSIZ];
		recv(clnt_sock, buffer, BUFSIZ, 0);
		if(strcmp(buffer, "start") == 0) {
			send(clnt_sock, "Good", sizeof("Good"),0);
		}
		else 
			send(clnt_sock, "Bad", sizeof("Bad"),0);
		close(clnt_sock);
	}
	return 0;
}

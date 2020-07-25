#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <regex.h>



typedef struct Token {
	struct Token *next;
	char *tok;
}Token;

void append(struct Token **head_ptr, struct Token *new) {
	if(*head_ptr == NULL) {
		*head_ptr = new;
		return;
	}
	else if((*head_ptr)->next == NULL) {
		(*head_ptr)->next = new;
		return;
	}
	else {
		append(&((*head_ptr)->next), new);
	}
	return;
}

/*Please make sure this function only takes null terminated strings */
struct Token * tokenize(char  *input) {
	struct Token *token_list = NULL;
	char *token;
	struct Token *new;
	char *start = input;
	char *split_char;
	int tok_size;
	while(strchr(start, ' ') != NULL)  {
		split_char = strchr(start, ' ');
		tok_size = split_char - start;
		token = malloc((tok_size + 1) * sizeof(char));
		strncpy(token, start, tok_size * sizeof(char));
		new = malloc(sizeof(Token));
		new->next = NULL;
		new->tok = token;
		append(&token_list, new);
		start += (tok_size + 1) * sizeof(char);
	}
	token = malloc((strlen(start) + 1 )* sizeof(char));
	strcpy(token, start);
	new = malloc(sizeof(Token));
	new->next = NULL;
	new->tok = token;
	append(&token_list, new);
	return token_list;
}

void print_list (struct Token *token_list) {
	if (token_list != NULL) {
		puts("Trying to print");
		puts(token_list->tok);
		print_list(token_list->next);
	}
	return;
}
int main(int argc, char **argv) {
	in_port_t port = 13043;
	puts("Use localhost 127.0.0.1");
	puts("Port: 13043");
	int bytes_read;
	int server_sock;
	if((server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
                puts("socket creation failed");
                exit(0);
        }

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);

	if(bind(server_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
            puts("bind to socket failed");
            exit(0);
        }
	
        if(listen(server_sock, 5) < 0) {
            puts("bind to socket failed");
            exit(0);
        }

	while(1) {
		struct sockaddr_in clnt_addr;
		socklen_t clnt_addr_len = sizeof(clnt_addr);
		int clnt_sock = accept(server_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_len);
		if(clnt_sock < 0) 
			puts("Error connecting to client");
		char clnt_name[INET_ADDRSTRLEN];
		
                if(inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, clnt_name, sizeof(clnt_name)) != NULL) {
                    puts("Handling Client");
                }
                else {
                    puts("Client connection failed");
                    exit(0);
                }
		char buffer[BUFSIZ + 1];
		bytes_read = recv(clnt_sock, buffer, BUFSIZ, 0);
		
		while(bytes_read > 0) {
			buffer[bytes_read] = '\0';
			print_list(tokenize(buffer));
			send(clnt_sock, "Good", sizeof("Good"),0);
			bytes_read = recv(clnt_sock,buffer, BUFSIZ, 0);
		}
		close(clnt_sock);
	}
	return 0;
}

#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
#include<arpa/inet.h>
#include<cstdlib>
#include<cstdio>
#include<cstring>

using namespace std;

#define SERVER_PORT 20000
#define CLIENT_PORT ((20001+rand())%65536)
#define BUFF_SIZE 255
#define REQUEST_MSG "Hi!"

int main(int argc, char* argv[]){

	if(argc < 2){
		cout<<"Addr:?"<<endl;
		return 1;
	}

	int serfd, clfd;
	struct sockaddr_in seraddr, claddr;
	socklen_t socklen = sizeof(seraddr);
	char buf[BUFF_SIZE];

	if( (clfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
		perror("Fail to create socket");
		return 1;
	}

	srand(time(NULL));

	bzero(&claddr, sizeof(claddr));
	claddr.sin_family = AF_INET;
	claddr.sin_port = htons(CLIENT_PORT);
	claddr.sin_addr.s_addr = htons(INADDR_ANY);

	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	inet_aton(argv[1], &seraddr.sin_addr);
	seraddr.sin_port = htons(SERVER_PORT);
	

	// if( bind(clfd, (struct sockaddr*)&claddr, sizeof(claddr)) < 0 ){
		// perror("Fail to bind");
		// return 1;
	/* } */

	if( connect(clfd, (struct sockaddr*)&seraddr, socklen) < 0 ){
		perror("Fail to connect");
		return 1;
	}

	if( recv(clfd, buf, BUFF_SIZE, 0) < 0 ){
		perror("Fail to recieve");
		return 1;
	}

	cout<<"Recieve from "<<argv[1]<<": "<<buf<<endl;

	close(clfd);

	return 0;
}

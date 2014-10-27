#include<iostream>
#include<string>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

#define SERVER_PORT 20000
#define LENGTH_OF_LISTEN_QUEUE 10
#define BUFF_SIZE 255
#define WELCOME_MSG "Welcome to Simple Server!"

using namespace std;

int main(int argc, char* argv[]){

	int serfd, clfd;
	struct sockaddr_in seraddr, claddr;

	if( (serfd = socket(AF_INET, SOCK_STREAM, 0))<0 ){
		perror("Fail to create socket");
		return 1;
	}

	bzero(&seraddr, sizeof(seraddr));

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SERVER_PORT);
	seraddr.sin_addr.s_addr = htons(INADDR_ANY);

	if( (bind(serfd, (struct sockaddr*)&seraddr, sizeof(seraddr)))<0){
		perror("Fail to bind to PORT");
		return 1;
	}

	if(listen(serfd, LENGTH_OF_LISTEN_QUEUE)<0){
		perror("Fail to listen");
		return 1;
	}

	while(1){
		char buf[BUFF_SIZE];
		long timestamp;
		socklen_t length = sizeof(claddr);
		clfd = accept(serfd, (struct sockaddr*)&claddr, &length);

		if(clfd<0){
			perror("Fail to access");
			break;
		}

		strcpy(buf, WELCOME_MSG);
		cout<<"From client, IP:"<<inet_ntoa(claddr.sin_addr)<<", PORT:"<<ntohs(claddr.sin_port)<<endl;

		timestamp = time(NULL);
		strcat(buf, " time:");
		strcat(buf, ctime(&timestamp));

		send(clfd, buf, BUFF_SIZE, 0);

		close(clfd);
	}

	close(serfd);

	return 0;
}

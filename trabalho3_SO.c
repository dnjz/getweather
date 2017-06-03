	#include "trabalho3_SO.h"

	
	socket_t *socket_init_server(int port){
		struct sockaddr_in serv_addr;
		socket_t *ps=malloc(sizeof(socket_t));
		
		printf("Server ...\n\n");

		if ( (port < 1) || (port > 65536) ) {
			printf("Error on port");
			exit(EXIT_FAILURE);
		}
		printf("Port: %d\n", port);
		ps->sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (ps->sockfd  < 0 )		
			FatalErrorSystem("Error");
		
		memset( (char*)&serv_addr, 0, sizeof(serv_addr) );				
		serv_addr.sin_family = AF_INET;							
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(port);

		if ( bind(ps->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 )	
			FatalErrorSystem("Error on bind");
		return ps;
	}

	


	socket_t *socket_accept(socket_t *passiveSocket){
			socklen_t dim_client;
			struct sockaddr_in client_addr;
			socket_t*s=malloc(sizeof(socket_t));
		    int newsockfd;
		   
		    memcpy(s,passiveSocket,sizeof(socket_t));
		    

		    if (listen( passiveSocket->sockfd, 5) < 0 )
				FatalErrorSystem("Erro no listen");

			dim_client = sizeof(client_addr );
			newsockfd = accept(passiveSocket->sockfd, (struct sockaddr *)(&client_addr), &dim_client);
			if ( newsockfd < 0 )
				FatalErrorSystem("Erro ao efectuar o accept");
		printf("Conection accepted...\n");
		s->sockfd=newsockfd;
		return s;
	}
	

	


	socket_t *socket_init_client(char *host, int port){
		socket_t *ps=malloc(sizeof(socket_t));
		struct hostent *phe;
		in_addr_t serverAddress;
		struct sockaddr_in serv_addr;
		phe = gethostbyname(host);
		
		if (phe != NULL) 
			memcpy(&serverAddress, phe->h_addr, phe->h_length);
		else 
			if ( (serverAddress = inet_addr(host)) == -1)
				FatalErrorSystem("Cannot resolve IP address \"%s\"",host);

			if ( (port < 1) || (port > 65536) ) {
				printf("Port must be between 1..65536\n");
				exit(EXIT_FAILURE);	 
			}
	
			if ( (ps->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
				FatalErrorSystem("Error on descriptor");
	    
	   
			memset((char*)&serv_addr, 0, sizeof(serv_addr));
			serv_addr.sin_family      = AF_INET;
			serv_addr.sin_addr.s_addr = serverAddress;
			serv_addr.sin_port        = htons(port);
			printf("Client will connect in: %s:%d\n", host, port);
			printf("IP: %s\n", inet_ntoa(serv_addr.sin_addr));
	   
			if ( connect(ps->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 )
				FatalErrorSystem("Error on connect");

			printf("Connection estabelished...\n");
			return ps;
		}


		
		int socket_read(socket_t *socket, char *buf, ssize_t size){
	 		int n_bytes=read(socket->sockfd,buf,size);
	 		return n_bytes;
		}
		
		int socket_write(socket_t *socket, char *buf, ssize_t size){
			int n_bytes=write(socket->sockfd,buf,size);
	 		return n_bytes;
		}
			 
	    
	    int socket_close(socket_t *socket){
	    	int ret=close(socket->sockfd);
	    	free(socket);
	    	return ret;
	    }
	 
	



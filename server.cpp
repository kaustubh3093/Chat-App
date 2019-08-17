/*
* Author ksingh42@binghamton.edu
* Clients X and Y will each open a TCP socket to your server and send a message to your server e.g., “Client X: Alice”, “Client Y: Bob”
* Server check which client contacted first and will respond to both the client X: Alice received before Y: Bob”, or “Y: Bob received before X: Alice
* After sending the message to both the client server will get terminated.
*/
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 12345 

int main(int argc, char const *argv[]) 
{ 
    int server_fd1,new_socket,new_socket1, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer1[1024];
    char buffer2[1024];	
    const char *message1 = "X: Alice received before Y: Bob";	
    const char *message2 = "Y: Bob received before X: Alice";	
    const char *cmp = "Client X:Alice";
    const char *cmp1 = "Client Y:Bob";   
   
    server_fd1 = socket(AF_INET, SOCK_STREAM, 0);
   
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
     
    // To forcefully bind the socket with the PORT number
    if (setsockopt(server_fd1, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
   
   
     if( bind(server_fd1, (struct sockaddr *)&address,sizeof(address)) < 0)
	{
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
	}
     
     listen(server_fd1, 100);
 
     //accept client connection
     new_socket = accept(server_fd1, (struct sockaddr *)&address,  
                       (socklen_t*)&address); 
     //printf("accept=%d\n",new_socket);
    
     //To receive message from the client    
     valread  = recv(new_socket, buffer1, sizeof(buffer1), 0);
	buffer1[valread]='\0';
     printf("%s\n",buffer1 );

     //accept client connection			
     new_socket1 = accept(server_fd1, (struct sockaddr *)&address,  
                       (socklen_t*)&address); 

     //To receive message from the client 
     valread  = recv(new_socket1, buffer2, sizeof(buffer2), 0);
	buffer2[valread]='\0';
     printf("%s\n",buffer2 );
   
     //Sending message to the client whether alice comes first or bob
       if(strcmp(buffer1,cmp) == 0 && strcmp(buffer2,cmp1) == 0)   
          {
       
       send( new_socket, message1 , strlen(message1) + 1 , 0 );	
       send( new_socket1, message1 , strlen(message1) + 1 , 0 );
          }
       else
       {
       send( new_socket, message2 , strlen(message2) + 1 , 0 );	
       send( new_socket1, message2 , strlen(message2) + 1 , 0 );
          }
    

       
	
    printf("Sent acknowledgement to both clients\n");
    close(server_fd1);
  
	return 0; 
} 

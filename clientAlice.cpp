/*
* Author ksingh42@binghamton.edu
* Clients Alice will send message to the server i.e "Client X: Alice”
* Server check which client contacted first and will respond to both the client X: Alice received before Y: Bob”, or “Y: Bob received before X: Alice
*/
#include <stdio.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <stdlib.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#define PORT 12345

int main(int argc, char const *argv[]) 
{ 
     
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    const char *message = "Client X:Alice"; 
    char buffer[1024]; 
    sock = socket(AF_INET, SOCK_STREAM, 0); 
 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
      
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    // To check wheather connect is working properly i used printf. The connect function was stable so i commented it out.
    //printf("connect=%d\n",connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) ;
     
    //Sending message to the server
    send(sock, message, strlen(message), 0);
    // To check wheather send is working properly i used printf. The send function was stable so i commented it out.
    //printf("send=%d\n", send(sock, message, strlen(message), 0));
    
    //Receiving response massage from the server
    valread  = recv(sock, buffer, sizeof(buffer), 0);
    //printf("recv=%d\n", valread);
    buffer[valread] = '\0'; 
    printf("Message sent by client Alice: %s\n" , message);
    printf("%s\n",buffer ); 
  
    return 0; 
} 

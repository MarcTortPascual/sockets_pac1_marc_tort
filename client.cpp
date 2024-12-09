#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define SERVER_ADDRESS  "127.0.0.1"     
#define PORT            8080 

/* Test sequences */
char buf_tx[] = "Hola servidor!";      
char buf_rx[100];                    
 
 

int main() 
{ 
    int sockfd; 
    struct sockaddr_in servaddr; 
    
    /* creació del socól */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        printf("CLIENT: Ha fallat la creació del socól..\n"); 
        return -1;  
    } 
    else
    {
        printf("CLIENT: Socól creat .\n"); 
    }
    
    
    memset(&servaddr, 0, sizeof(servaddr));

    /* Assinem la adreça del servidor */
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr( SERVER_ADDRESS ); 
    servaddr.sin_port = htons(PORT); 
  
    /* Intent de conexió al servidor*/
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("conexió amb el servidor fallada...\n");  
        return -1;
    } 
    
    printf("conectat al servidor..\n"); 
  
    /* send test sequences*/
    write(sockfd, buf_tx, sizeof(buf_tx));     
    read(sockfd, buf_rx, sizeof(buf_rx));
    printf("CLIENT:Missatje del servidor: %s \n", buf_rx);
   
       
    /* close the socket */
    close(sockfd); 
} 
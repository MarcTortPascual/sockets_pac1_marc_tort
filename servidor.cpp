#include <unistd.h>  

#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>

#include <errno.h>
#include <stdio.h> 
#include <string.h> 
//definim la adreça del servidor
#define SERV_PORT       8080           
#define SERV_HOST_ADDR "127.0.0.1"
//logitud dels misatges     
#define BUF_SIZE        100
//conexions maximes               
#define BACKLOG         5                

int main(int argc, char* argv[])          
{ 
    //descriptors dels socóls
    int sockfd, connfd ; 
    unsigned int len;
    //estructures per definir les adreces dels socóls     
    struct sockaddr_in servaddr, client; 
     
    int  len_rx, len_tx = 0;    
    //missages                 
    char buff_tx[BUF_SIZE] = "Hola des del servidor!";
    char buff_rx[BUF_SIZE];   
    
     
    //creem el socól del servidor amb els protocols ipv4 i tcp
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        fprintf(stderr, "[servidor-error]:. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[servidor]: Socól creat.\n"); 
    }
    

    memset(&servaddr, 0, sizeof(servaddr));
  

    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR); 
    servaddr.sin_port        = htons(SERV_PORT); 

    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
    { 
        fprintf(stderr, "[servidor-error]: %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[servidor]: Socól ellaçat \n");
    }

    if ((listen(sockfd, BACKLOG)) != 0) 
    { 
        fprintf(stderr, "[servidor-error]:. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[servidor]: Escoltant en el port %d \n\n", ntohs(servaddr.sin_port) ); 
    }
    
    len = sizeof(client); 
  
      /* Acetem la conexió del client  */
      while(1)
      {
        connfd = accept(sockfd, (struct sockaddr *)&client, &len); 
        if (connfd < 0) 
        { 
            fprintf(stderr, "[servidor-error]: %d: %s \n", errno, strerror( errno ));
            return -1;
        } 
        else
        {              
            while(1) /*Iteractuem amb el client fins que es tanqui*/ 
            {  
                /* llegim informació del client */
                len_rx = read(connfd, buff_rx, sizeof(buff_rx));  
                
                if(len_rx == -1)
                {
                    fprintf(stderr, "[servidor-error]:  %d: %s \n", errno, strerror( errno ));
                }
                else if(len_rx == 0) /* si la logitud es 0 significa que no hi ha mes a llegir*/
                {
                    printf("[servidor]: Client tancat \n\n");
                    close(connfd);
                    break; 
                }
                else
                {
                    write(connfd, buff_tx, strlen(buff_tx));
                    printf("[SERVER] missatge del client : %s \n", buff_rx);
                }            
            }  
        }                      
    }    
} 
/*
        UDP_Client. This Program will implement the Client Side for UDP_Socket Programming.
        It will get some data from user and will send to the server and as a reply from the
        server, it will get its data back.
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

int main(void)
{

		int socket_number = 5006;
        int socket_desc;
        struct sockaddr_in server_addr;
        char server_message[2000], client_message[2000];
        
        int server_struct_length = sizeof(server_addr);
        
        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Specifying the IP and Port of the server to connect
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(socket_number);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        //Get Input from the User
        
        printf("Enter Message: ");
        gets(client_message);
        
        //Send the message to Server
        
        if(sendto(socket_desc, client_message, strlen(client_message), 0, (struct sockaddr*)&server_addr, server_struct_length) < 0)
        {
                printf("Send Failed. Error!!!!\n");
                return -1;
        }
        
        //Receive the message back from the server
        
        if(recvfrom(socket_desc, server_message, sizeof(server_message),0, (struct sockaddr*)&server_addr, &server_struct_length) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Server Message: %s\n",server_message);
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Closing the Socket
        
        close(socket_desc);
        
        return 0;
}


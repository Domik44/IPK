// Authors: Dominik Pop
// Login: xpopdo00, <xpopdo00@stud.fit.vutbr.cz>
// VUT FIT, 2 BIT, summer semestr
// Date: 11.2.2021
// First project for IPK -> creating server communicating with HTTP

#include "server.h"

int main(int argc, char **argv){
    
    // Getting port number
    int port = atoi(argv[1]);

    // Getting informations
    double usage = cpu_usage(); // CPU usage

    char hostname[NAME_MAX]; // Hostname
    get_hostname(&hostname);

    char cpu_name[NAME_MAX]; // CPU name
    get_cpu_name(&cpu_name);

    // Creating socket
    int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server_fd == 0){
        perror("Error while creating socket!!! \n");
        exit(1);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    memset(address.sin_zero, '\0', sizeof(address.sin_zero));

    // Binding
    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("Error while binding socket!!\n");
        exit(1);
    }

    // Listening
    if(listen(server_fd, 10) < 0){
        perror("Error while listening!!\n");
        exit(1);
    }

    int new_socket;
    int addrlen = sizeof(address);

    for( ; ; ){
        // Preparing answer for writing out
        char answer[NAME_MAX] = "HTTP/1.1 200 OK\nContent-Type: text/plain\r\n\r\n";

        // Accepting requests
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if(new_socket < 0){
            perror("Error while accepting!! \n");
            exit(1);
        }

        // Reading requests
        char buffer[BUFFER_MAX] = {0};
        read(new_socket, buffer, BUFFER_MAX);

        // Checking requests
        if(strncmp(buffer, "GET /hostname", strlen("GET /hostname")) == 0){
            strcat(answer, hostname);
        }
        else if(strncmp(buffer, "GET /cpu-name", strlen("GET /cpu-name")) == 0){
            strcat(answer, cpu_name);
        }
        else if(strncmp(buffer, "GET /load", strlen("GET /load")) == 0){
            char usage_str[7];
            sprintf(usage_str,"%.2f", usage);
            strcat(answer, usage_str);
            strcat(answer, "%");
        }
        else{
            strcat(answer, "400 bad request!");
        }

        // Writing out
        write(new_socket, answer, strlen(answer));

        // Closing socket
        close(new_socket);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
int opt;

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Receiver is ready to receive messages...\n");

    while (1)
    {
        ssize_t n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, MSG_WAITALL,
                             (struct sockaddr *)&server_addr, &addr_len);
        if (n < 0)
        {
            perror("Receive failed");
            break;
        }
        buffer[n] = '\0';
        printf("Received message: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

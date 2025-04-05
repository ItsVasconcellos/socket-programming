#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define RECEIVER_IP "127.0.0.1"
#define RECEIVER_PORT 8080
#define BUFFER_SIZE 1024
#define FILE_NAME "text.txt"

int main()
{
    int sockfd;
    struct sockaddr_in receiver_addr;
    char buffer[BUFFER_SIZE];
    FILE *file;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(RECEIVER_PORT);
    receiver_addr.sin_addr.s_addr = inet_addr(RECEIVER_IP);

    printf("Sending file content...\n");

    file = fopen(FILE_NAME, "r");
    if (!file)
    {
        perror("Failed to open file");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, BUFFER_SIZE, file))
    {
        if (sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM,
                   (const struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) < 0)
        {
            perror("Send failed");
            fclose(file);
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }
    fclose(file);

    strcpy(buffer, "EOF");
    sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM,
           (const struct sockaddr *)&receiver_addr, sizeof(receiver_addr));

    printf("File sent successfully.\n");

    close(sockfd);
    return 0;
}

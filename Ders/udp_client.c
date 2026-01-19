#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct User
{
    int id;
    char name[100];
    char text[BUFFER_SIZE];
} User;

int main()
{
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;

    // 1. Socket oluşturma
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket oluşturulamadı");
        exit(EXIT_FAILURE);
    }

    // 2. Sunucu adresini ayarla
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost (Kendi bilgisayarım)

    int n;
    socklen_t len;

    // 3. Veri gönderme (sendto)
    // UDP'de connect() yoktur, her pakette adresi belirtiriz.

    User temp_user = {.name = "Wani", .id = 28};

    while (1)
    {
        printf("Enter your message : ");
        fgets(temp_user.text, BUFFER_SIZE, stdin);

        sendto(sockfd, &temp_user, sizeof(temp_user), MSG_CONFIRM,
               (const struct sockaddr *)&server_addr, sizeof(server_addr));

        printf("Mesaj gönderildi.\n");

        if (strncmp(temp_user.text, "exit", 4) == 0)
        {
            printf("Exiting system \n");
            break;
        }

        // 4. Cevap bekleme
        n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL,
                     (struct sockaddr *)&server_addr, &len);

        buffer[n] = '\0';
        printf("Sunucudan gelen cevap: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
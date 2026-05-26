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
    struct sockaddr_in server_addr, client_addr;

    // 1. Socket oluşturma (UDP için SOCK_DGRAM)
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket oluşturulamadı");
        exit(EXIT_FAILURE);
    }

    // 2. Adres yapısını sıfırla ve doldur
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Her yerden gelen veriyi kabul et
    server_addr.sin_port = htons(PORT);

    // 3. Bind (Socketi porta bağla)
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind hatası");
        exit(EXIT_FAILURE);
    }

    printf("UDP Sunucu %d portunda dinliyor...\n", PORT);

    int n;
    socklen_t len = sizeof(client_addr);

    // 4. Veri bekleme (recvfrom)
    // Mesaj gelene kadar kod burada durur (block olur).

    User temp_user;

    while (1)
    {

        n = recvfrom(sockfd, &temp_user, sizeof(temp_user), 0,
                     (struct sockaddr *)&client_addr, &len);

        temp_user.text[n] = '\0';

        printf("--------------------------------\n");
        printf("Gonderen ID   : %d\n", temp_user.id);
        printf("Kullanici Adi : %s\n", temp_user.name);
        printf("Mesaj         : %s", temp_user.text); 
        printf("--------------------------------\n");

        // 5. Cevap gönderme (sendto)
        char *hello = "Merhaba, mesajini aldim!";
        sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM,
               (const struct sockaddr *)&client_addr, len);

        if (strncmp(temp_user.text, "exit", 4) == 0)
        {
            printf("Exiting system \n");
            break;
        }

        printf("Cevap gönderildi.\n");
    }

    close(sockfd);
    return 0;
}
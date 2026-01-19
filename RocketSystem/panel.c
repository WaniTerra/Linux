#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>
#include "buffer.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int sockfd;
struct sockaddr_in server_addr, client_addr;
int n;
socklen_t len = sizeof(client_addr);

void server()
{
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
}

pthread_t thread1;

int main()
{

    server();
    // 4. Veri bekleme (recvfrom)
    // Mesaj gelene kadar kod burada durur (block olur).

    Rocket temp_rocket = {0};
    RingBuffer rb;
    pthread_t thread2;

    while (1)
    {

        n = recvfrom(sockfd, &rb, sizeof(rb), 0,
                     (struct sockaddr *)&client_addr, &len);
       

        pthread_create(&thread2, NULL, read_wrapper, &rb);
        pthread_join(thread2, NULL);

        rb.rocket_arr[rb.tail] = temp_rocket;

        if (temp_rocket.altitude == 0)
        {
            printf("Rocket impact \n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>
#include "buffer.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int sockfd;
struct sockaddr_in server_addr;
int n;
socklen_t len;

void server()
{

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
}

pthread_t thread1;
RingBuffer rb;

int main()
{
    server();
    Rocket temp_rocket = {.altitude = 1000, .speed = 0};
    pthread_mutex_init(&mutex, NULL);

    while (1)
    {
        temp_rocket.timestamp = (uint32_t)time(NULL);
        temp_rocket.altitude = temp_rocket.altitude - 5;
        temp_rocket.speed = temp_rocket.speed + 5;

        if (temp_rocket.speed >= 500)
        {
            temp_rocket.speed = 500;
        }

        Threads args;
        args.roket_ptr = &temp_rocket;
        args.ring_ptr = &rb;

        pthread_create(&thread1, NULL, add_wrapper, (void *)&args);
        pthread_join(thread1, NULL);
        // 3. Veri gönderme (sendto)
        // UDP'de connect() yoktur, her pakette adresi belirtiriz.
        sendto(sockfd, &rb, sizeof(rb), MSG_CONFIRM,
               (const struct sockaddr *)&server_addr, sizeof(server_addr));

        if (temp_rocket.altitude == 0)
        {
            printf("Rocket crashed \n");
            break;
        }
        usleep(50000);
    }

    close(sockfd);
    return 0;
}
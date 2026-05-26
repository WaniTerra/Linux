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

// Mutex'i extern olarak buffer.h'dan alıyoruz ama burada tanımlamalıyız
// Veya buffer.c içinde tanımlıysa burada tekrar init etmeliyiz.
// En garantisi main içinde init etmektir.

void server()
{
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket oluşturulamadı");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind hatası");
        exit(EXIT_FAILURE);
    }
    printf("UDP Sunucu %d portunda dinliyor...\n", PORT);
}

int main()
{
    server();
    
    // MUTEX BAŞLATMA EKLENDİ
    pthread_mutex_init(&mutex, NULL);

    RingBuffer rb;
    pthread_t thread2;

    while (1)
    {
        // rb'nin içini temizleyelim ki eski veri kalmasın
        // memset(&rb, 0, sizeof(rb)); // İsteğe bağlı, recvfrom zaten üzerine yazar.

        n = recvfrom(sockfd, &rb, sizeof(rb), 0,
                     (struct sockaddr *)&client_addr, &len);

        // Veriyi okuması için thread'i başlat
        pthread_create(&thread2, NULL, read_wrapper, &rb);
        pthread_join(thread2, NULL);
    
        int last_read_index = (rb.tail - 1 + 5) % 5;
        
        if (rb.rocket_arr[last_read_index].altitude <= 0 && rb.rocket_arr[last_read_index].speed > 0)
        {
            printf("Rocket impact detected!\n");
            break;
        }
    }

    close(sockfd);
    pthread_mutex_destroy(&mutex); // Temizlik
    return 0;
}
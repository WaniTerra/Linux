# --- Değişkenler (Ayarlar) ---
CC = gcc
CFLAGS = -Wall -Wextra -g

# --- Hedefler (Targets) ---

# 'make' yazınca varsayılan olarak çalışacak hedef
all: server client

# Server'ı derle
server: udp_server.c
	$(CC) $(CFLAGS) udp_server.c -o server

# Client'ı derle
client: udp_client.c
	$(CC) $(CFLAGS) udp_client.c -o client

# Temizlik yap (Derlenmiş dosyaları sil)
clean:
	rm -f server client
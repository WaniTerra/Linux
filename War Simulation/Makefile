CC = gcc

# Include yollarını buraya ekliyoruz (-I.)
# Derleyiciye hangi klasörlerin içine bakması gerektiğini söylüyoruz
CFLAGS = -I. -I./Screens -I./Experiments -Wall

# Kütüphane bayrakları
LDFLAGS = -lSDL2 -lSDL2_ttf -lm

# Çıktı dosyasının adı
TARGET = sim

# Derlenecek dosyalar
SRCS = main.c main_menu.c object.c ./Experiments/experiments.c ./Screens/screen_free_fall.c

# Nesne dosyaları (.c dosyalarından .o dosyaları oluşturulacak)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Her bir .c dosyasını .o dosyasına dönüştüren kural
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean run
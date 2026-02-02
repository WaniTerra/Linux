CC = gcc
# Kütüphane bayrakları (Linker flags) genellikle LDFLAGS veya LIBS olarak tanımlanır
LDFLAGS = -lSDL2 -lSDL2_ttf

# Çıktı dosyasının adı
TARGET = sim

# Derlenecek dosyalar
SRCS = main.c main_menu.c object.c

all: $(TARGET) run

run: all
	./$(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
CC = gcc
CFLAGS = -Wall -lm
TARGET = controle-de-impedancia
SRC = controle-de-impedancia.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
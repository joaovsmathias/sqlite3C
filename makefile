CC=gcc
CFLAGS=-g
LIBS=-lsqlite3
TARGET=datalogger-offline
SOURCE=main.c


all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

clean:
	rm -f $(TARGET)


CC = gcc
CFLAGS = -Wall -Wextra -std=c17
TARGET = exe
OBJS = main.o simulation.o mt19937ar-cok/mt19937ar-cok.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm -lgmp -lmpfr

main.o: main.c simulation.h
	$(CC) $(CFLAGS) -c main.c

simulation.o: simulation.c simulation.h
	$(CC) $(CFLAGS) -c simulation.c

mt19937ar-cok/mt19937ar-cok.o: mt19937ar-cok/mt19937ar-cok.c
	$(CC) $(CFLAGS) -c mt19937ar-cok/mt19937ar-cok.c -o mt19937ar-cok/mt19937ar-cok.o

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

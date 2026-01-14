CC = gcc
CFLAGS = -Wall -Wextra -std=c17
TARGET = exe
EXPERIMENTS = experiments
OBJS = main.o simulation.o config.o population.o aging.o reproduction.o mt19937ar-cok/mt19937ar-cok.o
EXP_OBJS = experiments.o simulation.o config.o population.o aging.o reproduction.o mt19937ar-cok/mt19937ar-cok.o

all: $(TARGET) $(EXPERIMENTS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm -lgmp -lmpfr

$(EXPERIMENTS): $(EXP_OBJS)
	$(CC) $(CFLAGS) -o $(EXPERIMENTS) $(EXP_OBJS) -lm -lgmp -lmpfr

main.o: main.c simulation.h
	$(CC) $(CFLAGS) -c main.c

experiments.o: experiments.c simulation.h population.h reproduction.h aging.h config.h
	$(CC) $(CFLAGS) -c experiments.c

simulation.o: simulation.c simulation.h population.h reproduction.h aging.h
	$(CC) $(CFLAGS) -c simulation.c

config.o: config.c config.h simulation.h
	$(CC) $(CFLAGS) -c config.c

population.o: population.c population.h simulation.h reproduction.h
	$(CC) $(CFLAGS) -c population.c

aging.o: aging.c aging.h simulation.h config.h reproduction.h
	$(CC) $(CFLAGS) -c aging.c

reproduction.o: reproduction.c reproduction.h simulation.h
	$(CC) $(CFLAGS) -c reproduction.c

mt19937ar-cok/mt19937ar-cok.o: mt19937ar-cok/mt19937ar-cok.c
	$(CC) $(CFLAGS) -c mt19937ar-cok/mt19937ar-cok.c -o mt19937ar-cok/mt19937ar-cok.o

clean:
	rm -f $(OBJS) $(EXP_OBJS) $(TARGET) $(EXPERIMENTS)

.PHONY: all clean

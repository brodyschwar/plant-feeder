CC = g++

CFLAGS = -Wall -pthread

LDFLAGS = -lpigpio -lrt

all: main.o stepperMotor.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o main main.o stepperMotor.o

main.o: main.cpp stepperMotor.o
	$(CC) $(CFLAGS) $(LDFLAGS) -c main.cpp stepperMotor.cpp

stepperMotor.o: stepperMotor.cpp stepperMotor.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c stepperMotor.cpp

.PHONY: clean

clean:
	rm -rvf *.o *.gch

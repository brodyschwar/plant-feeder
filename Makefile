CC = g++

CFLAGS = -Wall -pthread

LDFLAGS = -lpigpio -lrt

all: main.o stepperMotor.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o main main.o stepperMotor.o

main.o: main.cpp stepperMotor.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c main.cpp stepperMotor.h

stepperMotor.o: stepperMotor.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c stepperMotor.h

.PHONY: clean

clean:
	rm -rvf *.o *.gch

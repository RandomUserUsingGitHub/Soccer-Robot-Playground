CC = g++
CFLAGS  = -g -Wall
RM = rm

OPENCV = `pkg-config --cflags --libs opencv4`

lIBS = $(OPENCV)

all: main run

main: main.o Field.o World.o Robot.o HelpWindow.o model.o
	$(CC) $(CFLAGS) -o main main.o Field.o World.o Robot.o HelpWindow.o model.o $(lIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< $(lIBS)

run:
	./main
clean:
	rm *.o main
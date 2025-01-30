CC=g++

CFLAGS=-Ofast -march=native -mtune=native -std=c++11

LDFLAGS=

EXEC=main

SRC=./src/Media.cpp \
	./src/PaperMedia.cpp \
	./src/Book.cpp \
	./src/Magazine.cpp \
    ./src/CD.cpp \
	./src/VideoMedia.cpp \
	./src/DVD.cpp \
	./src/main.cpp

OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

main: $(OBJ)
	$(CC) $(CFLAGS) -o ./bin/$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	find ./bin -name main -exec rm {} \;
	find ./src -name *.o  -exec rm {} \;

mrproper: clean
	rm $(EXEC)

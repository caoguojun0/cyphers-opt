CC = gcc
CFLAGS = -lgmp
TARGET = cypher_main
SRCDIR = src/cyphers
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

UTILDIR = src/utils
UTILSOURCES = $(wildcard $(UTILDIR)/*.c)
UTILOBJECTS = $(UTILSOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(UTILOBJECTS) cypher_main.c
	$(CC) $^ -o $@ $(CFLAGS)
	sudo cp $(TARGET) /usr/local/bin

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) $(UTILOBJECTS)

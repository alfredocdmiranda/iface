CC=gcc
CFLAGS=-c -Wall
SRC_DIR=src
BUILD_DIR=build

all:	mkdir iface.o libiface.a

iface.o:	$(SRC_DIR)/iface.c
		$(CC) $(CFLAGS) $(SRC_DIR)/iface.c -o $(BUILD_DIR)/iface.o

libiface.a:	$(BUILD_DIR)/iface.o
		ar -crv $(BUILD_DIR)/libiface.a $(BUILD_DIR)/iface.o

mkdir:
		mkdir -p ./build

install:
		cp $(BUILD_DIR)/libiface.a /usr/lib/
		cp $(SRC_DIR)/iface.h /usr/include

clean:
	rm $(BUILD_DIR)/*.o

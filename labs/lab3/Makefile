#
# CIS330: Lab 3
#
# Makefile to build libraries and test applications.
#

CC=gcc
AR=ar

CFLAGS=-g -O2 -I./include -L./lib -fPIC
LIBS=-llab3 -lm

all: lab3_dyn

obj:
	mkdir -p obj

lib:
	mkdir -p lib

obj/stats.o: src/stats.c include/stats.h obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj/ohno.o: src/ohno.c include/ohno.h obj
	$(CC) $(CFLAGS) -c -o $@ $<

lib/liblab3.so: obj/stats.o obj/ohno.o lib
	$(CC) -shared -o lib/liblab3.so obj/stats.o obj/ohno.o
	export LD_LIBRARY_PATH==./lib:$LD_LIBRARY_PATH

lab3_dyn: src/lab3.c lib/liblab3.so
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

#lab3_dyn: src/lab3.c lib/liblab.so
#	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
clean:
	rm lab3_dyn lib/liblab3.so obj/ohno.o obj/stats.o
	rmdir obj
	rmdir lib

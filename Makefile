
C=g++
GTKFLAGS=`pkg-config gtkmm-3.0 --cflags --libs`
OFILES=`find -name '*.o'`

make:
	$(C) -o main main.cc -I $(GTKFLAGS) 

clean:
	rm -v main $(OFILES)

run:
	make
	./main

all:
	make run
	make clean

test:
	$(C) -o test test.cc

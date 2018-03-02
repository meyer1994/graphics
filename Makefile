
C=g++
GTKFLAGS=`pkg-config gtkmm-3.0 --cflags --libs`
CCFILES=`find -name '*.cc'`
OFILES=`find -name '*.o'`

make:
	$(C) -o main $(CCFILES) -I $(GTKFLAGS) 

clean:
	rm -v main $(OFILES)

run:
	make
	./main

all:
	make
	make run
	make clean

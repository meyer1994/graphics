
C=g++
GTKFLAGS=`pkg-config gtkmm-3.0 --cflags --libs`
OFILES=`find -name '*.o'`

make:
	$(C) -o main main.cc -I $(GTKFLAGS) 

clean:
	rm -v main $(OFILES)

debug:
	$(C) -o main main.cc -I $(GTKFLAGS) -g
	gdb ./main

run:
	make
	./main

all:
	make clean
	make run 
	make clean

test:
	cd tests/ && \
	$(C) -o test test.cc -I ../src/mode && \
	./test && \
	rm test

test_debug:
	cd tests/ && \
	$(C) -o test test.cc -I ../src/mode -g && \
	gdb ./test && \
	rm test

test_valgrind:
	cd tests/ && \
	$(C) -o test test.cc -I ../src/mode && \
	valgrind --leak-check=full ./test && \
	rm test

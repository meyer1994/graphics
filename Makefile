
C=g++
GTKFLAGS=`pkg-config gtkmm-3.0 --cflags --libs`
OFILES=`find -name '*.o'`
VALGRIND=valgrind --leak-check=full

make:
	$(C) -o main main.cc -I $(GTKFLAGS) 

run:
	make
	./main

clean:
	rm -v main $(OFILES)

debug:
	$(C) -o main main.cc -I $(GTKFLAGS) -g
	gdb ./main

valgrind:
	make
	$(VALGRIND) ./main

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
	$(VALGRIND) ./test && \
	rm test

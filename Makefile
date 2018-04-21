
GTKFLAGS=`pkg-config gtkmm-3.0 --cflags --libs`


make:
	g++ -o main main.cc -I $(GTKFLAGS) --std=c++11

run:
	make
	./main

clean:
	rm -v main `find -name '*.o'`

debug:
	g++ -o main main.cc -I $(GTKFLAGS) -g --std=c++11
	gdb ./main

valgrind:
	make
	valgrind --leak-check=full ./main

test:
	cd tests/ && \
	g++ -o test test.cc -I ../src/mode/shapes $(GTKFLAGS) && \
	./test && \
	rm test

test_debug:
	cd tests/ && \
	g++ -o test test.cc -I ../src/mode/shapes $(GTKFLAGS) -g && \
	gdb ./test && \
	rm test

test_valgrind:
	cd tests/ && \
	g++ -o test test.cc -I ../src/mode/shapes $(GTKFLAGS) && \
	valgrind --leak-check=full ./test && \
	rm test

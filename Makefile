
C=g++
CFLAGS=`pkg-config gtkmm-3.0 --cflags --libs`

make:
	$(C) -o t main.cpp $(CFLAGS)

clean:
	rm -fv t

run:
	./t

all:
	make
	make run
	make clean

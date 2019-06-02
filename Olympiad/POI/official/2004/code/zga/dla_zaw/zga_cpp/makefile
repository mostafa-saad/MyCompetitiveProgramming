CC_OPT = -Wall

all: kasyno

kasyno: zga.h kasyno.cpp zga.cpp
	g++ $(CC_OPT) zga.cpp kasyno.cpp -o kasyno

clean:
	rm -f *.o kasyno

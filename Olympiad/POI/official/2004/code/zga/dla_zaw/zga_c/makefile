CC_OPT = -Wall

all: kasyno

kasyno: zga.h kasyno.c zga.c
	gcc $(CC_OPT) zga.c kasyno.c -o kasyno

clean:
	rm -f *.o kasyno

PPC_OPT = -Ci -Cr -Co -gl

all: kasyno

kasyno: zga.pas kasyno.pas
	ppc386 $(PPC_OPT) kasyno.pas

clean:
	rm -f kasyno *.o *.ppu

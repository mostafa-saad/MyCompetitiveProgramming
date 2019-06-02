Informacje o testowaniu
zadania Krysztal
=======================

Pliki z testami
===============

W plikach kry0.in - kry4.in znajduja sie przykladowe dane.
Kazdy z tych testow zawiera opis calej planszy.

Format pliku *.in jest nastepujacy:

n
[1;1] [2;1] ... [n;1]
[1;2] [2;2] ... [n;2]
...
[1;n] [2;n] ... [n;n]

gdzie [x;y] oznacza stan kryszta³u o wspó³rzêdnych (x,y)

Sprawdzanie
===========

Twoj program sterujacy apartur± ma zostaæ skompilowany z modu³em
aparatury (krysztal.pas w Pascalu, krysztal.h w C/C++). 

Dla wlasnorecznego testowania swojego rozwiazania 
udostêpniamy uproszczony modu³ aparatury 
(krysztal.pas w Pascalu, krysztal.c w C/C++).

Aby testowac swoje rozwiazanie, nalezy skompilowac je z modu³em aparatury
i uruchomiæ, podaj±c na standardowym wejsciu opis planszy, w formacie opisanym wyzej.
(Pamietaj, ze w C/C++ musisz skompilowac program skladajacy sie z dwoch
plikow zrodlowych: pliku Twojego programu i pliku krysztal.c).

Mozna tego dokonac uzywajac przekierowania '<', oto przyklad:

Linux:
./kry < kry1.in

Dos/Windows:
kry.exe < kry1.in


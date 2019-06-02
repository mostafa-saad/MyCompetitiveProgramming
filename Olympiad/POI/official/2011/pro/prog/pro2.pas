(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Konkurs programistyczny                          *
 *   Autor:             Pawel Parys                                      *
 *   Zlozonosc czasowa: O(mk) = O(m^2 * n)                               *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      przez znajdowanie najlepszych sciezek            *
 *                      powiekszajacych; zaczynamy od osob, BFS-em,      *
 *                      konczymy jak znajdziemy wolne zadanie (ale bez   *
 *                      optymalizacji przydzielajacej na poczatek po     *
 *                      jednym zadaniu)                                  *
 *                                                                       *
 *************************************************************************)

type vi = record
	d : array[1..500] of integer;
	size : integer;
	{ tablica ze zmiennym rozmiarem }
end;

procedure PB(var tab : vi; d : integer);
begin
	inc(tab.size);
	tab.d[tab.size] := d;
end;

type queue = record
	tab : array[1..500] of integer;
	head, tail : integer;
	{ implementacja kolejki zakladajaca, 
	  ze w ogole przez kolejke przejdzie najwyzej 100 liczb }
end;

var Q : queue; { numery osob }

function front_pop : integer;
begin
	front_pop := Q.tab[Q.tail];
	inc(Q.tail);
end;

procedure push(d : integer);
begin
	Q.tab[Q.head] := d;
	inc(Q.head);
end;

var
	No, Nz : integer;
	maxZ : LongInt;
	zad2os_u : array[1..500] of integer; { skojarzenie zadañ, 0 = brak }
	os2zad_nu : array[1..500] of vi; { od osób do nieskojarzonych z nim zadañ }
	os_koniec : array[1..500] of boolean; { true = juz nie da sie znalezc 
			sciezki powiekszajacej z tej osoby }
	back_zad, back_os, { poprzednik w bfs, -1 = nieosi±gniêty }
	back_zadnr, { nasz numer w wektorze poprzednika }
	os_ile : array[1..500] of integer; { ile osoba ma zadan (liczone tylko na koniec) }

{ czy¶ci tablice po BFS }
procedure czyscBFS;
var z, o : integer;
begin
	for z := 1 to Nz do
		back_zad[z] := 0;
	for o := 1 to No do
		back_os[o] := 0;
	Q.tail := 1;
	Q.head := 1;
end;

var 
	o, o0, o2, po, z, pz, nr, ile, x, last : integer;
	R, T, K, a, krok, res : LongInt;
	ch, udalosie : boolean;

begin
	readln(No, Nz, R, T, K);
	maxZ := T div R;
	for z := 1 to Nz do
		zad2os_u[z] := 0;
	for a := 1 to K do
	begin
		readln(o, z);
		PB(os2zad_nu[o], z);
	end;
	czyscBFS;
	{ przydzielanie }
	for krok := 1 to maxZ do
	begin
		ch := false;
		for o0 := 1 to No do
		begin
			if os_koniec[o0] then
				continue;
			{ BFSem szukaj nieuzytego zadania }
			if back_os[o0]=0 then
			begin
				push(o0);
				back_os[o0] := 1000;
			end;
			udalosie := false;
			while (Q.head<>Q.tail) and not udalosie do
			begin
				o := front_pop;
				for nr := 1 to os2zad_nu[o].size do
				begin
					z := os2zad_nu[o].d[nr];
					if back_zad[z]>0 then
						continue; { juz tam bylismy }
					back_zad[z] := o;
					back_zadnr[z] := nr;
					o2 := zad2os_u[z];
					if o2=0 then { zadanie wolne }
					begin
						udalosie := true;
						break;
					end;
					if back_os[o2]>0 then
						continue; { juz tam bylismy }
					back_os[o2] := z;
					push(o2);
				end;
			end;
			{ nie udalo sie nic znalezc }
			if not udalosie then 
			begin
				os_koniec[o0] := true; { koniec }
				continue;
			end;
			{ udalo sie znalezc sciezke powiekszajaca
			  dodajemy j± do istniej±cego skojarzenia
			  na z jest docelowe zadanie }
			zad2os_u[z] := back_zad[z];
			while back_zad[z]<>o0 do
			begin
				po := back_zad[z];
				pz := back_os[po];
				os2zad_nu[po].d[back_zadnr[z]] := pz;
				z := pz;
				zad2os_u[z] := back_zad[z];
			end;
			last := os2zad_nu[o0].size;
			os2zad_nu[o0].d[back_zadnr[z]] := os2zad_nu[o0].d[last];
			os2zad_nu[o0].size := last-1;
			ch := true;
			czyscBFS;
		end;
		if not ch then
			break;
	end;
	{ wypisywanie wyniku }
	ile := 0;
	res := 0;
	for z := 1 to Nz do
		if zad2os_u[z]>0 then
			inc(os_ile[zad2os_u[z]]);
	for o := 1 to No do
	begin
		x := os_ile[o];
		inc(ile, x);
		inc(res, x*(x+1) div 2);
	end;
	writeln(ile, ' ', res*R);
	for z := 1 to Nz do
		if zad2os_u[z]>0 then
		begin
			o := zad2os_u[z];
			dec(os_ile[o]);
			writeln(o, ' ', z, ' ', os_ile[o]*R);
		end;
end.

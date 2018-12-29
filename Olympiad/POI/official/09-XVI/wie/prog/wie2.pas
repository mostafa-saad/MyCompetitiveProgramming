(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wiedzmak (WIE)                                            *
 *   Plik:     wie2.pas                                                  *
 *   Autor:    Miroslaw Michalski                                        *
 *   Opis:     Rozwiazanie wzorcowe bez kolejki priorytetowej            *
 *             O(4^pn^2+2^m)                                             *
 *                                                                       *
 *************************************************************************)

type pelem=^elem;
elem=record
	 dokad:longint;
	 czas:longint;
	 maska:longint;
	 next:pelem;
	 end;

const INF=1000000000; (* nieskonczonosc *)
const MAXN=521; (* maksymalna liczba miast *)
const MAXS=8221; (* 2^(maksymalna liczba mieczy) *)
const MAX_KOL=100000; (* dlugosc kolejki *)



var
v:array [0..MAXN] of pelem;
tab:array[0..MAXN,0..MAXS] of longint; (* tab[i][j], oznacza, ze da sie dojsc do pozycji i, majac miecze bin(j) *)
maska_kowala:array[0..MAXN] of longint; (* maski bitowe mowiace jakie miecze sa przez kowala wykuwane *)
kolej:array[1..MAX_KOL] of record x,y:longint; end;
wynik,max_maska,monster,i,j,head,tail,po,ko,il,cz,n,m,k,il_mieczy,maska,x,pk,miasto,nowa_maska,nowa_odleg:longint;
p:pelem;



procedure dod_kraw(po,ko,cz,maska:longint);
var p:pelem;
begin
	new(p);
	p^.dokad:=ko;
	p^.czas:=cz;
	p^.maska:=maska;
	p^.next:=v[po];
	v[po]:=p;
	end;


procedure dod_kolej(x,y:longint);
begin
	inc(tail);
	if (tail=MAX_KOL+1) then tail:=1;
	kolej[tail].x:=x; kolej[tail].y:=y;
end;

	
begin
readln(n,m,monster,k);
for i:=0 to MAXN do maska_kowala[i]:=0;
for i:=0 to (k-1) do 
	begin
	read(pk,il_mieczy);
	dec(pk);
	for j:=0 to (il_mieczy-1) do
		begin
		read(x); dec(x);
		maska_kowala[pk]:=(maska_kowala[pk] or (1 shl x));
		end;
	readln;	
	end;
	for i:=0 to (m-1) do
	begin
	read(po,ko,cz,il);
	maska:=0;
		for j:=0 to (il-1) do
			begin
			read(x); dec(x);
			maska:=maska+(1 shl x);
			end;
		readln;
		dec(po); dec(ko);
		
		dod_kraw(po,ko,cz,maska);
		dod_kraw(ko,po,cz,maska);
	end;


	for i:=0 to MAXN do 
		for j:=0 to MAXS do
		tab[i][j]:=INF;
	tab[0][maska_kowala[0]]:=0;
	
	head:=1; tail:=0;	
	dod_kolej(0,maska_kowala[0]);
	while (head<>tail+1) do
		begin
		if (head=MAX_KOL+1) then head:=1;
		miasto:=kolej[head].x; maska:=kolej[head].y;
		inc(head);
		p:=v[miasto];
			while (p<>nil) do
				begin
				if ((p^.maska or maska)=maska) then 
					begin
					j:=p^.dokad;
					nowa_maska:=(maska_kowala[j] or maska);
					nowa_odleg:=tab[miasto][maska]+p^.czas;

					if (nowa_odleg<tab[j][nowa_maska]) then
							begin
							tab[j][nowa_maska]:=nowa_odleg;
							dod_kolej(j,nowa_maska);
							end;
					end;
				p:=p^.next;
				end;
		end;

	wynik:=INF;
	max_maska:=(1 shl monster);
	for i:=0 to (max_maska-1) do
		if (tab[n-1][i]<wynik) then wynik:=tab[n-1][i];
	if (wynik=INF) then wynik:=(-1);
	writeln(wynik);
end.


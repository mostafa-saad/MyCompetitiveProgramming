(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Antysymetria (ANT)                               *
 *   Plik:              ants6.pas                                        *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Rozwiazanie tworzy slownik podslow bazowych.     *
 *   Zlozonosc czasowa: O(n * (log n)^2)                                 *
 *                                                                       *
 *************************************************************************)

const MAXN=500011;

var s,ss:array[0..MAXN] of char; // Slowo oraz jego odwrocenie i zamienienie 0<->1
    tab:array[0..1,0..19,0..MAXN] of longint; // slownik slow bazowych 
    dwa:array[0..30] of longint; // potegi dwojki
    n,curr:longint; // n-dlugosc slowa, curr-obecny poziom konstrukcji slownika
    v:array[0..MAXN*2,1..3] of longint;
    i,il,vsize,pocz,kon,max_radius,sr:longint;
    wynik:int64;

procedure sort(l,r:longint);
 var i,j,x1,x2,x3,a,y:longint;
 begin
 i:=l; j:=r; 
	x1:=v[(l+r) div 2][1];
	x2:=v[(l+r) div 2][2];
	x3:=v[(l+r) div 2][3]; 
 repeat
    while ((v[i][1]<x1) or ((v[i][1]=x1)and (v[i][2]<x2)) or ((v[i][1]=x1) and (v[i][2]=x2) and (v[i][3]<x3))) do inc(i);
    while ((x1<v[j][1]) or ((x1=v[j][1])and (x2<v[j][2])) or ((x1=v[j][1]) and (x2=v[j][2]) and (x3<v[j][3]))) do dec(j);
	if (i<=j) then
	  begin
	  for a:=1 to 3 do 	
		begin
	  	y:=v[i][a]; v[i][a]:=v[j][a]; v[j][a]:=y;
                end;
	  inc(i); dec(j);
	  end;
 until i>j;
 if (l<j) then sort(l,j);
 if (i<r) then sort(i,r);
 end;



procedure zrob_slownik;
begin
curr:=1;
vsize:=0;
// budowa slownika dla slow dlugosci 1
for i:=0 to n-1 do
    begin
    if (s[i]='0') then tab[0][0][i]:=1 else tab[0][0][i]:=2;
    if (ss[i]='0') then tab[1][0][i]:=1 else tab[1][0][i]:=2;
    end;

il:=0;
while (dwa[curr+1]<=n) do
begin
vsize:=0;
    for i:=0 to n-dwa[curr+1] do
	begin
	v[2*i][1]:=tab[0][curr-1][i]; v[2*i][2]:=tab[0][curr-1][i+dwa[curr]]; v[2*i][3]:=2*i;
	v[2*i+1][1]:=tab[1][curr-1][i]; v[2*i+1][2]:=tab[1][curr-1][i+dwa[curr]]; v[2*i+1][3]:=2*i+1;
	vsize:=vsize+2;
	end;
	
sort(0,vsize-1);

 if (vsize>0) then  
 begin 
 il:=1;
 tab[v[0][3] mod 2][curr][v[0][3] div 2]:=1; 
 for i:=1 to vsize-1 do
     if ((v[i][1]=v[i-1][1]) and (v[i][2]=v[i-1][2]) ) then tab[v[i][3] mod 2][curr][v[i][3] div 2]:=il else 
    			begin
			il:=il+1;
			tab[v[i][3] mod 2][curr][v[i][3] div 2]:=il;
			end;
 end;
curr:=curr+1;
end;
end;



function is_equal(p1,k1,p2,k2:longint):boolean;
var yes:boolean;
    i:longint;
    begin
    yes:=true;
    for i:=curr downto 1 do
		if (k1-p1+1>=dwa[i]) then 
			if (tab[0][i-1][p1]<>tab[1][i-1][p2]) then yes:=false else 
				begin
				 p1:=p1+dwa[i]; 
				 p2:=p2+dwa[i]; 
				end;
    is_equal:=yes;
    end;
    

begin // main

readln(n);
for i:=0 to n-1 do 
    begin
    read(s[i]); 
    if (s[i]='0') then ss[n-i-1]:='1' else ss[n-i-1]:='0';
    end;
    readln;

wynik:=0;

dwa[1]:=1; 
for i:=2 to 20 do dwa[i]:=dwa[i-1]*2;

zrob_slownik;

for i:=0 to n-2 do
     if (s[i]<>s[i+1]) then 
        begin
        max_radius:=i+1; if (max_radius>n-1-i) then max_radius:=n-1-i;
        pocz:=i+1;
	kon:=i+max_radius;
	while (pocz<kon) do
	    begin
	    sr:=kon+(pocz-kon+1) div 2; 
	    if (is_equal(2*i-sr+1,i,n-sr-1,n-i-2)) then pocz:=sr else kon:=sr-1;
	    end;
        wynik:=wynik+kon-i;
        end;
writeln(wynik);
end.

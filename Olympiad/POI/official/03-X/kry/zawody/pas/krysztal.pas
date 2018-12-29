unit krysztal; { krysztal.pas }

{* interefejs komunikacji z aparatur± 
 * w zadaniu Kryszta³
 * w jêzyku Pascal
 *
 * obja¶nienia w tre¶ci zadania
 *}

interface

function rozmiar: integer;

function zamroz(x, y : integer) : integer;

procedure niestabilna (x1, y1, x2, y2 : integer);

implementation

{* uproszczony modu³ sterujacy aparatura
 * do testowania rozwiazan przez zawodnikow
 * wczytuje dane o krysztale ze standardowego wejscia
 *}

const MAX_PROG = 1000; { Uwaga: W zadaniu ograniczenie wynosi MAX_N. }
const MAX_N = 10000; 

var 
  kry: array[1..MAX_PROG, 1..MAX_PROG] of integer;
  n : integer;

procedure wczytaj; 
var pom, i, j: integer;
begin
  read(n);
	if (n<3) or (n>MAX_N) then begin
	  writeln('Niepoprawna wartosc n.');
		halt(1);
	end;
	if (n > MAX_PROG) then begin
	  writeln('Poprawna wartosc n, ale za duza dla tego programu.');
		halt(1);
	end;
	for i:=1 to n do 
	  for j:=1 to n do begin
		  read(pom);
			if (pom=0) or (abs(pom)>2) then begin
			  writeln('Wczytano niepoprawna wartosc (', pom, ') stanu atomu (', i, ',', j, ').');
				halt(1);
			end;
			kry[i, j] := pom;
		end;
end;

var ile : integer;

function zamroz(x, y : integer) : integer;
begin
  if (x<1) or (x>n) or (y<1) or (y>n) then begin
	  writeln('Wspolrzedne atomu spoza dopuszczalnego zakresu');
		halt(1);
	end;
  if (x>1) and (x<n) and (y>1) and (y<n) then inc(ile);
  zamroz := kry[x][y];
end;

procedure niestabilna(x1, y1, x2, y2 : integer);
begin
  if (x1<1) or (x1>n) or (y1<1) or (y1>n) or 
	   (x2<1) or (x2>n) or (y2<1) or (y2>n) then begin
	  writeln('Wspolrzedne atomu spoza dopuszczalnego zakresu');
		halt(1);
	end;
	
  writeln('Program dokonal ', ile, ' zamrozen (limit=',3*n,').');
  if (abs(x2-x1) <= 1) and (abs(y2-y1) <= 1) and (kry[x1,y1] = -kry[x2, y2]) then begin
    writeln('Poprawna odpowiedz.');	
		halt(0);
	end else begin
    writeln('Niepoprawna odpowiedz.');	
	  halt(1);
	end;
end;

var initialized : boolean;

function rozmiar: integer; 
begin
  if (not initialized) then begin
    wczytaj;
    initialized := true;
    ile := 0;
  end else begin
    writeln('Funkcja rozmiar moze byc wywolana najwyzej raz'); 
  end;
  rozmiar := n;
end;

begin 
  initialized := false;
end.
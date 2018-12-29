(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspy na trojkatnej sieci (WYS)                           *
 *   Plik:     wys.java                                                  *
 *   Autor:    nieznany                                                  *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
 *                                                                       *
 *************************************************************************)

const
N=13;
type
 Wyraz = string[N];
 WskListy = ^ElementListy;
 ElementListy = record
    Kod : Wyraz;
    Wsk : WskListy;
    end;

function Przew(Obieg:Wyraz):Wyraz;
begin
    Przew := Copy(Obieg, 2, Length(Obieg)-1)+Obieg[1];
end;

function Wspak(Obieg:Wyraz):Wyraz;
begin
    if Length(Obieg)=1 then Wspak:=Obieg
    else Wspak := Wspak(Copy(Obieg, 2, Length(Obieg)-1))+Obieg[1];
end;

function Next(Obieg:Wyraz):Wyraz;
begin
    if Obieg[2] = 'a' then 
	Next := 
	    Pred(Obieg[1]) + Pred(Obieg[3]) + Copy(Obieg, 4, Length(Obieg)-3)
    else
	Next :=
	    Pred(Obieg[1]) + 'e' + Pred(Obieg[2]) + Copy(Obieg, 3, Length(Obieg)-2);
end;

function PoprawnyKod(Obieg:Wyraz) : Wyraz;
  var MinWyraz:  Wyraz;
    i : longint;

begin
    MinWyraz := Obieg;
    for i:=2 to Length(Obieg) do begin
	Obieg := Przew(Obieg);
	if Obieg < MinWyraz then MinWyraz := Obieg;
    end;
    Obieg := Wspak(Obieg);
    for i:=1 to Length(Obieg) do begin
	obieg := Przew(Obieg);
	if Obieg < MinWyraz then MinWyraz := Obieg;
    end;
    PoprawnyKod := MinWyraz;
end;

procedure Dopisz(Element:Wyraz; var Pochodne:WskListy; var Licznik:longint);
var Poprz, Biez, Nowy:WskListy;

begin
    Biez := Pochodne;
    Poprz := nil;
    while(Biez <> nil) and (Element > Biez^.Kod) do begin
	Poprz := Biez; 
	Biez := Biez^.Wsk;
    end;
    if (Poprz = nil) and ((Pochodne = nil) or (Pochodne^.Kod <> Element)) then begin
	new(Poprz);
	Poprz^.Kod := Element;
	Poprz^.Wsk := Pochodne;
	Licznik := Licznik + 1;
	Pochodne := Poprz;
    end 
    else if (Biez = nil) or (Element <> Biez^.Kod) then begin
	New(Nowy);
	Nowy^.Kod := Element;
	Nowy^.Wsk := Biez;
	Poprz^.Wsk := Nowy;
	Licznik := Licznik + 1;
    end;
end;

procedure SpecjalnyPrzypadek(var Pochodne:WskListy; var LWysp:longint);
const A:array[1..5] of Wyraz=('aadecddcddde',
	'aaececdcddde',
	'aaedceccddde',
	'aaeddcebddde',
	'cdddcddd');

var Koniec, Nowy : WskListy;
    i : longint;

begin
    New(Koniec);
    Koniec^.Kod := A[1];
    Koniec^.Wsk := nil;
    Pochodne:= Koniec;
    for i:=2 to 5 do begin
	New(Nowy);
	Nowy^.Kod := A[i];
	Nowy^.Wsk := nil;
	Koniec^.Wsk := Nowy;
	Koniec := Nowy;
    end;
    LWysp := 5;
end;

procedure Generuj(Obieg: Wyraz; var Pochodne:WskListy; var LWysp:longint);
    var i,n : integer;
begin
    if Copy(Obieg, 1, 2)='aa' then
	SpecjalnyPrzypadek(Pochodne, LWysp)
    else begin
	n := Length(Obieg)-1;
	if Obieg[1]='a' then Obieg:=Przew(Obieg);
	New(Pochodne);
	Pochodne^.Kod:=PoprawnyKod(Next(Obieg));
	Pochodne^.Wsk:=nil;
	LWysp := 1;
	Obieg:=Przew(Obieg);
	for i:=1 to n do begin
	    if Obieg[1] <> 'a' then
		Dopisz(PoprawnyKod(Next(Obieg)), Pochodne, LWysp);
	    Obieg:=Przew(Obieg);
	end;
    end;
end;

(* W tym miejscu material, ktory zachowal sie po I OI konczy sie... *)
var
    Wyniki : array [1..10] of WskListy;
    IleWynikow : array [1..10] of longint;
procedure GenerujWszystkie;
var Nowe, Akt : WskListy;
    ile,i : longint;

begin
    IleWynikow[1] := 1;
    New(Wyniki[1]);
    Wyniki[1]^.Wsk := nil;
    Wyniki[1]^.Kod := 'eee';
    for i:=1 to 9 do begin
	Akt := Wyniki[i];
	while Akt<>nil do begin
	    Generuj(Akt^.Kod, Nowe, Ile);
	    while Nowe <> nil do begin (* Nie zwalniam pamieci z listy *)
		Dopisz(Nowe^.Kod, Wyniki[i+1], IleWynikow[i+1]);
		Nowe := Nowe^.Wsk;
	    end;
	    Akt := Akt^.Wsk;
	end;
    end;
end;

var t, i, k, ile : longint;
    typ : string[1];
    Wsk : WskListy;
    Kod : string[N];
sp : char;
begin
    GenerujWszystkie;
    readln(t);
    for i:=1 to t do begin
	read(typ);
	if typ[1] = 'N' then begin
	    readln(K);
	    writeln(IleWynikow[K]);
	    Wsk := Wyniki[K];
	end;
	if typ[1] = 'K' then begin
	    readln(sp, Kod);
	    Wsk := nil;
	    Generuj(Kod, Wsk, Ile);
	    writeln(Ile);
	end;
	while Wsk <> nil do begin
	    write(Wsk^.Kod);
	    Wsk := Wsk^.Wsk;
	    if Wsk <> nil then write(' ');
	end;
	writeln;
    end;
end.

(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      Liczenie liczby inwersji dla wszystkich wezlow   *
 *                      wewnetrznych naraz                               *
 *                      dziala wolno gdy duza wysokosc drzewa            *
 *                                                                       *
 *************************************************************************)

program rot;
uses math;

type node_ptr = ^node;
node = record
	left, right, par : node_ptr;
	sz: longint;
	inv, al : Int64;
end;

var p : array[1..200100] of node_ptr;
var root, tmp : node_ptr;
var MX, i: longint;

// wczytywanie danych
procedure read_input(tr : node_ptr);
var c : longint;
begin
	Read(c); tr^.inv:=0;
	if c<>0 then begin
		tr^.sz:=1;
		p[c]:=tr;
	end
	else begin
		New(tr^.left); New(tr^.right);
		read_input(tr^.left); read_input(tr^.right);
		tr^.sz:=tr^.left^.sz+tr^.right^.sz;
		tr^.al:=tr^.left^.sz; tr^.al:=tr^.al*tr^.right^.sz;
		tr^.left^.par:=tr; tr^.right^.par:=tr;
	end;
end;

// obliczanie wyniku przy znanej liczbie inwersji w kazdym wezle
function compute(tr : node_ptr) : Int64;
begin
	if tr^.al=0 then
		compute:=0
	else
		compute:=compute(tr^.left)+compute(tr^.right)+min(tr^.inv, tr^.al-tr^.inv);
end;

begin
	Read(MX); New(root); read_input(root); 
	for i:=1 to MX do begin
		tmp:=p[i]; Dec(tmp^.sz);
		while tmp^.par<>nil do begin
			if tmp^.par^.right=tmp then
				tmp^.par^.inv:=tmp^.par^.inv+tmp^.par^.left^.sz;
			Dec(tmp^.par^.sz); tmp:=tmp^.par;
		end;
	end;
	WriteLn(compute(root));
end.

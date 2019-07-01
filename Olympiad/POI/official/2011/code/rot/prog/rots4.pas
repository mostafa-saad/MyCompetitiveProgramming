(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wolniejsze, silowe                   *
 *                                                                       *
 *************************************************************************)

program rot;
uses math;

var p, a, b, c : array[0..200100] of longint;
var n, m, i, j, k : longint;
var res, tmp, pro : Int64;

// wczytywanie danych
// kazdy wezel pamietamy jako (a,b,c), to znaczy ze liscie
// w poddrzewie zaczepionym w tym wezle zajmuja przedzial
// [a,c) - lisccie jego lewego poddrzewa przedzial [a,b), 
// a lisccie prawego poddrzewa przedzial [b,c).
// z dokladnoscia do nawiasow ;)
procedure read_input;
var d, r, s : longint;
begin
	Read(d);
	if d <> 0 then begin
		p[n]:=d;
		Inc(n)
	end else begin
		r:=n; read_input;
		s:=n; read_input;
		a[m]:=r; b[m]:=s-1; c[m]:=n-1;
		Inc(m)
	end;
end;

begin
	Read(n);
	n:=0; m:=0; res:=0;
	read_input; Dec(n); Dec(m);
	for i:=0 to m do begin
		tmp:=0;
		for j:=a[i] to b[i] do begin
			for k:=b[i]+1 to c[i] do
				if p[j]>p[k] then
					Inc(tmp);
		end;
		pro:=b[i]-a[i]+1; pro:=pro*(c[i]-b[i]);
		res:=res+min(tmp, pro-tmp);
	end;
	WriteLn(res);
end.

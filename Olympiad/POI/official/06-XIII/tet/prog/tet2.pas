(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TET (Tetris 3D)                                *
 *   Plik:                tet2.pas                                       *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                        Stosuje dwuwymiarowy dag prostokatow bazowych. *
 *                                                                       *
 *************************************************************************)

program tet;

var
  n,dl,sz: longint;
  wynik: longint;
  dag: array[0..2048,0..2048,0..3] of longint;
  bylo: array[0..2048,0..2048] of longint;
  licznik: longint;

function jak_wysoko(a,b,c,d,i,j,p,q,r,s: longint): longint;
var
  w,tmp: longint;
begin
  if bylo[i,j] = licznik then exit(0);
  bylo[i,j] := licznik;
  if (a >= r) or (p >= c) or (b >= s) or (q >= d) then exit(0);
  if (i >= 1024) and (j >= 1024) then exit(dag[i,j,1]);
  if (a <= p) and (b <= q) and (c >= r) and (d >= s) then exit(dag[i,j,1]);
  w := dag[i,j,0];
  if (a <= p) and (c >= r) and (w < dag[i,j,3]) then w := dag[i,j,3];
  if (b <= q) and (d >= s) and (w < dag[i,j,2]) then w := dag[i,j,2];
  if (i < 1024) and (not ((a <= p) and (c >= r))) then
  begin
    tmp := jak_wysoko(a,b,c,d,i shl 1,j,p,q,(p+r) shr 1,s);
    if tmp > w then w := tmp;
    tmp := jak_wysoko(a,b,c,d,(i shl 1)+1,j,(p+r) shr 1,q,r,s);
    if tmp > w then w := tmp
  end;
  if (j < 1024) and (not ((b <= q) and (d >= s))) then
  begin
    tmp := jak_wysoko(a,b,c,d,i,j shl 1,p,q,r,(q+s) shr 1);
    if tmp > w then w := tmp;
    tmp := jak_wysoko(a,b,c,d,i,(j shl 1)+1,p,(q+s) shr 1,r,s);
    if tmp > w then w := tmp
  end;
  exit(w)
end;

procedure wstaw_klocek(a,b,c,d,i,j,p,q,r,s,w: longint);
begin
  if bylo[i,j] = licznik then exit;
  bylo[i,j] := licznik;
  if (a >= r) or (p >= c) or (b >= s) or (q >= d) then exit;
  if dag[i,j,1] < w then dag[i,j,1] := w;
  if (a <= p) and (c >= r) and (dag[i,j,2] < w) then dag[i,j,2] := w;
  if (b <= q) and (d >= s) and (dag[i,j,3] < w) then dag[i,j,3] := w;
  if (a <= p) and (b <= q) and (c >= r) and (d >= s) then
  begin
    if dag[i,j,0] < w then dag[i,j,0] := w;
    exit
  end;
  if (i < 1024) and (not ((a <= p) and (c >= r))) then
  begin
    wstaw_klocek(a,b,c,d,i shl 1,j,p,q,(p+r) shr 1,s,w);
    wstaw_klocek(a,b,c,d,(i shl 1)+1,j,(p+r) shr 1,q,r,s,w);
  end;
  if (j < 1024) and (not ((b <= q) and (d >= s))) then
  begin
    wstaw_klocek(a,b,c,d,i,j shl 1,p,q,r,(q+s) shr 1,w);
    wstaw_klocek(a,b,c,d,i,(j shl 1)+1,p,(q+s) shr 1,r,s,w);
  end
end;

var
  poziom: longint;
  a,b,c,d,w: longint;
  i,j,k: longint;

begin
  licznik := 0;
  for i := 0 to 2048 do for j := 0 to 2048 do for k := 0 to 3 do dag[i,j,k] := 0;
  for i := 0 to 2048 do for j := 0 to 2048 do bylo[i,j] := licznik;
  wynik := 0;
  readln(dl,sz,n);
  while n > 0 do
  begin
    dec(n);
    readln(c,d,w,a,b);
    inc(c,a);
    inc(d,b);
    inc(licznik);
    poziom := jak_wysoko(a,b,c,d,1,1,0,0,1024,1024);
    inc(poziom,w);
    if wynik < poziom then wynik := poziom;
    inc(licznik);
    wstaw_klocek(a,b,c,d,1,1,0,0,1024,1024,poziom);
  end;
  writeln(wynik)
end.

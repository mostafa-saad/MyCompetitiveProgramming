(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Usuwanka                                      *
 *   Autor:                Igor Adamski                                  *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe, wersja ze stosem        *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

var n, k, s, w : longint;
    stos : array[0..MAXN+1] of longint;
    suma : array[0..MAXN+1] of longint; (* suma[i] = stos[1] + stos[2] + ... + stos[i] *)
    wynik : array[0..MAXN] of longint; (* stos na ktorym beda odkladane kolejne ruchy *)

var i, j, val : longint;
    z : char;

begin
  s := 0;
  w := 0;
  suma[0] := 0;
  
  read(n, k);
  read(z);
  for i := 1 to n do
  begin
    read(z);
    if z = 'b' then
      val := 1
    else
      val := -k;
    (* Dodanie wartosci na stos *)
    inc(s);
    stos[s] := i;
    suma[s] := suma[s-1] + val;
    (* Jesli suma k+1 elementow z wierzchu jest rowna 0 to jest to poprawny ruch *)
    if (s >= k+1) and (suma[s] - suma[s-k-1] = 0) then
    begin
      for j := 1 to k+1 do
      begin
        wynik[w] := stos[s];
        inc(w);
        dec(s);
      end;
    end;
  end;
  
  for i := 1 to n div (k+1) do
  begin
    for j := 1 to k+1 do
    begin
      dec(w);
      write(wynik[w], ' ');
    end;
    writeln();
  end;
  
end.

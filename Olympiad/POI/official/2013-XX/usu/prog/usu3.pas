(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Usuwanka                                      *
 *   Autor:                Igor Adamski                                  *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe, wersja z tablica next   *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000010;
type
przedzial = record
  l, r : longint;
end;

var next : array[0..MAXN] of longint;  (* ciag[i] + ciag[i+1] + ... + ciag[next[i]] = 0 *)
    ciag : array[0..MAXN] of longint;
    Q : array[0..MAXN] of przedzial;
    n, k, i, j, t, Qback, Qfront : longint;
    z : char;

procedure obliczNext();
(* pom[i] = ostatni indeks, taki ze suma sufiksu ciagu jest rowna i
   czyli pom[i] = j jesli
   ciag[j] + ciag[j+1] + ... ciag[n] = i *)
var pom : array[0..2*MAXN] of longint;
    i, sum : longint;
begin
  for i:=0 to 2*n-1 do
    pom[i] := n+2;
  pom[n] := n+1;
  sum := 0; (* Suma wartosci sufiksu ciagu *)
  for i:=n downto 1 do
  begin
    sum += ciag[i];
    next[i] := pom[n+sum] - 1;
    pom[n+sum] := i;
  end;
end;

procedure Qpush(l, r : longint);
begin
  Q[Qback].l := l;
  Q[Qback].r := r;
  inc(Qback);
end;

begin
  readln(n, k);
  for i:=1 to n do
  begin
    read(z);
    if z = 'b' then
      ciag[i] := 1
    else
      ciag[i] := -k;
  end;
  obliczNext();
  Qback := 0;
  Qfront := 0;
  (* Zaczynamy z calym przedzialem *)
  Qpush(1, n);
  while Qfront < Qback do
  begin
    i := Q[Qfront].l;
    j := Q[Qfront].r;
    inc(Qfront);
    t := next[i];
    (* Jezeli da sie ten przedzial rozdzielic na dwa niepuste
       przedzialy, ktorym sumy wynosza 0
       to tak robimy *)
    if t < j then
    begin
      Qpush(i, t);
      Qpush(t+1, j);
    end
    else
    begin
      (* W przeciwnym wypadku wykonujemy ruch *)
      write(i);
      inc(i);
      while i <= j do
      begin
        if next[i] <= j then
        begin
          (* Omijamy spojny zerowy podprzedzial i dodajemy go do zbioru *)
          Qpush(i, next[i]);
          i := next[i] + 1;
        end
        else
        begin
          write(' ', i);
          inc(i);
        end;
      end;
      writeln();
    end;
  end;
end.


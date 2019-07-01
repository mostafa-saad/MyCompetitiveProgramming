(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Odleglosc                                        *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Zlozonosc czasowa: O(n*lglg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

const
   MAX_N = 1000000;
   INFTY = 1000000000;

var
   num : LongInt;
   a : array[0 .. MAX_N - 1] of LongInt;
   numer : array[0 .. MAX_N] of LongInt; { ZERUJ}
   drugi_numer : array[0 .. MAX_N] of LongInt; { ZERUJ}
   n : LongInt;
   q : array[0 .. MAX_N] of LongInt;

type
   pkraw = ^kraw;
   kraw = record
      v : LongInt;
      next : pkraw;
   end;

var
   adj : array[0 .. MAX_N] of pkraw;

procedure dodaj_krawedz(const a, b : LongInt);
var
   k : pkraw;
begin
   k := new(pkraw);
   k^.v := b;
   k^.next := adj[a]^.next;
   adj[a]^.next := k;
end;

procedure buduj_graf;
var
   i, j, p : LongInt;
begin
   n := 0;
   for i := 0 to num - 1 do
      if a[i] > n then
         n := a[i];

   for i := 0 to n do
   begin
      adj[i] := new(pkraw);
      adj[i]^.next := nil;
   end;
   for i := 0 to n do
      q[i] := 0;

   i := 2;
   while i * i <= n do
   begin
      if q[i] = 0 then
      begin
         j := i;
         while j <= n do
         begin
            q[j] := i;
            Inc(j, i);
         end;
      end;
      Inc(i);
   end;
   for i := 2 to n do
      if q[i] = 0 then
         q[i] := i;

   for i := 2 to n do
   begin
      j := i;
      repeat
         p := q[j];
         while j mod p = 0 do
            j := j div p;
         dodaj_krawedz(i, i div p);
         dodaj_krawedz(i div p, i);
      until j <= 1;
   end;
   Inc(n);
end;

var
   ds, ms : array[0 .. MAX_N] of LongInt;
   dsv, msv : array[0 .. MAX_N] of LongInt;
   head, tail : LongInt;

procedure pierwsza_faza;
var
   i, v, w : LongInt;
   k : pkraw;
begin
   head := 1;
   tail := 0;
   for i := 0 to n - 1 do
      ds[i] := INFTY;
   for i := 0 to n - 1 do
      if numer[i] <> 0 then
      begin
         ds[i] := 0;
         ms[i] := i;
         Inc(tail);
         q[tail] := i;
      end;
   while head <= tail do
   begin
      v := q[head];
      Inc(head);
      k := adj[v]^.next;
      while k <> nil do
      begin
         w := k^.v;
         if ds[w] = INFTY then
         begin
            ds[w] := ds[v] + 1;
            ms[w] := ms[v];
            Inc(tail);
            q[tail] := w;
         end else if (ds[v] + 1 = ds[w]) and (numer[ms[v]] < numer[ms[w]]) then
            ms[w] := ms[v];
         k := k^.next;
      end;
   end;
end;

procedure druga_faza;
var
   i, v, w, d : LongInt;
   k : pkraw;
begin
   for i := 0 to n - 1 do
      dsv[i] := INFTY;
   for i := 0 to n - 1 do
   begin
      k := adj[i]^.next;
      while k <> nil do
      begin
         v := ms[i];
         w := ms[k^.v];
         if v <> w then
         begin
            d := ds[i] + 1 + ds[k^.v];
            if (d < dsv[v]) or ((d = dsv[v]) and (numer[w] < numer[msv[v]])) then
            begin
               dsv[v] := d;
               msv[v] := w;
            end;
         end;
         k := k^.next;
      end;
   end;
end;

var
   i, wynik : LongInt;

begin
   ReadLn(num);
   for i := 0 to num do
   begin
      numer[i] := 0;
      drugi_numer[i] := 0;
   end;
   for i := 0 to num - 1 do
   begin
      ReadLn(a[i]);
      if numer[a[i]] = 0 then
         numer[a[i]] := i + 1
      else if drugi_numer[a[i]] = 0 then
         drugi_numer[a[i]] := i + 1;
   end;
   buduj_graf;
   pierwsza_faza;
   druga_faza;

   for i := 0 to num - 1 do
   begin
      if drugi_numer[a[i]] <> 0 then
         if numer[a[i]] <> i+1 then
            wynik := numer[a[i]]
         else
            wynik := drugi_numer[a[i]]
      else
         wynik := numer[ msv[ a[i] ] ];
      WriteLn(wynik);
   end;
end.

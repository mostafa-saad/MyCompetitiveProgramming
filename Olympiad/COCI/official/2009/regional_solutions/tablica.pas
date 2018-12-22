program tablica;

const MAXK = 1000;

var 
   N, K, i, pomak_r, pomak_s : longint;
   x : array[1..MAXK] of longint;
   pozicija_r, cilj_r : array[1..MAXK] of longint;
   pozicija_s, cilj_s : array[1..MAXK] of longint;

procedure rotiraj_redak( r, pomak : longint );
var
   i : longint;
begin
   for i := 1 to K do 
      if pozicija_r[i] = r then
         pozicija_s[i] := (pozicija_s[i] + pomak) mod N;
end;

procedure rotiraj_stupac( s, pomak : longint );
var
   i : longint;
begin
   for i := 1 to K do 
      if pozicija_s[i] = s then
         pozicija_r[i] := (pozicija_r[i] + pomak) mod N;
end;

begin
   readln( N, K );
   for i := 1 to K do begin
      readln( x[i], cilj_r[i], cilj_s[i] );
      x[i] := x[i] - 1;
      cilj_r[i] := cilj_r[i] - 1;
      cilj_s[i] := cilj_s[i] - 1;
      pozicija_r[i] := x[i] div N;
      pozicija_s[i] := x[i] mod N;
   end;

   for i := 1 to K do begin   
      pomak_s := cilj_s[i] - pozicija_s[i];
      pomak_r := cilj_r[i] - pozicija_r[i];
      if pomak_s < 0 then pomak_s := pomak_s + N;
      if pomak_r < 0 then pomak_r := pomak_r + N;

      rotiraj_redak( pozicija_r[i], pomak_s );
      rotiraj_stupac( pozicija_s[i], pomak_r );

      writeln( pomak_s + pomak_r );
   end;
end.
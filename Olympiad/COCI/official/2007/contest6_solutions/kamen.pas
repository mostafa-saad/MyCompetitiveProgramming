
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task KAMEN
  Programming language Pascal
*)

program kamen;

type
   putanja = record
      stupac : array[1..30000] of integer;
      r : longint;
   end;

var
   RR, SS, N : longint;
   a : array[1..30000, 1..32] of char;
   P : array[1..30] of putanja;

procedure ubaci( var x : putanja );
begin
   a[x.r-1, x.stupac[x.r-1]] := 'O';
end;

procedure sredi( var x : putanja );
var
   s : longint;
begin
   while true do begin
      s := x.stupac[x.r-1];

      if (x.r > 1) and (a[x.r-1,s] <> '.') then begin dec( x.r ); continue; end;

      if x.r > RR then break;
      if a[x.r,s] = 'X' then break;

      if a[x.r,s] = '.' then begin
         x.stupac[x.r] := s;
         inc( x.r );
      end else begin
         if (s > 1) and (a[x.r,s-1] = '.') and (a[x.r-1,s-1] = '.') then begin
            x.stupac[x.r] := s-1;
            inc( x.r );
         end else if (s < SS) and (a[x.r,s+1] = '.') and (a[x.r-1,s+1] = '.') then begin
            x.stupac[x.r] := s+1;
            inc( x.r );
         end else break;
      end;
   end;
end;

var
   i, j : longint;

begin
   readln( RR, SS );
   for i := 1 to RR do readln( a[i] );

   for i := 1 to SS do begin
      P[i].stupac[1] := i;
      P[i].r := 2;
      sredi( P[i] );
   end;

   readln( N );
   for i := 1 to N do begin
      readln( j );
      ubaci( P[j] );
      for j := 1 to SS do sredi( P[j] );
   end;

   for i := 1 to RR do begin
      for j := 1 to SS do
         write( a[i,j] );
      writeln;
   end;
end.

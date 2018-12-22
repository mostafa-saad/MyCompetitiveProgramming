(*
  Croatian Olympiad in Informatics 2007
  Task SABOR
*)

program sabor;

const
   MAX                          = 1000;
   dx  : array[0..3] of longint = (-1, 0, 1, 0);
   dy  : array[0..3] of longint = (0, 1, 0, -1);

var
   P, K                   : longint;
   d                      : array[-MAX-1..MAX+1, -MAX-1..MAX+1] of longint;
   minx, maxx, miny, maxy : longint;
   x, y, i, dir, nx, ny   : longint;
   res                    : array[0..1] of int64;
   q                      : array[0..(2*MAX+3)*(2*MAX+3), 0..1] of longint;
   qhead, qtail           : longint;

procedure edge(x, y, d : longint);
begin
   res[(x+y+4*MAX)   mod 2] := res[(x+y+4*MAX)   mod 2] + (K-d) div 2;  
   res[(x+y+4*MAX+1) mod 2] := res[(x+y+4*MAX+1) mod 2] + (K-d+1) div 2;
end;

procedure corner(x, y, d : longint);
var n : int64;
begin
   n := (K-d)   div 2; res[(x+y+4*MAX)   mod 2] := res[(x+y+4*MAX)   mod 2] + n*n;
   n := (K-d-1) div 2; res[(x+y+4*MAX+1) mod 2] := res[(x+y+4*MAX+1) mod 2] + n*(n+1);
end;

begin
   readln(P, K);
   K := K+1;
   minx := 0; maxx := 0; miny := 0; maxy := 0;

   for i:=1 to P do begin
      readln(x, y);
      if x < minx then minx := x;
      if x > maxx then maxx := x;
      if y < miny then miny := y;
      if y > maxy then maxy := y;
      d[x, y] := -1;
   end;
   minx := minx-1; maxx := maxx+1;
   miny := miny-1; maxy := maxy+1;

   res[0] := 0; res[1] := 0;

   d[0, 0] := 1;
   q[0, 0] := 0; q[0, 1] := 0;
   qhead := 0; qtail := 1;

   while qhead < qtail do begin
      x := q[qhead, 0];
      y := q[qhead, 1];
      qhead := qhead+1;

      res[(x+y+4*MAX) mod 2] := res[(x+y+4*MAX) mod 2] + 1;

      if d[x, y] = K then
         continue;

      if (x = minx) or (x = maxx) then edge(x, y, d[x, y]);
      if (y = miny) or (y = maxy) then edge(x, y, d[x, y]);

      for dir:=0 to 3 do begin
         nx := x + dx[dir]; ny := y + dy[dir];
         if (nx < minx) or (nx > maxx) or (ny < miny) or (ny > maxy) or (d[nx, ny] <> 0) then continue;

         d[nx, ny] := d[x, y] + 1;
         q[qtail, 0] := nx;
         q[qtail, 1] := ny;
         qtail := qtail+1;
      end;
   end;

   if d[minx, miny] > 0 then corner(minx, miny, d[minx, miny]);
   if d[minx, maxy] > 0 then corner(minx, maxy, d[minx, maxy]);
   if d[maxx, miny] > 0 then corner(maxx, miny, d[maxx, miny]);
   if d[maxx, maxy] > 0 then corner(maxx, maxy, d[maxx, maxy]);

   writeln(res[0], ' ', res[1]);
end.

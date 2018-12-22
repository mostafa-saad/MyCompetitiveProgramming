
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task MARATON
  Programming language Pascal
*)

program maraton;

const
   dr : array[1..8] of longint = (-1, -1, 0, 1, 1, 1, 0, -1);
   dc : array[1..8] of longint = (0, 1, 1, 1, 0, -1, -1, -1);

var
   n, i, j, smjer         : longint;
   r1, c1, r2, c2, r3, c3 : longint;
   a                      : array[1..30, 1..30] of char;

begin
   readln(n);
   for i:=1 to n do begin
      for j:=1 to n do
         read(a[i, j]);
      readln;
   end;

   for r1:=1 to n do
      for c1:=1 to n do
         for smjer:=1 to 8 do begin
            if a[r1, c1] = '.' then continue;

            r2 := r1 + dr[smjer]; c2 := c1 + dc[smjer];
            r3 := r2 + dr[smjer]; c3 := c2 + dc[smjer];
            if (r3 < 1) or (r3 > n) then continue;
            if (c3 < 1) or (c3 > n) then continue;
            if (a[r1, c1] = a[r2, c2]) and (a[r2, c2] = a[r3, c3]) then begin
               writeln(a[r1, c1]);
               exit;
            end;
         end;

   writeln('ongoing');
end.

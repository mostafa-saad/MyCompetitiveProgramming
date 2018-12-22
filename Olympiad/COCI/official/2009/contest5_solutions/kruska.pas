program kruska;

const
   dr : array[0..3] of longint = (0, 1, 0, -1);
   dc : array[0..3] of longint = (1, 0, -1, 0);

var
   N, KVELIKI, M       : longint;
   a                   : array[0..200, 0..200, 0..6] of char;
   bio                 : array[0..200, 0..200, 0..3, 0..6] of int64;
   skret               : array[0..200, 0..200, 0..3, 0..6] of longint;
   i, j, r, c, d, t, k : longint;
   left, ciklus        : longint;
   tmp                 : char;
   ret                 : int64;

begin
   read(N, KVELIKI);
   fillchar(a, sizeof(a), 'S');

   read(M);
   for i:=1 to M do begin
      read(r, c); dec(r); dec(c);
      read(tmp);
      for j:=0 to 6 do read(a[r, c, j]);
   end;

   ret := 0;
   r := 0; c := 0; d := 0; t := 0; k := 0;

   while true do begin
      if a[r, c, t] = 'L' then begin d := (d+3) mod 4; inc(k); end;
      if a[r, c, t] = 'R' then begin d := (d+1) mod 4; inc(k); end;

      if (r+dr[d] < 0) or (r+dr[d] >= N) or
         (c+dc[d] < 0) or (c+dc[d] >= N) then begin
            d := (d+2) mod 4;
            inc(k);
         end;

      if bio[r, c, d, t] > 0 then begin
         ciklus := k - skret[r, c, d, t];
         left := KVELIKI - k;

         ret := ret + (left div ciklus) * (ret - bio[r, c, d, t]);
         k := k + (left div ciklus) * ciklus;
      end;
      bio[r, c, d, t] := ret;
      skret[r, c, d, t] := k;

      if k >= KVELIKI then break;

      r := r+dr[d];
      c := c+dc[d];
      inc(ret);
      inc(t);
      if t = 7 then t := 0;
   end;
   writeln(ret);
end.

   

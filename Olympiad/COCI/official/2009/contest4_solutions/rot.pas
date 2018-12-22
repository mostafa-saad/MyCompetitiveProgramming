program rot;

var
   REDOVA, STUPACA, kut, r, c : longint;
   a, b                       : array[0..100, 0..100] of char;

procedure rot90;
var r, c, tmp : longint;
begin
   tmp := REDOVA; REDOVA := STUPACA; STUPACA := tmp;
   for r:=0 to REDOVA-1 do
      for c:=0 to STUPACA-1 do
         b[r, c] := a[STUPACA-c-1, r];

   for r:=0 to REDOVA-1 do
      for c:=0 to STUPACA-1 do
         a[r, c] := b[r, c];
end;

procedure output1;
begin
   for r:=0 to REDOVA-1 do begin
      for c:=0 to STUPACA-1 do
         write(a[r, c]);
      writeln;
   end;
end;

procedure output2;
var d, leading, i, r, c : longint;
begin
   for d:=0 to REDOVA+STUPACA-2 do begin
      if d < REDOVA then begin
         leading := REDOVA-d-1;
         r := d;
         c := 0;
      end else begin
         leading := d-REDOVA+1;
         r := REDOVA-1;
         c := d-REDOVA+1;
      end;
      for i:=1 to leading do write(' ');

      write(a[r, c]);
      while true do begin
         dec(r); inc(c);
         if (r < 0) or (c >= STUPACA) then break;
         write(' ', a[r, c]);
      end;
      writeln;
   end;
end;

begin
   readln(REDOVA, STUPACA);
   for r:=0 to REDOVA-1 do begin
      for c:=0 to STUPACA-1 do
         read(a[r, c]);
      readln;
   end;
   read(kut);

   while kut >= 90 do begin
      kut := kut-90;
      rot90;
   end;

   if kut = 0 then output1 else output2;
end.

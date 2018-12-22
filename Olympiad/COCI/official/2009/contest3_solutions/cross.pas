program cross;

var
   i, j          : integer;
   z             : char;
   ploca         : array[0..8, 0..8] of char;
   ERROR, gotovo : boolean;

function cross(z : char):boolean;
var
   r, s, i, j          : integer;
   red, stupac         : array[0..8] of integer;
   blok                : array[0..2, 0..2] of integer;
   mog, gdje_r, gdje_s : integer;
begin
   fillchar(red, sizeof(red), 0);
   fillchar(stupac, sizeof(stupac), 0);
   fillchar(blok, sizeof(blok), 0);
   
   cross := false;
   for r:=0 to 8 do begin
      for s:=0 to 8 do begin
         if ploca[r, s] = z then begin
            red[r] := red[r]+1;
            stupac[s] := stupac[s]+1;
            blok[r div 3, s div 3] := blok[r div 3, s div 3]+1;
            if (red[r] > 1) or (stupac[s] > 1) or (blok[r div 3, s div 3] > 1) then
               ERROR := true;
         end;
      end;
   end;

   for i:=0 to 2 do begin
      for j:=0 to 2 do begin
         if blok[i, j] > 0 then continue;

         mog := 0;
         for r:=0 to 2 do begin
            for s:=0 to 2 do begin
               if (ploca[3*i+r, 3*j+s] = '.') and (red[3*i+r] = 0) and (stupac[3*j+s] = 0) then begin
                  mog := mog+1;
                  gdje_r := 3*i+r;
                  gdje_s := 3*j+s;
               end;
            end;
         end;

         if mog = 0 then begin
            ERROR := true;
         end;
         if mog = 1 then begin
            ploca[gdje_r, gdje_s] := z;
            red[gdje_r] := 1;
            stupac[gdje_s] := 1;
            blok[i, j] := 1;
            cross := true;
         end;
      end;
   end;
end;

begin
   for i:=0 to 8 do begin
      for j:=0 to 8 do
         read(ploca[i, j]);
      readln;
   end;

   repeat
      gotovo := true;
      for z:='1' to '9' do 
         gotovo := gotovo and not cross(z);
   until gotovo or ERROR;

   if ERROR then 
      writeln('ERROR')
   else begin
      for i:=0 to 8 do begin
         for j:=0 to 8 do
            write(ploca[i, j]);
         writeln;
      end;
   end;
end.

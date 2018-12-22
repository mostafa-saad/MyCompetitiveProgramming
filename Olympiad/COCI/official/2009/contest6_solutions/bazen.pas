program bazen;

var ax, ay, bx, by, p: real;

begin
   read( ax, ay );
   p := 250*250/2;

   if ax = 0 then begin

      if ay < 125 then begin bx := p/(250-ay); by := 250-p/(250-ay) end
      else begin bx := p/ay; by := 0; end

   end;

   if ay = 0 then begin

      if ax < 125 then begin bx := 250-p/(250-ax); by := p/(250-ax); end
      else begin bx := 0; by := p/ax; end

   end;

   if (ax > 0) and (ay > 0) then begin

       if ax > 125 then begin bx := 0; by := 250-p/ax; end
       else begin bx := 250-p/ay; by := 0; end

   end;

   writeln( bx:0:2, ' ', by:0:2 );
end.


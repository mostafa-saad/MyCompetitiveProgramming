program kornislav;

var
   A, B, C, D, t : longint;

begin
   readln( A, B, C, D );
   
   if A > B then begin t := A; A := B; B := t; end;
   if A > C then begin t := A; A := C; C := t; end;
   if A > D then begin t := A; A := D; D := t; end;
   if B > C then begin t := B; B := C; C := t; end;
   if B > D then begin t := B; B := D; D := t; end;
   if C > D then begin t := C; C := D; D := t; end;

   writeln( A * C );   
end.
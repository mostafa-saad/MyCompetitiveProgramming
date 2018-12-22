program profesor;

const MAXN = 100100;

var
   N, x, y : longint;
   A : array[1..MAXN] of longint;
   B : array[1..MAXN] of longint;

procedure load;
var
   i : longint;
begin
   readln(N);
   for i := 1 to N do
      readln(A[i], B[i]);
end;

procedure solve;
var
   grade, len, i : longint;
begin
   for grade := 1 to 5 do begin
      len := 0;
      for i := 1 to N do begin
         if (A[i] = grade) or (B[i] = grade) then inc(len) else len := 0;
         if (len > x) then begin
            x := len;
            y := grade;
         end;
      end;
   end;
end;

procedure output;
begin
   writeln(x, ' ', y);
end;

begin
   load;
   solve;
   output;
end.

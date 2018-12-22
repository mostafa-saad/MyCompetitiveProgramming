program cavli;

const
   LEFT  = 0;
   RIGHT = 1;
   DOWN  = 2;
   UP    = 3;

type
   int64array = array of int64;

type
   ppoint  = ^point;
   point   = 
   record  
      x, y    : int64;
      flag    : boolean;
      next    : array[0..3] of ppoint;
      ccw, cw : ppoint;
   end;

procedure init(var p : point);
var i : longint;
begin
   p.flag := false;
   for i:=0 to 3 do
      p.next[i] := nil;
   p.ccw := nil;
   p.cw := nil;
end;
      
function ccw(A, B, C : ppoint) : longint;
var t : int64 ;
begin
   t := (B^.x-A^.x)*(C^.y-A^.y) - (C^.x-A^.x)*(B^.y-A^.y);
   if t < 0 then ccw := -1
   else if t > 0 then ccw := 1
   else ccw := 0;
end;

var QSORT_PASS : longint; (* 0 za sortiranje po x, 1 za sortiranje po y *)

function cmp(a, b : ppoint) : longint;
begin
   if QSORT_PASS = 0 then begin
      if a^.x < b^.x then cmp := -1
      else if a^.x > b^.x then cmp := 1
      else cmp := 0;
   end else begin
      if a^.y < b^.y then cmp := -1
      else if a^.y > b^.y then cmp := 1
      else cmp := 0;
   end;
end;

procedure swap(var a, b : ppoint); var t : ppoint; begin t := a; a := b; b := t; end;

procedure qsort(var arr : array of ppoint; l, r: longint);
var x, y : longint;
    mid  : ppoint;
begin
    if r-l < 2 then exit;
    if r-l = 2 then begin
        if cmp(arr[l+1], arr[l]) < 0 then swap(arr[l], arr[l+1]);
        exit;
    end;

    mid := arr[(l+r) div 2];
    y := l;

    for x := l to r-1 do  (* sve strogo manje stavi na pocetak *)
        if cmp(arr[x], mid) < 0 then begin
            swap(arr[x], arr[y]);
            inc(y);
        end;

    qsort(arr, l, y); (* sortiraj sve strogo manje *)

    for x:=y to r-1 do (* sve jednake stavi poslije ovih manjih *)
        if cmp(arr[x], mid) = 0 then begin
            swap(arr[x], arr[y]);
            inc(y);
        end;

    qsort(arr, y, r); (* sortiraj sve strogo vece *)
end;

procedure connect(n : longint; var order, extreme : array of ppoint; A, B : longint);
var i : longint;
begin
   extreme[A] := order[0];
   extreme[B] := order[n-1];
   for i:=1 to n-1 do begin
      order[i]^.next[A] := order[i-1];
      order[i-1]^.next[B] := order[i];
   end;
end;

procedure go_inwards(var chosen  : array of char;
                     var order   : array of ppoint;
                         steps   : longint;
                     var extreme : array of ppoint);
var i, d : longint;
begin
   for i:=0 to steps-1 do begin
      if chosen[i] = 'L' then order[i] := extreme[LEFT];
      if chosen[i] = 'R' then order[i] := extreme[RIGHT];
      if chosen[i] = 'D' then order[i] := extreme[DOWN];
      if chosen[i] = 'U' then order[i] := extreme[UP];
      
      order[i]^.flag := true;

      for d:=0 to 3 do
         while extreme[d]^.flag do
            extreme[d] := extreme[d]^.next[d xor 1];
   end;
end;

procedure add(var area : int64; P : ppoint);
begin
   P^.CCW^.CW := P;
   P^.CW^.CCW := P;
   area := area + (P^.x     * P^.CCW^.y  - P^.y     * P^.CCW^.x);
   area := area + (P^.CW^.x * P^.y       - P^.CW^.y * P^.x);
   area := area - (P^.CW^.x * P^.CCW^.y  - P^.CW^.y * P^.CCW^.x);
end;

procedure sub(var area : int64; P : ppoint);
begin
   P^.CCW^.CW := P^.CW;
   P^.CW^.CCW := P^.CCW;
   area := area - (P^.x     * P^.CCW^.y  - P^.y     * P^.CCW^.x);
   area := area - (P^.CW^.x * P^.y       - P^.CW^.y * P^.x);
   area := area + (P^.CW^.x * P^.CCW^.y  - P^.CW^.y * P^.CCW^.x);
end;

function go_outwards(var chosen  : array of char;
                     var order   : array of ppoint;
                         steps   : longint;
                     var extreme : array of ppoint) : int64array;
var
   result : int64array;
   area   : int64;
   i, d   : longint;
   A      : ppoint;
begin
   setlength(result, steps);
   area := 0;

   for i:=steps-1 downto 0 do begin
      if chosen[i] = 'L' then d := LEFT;
      if chosen[i] = 'R' then d := RIGHT;
      if chosen[i] = 'D' then d := DOWN;
      if chosen[i] = 'U' then d := UP;
      
      A := order[i];

      A^.CCW := extreme[d];
      while (A^.CCW <> extreme[d xor 1]) and (ccw(A, A^.CCW, A^.CCW^.CCW) <= 0) do begin
         if A^.CCW <> extreme[d] then sub(area, A^.CCW);
         A^.CCW := A^.CCW^.CCW;
      end;
         
      A^.CW := extreme[d];
      while (A^.CW <> extreme[d xor 1]) and (ccw(A, A^.CW, A^.CW^.CW) >= 0) do begin
         if A^.CW <> extreme[d] then sub(area, A^.CW);
         A^.CW := A^.CW^.CW;
      end;

      if (A^.CW <> extreme[d]) and (A^.CCW <> extreme[d]) then sub(area, extreme[d]);

      add(area, A);
      
      if A^.x < extreme[LEFT]^.x then extreme[LEFT] := A;
      if A^.x > extreme[RIGHT]^.x then extreme[RIGHT] := A;
      if A^.y < extreme[DOWN]^.y then extreme[DOWN] := A;
      if A^.y > extreme[UP]^.y then extreme[UP] := A;

      result[i] := area;
   end;

   go_outwards := result;
end;

var
   i, n    : longint;
   data    : array of point;
   order   : array of ppoint;
   extreme : array[0..3] of ppoint;
   chosen  : array of char;
   result  : int64array;

begin
   readln(n);
   setlength(data, n);
   setlength(order, n);

   for i:=0 to n-1 do begin
      init(data[i]);
      readln(data[i].x, data[i].y);
      order[i] := @data[i];
   end;

   QSORT_PASS := 0; qsort(order, 0, n); connect(n, order, extreme, LEFT, RIGHT);
   QSORT_PASS := 1; qsort(order, 0, n); connect(n, order, extreme, DOWN, UP);

   setlength(chosen, n);
   for i:=0 to n-1 do read(chosen[i]);

   go_inwards(chosen, order, n-2, extreme);

   extreme[LEFT]^.CCW := extreme[RIGHT];
   extreme[LEFT]^.CW := extreme[RIGHT];
   extreme[RIGHT]^.CCW := extreme[LEFT];
   extreme[RIGHT]^.CW := extreme[LEFT];
   
   result := go_outwards(chosen, order, n-2, extreme);

   for i:=0 to n-3 do 
      writeln(result[i] div 2, '.', result[i] mod 2 * 5);
end.

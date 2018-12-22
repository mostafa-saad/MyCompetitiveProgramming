program periodni;

const MAXN = 500;
const MAXK = 500;
const MODC = 1000000007;

function gcd(a, b : longint) : longint;
begin if b = 0 then gcd := a else gcd := gcd(b, a mod b); end;

type
   pnode = ^node;
   node  = array[0..MAXK] of int64;

var
   komb            : array[0..MAXN, 0..MAXK] of int64;
   povrh           : array[0..MAXK] of int64;
   nodes           : array[0..3*MAXN] of node;
   allocator, root : pnode;
   n, k, i, j      : longint;
   h               : array[0..MAXN] of longint;
   gore            : array[0..MAXK] of longint;

procedure calc_povrh(n : longint);
var
   i, j, g, dole : longint;
begin
   povrh[0] := 1;
   i := 1;
   while (i<=k) and (n>=i) do begin
      gore[i-1] := n-i+1;

      dole := i;
      for j:=0 to i-1 do begin
         g := gcd(gore[j], dole);
         dole := dole div g;
         gore[j] := gore[j] div g;
      end;

      povrh[i] := 1;
      for j:=0 to i-1 do povrh[i] := povrh[i] * gore[j] mod MODC;
      
      inc(i);
   end;

   while i<=k do begin
      povrh[i] := 0;
      inc(i);
   end;
end;

function rec(a, b, h0 : longint) : pnode;
var
   curr, up, left, right  : pnode;
   minh, minh_index, i, j : longint;
   leaf                   : boolean;
begin
   curr := allocator; inc(allocator);
   leaf := true;
   minh := 1000000000;
   minh_index := -1;
   for i:=a to b-1 do begin
      if h[i] < minh then begin
         minh := h[i];
         minh_index := i;
      end;
      if h[i] <> h[a] then leaf := false;
   end;

   if leaf then begin
      calc_povrh(minh-h0);
      for i:=0 to k do
         curr^[i] := komb[b-a, i] * povrh[i] mod MODC;
   end else if minh > h0 then begin
      up := rec(a, b, minh);
      calc_povrh(minh-h0);

      for i:=0 to k do begin
         curr^[i] := 0;
         j := 0;
         while (j <= i) and (b-a-j >= 0) do begin
            curr^[i] := curr^[i] + up^[j] * povrh[i-j] mod MODC * komb[b-a-j, i-j] mod MODC;
            inc(j);
         end;
         curr^[i] := curr^[i] mod MODC;
      end;
   end else begin
      left := rec(a, minh_index, h0);
      right := rec(minh_index+1, b, h0);

      for i:=0 to k do begin
         curr^[i] := 0;
         for j:=0 to i do 
            curr^[i] := curr^[i] + left^[j] * right^[i-j] mod MODC;
         curr^[i] := curr^[i] mod MODC;
      end;
   end;
   rec := curr;
end;

begin
   read(n, k);
   for i:=0 to n-1 do read(h[i]);

   for i:=0 to n do begin
      komb[i, 0] := 1;
      for j:=1 to i do
         komb[i, j] := komb[i, j-1] * (i-j+1) mod MODC;
   end;

   allocator := @nodes[0];
   root := rec(0, n, 0);
   writeln(root^[k]);
end.

program jez;

const LOG_MAXN = 20;

var
   R, S, nd, visak  : longint;
   red, najdulja, i : longint;
   K, ukupno, rez   : int64;

function min(a, b : longint) : longint; begin if a <= b then min := a else min := b; end;
function max(a, b : longint) : longint; begin if a >= b then max := a else max := b; end;

function popcount(x : longint):longint;
var rez : longint;
begin
   rez := 0;
   while x <> 0 do begin
      inc(rez);
      x := x - (x and -x);
   end;
   popcount := rez;
end;

function prebroji(x, ymax : longint):longint;
var k, jed, rez : longint;
begin
   rez := 0;
   for k:=LOG_MAXN downto 0 do begin
      if (ymax shr k) and 1 <> 0 then begin
         (* jed = broj jedinica u x na pozicijama 0..k-1 *)
         jed := popcount(x and ((1 shl k) - 1));
         rez := rez + (1 shl (k - jed));

         (* ako x ima jedinicu na poziciji k, svi brojevi izmedu 2^k i
            ymax imaju neki zajednicki bit, pa smo gotovi *)
         if (x shr k) and 1 <> 0 then break;
      end;
   end;
   prebroji := rez;
end;

function jedanred(red : longint) : longint;
var smax, sr : longint;
begin
   smax := nd-red;
   if nd mod 2 = 0 then begin
      sr := nd - max(0, nd-R+1);
      if (sr-red >= 0) and (sr-red < visak) then inc(smax);
   end else begin
      sr := max(0, nd-S+1);
      if (red-sr >= 0) and (red-sr < visak) then inc(smax);
   end;

   smax := max(smax, 0);
   smax := min(smax, S);
   jedanred := prebroji(red, smax);
end;

function dodaj(var ukupno : int64; x : longint) : boolean;
begin
   ukupno := ukupno + x;
   if ukupno > K then begin
      dodaj := true;
      exit;
   end;
   inc(nd);
   visak := K - ukupno;
   dodaj := false;
end;

begin
   read(R, S, K);
   najdulja := min(R, S);
   ukupno := 0;
   nd := 0;
   for i:=1 to najdulja do
      if dodaj(ukupno, i) then break;
   for i:=0 to R+S-2*najdulja-1 do
      if dodaj(ukupno, najdulja) then break;
   for i:=najdulja-1 downto 1 do 
      if dodaj(ukupno, i) then break;

   rez := 0;
   for red:=0 to R-1 do
      rez := rez+jedanred(red);
   writeln(rez);
end.

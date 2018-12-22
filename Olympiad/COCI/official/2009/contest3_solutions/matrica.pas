program matrica;

const MAXP = 50;
const MAXN = 30000;

var
   N, K, P, x, neparnih, i, r, s, poz, slovo, p_start, prvi, prvi_neparni, next_s : longint;
var
   c          : char;
   ispis      : array[1..MAXP+1] of longint;
   ret        : array[1..MAXN, 1..MAXP+1] of char;
   koliko     : array[0..26] of longint;
   cijeli_red : boolean;

function min(a, b : longint) : longint; begin if a < b then min := a else min := b; end;

begin
   readln(N, K);
   for i:=1 to K do begin
      readln(c, x);
      koliko[ord(c)-ord('A')] := x;
   end;

   neparnih := 0;
   for i:=0 to 25 do
      neparnih := neparnih + koliko[i] mod 2;

   if neparnih > N then begin
      writeln('IMPOSSIBLE');
      exit;
   end;

   readln(P);
   for i:=1 to P do read(ispis[i]);
   ispis[P+1] := N+1;

   p_start := 1;
   for r:=1 to N do begin
      neparnih := 0;
      for i:=25 downto 0 do begin
         if koliko[i] > 0 then prvi := i;
         if koliko[i] mod 2 > 0 then begin
            prvi_neparni := i;
            neparnih := neparnih + 1;
         end;
      end;

      if N-r+1 > neparnih then slovo := prvi
      else slovo := prvi_neparni;

      koliko[slovo] := koliko[slovo]-1;
      cijeli_red := r = ispis[p_start];
      if cijeli_red then ret[r][p_start] := chr(ord('A')+slovo);

      slovo := 0;
      s := r+1;
      poz := p_start + ord(cijeli_red);
      while s <= N do begin
         while koliko[slovo] < 2 do slovo := slovo+1;

         if cijeli_red then ret[s, p_start] := chr(ord('A')+slovo);
         if s = ispis[poz] then begin
            ret[r, poz] := chr(ord('A')+slovo);
            poz := poz+1;
         end;

         next_s := ispis[poz];
         if cijeli_red then next_s := s+1;
         next_s := min(next_s, s + koliko[slovo] div 2);

         koliko[slovo] := koliko[slovo] - 2*(next_s-s);
         s := next_s;
      end;

      if cijeli_red then p_start := p_start + 1;

      for i:=1 to P do
         write(ret[r, i]);
      writeln;
   end;
end.

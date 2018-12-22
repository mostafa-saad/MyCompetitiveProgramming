
(*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak STRAZA
  Programski jezik Pascal

  Rovove smo predstavili duzinama. Pretpostavimo da se nijedne dvije
  duzine koje se nalaze na istom pravcu ne sijeku. U tom slucaju svake
  tri duzine, koje se sijeku svaka sa svakom, a da ta tri sjecista nisu
  u istoj tocki, predstavljaju jedno rjesenje - strazare mozemo
  postaviti u sjecista tih duzina. Za svaku trojku duzina provjerimo
  vrijede li ta svojstva, i ako da ubrojimo ju u rjesenje.  Preostaje
  samo osigurati pretpostavku. Ako postoje dvije duzine koje se nalaze
  na istom pravcu i sijeku se, mozemo ih spojiti i tretirati kao jednu
  duzinu. Taj postupak ponavljamo sve dok imamo sto za spojiti i
  osigurali smo pretpostavku.

  Da bismo izbrojali rjesenja potrebno je provjeriti sve trojke duzina
  sto daje slozenost O(N^3).
*)

program straza;

type tocka = object
   x, y : double;
   constructor Create;
   constructor Create(drugi : tocka);
   constructor Create(xt, yt : double);
end;

type duzina = object
   a, b : tocka;
   constructor Create(at, bt : tocka);
end;

type pravac = object
   A, B, C : double;
   constructor Create(S : duzina);
end;

const EPS : double = 1e-9;

function eq(a, b : double):boolean;
begin
   eq := (a-EPS <= b) and (b <= a+eps);
end;

function lt(a, b : double):boolean;
begin
   lt := a+eps < b;
end;

function gt(a, b : double):boolean;
begin
   gt := a-eps > b;
end;

constructor tocka.Create;
begin
   x := 0; y := 0;
end;

constructor tocka.Create(drugi : tocka);
begin
   x := drugi.x; y := drugi.x;
end;

constructor tocka.Create(xt, yt : double);
begin
   x := xt; y := yt;
end;

function eq(a, b : tocka):boolean;
begin
   eq := eq(a.x, b.x) and eq(a.y, b.y);
end;

constructor duzina.Create(at, bt : tocka);
begin
   a := at; b := bt;
end;

constructor pravac.Create(S : duzina);
begin
   A := S.b.y - S.a.y;
   B := S.a.x - S.b.x;
   C := A*S.a.x + B*S.a.y;
end;

function mysgn(x : double):integer;
begin
   if      lt(x, 0) then mysgn := -1
   else if gt(x, 0) then mysgn := 1
   else mysgn := 0;
end;

function ccw(A, B, C : tocka):integer;
begin
   ccw := mysgn((B.x-A.x)*(C.y-A.y) - (C.x-A.x)*(B.y-A.y));
end;

function strana(L : pravac; T : tocka):integer;
begin
   strana := mysgn( L.A*T.x + L.B*T.y - L.C );
end;

function sijece(L : pravac; P : tocka):boolean;
begin
   sijece := eq( L.A*P.x + L.B*P.y - L.C, 0 );
end;

function sijece(S : duzina; P : tocka):boolean;
var pr : pravac;
begin
   pr.Create(S);
   sijece :=
      sijece( pr, P ) and
      eq( abs(S.b.x-P.x)+abs(S.a.x-P.x), abs(S.b.x-S.a.x) ) and
      eq( abs(S.b.y-P.y)+abs(S.a.y-P.y), abs(S.b.y-S.a.y) );
end;

function sijece(L1, L2 : pravac):boolean;
begin
   sijece := not eq( L1.A*L2.B, L2.A*L1.B );
end;

function sijece(L : pravac; S : duzina):boolean;
begin
   sijece := strana( L, S.a ) * strana( L, S.b ) <= 0;
end;

function sijece(S1, S2 : duzina):boolean;
var prs1, prs2 : pravac;
begin
   prs1.Create(S1);
   prs2.Create(S2);
   if sijece(prs1, S2.a) and sijece(prs1, S2.b) then
      sijece := sijece(S1, S2.a) or sijece(S1, S2.b) or sijece(S2, S1.a) or sijece(S2, S1.b)
   else
      sijece := sijece(prs1, S2) and sijece(prs2, S1);
end;

function sjeciste(L1, L2 : pravac):tocka;
begin
   sjeciste.Create((L1.C*L2.B-L2.C*L1.B) / (L1.A*L2.B-L2.A*L1.B),
                   (L1.A*L2.C-L2.A*L1.C) / (L1.A*L2.B-L2.A*L1.B));
end;

function sjeciste(s1, s2 : duzina):tocka;
var L1, L2 : pravac;
begin
   L1.create(S1);
   L2.create(S2);
   sjeciste := sjeciste(L1, L2);
end;

function izmedu(A, B, C : tocka):boolean;
begin
   izmedu := not (
      lt(abs(A.x-C.x),abs(A.x-B.x)) or
      lt(abs(A.y-C.y),abs(A.y-B.y)) or
      lt(abs(A.x-C.x),abs(C.x-B.x)) or
      lt(abs(A.y-C.y),abs(C.y-B.y))
   );
end;

function treba_spojiti(s1, s2 : duzina):boolean;
begin
   if ( ccw(s1.a,s1.b,s2.a) <> 0 ) or ( ccw(s1.a,s1.b,s2.b) <> 0 ) then
      treba_spojiti := false
   else if izmedu(s1.a,s2.a,s1.b) or izmedu(s1.a,s2.b,s1.b) then
      treba_spojiti := true
   else
      treba_spojiti := false;
end;

function spoji(s1, s2 : duzina):duzina;
begin
   if izmedu(s1.a,s2.a,s1.b) and izmedu(s1.a,s2.b,s1.b) then
      spoji := s1
   else if izmedu(s2.a,s1.a,s2.b) and izmedu(s2.a,s1.b,s2.b) then
      spoji := s2
   else if izmedu(s1.a,s2.a,s1.b) then begin
      if izmedu(s2.a,s1.a,s2.b) then
         spoji.Create(s1.b,s2.b)
      else if izmedu(s2.a,s1.b,s2.b) then
         spoji.Create(s1.a,s2.b);
   end
   else if izmedu(s1.a,s2.b,s1.b) then begin
      if izmedu(s2.a,s1.a,s2.b) then
         spoji.Create(s1.b,s2.a)
      else if izmedu(s2.a,s1.b,s2.b) then
         spoji.Create(s1.a,s2.a);
   end;
end;

var
   n, i, j, k : integer;
   spojio     : boolean;
   niz        : array[1..20] of duzina;
   rez        : integer;

begin
   readln(n);

   for i:=1 to n do begin
      readln(niz[i].a.x, niz[i].a.y, niz[i].b.x, niz[i].b.y);
   end;

   spojio := true;
   while spojio do begin
      spojio := false;

      for i:=1 to n do begin
         for j:=i+1 to n do begin
            if treba_spojiti(niz[i], niz[j]) then begin
               niz[i] := spoji(niz[i], niz[j]);
               niz[j] := niz[n];
               n := n-1;
               spojio := true;
               break;
            end;
         end;
         if spojio then break;
      end;
   end;

   rez := 0;
   for i:=1 to n do
      for j:=i+1 to n do
         for k:=j+1 to n do begin
            if sijece(niz[i],niz[j]) and sijece(niz[i],niz[k]) and sijece(niz[j],niz[k]) then begin
               if not eq(sjeciste(niz[i],niz[j]), sjeciste(niz[i],niz[k])) then begin
                  rez := rez + 1;
               end;
            end;
         end;

   writeln(rez);
end.

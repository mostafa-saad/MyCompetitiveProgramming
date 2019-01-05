Program Rastove_otlaky; {KSP XV-4-4}

const MAXN = 1000;
      MAXSUS = 6;
      {ak ma nejaky otlak viac nez 6 susedov, uloha nema riesenie}
      meno = 'o2';

type
 otlak = record
   x,y : integer;
   sus : array[0..MAXSUS-1] of integer;
   pocs : integer; {pocet susedov}
   val : array[boolean] of integer;
   smer : boolean;
 end;
 vrchol = record
   i : integer;
   smer : boolean;
 end;

var otlaky : array[1..MAXN] of otlak;
    N : integer;
    id : integer;
    stack,buf : array[0..MAXN-1] of vrchol;
    sp,pocbuf : integer;

Procedure Nacitaj;
 var f : text;
     i : integer;
 Begin
   Assign(f,meno+'.in'); Reset(f);
   otlaky[N+1].x:=MaxInt; otlaky[N+1].y:=MaxInt;
   otlaky[N+2].x:=MaxInt; otlaky[N+2].y:=MaxInt;
   {zarazka pre proceduru Zlinkuj}
   ReadLn(f,N);
   for i:=1 to N do with otlaky[i] do begin
     ReadLn(f,x,y); pocs:=0;
   end;
   Close(f);
 End;

Procedure Tried;
 {predstavme si, ze triedenie je v case n log n..}
 var i,j : integer;
     pom : otlak;
 Begin
   for i:=1 to N do begin
     for j:=i+1 to N do
       if (otlaky[i].x>otlaky[j].x) or
         ((otlaky[i].x=otlaky[j].x) and
          (otlaky[i].y>otlaky[j].y)) then begin
         pom:=otlaky[i]; otlaky[i]:=otlaky[j]; otlaky[j]:=pom;
       end;
   end;
 End;

Procedure Koniec(ok : boolean);
 var i : integer;
 Begin
   WriteLn;
   if ok then begin
     for i:=1 to N do begin
       Write('Otlak (',otlaky[i].x,', ',otlaky[i].y,') ');
       if otlaky[i].smer then WriteLn('prelepit zvislo')
                         else WriteLn('prelepit vodorovne');
     end;
   end else begin
     WriteLn('Chudak Rasto..');
   end;
   Halt;
 End;

Function Hrana(a,b : integer; sa,sb : boolean) : Boolean;
 {ak ma naplast a smer sa, vyplyva z toho, ze naplast b ma smer sb?}
 {vodorovne - false; zvislo - true}
 var dx,dy,pom : integer;
     ok : boolean;
     odx,ody : integer;
     osa,osb : boolean;
 Begin
   dx:=abs(otlaky[a].x-otlaky[b].x);
   dy:=abs(otlaky[a].y-otlaky[b].y);
   odx:=dx; ody:=dy;
   osa:=sa; osb:=sb;
   if dx<dy then begin {vyuzijeme symetriu}
     pom:=dx; dx:=dy; dy:=pom;
     sa:= not sa; sb:=not sb;
   end;
   ok:=False;
   if (dx=1) and (dy=1) and (sa=sb) then ok:=True;
   if (dx=1) and (dy=0) and sb then ok:=True;
   if (dx=2) and (dy=0) and not sa and sb then ok:=True;
   Hrana:=ok;
 End;

Procedure PridajSuseda(a,b : integer);
 {otlaku a zapiseme, ze susedi s otlakom b a naopak}
 Begin
   if otlaky[a].pocs>=MAXSUS then Koniec(False);
   otlaky[a].sus[otlaky[a].pocs]:=b;
   Inc(otlaky[a].pocs);
   if otlaky[b].pocs>=MAXSUS then Koniec(False);
   otlaky[b].sus[otlaky[b].pocs]:=a;
   Inc(otlaky[b].pocs);
 End;

Procedure Zlinkuj;
 {kazdemu otlaku vyrobime zoznam susedov}
 var i,j,k,ii,jj,kk,ll : integer;
     xi : integer;
 Begin
   ii:=1; xi:=otlaky[ii].x;
   jj:=ii; while (jj<=N) and (otlaky[jj].x<xi+1) do Inc(jj);
   kk:=jj; while (kk<=N) and (otlaky[kk].x<xi+2) do Inc(kk);
   ll:=kk; while (ll<=N) and (otlaky[ll].x<xi+3) do Inc(ll);

   while ii<N do begin
     j:=jj; k:=kk;
     for i:=ii to jj-1 do begin
       if (i+1<jj) and (otlaky[i+1].y-otlaky[i].y<=2) then
         PridajSuseda(i,i+1);
       {sused s rovnakou x-ovou suradnicou; ak su dvaja, staci blizsi}
       j:=j-2; if j<jj then j:=jj;
       while (j<kk) and (otlaky[j].y-otlaky[i].y<=1) do begin
         if  abs(otlaky[j].y-otlaky[i].y)<=1 then
           Pridajsuseda(i,j);
           {susedia  s x-ovou suradnicou xi+1}
         Inc(j);
       end;
       while (k<ll) and (otlaky[i].y>otlaky[k].y) do Inc(k);
       if otlaky[i].y=otlaky[k].y then
         PridajSuseda(i,k);
         {sused o dve policka napravo}
     end;
     ii:=jj;
     xi:=otlaky[ii].x;

     while (jj<=N) and (otlaky[jj].x<xi+1) do Inc(jj);
     kk:=jj; while (kk<=N) and (otlaky[kk].x<xi+2) do Inc(kk);
     ll:=kk; while (ll<=N) and (otlaky[ll].x<xi+3) do Inc(ll);
   end;
 End;

Procedure Push(i : integer; smer : boolean);
 Begin
   stack[sp].i:=i;
   stack[sp].smer:=smer;
   Inc(sp);
 End;

Procedure Pop(var x : vrchol);
 Begin
   Dec(sp);
   x:=stack[sp];
 End;

Procedure SpracujKomponent;
 {v poli buf dostaneme zoznam vrcholov daneho komponentu
  ak uz bol jeho komplementarny komponent navstiveny, nic sa nedeje
  inak mu nastavime smery}
 var i : integer;
 Begin
   if otlaky[buf[0].i].val[not buf[0].smer] = MaxInt then begin
     {skontrolujeme, ci naozaj vsetci maju spravny smer}
     for i:=0 to pocbuf-1 do begin
       if (otlaky[buf[i].i].val[not buf[i].smer]<>MaxInt) or
          (otlaky[buf[i].i].smer=buf[i].smer) then
         Koniec(False);
     end;
   end else begin
     {komplementarny komponent este nesmel byt navstiveny}
     for i:=0 to pocbuf-1 do begin
       if otlaky[buf[i].i].val[not buf[i].smer]=MaxInt then
         Koniec(False);
       otlaky[buf[i].i].smer:=buf[i].smer; {a nastavime smer}
     end;

   end;
 End;

Function Visit(i : integer; smer : boolean) : integer;
 var tmp : vrchol;
     ii,j,min,m : integer;
     s2 : boolean;
 Begin
   Inc(id);
   otlaky[i].val[smer]:=id;
   min:=id;
   Push(i,smer);
   for j:=0 to otlaky[i].pocs-1 do
     for s2:=False to True do begin
       ii:=otlaky[i].sus[j];
       if Hrana(i,ii,smer,s2) then begin
         if otlaky[ii].val[s2]=0 then m:=Visit(ii,s2)
                                 else m:=otlaky[ii].val[s2];
         if m<min then min:=m;
       end;
     end;

   if min = otlaky[i].val[smer] then begin
     pocbuf:=0;
     repeat
       Pop(tmp);
       buf[pocbuf]:=tmp; Inc(pocbuf); {zaradime do zoznamu}
       otlaky[tmp.i].val[tmp.smer]:=MaxInt;
     until (tmp.i = i) and (tmp.smer = smer);
     SpracujKomponent;
   end;
   Visit:=min;
 End;

var i : integer;
    smer : boolean;
Begin
  Nacitaj;
  Tried;
  Zlinkuj;
  id:=0;
  sp:=0;
  for i:=1 to N do
    for smer:=False to True do
      if otlaky[i].val[smer]=0 then Visit(i,smer);
  Koniec(True);
End.

{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Egzamin na prawo jazdy (EGZ)                               *}
{*   Plik:    egzs2.pas                                                  *}
{*   Autor:   Michal Brzozowski                                          *}
{*   Opis:    Rozwiazanie za wolne.                                      *}
{*                                                                       *}
{*************************************************************************}
type 
 droga=record
  num,wys,zbud:longint;
 end;

const maxn=100000;

var n,m,p,k:longint;
    ul:array[1..2, 0..maxn] of droga;
    ile:array[1..2] of longint;
    zbud:array[1..2,0..maxn] of longint;

procedure wczytaj;
var 
 i,a,b,c:longint;

begin
 ile[1]:=0;
 ile[2]:=0;
 readln(n,m,p,k);
 for i:=1 to p do
 begin
  readln(a,b,c);
 if c=1 then 
 begin
  ul[1,ile[1]].num:=a;
  ul[1,ile[1]].wys:=b;
  ul[1,ile[1]].zbud:=a-1;
  ile[1]:=ile[1]+1;
 end else
 begin
  ul[2,ile[2]].num:=n-a;
  ul[2,ile[2]].wys:=b;
  ul[2,ile[2]].zbud:=n-a-1;
  ile[2]:=ile[2]+1;

 end;
 end;
end;
function mniejszy(a,b:droga):boolean;

begin
 if (a.num<b.num) or ((a.num=b.num) and (a.wys<b.wys)) then 
  mniejszy:=true else
  mniejszy:=false;
end;

procedure zamien(var a,b:droga);
var c:droga;
begin
 c:=a;
 a:=b;
 b:=c;
end;

procedure sortuj(d,l,r:longint);
var
 i,j:longint;
 x,y:droga;
begin
 i:=l;
 j:=r;
 x:=ul[d,(l+r) div 2];
 repeat
  while mniejszy(ul[d,i],x) do i:=i+1;
  while mniejszy(x,ul[d,j]) do j:=j-1;
  if i<=j then begin
   zamien(ul[d][i],ul[d][j]);
   i:=i+1;
   j:=j-1;
  end;
 until i>j;
 if l<j then sortuj(d,l,j);
 if i<r then sortuj(d,i,r);
end;

procedure podciag(d:longint);
var  
 i,j,a,b,c,l:longint;
 m:array[0..maxn] of longint;

begin
 sortuj(d,0,ile[d]-1);
 l:=0;
 for i:=0 to maxn do m[i]:=0;
 for i:=0 to ile[d]-1 do begin
  for j:=0 to i-1 do begin
   if (ul[d,j].wys>=ul[d,i].wys) and 
      (ul[d,j].zbud+ul[d,i].num-ul[d,j].num-1<ul[d,i].zbud) then
    ul[d,i].zbud:=ul[d,j].zbud+ul[d,i].num-ul[d,j].num-1;
  end;
  if ul[d,i].zbud<zbud[d,ul[d,i].num] then zbud[d,ul[d,i].num]:=ul[d,i].zbud;
 end;
 for i:=1 to n-1 do 
  if zbud[d,i]>zbud[d,i-1]+1 then zbud[d,i]:=zbud[d,i-1]+1;

end;

var i,l,wyn:longint;

begin
 wczytaj;
 for i:=0 to n-1 do begin
  zbud[1,i]:=i;
  zbud[2,i]:=i;
 end;
 podciag(1);
 podciag(2);
 for i:=0 to ((n-1) div 2) do begin l:=zbud[2,i];zbud[2,i]:=zbud[2,n-i-1];zbud[2,n-i-1]:=l;end;

 l:=n-1;
 while (zbud[2,0]+zbud[1,l]>k) and(l>0) do l:=l-1;
 if zbud[2,0] + zbud[1,l]<=k then wyn:=l+1 else wyn:=0;
 for i:=0 to n-1 do 
  while (l<n-1) and (zbud[2,i]+zbud[1,l+1]<=k) do begin
   l:=l+1;
   if l-i+1>wyn then wyn:=l-i+1;
  end;
 for i:=0 to n-1 do
  if (zbud[1,i]=0) and (zbud[2,i]=0) then wyn:=wyn-1;
 writeln(wyn);

end.

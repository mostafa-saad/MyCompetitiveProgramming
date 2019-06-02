(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Szyfr                                          *
 *   Plik:                szy.pas                                        *
 *   Autor:               Wojciech Dudek                                 *
 *   Uwagi:               rozwi±zanie wzorcowe                           *
 *   Z³o¿ono¶æ:           czas O(n^2), pamiec O(n)                       *
 *************************************************************************)
const
  MAX = 40;
  M = 1024* 1024;
type
  int = longint;
  TTab = array [1..MAX] of int;
  TREC = record l:int;i:int; end;
  TTabLiczb = array [1..M] of TREC;
var
  tab1, tab2 :TTabLiczb;
  tab :TTab;
  roz :integer;
  S :int;
  
procedure Wypisz(l,r :int);
var
  i : integer;
begin
  for i:=r-1 downto 0 do begin
    if (l shr i) mod 2 = 0 then 
      Write ('0')
    else
      Write ('1');
  end;
end;

procedure Zamien(var a,b:TREC);
var c :TREC;
begin c:=a; a:=b; b:=c end;

{to jest po to ¿eby tylko ciut-ciut przyspieszyæ}
procedure Sortuj(var t:TTabLiczb;l,p :int);
var
  v, i,j :int;
begin
  v := t[l].l;
  i := l+1;
  j := p;
  repeat
    while (i<p) and (t[i].l<=v) do inc(i);
    while (j>l) and (t[j].l>v) do dec(j);
    if i<j then begin Zamien (t[i],t[j]);end;
  until (i>=j);
  Zamien (t[l],t[j]);
  if j-1 > l then Sortuj (t, l,j-1);
  if j+1 < p then Sortuj (t, j+1,p);
end;

procedure Generuj(var t :TTabLiczb; p,k :integer; var i:int; suma:int);
begin
{  Write (p,' ',suma,' '); Wypisz;}
  if p=k then begin
    Inc(i);
    t[i].l:=suma;
    t[i].i:=i-1;
    Inc(i);
    t[i].l:=suma + tab[p];
    t[i].i:=i-1;
  end
  else begin
    Generuj(t,p+1,k,i,suma);
    Generuj(t,p+1,k,i,suma+tab[p]);
  end;
  
end;

procedure Szukaj (var t1,t2 :TTabLiczb; s1,s2:int ;r1,r2:integer);
var 
 OK : boolean;
 i,j : int;
 ss : int;
begin
  i := 1;
  j := s2;
  OK := false;
  while (not OK) do begin
    ss := t1[i].l + t2[j].l;
    if ss < S then Inc(i)
    else 
      if ss > S then Dec(j) 
        else OK :=true;
    if (j<1) or (i>s1) then break;
  end;
  if OK then begin
    Wypisz(t1[i].i, r1);
    Wypisz(t2[j].i, r2);
    WriteLn ();
  end else 
    WriteLn ('nie ma');
end;

var
  i :integer;
  s1, s2 :int;
begin
  ReadLn (roz);
  for i:= 1 to roz do begin
     ReadLn (tab[i]);
  end;
  ReadLn (S);
  s1:=0; s2:=0;
  Generuj(tab1, 1, roz div 2, s1,0);
  Generuj(tab2,(roz div 2) +1, roz, s2,0);
  Sortuj ( tab1 , 1, s1);
  Sortuj ( tab2 , 1, s2);
  Szukaj (tab1,tab2, s1,s2, roz div 2, roz -(roz div 2));
end.

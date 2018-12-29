(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbb7.pas                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie autorskie, zlozonosc O(n). Implementacja      *
 *             w Pascalu.                                                *
 *                                                                       *
 *************************************************************************)

program bbb;
const MAX=1100000;
const inf=2000*1000*1000+100;

var
    input:array[0..MAX] of char;                // wejsciowe slowo +-
    height:array[0..MAX] of longint;                // wysokosci bilansu na koncie
    mn:longint;                                        // minimalna wysokosc bilansu przy rozwazanym przesunieciu
    n,p,q,x,y,h,k,M,opt,r,ii:longint;
    { ii - pomocniczy indeks
      opt - znalezione optimum
      M - 2m z opracowania
      h - aktualna wysokosc balansu w czasie przetwarzania }
    ch:char;
    i:longint;
    
    heap:array[0..MAX,0..1] of longint;        // stog - korzen w 1, w [0] wartosc, w [1] klucz
    gdzie:array[0..2*MAX] of longint;        // tablica gdzie w stogu jest jaki klucz
    hsize:longint;
    
{ IMPLEMENTACJA STOGU }

procedure xch(a,b:longint);
var f:longint;
begin
    gdzie[heap[a,1]]:=b;
    gdzie[heap[b,1]]:=a;
    
    f:=heap[a,0];
    heap[a,0]:=heap[b,0];
    heap[b,0]:=f;
    
    f:=heap[a,1];
    heap[a,1]:=heap[b,1];
    heap[b,1]:=f;
end;
// wymiana elementow a i b w stogu 

procedure heapup(l:longint);
begin
    while ((l>1) and (heap[l,0]<heap[l shr 1,0])) do
    begin
        xch(l,l shr 1);
        l:=(l shr 1);
    end;
end;
// funkcja do przepychania elementu w gore stogu

procedure heapdown(l:longint);
var v:longint;        // syn - kandydat na podmiane
begin
    while ((l shl 1)<=hsize) do
    begin
        v:=(l shl 1);
        if ((v<hsize) and (heap[v,0]>heap[v+1,0])) then inc(v);
        if (heap[l,0]>heap[v,0]) then
        begin
            xch(v,l);
        end else break;
        l:=v;
    end;
end;
// funkcja do przepychania elementu w dol stogu

procedure heapadd(val,key:longint);
begin
    inc(hsize);
    heap[hsize,0]:=val;
    heap[hsize,1]:=key;
    gdzie[key]:=hsize;
    heapup(hsize);
end;
// funkcja do dodawania do stogu elementu o wartosci val i kluczu key

procedure heapdelete(key:longint);
begin
    gdzie[heap[hsize,1]]:=gdzie[key];
    heap[gdzie[key],0]:=heap[hsize,0];
    heap[gdzie[key],1]:=heap[hsize,1];
    dec(hsize);
    heapdown(gdzie[key]);
end;
// funkcja do wyrzucania ze stogu elementu o kluczu key

begin
    readln(n,p,q,x,y);
    h:=0;
    height[0]:=0;
    hsize:=1;
    heap[1][0]:=0;
    heap[1][1]:=0;
    gdzie[0]:=1;
    for i:=0 to n-1 do
    begin
        read(ch);
        if (ch='+') then inc(h) else dec(h);
        height[i+1]:=h;
        heapadd(h,i+1);
        input[i]:=ch;
    end;
    // przetworzenie slowa
    opt:=inf;
    for i:=n to 2*n-1 do
    begin
        if (input[i-n]='+') then inc(h) else dec(h);
        heapdelete(i-n);
        heapadd(h,i+1);
        mn:=p+heap[1][0]-height[i-n+1];
        // obliczenie minimalnej wysokosci bilansu
        ii:=i-n+1;
        if (mn>0) then M:=0 else M:=-mn;
        inc(M,(M mod 2));
        if (q-p>height[n]+M) then
            k:=((q-p-height[n]) div 2)
        else
            k:=M+((height[n]-(q-p)) div 2);
        // obliczenie liczby potrzebnych zmian znaku
        r:=y*(n-ii)+x*k;
        if (r<opt) then opt:=r;
        //aktualizacja optimum
    end;
    writeln(opt);
end.
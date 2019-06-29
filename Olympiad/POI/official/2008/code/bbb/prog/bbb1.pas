(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbb1.pas                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowy, zlozonosc O(n). Implementacja       *
 *             w Pascalu.                                                *
 *                                                                       *
 *************************************************************************)

program bbb;
const MAX=1100000;
const inf=2000*1000*1000+100;

var
    height:array[0..MAX] of longint;                // wysokosci bilansu na koncie
    min_prefix:array[0..MAX] of longint;        // minima w prefiksach
    min_sufix:array[0..MAX] of longint;                // minima w sufiksach
    n,p,q,x,y,h,min,k,l_pre,l_suf,opt,r:longint;
    { min - znalezione minimum (do interacji do min_prefix i min_sufix)
      opt - znalezione optimum
      l_pre,l_suf - minima po zamianie cyklicznej odpowiednio w sufiksie i prefiksie
      h - aktualna wysokosc balansu w czasie przetwarzania }
    ch:char;
    i:longint;

begin
    readln(n,p,q,x,y);
    h:=0;
    height[0]:=0;
    for i:=1 to n do
    begin
        read(ch);
        if (ch='+') then inc(h) else dec(h);
        height[i]:=h;
    end;
    // wypelnianie wysokosci
    min:=inf;
    for i:=0 to n do
    begin
        if (min>height[i]) then min:=height[i];
        min_prefix[i]:=min;
    end;
    min:=inf;
    for i:=n downto 0 do
    begin
        if (min>height[i]) then min:=height[i];
        min_sufix[i]:=min;
    end;
    // wypelnianie min_prefix i min_sufix
    opt:=inf;
    for i:=1 to n do
    begin
        l_suf:=(height[i]-min_sufix[i])-p;
        if (l_suf<0) then l_suf:=0;
        l_pre:=(-min_prefix[i])+(height[i]-height[n])-p;
        if (l_pre<0) then l_pre:=0;
        if (l_suf<l_pre) then l_suf:=l_pre;
        // w l_suf jest zapisane a z algorytmu wzorcowego
        inc(l_suf,l_suf mod 2);
        if (q-p>height[n]+l_suf) then
            k:=((q-p-height[n]) div 2)
        else
            k:=l_suf+((height[n]-(q-p)) div 2);
        // obliczenie liczby potrzebnych zmian znaku
        r:=y*(n-i)+x*k;
        if (r<opt) then opt:=r;
        //aktualizacja optimum
    end;
    writeln(opt);
end.
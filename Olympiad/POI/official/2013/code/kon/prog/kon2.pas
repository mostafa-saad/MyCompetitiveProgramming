(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Konewka                                       *
 *   Autor:                Michal Adamczyk                               *
 *   Zlozonosc czasowa:    O((n + q) log n)                              *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         A - drzewo potegowe                           *
 *                         B - drzewo przedzialowe                       *
 *                                                                       *
 *************************************************************************)

unit kon;

interface

    procedure inicjuj(n, k : LongInt; var D : array of LongInt);

    procedure podlej(a, b : LongInt);

    function dojrzale(a, b : LongInt) : LongInt;

implementation

    const maxn = 300001;
    const infty = 1000*1000*1000;
    const M = 524288;

    var
        NN, KK : LongInt;
        dd : array[0..2*maxn] of LongInt; {drzewa dojrzale}
        nd_w : array[0..2*M] of LongInt; {drzewa niedojrzale - wartosc w wezle}
        nd_max : array[0..2*M] of LongInt; {drzewa niedojrzale - max z synow + wartosc dla wezla}

    {operacje na drzewach dojrzalych - drzewo potegowe}

    function magia(x : LongInt) : LongInt;
    begin
        magia := x - (x and (x-1));
    end;

    function suma(x : LongInt) : LongInt;
    begin
        suma := 0;
        inc(x);
        while x>0 do
        begin
            inc(suma, dd[x]);
            dec(x,magia(x));
        end;
    end;

    {wstawia drzewo o numerze x}
    procedure wstawDojrzale(x : LongInt);
    begin
        inc(x);
        while x <= 2*maxn do
        begin
            inc(dd[x]);
            x := x + magia(x);
        end
    end;

    {zwraca liczbe dojrzalych drzew na przedziale [a, b]}
    function ileDojrzalych(a, b : LongInt) : LongInt;
    begin
        ileDojrzalych := suma(b) - suma(a-1);
    end;

    {operacje na drzewach niedojrzalych}

    procedure przesun_nizej(v : LongInt);
    begin
        inc(nd_w[2*v], nd_w[v]);
        inc(nd_w[2*v+1], nd_w[v]);
        inc(nd_max[2*v], nd_w[v]);
        inc(nd_max[2*v+1], nd_w[v]);
        nd_w[v] := 0;
    end;

    {ustaw wysokosc drzewa a na x}
    procedure ustawWysokosc(a, x : LongInt);
    var
        v : LongInt;
    begin
        v := M + a;
        nd_w[v] := x;
        nd_max[v] := x;
        while v <> 1 do
        begin
            v := v div 2;
            if nd_max[2*v] > nd_max[2*v+1] then
                nd_max[v] := nd_w[v] + nd_max[2*v]
            else
                nd_max[v] := nd_w[v] + nd_max[2*v+1];
        end
    end;

    {zwieksza o jeden wysokosc drzew na przedziale [p, k]}
    procedure zwieksz(v, p, k, p_b, k_b : LongInt);
    var
        m : LongInt;
    begin
        {writeln('zwieksz ',v);}
        if ((k < p_b) or (k_b < p) or (p_b > k_b)) then
            exit;

        if ((p <= p_b) and (k_b <= k)) then
        begin
            inc(nd_w[v]);
            inc(nd_max[v]);
            exit;
        end;

        if (nd_w[v] > 0) then
            przesun_nizej(v);

        m := (p_b + k_b) div 2;
        zwieksz(2*v, p, k, p_b, m);
        zwieksz(2*v+1, p, k, m+1, k_b);

        if nd_max[2*v] > nd_max[2*v+1] then
            nd_max[v] := nd_w[v] + nd_max[2*v]
        else
            nd_max[v] := nd_w[v] + nd_max[2*v+1];
    end;

    {znajduje dojrzale drzewa wśród niedojrzalych (na przedziale [p, k])
     dodaje je do struktury dla drzew dojrzalych oraz "usuwa" spośróð niedojrzaych,
     ustawiajac ich wysokosc na -infty.}
    procedure znajdzDojrzale(v, p, k, p_b, k_b : LongInt);
    var
        m : LongInt;
    begin
        if ((nd_max[v] < KK) or (k < p_b) or (k_b < p) or (p_b > k_b)) then
            exit;

        if (p_b = k_b) then
        begin
            wstawDojrzale(p_b);
            ustawWysokosc(p_b, -infty);
            exit;
        end;

        if (nd_w[v] > 0) then
            przesun_nizej(v);

        m := (p_b + k_b) div 2;
        znajdzDojrzale(2*v, p, k, p_b, m);
        znajdzDojrzale(2*v+1, p, k, m+1, k_b);
    end;

    procedure inicjuj(n, k : LongInt; var D : array of LongInt);
    var
        i : LongInt;
    begin
        NN := n; KK := k;
        for i := 0 to NN-1 do
            ustawWysokosc(i, D[i]);
    end;

    procedure podlej(a, b : LongInt);
    begin
        zwieksz(1, a, b, 0, M-1);
    end;

    function dojrzale(a, b : LongInt) : LongInt;
    begin
        znajdzDojrzale(1, a, b, 0, M-1);
        dojrzale := ileDojrzalych(a, b);
    end;

begin
end.

(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Konewka                                       *
 *   Autor:                Michal Adamczyk                               *
 *   Zlozonosc czasowa:    O(q * n)                                      *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

unit kon;

interface

    procedure inicjuj(n, k : LongInt; var D : array of LongInt);

    procedure podlej(a, b : LongInt);

    function dojrzale(a, b : LongInt) : LongInt;

implementation

    const maxn = 300000;

    var
        NN, KK : LongInt;
        t : array[0..maxn] of LongInt;

    procedure inicjuj(n, k : LongInt; var D : array of LongInt);
    var
        i : LongInt;
    begin
        NN := n; KK := k;
        for i := 0 to NN-1 do
            t[i] := D[i];
    end;

    procedure podlej(a, b : LongInt);
    var
        i : LongInt;
    begin
        for i:=a to b do
            inc(t[i]);
    end;

    function dojrzale(a, b : LongInt) : LongInt;
    var
        i : LongInt;
    begin
        dojrzale := 0;
        for i:=a to b do
            if t[i] >= KK then
                inc(dojrzale);
    end;

begin
end.

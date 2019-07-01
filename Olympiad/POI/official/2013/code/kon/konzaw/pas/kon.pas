unit kon;

interface

    procedure inicjuj(n, k : LongInt; var D : array of LongInt);

    procedure podlej(a, b : LongInt);

    function dojrzale(a, b : LongInt) : LongInt;

implementation

    var
        N, K : LongInt;
        t : array[0..300000] of LongInt;

    procedure inicjuj(n, k : LongInt; var D : array of LongInt);
    var
        i : LongInt;
    begin
        N := n; K := k;
        for i := 0 to n-1 do
            t[i] := D[i];
    end;

    procedure podlej(a, b : LongInt);
    begin
        inc(t[a]);
        inc(t[b]);
    end;

    function dojrzale(a, b : LongInt) : LongInt;
    begin
        dojrzale := 0;
        if (t[a] >= K) then inc(dojrzale);
        if (t[b] >= K) then inc(dojrzale);
        { cos glupiego }
    end;

begin
end.

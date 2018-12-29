(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MIS (Misie)                                    *
 *   Plik:                mis1.pas                                       *
 *   Autor:               Szymon Acedañski                               *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                                                                       *
 *************************************************************************)

program mis;
const
    AA1 = 0;
    AA2 = 1;
    BB1 = 2;
    BB2 = 3;
    MODULO = 1000000;


type
    tt = array [0..1,0..42,0..42,0..42,0..3,0..3] of longint;
    hh = array [0..2,0..2,0..2,0..2,0..3,0..3] of longint;

var
    h: hh;
    t: tt;

function theT(a1, a2, b1, b2, x, y: longint): longint;
var sum: longint;
begin
    if (a1 < 0) or (a2 < 0) or (b1 < 0) or (b2 < 0) then
        theT := 0
    else begin
        sum := a1 + a2 + b1 + b2;
        if sum <= 2 then
            theT := h[a1,a2,b1,b2,x,y]
        else
            theT := t[a1 mod 2,a2,b1,b2,x,y];
    end;
end;

function bad(i, j, k: longint): boolean;
begin
    bad := ((((i and 1) = (j and 1)) and ((j and 1) = (k and 1)))
        or (((i and 2) = (j and 2)) and ((j and 2) = (k and 2))));
end;

function iv(a: boolean): longint;
begin
    if a then
        iv := 1
    else
        iv := 0
end;

procedure calc(a1, a2, b1, b2: longint);
var alt, i, j, k: longint;
begin
    alt := a1 mod 2;
    for i := 0 to 3 do for j := 0 to 3 do begin
        t[alt,a2,b1,b2,i,j] := 0;
        for k := 0 to 3 do
            if not bad(i, j, k) then
                t[alt,a2,b1,b2,i,j] :=
                    ( t[alt,a2,b1,b2,i,j] +
                    theT(a1 - iv(j=AA1), a2 - iv(j=AA2), b1 - iv(j=BB1), b2 - iv(j=BB2), k, i) )
                    mod MODULO;
    end;
end;

procedure main;
var a1, a2, b1, b2, i, j, k, l, sum: longint;
begin
    for i := 0 to 3 do for j := 0 to 3 do
        h[iv(i=AA1) + iv(j=AA1),iv(i=AA2) + iv(j=AA2),iv(i=BB1) + iv(j=BB1),iv(i=BB2) + iv(j=BB2),i,j] := 1;

    read(a1); read(a2); read(b1); read(b2);
    if a1 + a2 + b1 + b2 = 1 then begin
        writeln(1);
        exit;
    end;

    for i := 0 to a1 do for j := 0 to a2 do for k := 0 to b1 do for l := 0 to b2 do
        calc(i,j,k,l);

    sum := 0;
    for i := 0 to 3 do for j := 0 to 3 do
        sum := sum + theT(a1,a2,b1,b2,i,j);

    writeln(sum mod MODULO);
end;

begin
    main;
end.

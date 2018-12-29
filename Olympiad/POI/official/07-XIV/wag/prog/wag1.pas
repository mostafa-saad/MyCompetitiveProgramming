{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wag1.pas                                                   *}
{*   Autor:   Szymon Acedanski                                           *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*                                                                       *}
{*************************************************************************}
program Wag;
var
    x, y, dig, l, i: LongInt;
    digits: array [0..5000] of LongInt;
    num: array[0..1100] of LongInt;
    s: ansistring;
    xw, yw: Int64;
function div4(): LongInt;
var i, r: LongInt;
begin
    r := 0;
    for i := 999 downto 0 do begin
        r := r*100000000 + num[i];
        num[i] := r div 4;
        r := r mod 4;
    end;
    div4 := r;
end;
begin
    dig := 0;
    x := 0;
    y := 1;
    xw := 1;
    yw := 1;
    readln(s);
    l := length(s);
    for i := 0 to 1000 do
        num[i] := 0;
    for i := 0 to l-1 do begin
        num[(l-i-1) div 8] := num[(l-i-1) div 8]*10 + ord(s[i+1]) - ord('0');
    end;

    for i := 0 to 2999 do begin
        digits[dig] := div4();
        dig := dig + 1
    end;

    while dig >= 1 do begin
        dig := dig-1;
        if digits[dig] = 0 then begin
            y := x+1;
            yw := xw;
        end else if digits[dig] = 1 then begin
            if x < y then begin
                y := x+2;
                yw := xw;
            end else if x = y then begin
                y := y + 2;
                yw := (yw + xw) mod 1000000000;
            end else begin
                y := y + 2;
            end;
            x := x + 1;
        end else if digits[dig] = 2 then begin
            if x < y then begin
                x := x + 2;
            end else if x = y then begin
                x := x + 2;
                xw := (xw + yw) mod 1000000000;
            end else begin
                x := y + 2;
                xw := yw;
            end;
            y := y + 1;
        end else if digits[dig] = 3 then begin
            x := y + 1;
            xw := yw;
        end else begin
            writeln('invalid digit', digits[dig], dig);
            halt(1);
        end;
    end;
    writeln(xw);
end.

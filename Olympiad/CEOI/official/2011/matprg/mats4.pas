(*
 * Task: Matching
 *  Pascal version of inefficient solution 3
 *  O(m n^2)
 * Author: Jakub Lacki
 *)

const MAXNM=1000000;

type Ttab = array[0..MAXNM-1] of longint;

function good_match(const pattern : Ttab; length : longint; const ttext : Ttab; text_offset : longint) : boolean;

var i, j : longint;

begin
    for i:=1 to length - 1 do
        for j:=0 to length-i-1 do
            if ((pattern[j] < pattern[j+i]) <> (ttext[j+text_offset] < ttext[j+i+text_offset])) then
            exit(false);
    good_match := true;
end;

var n, m, i, x, matches_count : longint;
    pattern, ttext, matches : Ttab;

begin
    read(n, m);
    for i:=0 to n-1 do begin
        read(x);
        pattern[x-1] := i;
    end;

    for i:=0 to m-1 do
        read(ttext[i]);

    matches_count := 0;
    for i:=0 to m-n do begin
        if good_match(pattern, n, ttext, i) then begin
            matches[matches_count] := i;
            inc(matches_count);
        end;
    end;

    writeln(matches_count);
    for i:=0 to matches_count-1 do begin
        write(matches[i]+1);
        if i+1 < matches_count then
            write(' ');
        end;
    writeln;
end.


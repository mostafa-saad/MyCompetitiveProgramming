(*
 * Task: Matching
 *  Pascal version of inefficient solution 5
 *  O(mn)
 * Author: Jakub Lacki
 *)

const MAXNM=1000000;

type Ttab = array[0..MAXNM-1] of longint;

function good_match(const pattern : Ttab; length : longint; const ttext : Ttab; text_offset : longint) : boolean;

var i : longint;

begin
    for i:=0 to length - 2 do
        if ttext[pattern[i]+text_offset] > ttext[pattern[i+1]+text_offset] then
            exit(false);
    good_match := true;
end;

var n, m, i, matches_count : longint;
    pattern, ttext, matches : Ttab;

begin
    read(n, m);
    for i:=0 to n-1 do begin
        read(pattern[i]);
        dec(pattern[i]);
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


(*
 * Task: Matching
 *  Model solution in Pascal
 *  O(n + m)
 * Author: Jakub Lacki
 *)

const MAXNM = 1000000;

type Ttab = array[0..MAXNM-1] of longint;


var prev, next,where_is : Ttab;

procedure bigger_and_smaller(const tab : Ttab; n : longint; var bigger, smaller : Ttab);
var        i, x : longint;
begin
    for i:=0 to n-1 do begin
        next[i] := i+1;
        prev[i] := i-1;
        where_is[tab[i]] := i;
    end;

    for i:=n-1 downto 0 do begin
        x := tab[i];
        if next[x] = n then
            bigger[i] := -1
        else
            bigger[i] := where_is[next[x]];

        if prev[tab[i]] = -1 then
            smaller[i] := -1
        else
            smaller[i] := where_is[prev[x]];

        if prev[x] <> -1 then
            next[prev[x]] := next[x];

        if next[x] <> n then
            prev[next[x]] := prev[x];
    end;
end;

function kmp_equal(const ttext, bigger, smaller : Ttab; a, b : longint) : boolean;
begin
    if (bigger[a] <> -1) and (ttext[b] > ttext[b-(a-bigger[a])]) then
        kmp_equal := false
    else if (smaller[a] <> -1) and (ttext[b] < ttext[b-(a-smaller[a])]) then
        kmp_equal := false
    else
        kmp_equal := true;
end;



var p, bigger, smaller : Ttab;



function kmp(const pattern : Ttab; n : longint;
        const ttext : Ttab; m : longint;
        var matches : Ttab) : longint;
    var i, matched_characters, matches_count : longint;
begin
    bigger_and_smaller(pattern, n, bigger, smaller);

    
    p[0] := 0;

    for i:=1 to n-1 do begin
        matched_characters := p[i-1];
        while (matched_characters > 0) and (not kmp_equal(pattern, bigger, smaller, matched_characters, i)) do
            matched_characters := p[matched_characters-1];

        if kmp_equal(pattern, bigger, smaller, matched_characters, i) then
            inc(matched_characters);

        p[i] := matched_characters;
    end;

    matched_characters := 0;
    matches_count := 0;
    for i:=0 to m-1 do begin
        while (matched_characters > 0) and (not kmp_equal(ttext, bigger, smaller, matched_characters, i)) do
            matched_characters := p[matched_characters-1];

        if kmp_equal(ttext, bigger, smaller, matched_characters, i) then
            inc(matched_characters);

        if matched_characters = n then begin
            matches[matches_count] := i - n + 1;
            inc(matches_count);
            matched_characters := p[matched_characters-1];
        end;
    end;
    kmp := matches_count;
end;

var n, m, i, x, nmatches : longint;
    pattern, ttext, matches : Ttab;

begin
    read(n, m);
    readln;
    for i:=0 to n-1 do begin
        read(x);
        pattern[x-1] := i;
    end;

    for i:=0 to m-1 do
        read(ttext[i]);
    
    nmatches := kmp(pattern, n, ttext, m, matches);

    writeln(nmatches);

    for i:=0 to nmatches-1 do begin
        write(matches[i]+1);
        if i+1 < nmatches then
            write(' ');
    end;
    writeln;
end.

    

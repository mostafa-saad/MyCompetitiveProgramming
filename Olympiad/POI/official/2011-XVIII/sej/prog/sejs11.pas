(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Pawel Parys                                      *
 *   Zlozonosc czasowa: O(k*nwd(n, m_k))                                 *
 *   Opis:              Rozwiazanie bardzo powolne                       *
 *                      brutalnie probuje wszystkie liczby po kolei      *
 *                                                                       *
 *************************************************************************)

var 
    a, k : longint;
    d, n : int64;
    m : array[0..250000] of int64;
    ok : boolean;

begin
    readln(n, k);
    for a := 0 to k-1 do 
        read(m[a]);
    d := 1; { nie da sie zrobic petli po int64, wiec while } 
    while d<=n do begin
        if ((n mod d)>0) or ((m[k-1] mod d)>0) then begin
            inc(d);
            continue;
        end;
        ok := true;
        for a := 0 to k-2 do 
            if (m[a] mod d)=0 then begin
                ok := false;
                break;
            end;
        if ok then begin 
            writeln(n div d);
            halt;
        end;
        inc(d);
    end;
end.

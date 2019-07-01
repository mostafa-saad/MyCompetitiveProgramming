(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Konewka                                       *
 *   Autor:                Michal Adamczyk                               *
 *   Opis:                 Program oceniajacy                            *
 *                                                                       *
 *************************************************************************)

uses kon;

(* Funny names in order to avoid duplicate identifiers with the
* contestant's variables. *)
procedure jdS9d1wS;
const MAGIC = 873454312; {stala dla kazdego programu}
MAGIC3 = 908903022; {ostatnia liczba w kazdym tescie}
const maxn = 300000;

var
    num_calls, i, a, b, call, magic2 : LongInt;
    n, k : LongInt;
    D : array[0..maxn] of LongInt;

begin
    ReadLn(n, k, magic2);
    magic2 := magic2 xor MAGIC;
    n := n xor magic2;
    k := k xor magic2;
    for i := 0 to n-1 do
    begin
        Read(D[i]);
        D[i] := D[i] xor magic2;
    end;

    inicjuj(n, k, D);
    ReadLn(num_calls);
    num_calls := num_calls xor magic2;
    for i := 1 to num_calls do
    begin
        ReadLn(call, a, b);
        call := call xor magic2 xor (i+1);
        a := a xor magic2;
        b := b xor magic2;
        if call = 0 then
            podlej(a, b)
        else
            WriteLn(dojrzale(a, b) xor magic2);
    end;
    ReadLn(magic2);
    if magic2 <> MAGIC3 then
    begin
        WriteLn('WRONG: rozwiazanie czytalo dane wejsciowe');
        Halt(1);
    end;
end;

begin
    jdS9d1wS;
end.

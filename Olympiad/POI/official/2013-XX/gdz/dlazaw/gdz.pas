{ gdz.pas - Przykladowe uzycie biblioteki do zadania GDZ }
program gdz;

uses pgdzlib;

var i, n, mini : LongInt;

begin
    n := inicjuj();
    mini := 1;
    for i := 2 to n do
        if g(mini, i) = 1 then
            mini := i;
    odpowiedz(mini);
end.


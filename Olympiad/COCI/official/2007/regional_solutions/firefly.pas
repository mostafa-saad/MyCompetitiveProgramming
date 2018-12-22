
(*
  Croatian Regional Competition in Informatics 2007
  Task FIREFLY
  Programming language Pascal
*)

program buba;

const MAXH = 500000;

var
   i, n, h, duljina                           : longint;
   najmanjePrepreka, brojNacina, brojPrepreka : longint;
   gore, dolje                                : array[1..MAXH] of longint;

begin

    readln(n, h);

    for i:=1 to h do
    begin
        gore[i]:=0;
        dolje[i]:=0;
    end;

    for i:=1 to n div 2 do
    begin
        readln(duljina);
        inc(dolje[duljina]);
        readln(duljina);
        inc(gore[duljina]);
    end;

    for i:=h-2 downto 1 do
    begin
        gore[i] := gore[i] + gore[i+1];
        dolje[i] := dolje[i] + dolje[i+1];
    end;

    najmanjePrepreka := n;
    brojNacina := 0;

    for i:=1 to h do
    begin
        brojPrepreka := dolje[i] + gore[h-i+1];
        if brojPrepreka < najmanjePrepreka then
        begin
            najmanjePrepreka := brojPrepreka;
            brojNacina := 1;
        end else
            if brojPrepreka = najmanjePrepreka then
                inc(brojNacina);
    end;

    writeln(najmanjePrepreka, ' ', brojNacina);

end.

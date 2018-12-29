(*
  Croatian Olympiad in Informatics 2007
  Task PATRIK
*)

const MAX = 500000;
var n, i, height, top : longint;
    stack : array[1..MAX] of longint;
    howmany : array[0..MAX] of longint;
    solution : int64;    
begin
    readln(n);
    for i:=1 to n do
    begin        
        readln(height);
        while (top>0)and(stack[top]<height) do 
        begin
            solution := solution + howmany[top];
            dec(top);
        end;
        if (top>0)and(stack[top]=height) then
        begin
            solution := solution + howmany[top];
            inc(howmany[top]);
            if top>1 then inc(solution);
        end else
        begin
            if top>0 then inc(solution);
            inc(top);
            howmany[top]:=1;            
            stack[top]:=height;
        end;
    end;    
    writeln(solution);
end.

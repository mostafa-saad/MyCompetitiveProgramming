program mjehuric;

var 
    a        : array[1..5] of longint;
    i, j, t  : longint;
    promjena : boolean;
    
begin
    for i:=1 to 5 do
        read(a[i]);
        
    repeat
        promjena := false;
        for i:=2 to 5 do
            if a[i-1] > a[i] then begin
                promjena := true;
                t := a[i-1]; a[i-1] := a[i]; a[i] := t;
                
                for j:=1 to 5 do begin
                    if j > 1 then write(' ');
                    write(a[j]);
                end;
                writeln;
            end;
    until not promjena;
end.

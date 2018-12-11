unit koala;

interface
    function minValue(N, W: longint) : longint;
    function maxValue(N, W: longint) : longint;
    function greaterValue(N, W : longint) : longint;
    procedure allValues(N, W : longint; P : array of longint);

implementation
    uses graderlib;

    const
        MAX_N = 105;

    var
        B, R : array[0..MAX_N] of longint;

    function minValue(N, W: longint) : longint;
    begin
        { TODO: Implement Subtask 1 solution here. }
        { You may leave this function unmodified if you are not attempting this
        subtask. }
        minValue := 0;
    end;

    function maxValue(N, W: longint) : longint;
    begin
        { TODO: Implement Subtask 2 solution here. }
        { You may leave this function unmodified if you are not attempting this
        subtask. }
        maxValue := 0;
    end;

    function mini(N, W, num : longint; var g : longint) : longint;
    var
        i : longint;
    begin
        for i := 2 to N - 1 do
            B[i] := 0;
        B[0] := num;
        B[1] := num;
        playRound(B, R);
        mini := 0;
        if R[0] > B[0] then Inc(mini);
        if R[1] > B[1] then Inc(mini);
        if mini = 1 then
            if R[0] > B[0] then
                g := 0
            else
                g := 1;
    end;

    function greaterValue(N, W : longint) : longint;
    var
        a : longint;
    begin
        { TODO: Implement Subtask 3 solution here. }
        { You may leave this function unmodified if you are not attempting this
        subtask. }
        a := mini(N, W, 6, greaterValue);
        if a = 0 then
            begin
                a := mini(N, W, 3, greaterValue);
                if a = 0 then
                    a := mini(N, W, 1, greaterValue)
                else if a <> 1 then
                    begin
                        Writeln('FIRST something went wrong! a=', a);
                        halt(1);
                    end;
            end
        else if a = 2 then
            begin
                a := mini(N, W, 8, greaterValue);
                if a <> 1 then
                    begin
                        Writeln('SECOND something went wrong! a=', a);
                        halt(1);
                    end;
            end
        else if a <> 1 then
            begin
                Writeln('LAST something went wrong! a=', a);
                halt(1);
            end;
    end;

    procedure allValues(N, W : longint; P : array of longint);
    begin
        if W = 2*N then
            begin
                { TODO: Implement Subtask 4 solution here. }
                { You may leave this block unmodified if you are not attempting
                this subtask. }
            end
        else
            begin
                { TODO: Implement Subtask 5 solution here. }
                { You may leave this block unmodified if you are not attempting
                this subtask. }
            end;
    end;

end.

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
    var
        i : longint;
    begin
        { TODO: Implement Subtask 1 solution here. }
        { You may leave this function unmodified if you are not attempting this
        subtask. }
        for i := 1 to N - 1 do
            B[i] := 0;
        B[0] := 1;
        playRound(B, R);

        for i := 0 to N - 1 do
            if R[i] <= B[i] then minValue := i;
    end;

    function maxValue(N, W: longint) : longint;
    begin
        { TODO: Implement Subtask 2 solution here. }
        { You may leave this function unmodified if you are not attempting this
        subtask. }
        maxValue := 0;
    end;

    function greaterValue(N, W : longint) : longint;
    begin
        { TODO: Implement Subtask 3 solution here. }
        { You may leave this function unmodified if you are not attempting this
        subtask. }
        greaterValue := 0;
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

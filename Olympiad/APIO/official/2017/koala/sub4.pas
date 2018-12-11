unit koala;

interface
    function minValue(N, W: longint) : longint;
    function maxValue(N, W: longint) : longint;
    function greaterValue(N, W : longint) : longint;
    procedure allValues(N, W : longint; var P : array of longint);

implementation
    uses graderlib;

    const
      MAX_N = 105;

    var
      NN : longint;

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

    function greaterValue(N, W : longint) : longint;
    begin
        { TODO: Implement Subtask 3 solution here. }
        { You may leave this function unmodified if you are not attempting this
        subtask. }
        greaterValue := 0;
    end;

    function compare(c, d : longint) : boolean;
    var
      i : longint;
      B, R : array[0..MAX_N] of longint;
    begin
      for i := 0 to NN - 1 do B[i] := 0;
      B[c] := NN;
      B[d] := NN;
      playRound(B, R);
      compare := (R[d] > B[d]);
    end;

    procedure mergeSort(var nums : array of longint; l, r : longint);
    var
      mid, ul, ur, i : longint;
      out : array[0..MAX_N] of longint;
    begin
      if r - l > 1 then
      begin
        mid := (l + r) div 2;
        mergeSort(nums, l, mid);
        mergeSort(nums, mid, r);
        ul := l;
        ur := mid;

        i := l;
        while (ul < mid) and (ur < r) do
        begin
          if compare(nums[ul], nums[ur]) then
            begin
              out[i] := nums[ul];
              Inc(ul);
            end
          else
            begin
              out[i] := nums[ur];
              Inc(ur);
            end;
          Inc(i);
        end;

        while ul < mid do
        begin
          out[i] := nums[ul];
          Inc(i);
          Inc(ul);
        end;

        while ur < r do
        begin
          out[i] := nums[ur];
          Inc(i);
          Inc(ur);
        end;

        for i := l to r - 1 do
        begin
          nums[i] := out[i];
        end;
      end;
    end;

    procedure allValues(N, W : longint; var P : array of longint);
    var
      i : longint;
      nums : array[0..MAX_N] of longint;
    begin
      NN := N;
        if W = 2*N then
            begin
                { TODO: Implement Subtask 4 solution here. }
                { You may leave this block unmodified if you are not attempting
                this subtask. }
                for i := 0 to N - 1 do nums[i] := i;
                mergeSort(nums, 0, N);
                for i := 0 to N - 1 do P[nums[i]] := i + 1;
            end
        else
            begin
                { TODO: Implement Subtask 5 solution here. }
                { You may leave this block unmodified if you are not attempting
                this subtask. }
            end;
    end;

end.

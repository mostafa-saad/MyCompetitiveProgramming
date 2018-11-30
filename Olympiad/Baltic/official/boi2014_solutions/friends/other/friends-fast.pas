program friends;


var N, NN : longint;
    s, s1, s2 : ansistring;


function substr (s : ansistring; pr, c : longint) : ansistring;
begin
    substr := copy(s,pr,c);
end;

function checkIt (pr1, pb1, pr2, pb2 : longint) : ansistring;
  var x, y, times : longint;
begin
  times := 0;
  x := pr1; y := pr2;
  while (x <= pb1) and (y <= pb2) do begin
    //writeln(s[x], ' ', s[y]);
    if (s[x] = s[y]) then begin
        inc(x); inc(y);
    end else begin
        inc(y); inc (times);
    end;
  end;
  //writeln('times = ', times);
  if (times > 1) then
    checkIt := ''
  else
    checkIt :=  substr(s, pr1, pb1 - pr1 + 1);
end;




begin

    Readln(N);
    Readln(s);
    if (N mod 2 = 0) then
        Writeln('NOT POSSIBLE')
    else begin
        NN := N div 2;
        //Writeln('NN = ', NN);
        s1 := checkIt(1, NN, NN + 1, N);
        s2 := checkIt(NN + 2, N, 1, NN+1);
        //Writeln (copy(s, 1, NN - 1 + 1)) ;
        //writeln(s);
       // Writeln (copy(s, NN+2, N - (NN+2) + 1))    ;
       // Writeln(s1);
      //  Writeln(s2);
        if (s1 = '') and (s2 = '') then
            Writeln('NOT POSSIBLE')
        else if (s1 = '') then
            Writeln(s2)
        else if (s2 = '') then
            Writeln(s1)
        else if (s1 <> s2) then
            Writeln('NOT UNIQUE')
        else Writeln(s1);
    end;

end.

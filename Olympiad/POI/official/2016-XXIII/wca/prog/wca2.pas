(******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Wcale nie Nim                                      *
 *   Autor programu:       Pawel Parys                                        *
 *   Opis:                 Rozwiazanie wzorcowe weryfikujace                  *
 *****************************************************************************)

var N, i, suma, najw, x, ile1 : longint;
    tyle1 : array[0..39] of longint;

procedure find_max;
begin
  while (tyle1[najw]=0) do
    dec(najw);
end;

begin
  readln(N);
  suma := N-1;
  for i := 0 to 39 do tyle1[i] := 0;
  for i := 0 to N-1 do begin
    ile1 := 0;
    read(x);
    while (x>0) do begin
      inc(suma);
      if (x and 1)>0 then 
        inc(ile1)
      else
        ile1 := 0;
      x := x div 2;
    end;
    inc(tyle1[ile1]);
  end;
  najw := 39;
  find_max;
  dec(tyle1[najw]);
  for i := 0 to N-2 do begin
    find_max;
    if najw>1 then begin
      dec(tyle1[najw]);
      inc(tyle1[najw-1]);
      find_max;
      dec(tyle1[najw]);
    end
    else begin
      dec(tyle1[najw]);
      dec(suma);
    end
  end;
  writeln(suma*2+1);
end.

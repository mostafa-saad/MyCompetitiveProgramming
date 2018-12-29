(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Tomasz Syposz                                 *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

const
  X = 660;
var
  n:longint;
  p:array[1..10000100] of longint;
  dziel:array[0..1000000] of longint;
  a:longint;
  b:longint;
  c:longint;
  d:longint;
  i:longint;
  i1:longint;
  j:longint;
  k:longint;
  temp:longint;
  odp:longint;
  q1:longint;
  q2:longint;

PROCEDURE dzielniki(d:longint);
var pi:longint;
        cur:longint;
    ost:longint;
begin
  if d = 1 then
  begin
    exit
  end;
  ost:= dziel[0]+1;
  while d > 1 do
  begin
    pi := p[d];
    cur := 1;
    while d mod pi = 0 do
    begin
          cur := cur*pi;
      for i1 := 1 to dziel[0] do
      begin
        dziel[ost] := dziel[i1]*cur;
        ost := ost+1;
      end;
      d := d div pi;
    end;
    dziel[0] := ost-1;
  end;
end;

PROCEDURE all_dzielniki(x:longint);
begin
  dziel[0] := 1;
  dziel[1] := 1;
  dzielniki(x);
end;
  
PROCEDURE sito;
begin
  for i:= 2 to 10000010 do
  begin
    if i*i > 10000010 then
    begin
      break;
    end;
    if p[i] = 0 then
    begin
      p[i] := i;
      j:=i*i;
      while j < 10000010 do
      begin
        p[j] := i;
        j:=j+i;
      end;
    end;
  end;
  for i:= 1 to 10000010 do
  begin
    if p[i] = 0 then
    begin
      p[i] := i;
    end;
  end;
end;

begin
        sito();
        Read(n);
        for i:=1 to n do
        begin
          Read(a);
          Read(b);
          Read(c);
          Read(d);
          if b-a < X then
          begin
            odp := 0;
            for j:=a to b do
            begin
              all_dzielniki(j);
              for k:=1 to dziel[0] do
              begin
                temp :=(c div dziel[k])*dziel[k];
                if temp < c then
                        temp := temp+dziel[k];
                if temp <= d then
                  if dziel[k] > odp then
                    odp := dziel[k];
              end;
            end;
            writeLn(odp);
          end else
            if d-c < X then
            begin
              odp := 0;
            for j:=c to d do
            begin
              all_dzielniki(j);
              for k:=1 to dziel[0] do
              begin
                temp :=(a div dziel[k])*dziel[k];
                if temp < a then
                        temp := temp+dziel[k];
                if temp <= b then
                  if dziel[k] > odp then
                    odp := dziel[k];
              end;
            end;
            writeLn(odp);
            end else
              begin
                q1:=1;
                q2:=1;
                while true do
                begin
                  if (d div q2 <= b div q1) and (d div q2 >= (a+q1-1) div q1) then
                  begin
                    writeLn(d div q2);
                    break;
                  end;
                  if (b div q1 <= d div q2) and (b div q1 >= (c+q2-1) div q2) then
                  begin
                    writeLn(b div q1);
                    break;
                  end;
                  if d div q2 < a div q1 then
                  begin
                        q1 := q1+1;
                  end else q2:= q2+1;
                end;
              end;
        end;
end.

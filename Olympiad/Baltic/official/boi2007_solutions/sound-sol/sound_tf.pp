// Thomas Fersch
program sound;

const
  MAX_M = 10000;

type
  TQue = record
    isMax: Boolean;
    Start, Stop, Count: LongInt;
    Val, Pos: Array[0..MAX_M-1] of LongInt;
  end;

var
  fIn, fOut: Text;
  N, M, C, I, V: LongInt;
  None: Boolean = True;
  Min, Max: TQue;

Procedure Prev(var I: LongInt);
Begin
  Dec(I);
  if I<0 then
    I := MAX_M-1;
End;

Procedure Next(var I: LongInt);
Begin
  Inc(I);
  if I=MAX_M then
    I := 0;
End;

Procedure Clear(var Que: TQue);
Begin
  Que.Start := 1;
  Que.Stop  := 0;
  Que.Count := 0;
End;

Procedure Insert(V, I: LongInt; var Que: TQue);
begin
  with Que do begin
    while Count>0 do
      if (Val[Stop]=V) OR ((Val[Stop]>V) XOR isMax) then begin
        Dec(Count);
        Prev(Stop);
      end
      else
        break;
    Inc(Count);
    Next(Stop);
    Val[Stop] := V;
    Pos[Stop] := I;
  end;
end;

Procedure Remove(I: LongInt; var Que: TQue);
Begin
  if I=Que.Pos[Que.Start] then begin
    Dec(Que.Count);
    Next(Que.Start);
  end;
End;

begin
  (* Initialize IO *)
  Assign(fIn, 'sound.in');
  Reset(fIn);
  Assign(fOut, 'sound.out');
  Rewrite(fOut);
  (* Initialize Empty Queues *)
  Clear(Max);
  Clear(Min);
  Max.isMax:=True;
  Min.isMax:=False;
  (* Run through sequence *)
  ReadLn(fIn, N, M, C);
  for I:=1 to N do begin
    Read(fIn, V);
    if I-M>0 then begin
      Remove(I-M, Min);
      Remove(I-M, Max);
    end;
    Insert(V, I, Min);
    Insert(V, I, Max);
    (* Silence? *)
    if (I>=M) AND (Max.Val[Max.Start]-Min.Val[Min.Start]<=C) then begin
      WriteLn(fOut, I-M+1);
      None:=False;
    end;
  end;
  if None then
    WriteLn(fOut, 'NONE');
  (* Finalize IO *)
  Close(fIn);
  Close(fOut);
end.

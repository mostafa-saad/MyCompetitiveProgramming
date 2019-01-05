Program Circuit;
Const
  MaxN=101;
  Visited=16;
Type
  Node=Record x,y:Byte End;
  Table=Record HEnd,VEnd:Word; T:Array[1..MaxN*MaxN] of Node End;
Var
  N,M,MN:Word;
  G:Array[0..MaxN,0..MaxN] Of Byte;
  Disp:Table;
  Cost,OC:Word;
  OList:Array[1..MaxN*MaxN] of Record x,y,c:Byte End;

Procedure ReadIn;
Var
  InFile:Text;
  x,y,z:Byte;
Begin{ReadIn}
  Assign(InFile, 'circuit.in'); Reset(InFile);
  ReadLn(InFile, N,M);
  For x:=1 To N Do Begin
    For y:=1 To M Do Begin
      Read(InFile, z);
      G[x,y]:=z;
    End;
    ReadLn(InFile);
  End{for x};
  Close(InFile);

  For x:=0 To N+1 Do Begin
    G[x,0]:=Visited;
    G[x,M+1]:=Visited;
  End;
  For y:=0 To M+1 Do Begin
    G[0,y]:=Visited;
    G[N+1,y]:=Visited;
  End;
End{ReadIn};

Procedure WriteOut;
Var i:Integer;
  OutF:Text;
Begin{WriteOut}
  Assign(OutF, 'circuit.out'); Rewrite(OutF);
  WriteLn(OutF, OC,' ',Cost);
  For i:=1 To OC Do
    WriteLn(OutF, OList[i].x,' ',OList[i].y,' ',OList[i].c);
  Close(OutF);
End{WriteOut};

Function NotEmptyVert:Boolean;
Begin
  NotEmptyVert:=Disp.VEnd>0
End;
Function NotEmptyHoriz:Boolean;
Begin
  NotEmptyHoriz:=Disp.HEnd<=MN
End;

Procedure TakeVert(Var P:Node);
Begin{TakeVert}
  P:=Disp.T[Disp.VEnd];
  Dec(Disp.VEnd);
End{TakeVert};
Procedure TakeHoriz(Var P:Node);
Begin{TakeHoriz}
  P:=Disp.T[Disp.HEnd];
  Inc(Disp.HEnd);
End{TakeHoriz};

Procedure PutVert(Const P:Node);
Begin
  Inc(Disp.VEnd);
  Disp.T[Disp.VEnd]:=P;
End{PutVert};
Procedure PutHoriz(Const P:Node);
Begin
  Dec(Disp.HEnd);
  Disp.T[Disp.HEnd]:=P;
End{PutHoriz};

Procedure DFS(P:Node);
Var
  Q1,Q2,Q3,Q4:Node;{must be global in DOS!}
Begin{DFS}
  G[P.x,P.y]:=G[P.x,P.y]+Visited;
  Q1.x:=P.x; Q1.y:=P.y-1;
  If (G[Q1.x,Q1.y]<Visited) And (G[Q1.x,Q1.y]>1) Then
    DFS(Q1);
  Q2.x:=P.x+1; Q2.y:=P.y;
  If (G[Q2.x,Q2.y]<Visited) And Odd(G[P.x,P.y]-Visited) Then
    DFS(Q2);
  Q3.x:=P.x; Q3.y:=P.y+1;
  If (G[Q3.x,Q3.y]<Visited) And (G[P.x,P.y]-Visited>1) Then
    DFS(Q3);
  Q4.x:=P.x-1; Q4.y:=P.y;
  If (G[Q4.x,Q4.y]<Visited) And Odd(G[Q4.x,Q4.y]) Then
    DFS(Q4);

  If G[Q1.x,Q1.y]<Visited Then Begin
    PutHoriz(Q1);
  End;
  If G[Q2.x,Q2.y]<Visited Then Begin
    Q2.x:=Q2.x+N;
    PutVert(Q2);
  End;
  If G[Q3.x,Q3.y]<Visited Then Begin
    Q3.y:=Q3.y+M;
    PutHoriz(Q3);
  End;
  If G[Q4.x,Q4.y]<Visited Then Begin
    PutVert(Q4);
  End;

End{DFS};

Procedure PutOut(P:Node; c:Byte);
Begin
  Inc(Cost,c);
  Inc(OC);
  OList[OC].x:=P.x; OList[OC].y:=P.y; OList[OC].c:=c;
End;

Procedure Compute;
Var
  P,Q:Node;
Begin{Compute}
  MN:=M*N;
  Disp.VEnd:=0; Disp.HEnd:=MN+1;
  Cost:=0; OC:=0;
  P.x:=1; P.y:=1;
  DFS(P);
  While True Do Begin
    If NotEmptyVert Then Begin
      TakeVert(P);
      If P.x>N Then Begin
        P.x:=P.x-N;
        Q.x:=P.x-1;
      End Else
        Q.x:=P.x;
      If G[P.x,P.y]>=Visited Then Continue;
      Q.y:=P.y;
      PutOut(Q,1);
      DFS(P);
    End Else If NotEmptyHoriz Then Begin
      TakeHoriz(P);
      If P.y>M Then Begin
        P.y:=P.y-M;
        Q.y:=P.y-1;
      End Else
        Q.y:=P.y;
      If G[P.x,P.y]>=Visited Then Continue;
      Q.x:=P.x;
      PutOut(Q,2);
      DFS(P);
    End Else
      Break;
  End{while};
End{Compute};

Begin{program}
  ReadIn;
  Compute;
  WriteOut;
End.

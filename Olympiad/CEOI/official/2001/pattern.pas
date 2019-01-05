Program Pattern;
Const
  MaxL=20;
Var
  A,AA,B,BB:String[MaxL];
  SA,SB:Array[0..MaxL] Of Boolean;
  LA,LB:Integer;
  CC:Integer;
  P:Array[1..2*MaxL] of Char;
  T:Array[0..MaxL, 0..MaxL] of Boolean;
  OList:Array[1..1000] of String[2*MaxL];
  OLc,i,j:Integer;

Procedure ReadIn;
Var
  InFile:Text;
Begin{ReadIn}
  Assign(InFile, 'pattern.in'); Reset(InFile);
  ReadLn(InFile, A);
  ReadLn(InFile, B);
  Close(InFile);
End{ReadIn};

Procedure WriteOut;
Var i:Integer;
  OutF:Text;
Begin{WriteOut}
  Assign(OutF, 'pattern.out'); Rewrite(OutF);
  WriteLn(OutF, OLc);
  For i:=1 To OLc Do
    WriteLn(OutF, OList[i]);

  Close(OutF);
End{WriteOut};

Function Match(Const P,Q:String):Boolean;
{<=>h(P)=Q}
Var
  T:Array[0..2*MaxL, 0..2*MaxL] Of Boolean;
  LP,LQ,i,j:Integer;
Begin{Match}
  LP:=Length(P); LQ:=Length(Q);
  T[0,0]:=True;
  For i:=1 To LP Do
    T[i,0]:=(P[i]='*') And T[i-1,0];
  For j:=1 To LQ Do T[0,j]:=False;

  For i:=1 To LP Do
    For j:=1 To LQ Do
      T[i,j]:=(P[i]='*') And (T[i-1,j-1] Or T[i-1,j] Or T[i,j-1])Or
              (P[i]=Q[j]) And T[i-1,j-1];
    {for j};
  {for i};
  Match:=T[LP,LQ];
End{Match};

Procedure PutPattern;
Var i,k:Integer;
  S:String;
Begin{PutPattern}
  S:='';
  For k:=CC Downto 1 Do
    S:=S+P[k];
  If OLc=0 Then Begin
    OLc:=1; OList[1]:=S;
    Exit;
  End;
  i:=1;
  While i<=OLc Do Begin
    If Match(S, OList[i]) Then Begin
      OList[i]:=OList[OLc];
      Dec(OLc);
    End Else If Match(OList[i], S) Then Begin
      Break;
    End Else
      Inc(i);
  End{while};

  If i>OLc Then Begin
    Inc(OLc);
    OList[OLc]:=S;
  End;
End{PutPattern};

Procedure Traverse(i,j:Byte);
Begin{Traverse}
  If SA[i] And SB[j] Then Begin
    Inc(CC); P[CC]:='*';
  End;
  If (i=0)And(j=0) Then Begin
    PutPattern
  End Else Begin
    If (i>0) And SB[j] And T[i-1,j] Then Begin
      Inc(CC); P[CC]:=AA[i];
      Traverse(i-1,j);
      Dec(CC);
    End;
    If (j>0) And SA[i] And T[i,j-1] Then Begin
      Inc(CC); P[CC]:=BB[j];
      Traverse(i,j-1);
      Dec(CC);
    End;
    If (i>0) And (j>0) And T[i-1,j-1] And (AA[i]=BB[j]) Then Begin
      Inc(CC); P[CC]:=AA[i];
      Traverse(i-1,j-1);
      Dec(CC);
    End;
  End;
  If SA[i] And SB[j] Then Dec(CC);
End{Traverse};

Begin{Program}
  ReadIn;

  CC:=0; OLc:=0;

  LA:=0; SA[0]:=False;
  For i:=1 To Length(A) Do
    If A[i]='*' Then
      SA[LA]:=True
     Else Begin
       Inc(LA);
       AA[LA]:=A[i];
       SA[LA]:=False;
     End;
  LB:=0; SB[0]:=False;
  For j:=1 To Length(B) Do
    If B[j]='*' Then
      SB[LB]:=True
     Else Begin
       Inc(LB);
       BB[LB]:=B[j];
       SB[LB]:=False;
     End;

  T[0,0]:=True;
  For i:=1 To LA Do T[i,0]:=SB[0];
  For j:=1 To LB Do T[0,j]:=SA[0];
  For i:=1 To LA Do
    For j:=1 To LB Do
      T[i,j]:=T[i-1,j] And SB[j] Or
              T[i,j-1] And SA[i] Or
              T[i-1,j-1] And (AA[i]=BB[j]);

  If T[LA,LB] Then Traverse(LA, LB);

  WriteOut;
End.

Program Bitmap;
{tree + double linked list of chirdren, with path compression}
Const
  MaxN=10000;
  MaxM=1000;
Type
  STree=Array[0..MaxM] of Record
                            Rep,        {father}
                            l1,l2,      {double link}
                            Fch:Longint;{first child}
                            comp:Boolean
                          End;
Var
  InFile:Text;
  N,M:Longint;
  NComp,CComp:Longint;
  T:STree;

Procedure Init;
Var
  i:Word;
Begin{ReadIn}
  Assign(InFile, 'bitmap.in'); Reset(InFile);
  ReadLn(InFile, N,M);
  For i:=1 To M Do Begin
    T[i].Rep:=0;
    T[i].l1:=i; T[i].l2:=i;
    T[i].Fch:=0;
    T[i].comp:=True;
  End;
End{Init};

Procedure WriteOut;
Var i:Integer;
  OutF:Text;
Begin{WriteOut}
  Close(InFile);
  Assign(OutF, 'bitmap.out'); Rewrite(OutF);
  WriteLn(OutF, NComp);
  WriteLn(OutF, CComp);
  Close(OutF);
End{WriteOut};

Function SFind(x:Longint):Longint;
Var Nx,x1,x2,y1,y2,xRep:Longint;
Begin{SFind}
  If T[x].Rep=0 Then
    Nx:=0
  Else Begin
    Nx:=x;
    While T[Nx].Rep>0 Do Nx:=T[Nx].Rep;
                                       {path compression}
(*
    If (x<>Nx) And (T[x].Rep<>Nx) Then Begin
      x1:=T[Nx].Fch; x2:=T[x1].l2;
      xRep:=T[x].Rep;
      While xRep<>Nx Do Begin
        y1:=T[x].l1; y2:=T[x].l2;
        If x=T[xRep].Fch Then Begin
          If T[x].l1=x Then
            T[xRep].Fch:=0
          Else
            T[xRep].Fch:=y1;
        End;
        T[y2].l1:=y1; T[y1].l2:=y2;
        T[x2].l1:=x; T[x].l2:=x2;
        x2:=x;
        T[x].Rep:=Nx;
        x:=xRep; xRep:=T[x].Rep;
      End{while};
      T[x1].l2:=x2; T[x2].l1:=x1;
    End;
*)
  End;

  SFind:=Nx;
End{SFind};

Procedure SUnion(Var Nx:Longint; Ny:Longint);
  Var x,x1,x2,y1,y2:Longint;
Begin{SUnion}
  If Nx=Ny Then Exit;
  If T[Ny].Rep=0 Then T[Ny].Rep:=-1;
  If Nx=0 Then Begin Nx:=Ny; Exit End;

  If T[Nx].Rep>T[Ny].Rep Then Begin
    X:=Nx; Nx:=Ny; Ny:=X;
  End;
  T[Nx].Rep:=T[Nx].Rep+T[Ny].Rep;
  T[Nx].comp:=T[Nx].comp And T[Ny].comp;
  T[Ny].Rep:=Nx; T[Ny].comp:=True;
  x1:=T[Nx].Fch;
  If x1=0 Then Begin
    T[Nx].Fch:=Ny
  End Else Begin
    x2:=T[x1].l2;
    T[Ny].l1:=x1; T[x1].l2:=Ny;
    T[x2].l1:=Ny; T[Ny].l2:=x2;
  End;
End{SUnion};

Procedure SDelete(Var Nx:Longint; X:Longint);
Var xRep,Root,S:Longint;
  x1,x2,y1,y2:Longint;
  Ocomp:Boolean;
Begin{SDelete}
  S:=T[Nx].Rep;
  If S=0 Then Begin Nx:=0; Exit End;
  Ocomp:=T[Nx].comp;
  Inc(S);
  If S=0 Then Begin   {deleting last node in a component tree}
    Inc(NComp);
    If T[Nx].comp Then{compact component}
      Inc(CComp);
    T[x].Rep:=0;
    T[x].comp:=True;
    Nx:=0;
    Exit;
  End;

  If x=Nx Then Begin{x is the root}
    Root:=T[x].Fch;
    x1:=T[Root].l1;
    If x1<>Root Then Begin
      x2:=x1; T[x2].Rep:=Root;
      While T[x2].l1<>Root Do Begin
        x2:=T[x2].l1;
        T[x2].Rep:=Root;
      End;
      T[Root].l1:=Root; T[Root].l2:=Root;
      y1:=T[Root].Fch;
      If y1=0 Then Begin
        T[Root].Fch:=x1;
        T[x1].l2:=x2; T[x2].l1:=x1;
      End Else Begin
        y2:=T[y1].l2;
        T[y2].l1:=x1; T[x1].l2:=y2;
        T[y1].l2:=x2; T[x2].l1:=y1;
      End;
    End;
  End Else Begin{x is not the root}
    Root:=Nx;
    xRep:=T[x].Rep;
    x1:=T[x].l1; x2:=T[x].l2;
    y1:=T[x].Fch;
    If y1=0 Then Begin
      T[x1].l2:=x2; T[x2].l1:=x1;
      If x=x1 Then
        T[xRep].Fch:=0
      Else
        T[xRep].Fch:=x1;
    End Else Begin{y1<>0}
      y2:=y1; T[y2].Rep:=xRep;
      While T[y2].l1<>y1 Do Begin
        y2:=T[y2].l1;
        T[y2].Rep:=xRep;
      End;
      If T[x].l1<>x Then Begin
        T[x2].l1:=y1; T[y1].l2:=x2;
        T[x1].l2:=y2; T[y2].l1:=x1;
      End;
      T[xRep].Fch:=y1;
    End;
  End;
  T[Root].Rep:=S;
  T[Root].comp:=Ocomp;
  T[x].Rep:=0; T[x].l1:=x;  T[x].l2:=x; T[x].Fch:=0;
  T[x].comp:=True;
  Nx:=Root;
End{SDelete};

Procedure Process;
Var
  i,x:Longint;
  C10,C1,C2:Longint;
  Pix:Array[0..MaxM] of Boolean;

Procedure ReadRow;
Var i,ii,w,b:longint;
Begin{ReadRow}
  i:=1;
  While True Do Begin
    Read(InFile, w);
    If w=-1 Then Exit;
    For ii:=i To i+w-1 Do Pix[ii]:=False;
    Inc(i,w);
    Read(InFile, b);
    For ii:=i To i+b-1 Do Pix[ii]:=True;
    Inc(i,b);
  End;
  ReadLn(InFile);
End{ReadRow};

Begin{Process}
  For x:=1 To N Do Begin
    ReadRow;              {read the next row into Row}
    C10:=0; C2:=0;
    For i:=1 To M Do Begin
      C1:=SFind(i);
      If Pix[i] Then Begin
	If C1=0 Then Begin{0}
	  SUnion(C2, i);  {1}
	  C10:=0;
	End Else Begin
	  If (C2=C1) And (C10=0) Then{01}
            T[C1].comp:=False;       {11}
	  If C2<>C1 Then Begin
	    SUnion(C2, C1);
	    C10:=C2;
	  End Else
            C10:=C1;
	End;{C1<>0}
      End Else Begin      {0}
        If C1<>0 Then SDelete(C1, i);
	C10:=C1;
	C2 :=0;
      End;
    End{for i};
  End{for x};

  For i:=1 To M Do
    If (T[i].Rep<0)  Then Begin
    Inc(NComp);
    If T[i].comp Then Inc(CComp);
  End;
End{Process};

Begin{Program}
  Init;
  NComp:=0; CComp:=0;
  Process;
  WriteOut;
End.

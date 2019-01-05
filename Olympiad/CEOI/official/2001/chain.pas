Program Chain;
Uses Meter;
Const
  MaxN=10000;                    {max. # atoms}
Var
  N:Integer;                     {# atoms }
  S:Array[0..MaxN] of Integer;   {solution}
  i:Integer;

Procedure Compute;
{Global: N, S }
Var
  Pos:Array[0..MaxN] Of -MaxN..MaxN;{atom positions relative to atom 1}
  a,b,c,x,y:Integer;             {atom labels}
  Dab,Dxy,Dax,Dbx,Dby:Integer;   {distances}
  i,k,min,z:Integer;

Begin{Compute};
  a:=1; b:=2; c:=3;  {chose three atoms}
  Dab:=Span(a,b); Dax:=Span(a,c); Dbx:=Span(b,c);
  Pos[1]:=0; Pos[2]:=Dab;
  If (Dax=Dab+Dbx) Or (Dab=Dax+Dbx) Then {compute the position of c relative to a->b}
    Pos[c]:=Pos[a]+Dax
  Else If (Dbx=Dax+Dab) Then
    Pos[c]:=Pos[a]-Dax;

  i:=3;
  While i+2<=N Do Begin
  {a,b and c accessed only two times, their relative positions are known}
    x:=i+1; y:=i+2;        {next two atoms:x, y}
    Inc(i,2);
    Dxy:=Span(x,y);        {query the distance of x and y}
    {Select two atoms from [a,b,c] such that their distance
     is different from Dxy.}
    If Dxy<>Abs(Pos[b]-Pos[c]) Then Begin         {b--c<>x--y}
      z:=a; a:=c; c:=z;
    End Else If Dxy<>Abs(Pos[a]-Pos[c]) Then Begin{a--c<>x--y}
      z:=b; b:=c; c:=z;
    End;  {Else a--b<>x--y }
    Dab:=Abs(Pos[a]-Pos[b]);
    If Pos[b]<Pos[a] Then Begin{ensure that Pos[a]<Pos[b]}
      z:=a; a:=b; b:=z;
    End;
    {Pos[a]<Pos[b], Dab<>Dxy}
    Dax:=Span(a,x);
    Dby:=Span(b,y);
    {determine the relative position of x and y}
    If (Dax=Dab+Dby+Dxy) Or                 {a--b--y--x}
       (Dax+Dxy=Dab+Dby) Then Begin         {a--b--x--y}
      Pos[x]:=Pos[a]+Dax;                   {a--x--b--y}
      Pos[y]:=Pos[b]+Dby;
    End Else If (Dab=Dax+Dxy+Dby) Or        {a--x--y--b}
       (Dab+Dxy=Dax+Dby) Then Begin         {a--y--b--x}
      Pos[x]:=Pos[a]+Dax;                   {a--y--x--b}
      Pos[y]:=Pos[b]-Dby;                   {y--a--b--x}
                                            {y--a--x--b}
    End Else If (Dxy=Dab+Dax+Dby) Then Begin{x--a--b--y}
      Pos[x]:=Pos[a]-Dax;
      Pos[y]:=Pos[b]+Dby;
    End Else If (Dby=Dxy+Dax+Dab) Or        {y--x--a--b}
                (Dax+Dab=Dby+Dxy) Then Begin{x--y--a--b}
      Pos[x]:=Pos[a]-Dax;                   {x--a--y--b}
      Pos[y]:=Pos[b]-Dby;
    End{If};
    a:=x; b:=y;      {replace a and b by x and y, resp.}
  End{while};

  If Not Odd(N) Then Begin{process the last item if N is even}
    If Pos[b]<Pos[a] Then Begin
      z:=a; a:=b; b:=z;
    End;
    Dab:=Abs(Pos[a]-Pos[b]);
    Dax:=Span(a,N);
    Dbx:=Span(b,N);;
    If Dax=Dab+Dbx Then
      Pos[N]:=Pos[b]+Dbx
    Else If Dab=Dax+Dbx Then
      Pos[N]:=Pos[a]+Dax
    Else
      Pos[N]:=Pos[a]-Dax
  End;
  min:=Pos[1];
  For i:=2 To N Do
  If Pos[i]<min Then min:=Pos[i];
  min:=-min+1;
  For i:=1 To N Do     {shift positions to the range 1..N}
    S[Pos[i]+min-1]:=i;
End{Compute};

Begin{program}
  N:=Size;
  Compute;
  For i:=0 To N-1 Do
    Answer(i+1,S[i]);
End.


Program Trip;
Const
  MaxN=1000;
Type
  Point=1..MaxN;
  List=^Cell;
  Cell=Record P:Point; link:List End;
  Graph=Array[1..MaxN] Of List;
  Path=Array[1..MaxN] Of 0..MaxN;
Var
  G:Graph;      {input graph}
  N:Word;       {# junctions}
  A,B:Word;     {source and destination}
  CommE:Word;   {min. # common edges}
  P1,P2:Path;   {the two paths between A and B}
  P1n,P2n:Word; {number of nodes in paths }

Procedure ReadIn;
Var InF:Text;
  u,v:Point;
  E,i:Word;
  Guv:List;
Begin
  Assign(InF, 'trip.in'); Reset(InF);
  ReadLn(InF, A, B);
  ReadLn(InF, N, E);

  For u:=1 To N Do Begin       {Init}
    G[u]:=Nil;
  End;
  For i:=1 To E Do Begin       {Read input}
    ReadLn(InF, u,v);
    New(Guv);
    Guv^.p:=v; Guv^.link:=G[u];
    G[u]:=Guv;
    New(Guv);
    Guv^.p:=u; Guv^.link:=G[v];
    G[v]:=Guv;
  End{for i};

 Close(InF);
End{ReadIn};

Procedure WriteOut;
Var OutF:Text;
  i:Word;
Begin
  Assign(OutF, 'trip.out'); Rewrite(OutF);
  If P1n=0 Then
    WriteLn(OutF,-1)
  Else Begin
    WriteLn(OutF,CommE:1);
    For i:=P1n DownTo 2 Do
      Write(OutF, P1[i]:1,' ');
    WriteLn(OutF, P1[1]:1);

    For i:=1 To P2n-1 Do
      Write(OutF, P2[i]:1,' ');
    WriteLn(OutF,P2[P2n]:1);
  End;
  Close(OutF);
End{WriteOut};

Procedure Compute;
Var
  D,T,L,R:Array[Point] of 0..MaxN;
  (*T[u]->u are the tree edges in the DFS tree *)
  (* L[u]= v: path exists in DFS tree u~>w, w->v is back edge, and D[v] min *)
  (* u->R[u]~>w->L[u] *)
  Time:Word;
  u:Point;

  Procedure DFS(u:Point);
  {Global: Time, D,T,L,R}
  Var
    El:List;
    v,w,bw:Point;
  Begin
    D[u]:=Time;
    Inc(Time);
    w:=u; bw:=u;
    El:=G[u];
    While El<>Nil Do Begin{processing u->v edges}
      v:=El^.p;
      If T[v]=0 Then Begin{u->v is a tree edge}
        T[v]:=u;
        DFS(v);
        If D[L[v]]<D[w] Then Begin
          w:=L[v]; bw:=v;
        End;
      End Else Begin      {u->v is a back edge}
        If (v<>T[u])And(D[v]<D[w]) Then Begin
          w:=v; bw:=u;
        End;
      End;
      El:=El^.link;
    End{while u->v};
    L[u]:=w; R[u]:=bw;
  End{DFS};

  Procedure Traverse1(u:Point; Var P:Path; Var Pn:Word);
  Var Lu:Integer;
  Begin{Traverse}
    Repeat
      If L[u]=u Then Begin {u-T[u] is a bridge}
        Inc(CommE);
        Inc(Pn); P[Pn]:=u;
        u:=T[u];
      End Else Begin
        While u<>R[u] Do Begin
          Inc(Pn); P[Pn]:=u;
          u:=R[u];
        End;
        Inc(Pn); P[Pn]:=u;
        u:=L[u];
        If u=L[u] Then Continue;
        Lu:=L[L[u]];
        If L[u]=Lu Then
          Repeat
            Inc(Pn); P[Pn]:=u;
            u:=T[u];
          Until (u=Lu)
        Else
          Repeat
            Inc(Pn); P[Pn]:=u;
            u:=T[u];
          Until L[u]=Lu;
      End;
    Until u=A;
    Inc(Pn); P[Pn]:=A;
  End{Traverse1};

  Procedure Traverse2(u:Point; Var P:Path; Var Pn:Word);
  Var Lu:Integer;
  Begin{Traverse}
    Repeat
      If L[u]=u Then Begin {u-T[u] is a bridge}
        Inc(Pn); P[Pn]:=u;
        u:=T[u];
      End Else Begin
        Lu:=L[L[u]];
        If L[u]=Lu Then Begin
          Repeat
            Inc(Pn); P[Pn]:=u;
            u:=T[u];
          Until u=Lu;
        End Else Begin
          Repeat
            Inc(Pn); P[Pn]:=u;
            u:=T[u];
          Until L[u]=Lu;
          While u<>R[u] Do Begin
            Inc(Pn); P[Pn]:=u;
            u:=R[u];
          End;
          Inc(Pn); P[Pn]:=u;
          u:=L[u];
        End;
      End;
    Until u=A;
    Inc(Pn); P[Pn]:=A;
  End{Traverse2};

Begin{Compute}
  For u:=1 To N Do T[u]:=0; {init}
  T[A]:=A; Time:=0;
  P1n:=0; P2n:=0;
  CommE:=0;

  DFS(A);                   {build DFS tree, compute T,L,R}

  If T[B]=0 Then            {no route to B}
    Exit;
  Traverse1(B, P1, P1n);    {forward route to B}

  Traverse2(B, P2, P2n);    {return rote to A  }

End{Compute};

Begin{Prog}
  ReadIn;
  Compute;
  WriteOut;
End.

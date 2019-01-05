Program Select;
Uses Query;
Const
  MaxN=30000;                    {max. size}
  MaxK=20;                       {MaxN<=2^MaxK}
Var
  N:1..MaxN;                     {# of all elements}
  M:0..MaxN;                     {the actual # number of elements}
  Half:Longint;                  {the actual # of elements of the majority group}
  B:Array[0..MaxK] Of Boolean;   {having a subgroup with 2^k elements}
  R:Array[0..MaxK] Of 0..MaxN;   {representatives of the subgroups}
  Pow2:Array[0..MaxK] Of Longint;{Pow2[k]=2^k}
  L:Word;                        {the largest subgroup has 2^L elements}
  i,k:Integer;
Begin
  Pow2[0]:=1;
  For k:=1 To MaxK Do Pow2[k]:=Pow2[k-1] Shl 1;
  N:=Size;
  If Odd(N) Then M:=N Else M:=N-1;
  Half:=M div 2 +1;
  L:=0;  i:=0;
  While i<N Do Begin              {search for majority member of M elements}
    k:=0; B[0]:=True;
    Inc(i); R[0]:=i;
    Inc(i);                       {take the next two elements i and i+1}
    If i>N Then Break;
    While B[k] Do Begin           {there are two subgroups with 2^k elements}
      If Member(R[k],i)=1 Then Begin{join the two subgroups of 2^k elements}
        B[k]:=False;
        Inc(k);
        If k>L Then L:=k;         {new largest subgroup}
      End Else Begin              {different subgroups}
        Dec(M, Pow2[k+1]);        {M:=M-2^(k+1)}
        Dec(Half, Pow2[k]);       {Half:=Half-2^k}
        B[k]:=False;              {discard the subgroup}
        If k=L Then               {update L}
          While (L>0)And Not B[L] Do Dec(L);
        k:=-1;
        Break;
      End;
    End{while B[k]};

    If k>=0 Then Begin
      B[k]:=True;                 {form a new subgroup having 2^k elements}
      R[k]:=i;                    {i is the representativ of the new subgroup}
    End;

    If (L>0)And(Pow2[L]>=Half) Then{the largest subgroup is the majority}
      Break;
  End{while i<N};

  Answer(R[L]);                   {the largest subgroup is the majority}
End.

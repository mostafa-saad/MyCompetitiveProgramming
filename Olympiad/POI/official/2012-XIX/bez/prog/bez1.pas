(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Bezpieczenstwo minimalistyczne                   *
 *   Autor:             Krzysztof Leszczynski                            *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

program Wzorcowka;

type 
  para = record
    a,b,x: Longint;
  end;

const   INF: Longint = 1000000100;
    LONG_INF: qword = 1000000010000000;
var n,m,i,maxi,mini: Longint; 
  sum,ans_frs,ans_sec,ans1,ans2: int64; 
  P,A,B,vis: array[0..500100] of Longint;  
  ile: array[0..500100] of Longint;
  graf: array[0..6000100] of para; 
  ggraf: array[0..6000100] of para;
  label koniec;

procedure add(nr: Longint);
var
  a,b,c: Longint;
begin
  readln(a,b,c);
  ile[a]:=ile[a]+1;
  ile[b]:=ile[b]+1;
  graf[nr].a:=a;
  graf[nr].b:=b;
  graf[nr].x:=c;
  graf[nr+1].a:=b;
  graf[nr+1].b:=a;
  graf[nr+1].x:=c;
end;

function max_LL(a,b: int64): int64;
begin
  if a>b then max_LL:=a
  else max_LL:=b;
end;
function min_LL(a,b: int64): int64;
begin
  if a<b then min_LL:=a
  else min_LL:=b;
end;
function max(a,b: Longint):Longint;
begin
  if a>b then max:=a
  else max:=b;
end;
function min(a,b: Longint):Longint;
begin
  if a<b then min:=a
  else min:=b;
end;
function reboot(aa,bb,bezp,nr: Longint):boolean;
var bol:boolean;
begin
  bol:=true;
  vis[nr]:=1;
  if aa<>INF then begin
    if (B[nr]<>INF) AND (B[nr] <> bezp-aa) then bol:=false;
    B[nr]:=bezp-aa;
  end;
  if bb<>INF then begin
    if (A[nr]<>INF) AND (A[nr]<>bezp-bb) then bol:=false;
    A[nr]:=bezp-bb;
  end;
  reboot:=bol;
end;
function get_new(nr: Longint):boolean;
begin
  vis[nr]:=2;
  if(A[nr]<>INF) and (B[nr]<>INF) then begin
    if mini>(B[nr]-A[nr])div 2 then get_new:=false
    else if maxi<(B[nr]-A[nr])div 2 then get_new:=false
    else if B[nr]-A[nr]<0 then get_new:=false
    else if ((B[nr]-A[nr])and 1)>0 then get_new:=false
    else begin
      mini:=(B[nr]-A[nr])div 2;
      maxi:=(B[nr]-A[nr])div 2;
      get_new:=true;
    end;
  end
  else if(A[nr]<>INF) then begin
    mini:=max(mini,0-A[nr]);
    maxi:=min(maxi,P[nr]-A[nr]);
    get_new:=(mini<=maxi);
  end
  else if(B[nr]<>INF) then begin
    mini:=max(mini,B[nr]-P[nr]);
    maxi:=min(maxi,B[nr]);
    get_new:=(mini<=maxi);
  end
  else get_new:=true;
end;
function dfs(v,war: Longint):int64;
var ret: int64;
  j: Longint;
begin
  ret:=0;
  vis[v]:=m;
  for j:=ile[v] to ile[v+1]-1 do begin
    if vis[ggraf[j].a]=m then continue;
    ret:=ret+dfs(ggraf[j].a,war);
  end;
  if (A[v]<>INF) and (A[v]+war<=P[v]) and (A[v]+war>=0) then dfs:=ret+A[v]+war
  else if (B[v]<>INF) and (B[v]-war<=P[v]) and (B[v]-war>=0) then dfs:=ret+B[v]-war
  else dfs:=LONG_INF;
end;
function dfs2(v: Longint): boolean;
var bol:boolean;
  j:Longint;
begin
  bol:=true;
  if get_new(v)=false then bol:=false;
  for j:=ile[v] to ile[v+1]-1 do begin
    if (vis[ggraf[j].a]<>2) and (dfs2(ggraf[j].a)=false) then bol:=false;
  end;
  dfs2:=bol;
end;
function dfs3(v: Longint): boolean;
var odw,j: Longint;
  bol: boolean;
begin
  bol:=true;
  for j:=ile[v] to ile[v+1]-1 do begin
    odw:=vis[ggraf[j].a];
    if reboot(A[v],B[v],ggraf[j].x,ggraf[j].a)=false then bol:=false;
    if (odw=0) and (dfs3(ggraf[j].a)=false) then bol:=false;
  end;
  dfs3:=bol;
end;

BEGIN
  sum:=0; ans_frs:=0; ans_sec:=0;
  readln(n,m);
  for i:=1 to n do begin
    read(P[i]);
    sum+=P[i];
    vis[i]:=0;
    A[i]:=INF;
    B[i]:=INF;
    ile[i]:=0;
  end;
  readln();
  for i:=0 to m-1 do begin
    add(i*2);
  end;
  ile[0]:=0;
  for i:=1 to n+1 do begin
    ile[i]:=ile[i-1]+ile[i];
  end;
  for i:=0 to m*2-1 do begin
    ile[graf[i].b]:=ile[graf[i].b]-1;
    ggraf[ile[graf[i].b]]:=graf[i];
  end;
  (*Graf wczytany, moĹzna przejĹÄ do powaĹznej czÄĹci zadania*)

  for i:=1 to n do begin
    if vis[i]>0 then continue;
    A[i]:=0;
    if dfs3(i)=false then begin
      writeln('NIE');
      goto koniec;
    end;
    maxi:=INF;
    mini:=0;
    if dfs2(i)=false then begin
      writeln('NIE');
      goto koniec;
    end;

    m:=3; ans1:=dfs(i,mini);
    m:=4; ans2:=dfs(i,maxi);
    if (ans1>=LONG_INF) or (ans2>=LONG_INF) then begin
      writeln('NIE');
      goto koniec;
    end;
    ans_frs:=ans_frs+max_LL(ans1,ans2);
    ans_sec:=ans_sec+min_LL(ans1,ans2);
  end;
  writeln(sum-ans_frs,' ',sum-ans_sec);
  koniec:;
END.

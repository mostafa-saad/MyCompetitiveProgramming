(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Kolej (KOL)                                   *
 *   Plik:                 kol1.pas                                      *
 *   Autor:                Michal Pilipczuk                              *
 *   Opis:                 Rozwiazanie wzorcowe.                         *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n log n)                                    *
 *                                                                       *
 *************************************************************************)

program kolej;

const MAX=100100;
      zz=132000;
      CMAX=5000000;

type Listener=record
    h:longint;
    node_next:longint;
    node_prev:longint;
    listen_next:longint;
end;

type Node=record
    mx:longint;
    listeners:longint;
end;

var AA			:array [0..MAX-1] of longint;
    BB			:array [0..MAX-1] of longint;
    R			:array [0..MAX-1] of longint;
    colors		:array [0..MAX-1] of longint;
    c,tmp,i,j,n,mcount	:longint;
    tree		:array [0..2*zz] of Node;
    listen_nodes	:array [0..MAX-1] of longint;
    lst			:array [0..CMAX] of Listener;
    st			:array [0..MAX,0..1] of longint;
    stc			:array [0..1] of longint;

procedure list_add(nw,hd:longint);
begin
    lst[nw].node_next:=lst[hd].node_next;
    lst[nw].node_prev:=hd;
    lst[lst[hd].node_next].node_prev:=nw;
    lst[hd].node_next:=nw;
end;

procedure list_del(en:longint);
begin
    lst[lst[en].node_prev].node_next:=lst[en].node_next;
    lst[lst[en].node_next].node_prev:=lst[en].node_prev;
end;

procedure init_list(en:longint);
begin
    lst[en].node_next:=en;
    lst[en].node_prev:=en;
end;

function list_empty(en:longint):boolean;
begin
    if lst[en].node_next=en then
	list_empty:=true
    else
	list_empty:=false;
end;
    
function malloc:longint;
begin
    malloc:=mcount;
    inc(mcount);
end;

procedure addListener(k,node,value:longint);
var l:longint;
begin
    l:=malloc();
    list_add(l,tree[node].listeners);
    lst[l].listen_next:=listen_nodes[k];
    listen_nodes[k]:=l;
    lst[l].h:=value;
end;

procedure addToBucket(k:longint);
var a,b,l,left,right:longint;
begin
    a:=AA[k];
    b:=BB[k];
    l:=k+zz;
    left:=k+zz-1;
    right:=b+zz+1;
    
    tree[l].mx:=a;
    l:=l shr 1;
    while l>0 do
    begin
	tree[l].mx := tree[l shl 1].mx;
	if tree[l].mx < tree[(l shl 1)+1].mx then
	    tree[l].mx:=tree[(l shl 1)+1].mx;
	l:=l shr 1;
    end;
    
    while not ((left shr 1) = (right shr 1)) do
    begin
	if (left mod 2 = 0) then
	    addListener(k,left+1,a);
	if (right mod 2 = 1) then
	    addListener(k,right-1,a);
	left:=(left shr 1);
	right:=(right shr 1);
    end;
end;

procedure deleteFromBucket(k:longint);
var l,it:longint;
begin
    l:=k+zz;
    tree[l].mx:=-1;
    
    l:=l shr 1;
    while l>0 do
    begin
	tree[l].mx := tree[l shl 1].mx;
	if tree[l].mx < tree[(l shl 1)+1].mx then
	    tree[l].mx:=tree[(l shl 1)+1].mx;
	l:=l shr 1;
    end;
    
    it:=listen_nodes[k];
    while it>=0 do
    begin
	list_del(it);
	it:=lst[it].listen_next;
    end;
    listen_nodes[k]:=-1;
end;

function getForwardEdge(k:longint):longint;
var b,h,left,right:longint;
begin
    b:=BB[k];
    h:=AA[k];
    left:=k+zz-1;
    right:=b+zz+1;
    getForwardEdge:=-1;
    while not ((left shr 1) = (right shr 1)) do
    begin
	if (left mod 2 = 0) and (tree[left+1].mx>h) then
	begin
	    getForwardEdge:=R[tree[left+1].mx];
	    break;
	end;
	if (right mod 2 = 1) and (tree[right-1].mx>h) then
	begin
	    getForwardEdge:=R[tree[right-1].mx];
	    break;
	end;
	left:=(left shr 1);
	right:=(right shr 1);
    end;    
end;

function getBackwardEdge(k:longint):longint;
var my_h,l:longint;
begin
    my_h:=AA[k];
    l:=k+zz;
    getBackwardEdge:=-1;
    while l>0 do
    begin
	if (not list_empty(tree[l].listeners)) and 
	   (lst[lst[tree[l].listeners].node_prev].h < my_h) then
	begin
	    getBackwardEdge:=R[lst[lst[tree[l].listeners].node_prev].h];
	    break;
	end;
	l:=l shr 1;
    end;
end;

procedure buildA;
begin
    readln(n);
    for i:=0 to n-1 do 
    begin
        read(tmp);
        AA[i]:=tmp-1;
    end;
end;

procedure buildR;
begin
    for i:=0 to n-1 do R[AA[i]]:=i;
end;

procedure buildB;
var m:longint;
begin
    m:=-1;
    for i:=0 to n-1 do 
    begin
	if R[i]>m then m:=R[i];
	BB[R[i]]:=m;
    end;
end;

procedure buildTree;
begin
    mcount:=0;
    for i:=0 to n-1 do
    begin
	colors[i]:=-1;
	listen_nodes[i]:=-1;
    end;
    for i:=0 to 2*zz-1 do
    begin
	tree[i].mx:=-1;
	tree[i].listeners:=malloc();
	init_list(tree[i].listeners);
    end;
    for i:=0 to n-1 do
	addToBucket(R[i]);
end;

procedure dfs(v,c:longint);
var e:longint;
begin
    colors[v]:=c;
    deleteFromBucket(v);
    while true do
    begin
	e:=getForwardEdge(v);
	if (e<0) then break;
	dfs(e,c xor 1);
    end;
    while true do
    begin
	e:=getBackwardEdge(v);
	if (e<0) then break;
	dfs(e,c xor 1);
    end;
end;

procedure buildSolution;
begin
    for i:=0 to n-1 do
	if colors[i]<0 then
	    dfs(i,0);
end;

procedure flush;
var flag:boolean;
begin
    while true do
    begin
	flag:=true;
	for j:=0 to 1 do
	begin
	    if st[stc[j]-1,j]=c then
	    begin
		inc(c);
		dec(stc[j]);
		flag:=false;
	    end;
	end;
	if flag then break;
    end;
end;

function checkSolution:boolean;
begin
    for j:=0 to 1 do 
    begin
	stc[j]:=1;
	st[0,j]:=n+2;
    end;
    c:=0;
    for i:=0 to n-1 do
    begin
	st[stc[colors[i]],colors[i]]:=AA[i];
	inc(stc[colors[i]]);
	flush();
    end;
    if c>=n then
	checkSolution:=true
    else
	checkSolution:=false;
end;

procedure buildAnswer;
begin
    if checkSolution() then
    begin
	writeln('TAK');
	for i:=0 to n-1 do
	begin
	    if i>0 then write(' ');
	    write(colors[i]+1);
	end;
	writeln;
    end else writeln('NIE');
end;

begin
    buildA();
    buildR();
    buildB();
    buildTree();
    buildSolution();
    buildAnswer();
end.

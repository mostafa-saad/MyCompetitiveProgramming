(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      Scalenie zbiorow synow w zbior ojca              *
 *                      - podobienstwo do Mergesorta nieprzypadkowe      *
 *                      dziala wolno dla drzew o duzej wysokosci         *
 *                                                                       *
 *************************************************************************)

program rot;
uses math;

type list_ptr = ^list;
list = record
	v : longint;
	next : list_ptr;
end;

type list_ref = ^list_ptr;

procedure list_add(l : list_ref; a : longint);
var tmp : list_ptr;
begin
	New(tmp); tmp^.v:=a; tmp^.next:=nil;
	if l^=nil then
		l^:=tmp
	else begin
		tmp^.next:=l^^.next;
		l^^.next:=tmp;
	end;
end;

procedure list_clear(l : list_ptr);
var tmp : list_ptr;
begin
	repeat
		tmp:=l^.next;
		Dispose(l);
		l:=tmp;
	until l=nil;
end;

function list_size(l : list_ptr) : longint;
begin
	list_size:=0;
	while l<>nil do begin	
		Inc(list_size);
		l:=l^.next;
	end;
end;

type node_ptr = ^node;
node = record
	left, right : node_ptr;
	st : list_ptr;
end;

// wczytywanie danych
procedure read_input(tr : node_ptr);
var c : longint;
begin
	Read(c);
	if c<>0 then begin
		tr^.st:=nil; tr^.left:=nil; tr^.right:=nil;
		list_add(@tr^.st, c);
	end
	else begin
		New(tr^.left); New(tr^.right);
		read_input(tr^.left); read_input(tr^.right);
	end;
end;

// obliczenie wyniku
function compute(tr : node_ptr) : Int64;
var a, b : longint;
var inv, al : Int64;
var ca, cb : list_ptr;
var cur : list_ref;
begin
	if tr^.left=nil then
		compute:=0
	else begin
		compute:=compute(tr^.left)+compute(tr^.right);
		ca:=tr^.left^.st; cb:=tr^.right^.st; cur:=@tr^.st;
		al:=list_size(ca); al:=al*list_size(cb);
		inv:=0; a:=0; b:=0;
		while (ca<>nil) and (cb<>nil) do begin
			if ca^.v<cb^.v then begin
				list_add(cur, ca^.v);
				if a+b>0 then 
					cur:=@cur^^.next;
				ca:=ca^.next;
				inv:=inv+b;
				Inc(a);
			end
			else begin
				list_add(cur, cb^.v);
				if a+b>0 then 
					cur:=@cur^^.next;
				cb:=cb^.next;
				Inc(b);
			end;
		end; 
		while ca<>nil do begin
			list_add(cur, ca^.v);
			if a+b>0 then 
				cur:=@cur^^.next;
			ca:=ca^.next;
			inv:=inv+b;
			Inc(a);
		end;
		while cb<>nil do begin
			list_add(cur, cb^.v);
			if a+b>0 then 
				cur:=@cur^^.next;
			cb:=cb^.next;
			Inc(b);
		end;
		list_clear(tr^.left^.st);
		list_clear(tr^.right^.st);
		compute:=compute+min(inv, al-inv);
	end;
end;

var tmp : longint;
var root : node_ptr;

begin
	Read(tmp); New(root); 
	read_input(root);
	WriteLn(compute(root));
end.
		

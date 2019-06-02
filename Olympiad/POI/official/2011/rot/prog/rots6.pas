(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n^2*lg(n))                                     *
 *   Opis:              Rozwiazanie wolniejsze, silowe                   *
 *                                                                       *
 *************************************************************************)

program rot;
uses math;

// naiwne drzewo bst
type bst_node_ptr = ^bst_node;
bst_node = record
	left, right : bst_node_ptr;
	sz, val : longint;
end;

type bst_node_ref = ^bst_node_ptr;

function make(v : longint) : bst_node_ptr;
begin
	New(make); make^.left:=nil; make^.right:=nil;
	make^.val:=v; make^.sz:=1;
end;

// wielkosc poddrzewa
function size(tr : bst_node_ptr) : longint;
begin
	if tr=nil then
		size:=0
	else
		size:=tr^.sz;
end;

// wstawianie do drzewa
procedure insert(tr : bst_node_ref; v : longint);
begin
	if v<tr^^.val then begin
		if tr^^.left=nil then
			tr^^.left:=make(v)
		else
			insert(@tr^^.left, v);
	end else begin
		if tr^^.right=nil then
			tr^^.right:=make(v)
		else
			insert(@tr^^.right, v);
	end;
	tr^^.sz:=size(tr^^.left)+size(tr^^.right)+1;
end;

// ile wiekszych od v w drzewie
function cnt_greater(tr : bst_node_ptr; v : longint) : longint;
begin
	cnt_greater:=0;
	while tr<>nil do begin
		if v>tr^.val then
			tr:=tr^.right
		else begin
			cnt_greater:=cnt_greater+size(tr^.right)+1;
			tr:=tr^.left;
		end;
	end;
end;

// usuwanie drzewa z pamieci
procedure erase(tr : bst_node_ptr);
begin
	if tr<>nil then begin
		erase(tr^.left);
		erase(tr^.right);
		Dispose(tr);
	end;
end;

type node_ptr = ^node;
node = record
	left, right : node_ptr;
	st : bst_node_ptr;
end;

// wczytywanie danych
procedure read_input(tr : node_ptr);
var c : longint;
begin
	Read(c);
	if c<>0 then
		tr^.st:=make(c)
	else begin
		New(tr^.left); New(tr^.right);
		read_input(tr^.left);
		read_input(tr^.right);
	end;
end;

// przejscie po elementach a i zsumowanie dla kazdego elementu a,
// ile jest wiekszych od niego elementow w b
function iter_inv(a : bst_node_ptr; b : bst_node_ptr) : Int64;
begin
	if a=nil then
		iter_inv:=0
	else
		iter_inv:=iter_inv(a^.left, b)+iter_inv(a^.right, b)+cnt_greater(b, a^.val);
end;

// przejscie po elementach a i wstawienie kazdego z nich do b
procedure iter_merge(a : bst_node_ptr; b : bst_node_ref);
begin
	if a<>nil then begin
		insert(b, a^.val);
		iter_merge(a^.left, b);
		iter_merge(a^.right, b);
	end;
end;

// obliczenie wyniku
function compute(tr : node_ptr) : Int64;
var inv, al : Int64;
begin
	if size(tr^.st)=1 then
		compute:=0
	else begin
		compute:=compute(tr^.left)+compute(tr^.right);
		inv:=0; al:=size(tr^.left^.st); al:=al*size(tr^.right^.st);
		if size(tr^.left^.st)<size(tr^.right^.st) then begin
			tr^.st:=tr^.right^.st;
			inv:=iter_inv(tr^.left^.st, tr^.st);
			iter_merge(tr^.left^.st, @tr^.st);
			erase(tr^.left^.st);
		end else begin
			tr^.st:=tr^.left^.st;
			inv:=iter_inv(tr^.right^.st, tr^.st);
			iter_merge(tr^.right^.st, @tr^.st);
			erase(tr^.right^.st);
		end;
		compute:=compute+min(inv, al-inv);
	end;
end;

var root : node_ptr;
var n : longint;

begin
	Read(n); New(root);
	read_input(root);
	WriteLn(compute(root));
end.

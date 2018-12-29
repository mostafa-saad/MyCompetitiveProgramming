(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *   Zlozonosc czasowa: O(n*lg^2(n))                                     *
 *                                                                       *
 *************************************************************************)

program rot;
uses math;

// drzewo AVL wzbogacone o mozliwosc odpowiadania na zapytania
// "ile wiekszych od x" w czasie logarytmicznym
type avl_node_ptr = ^avl_node;
avl_node = record
	left, right : avl_node_ptr;
	sz, val, h: longint;
end;

type avl_node_ref = ^avl_node_ptr;

function init(v : longint) : avl_node_ptr;
begin
	New(init); init^.left:=nil; init^.right:=nil;
	init^.val:=v; init^.sz:=1; init^.h:=1;
end;

// wielkosc poddrzewa
function size(tr : avl_node_ptr) : longint;
begin
	if tr=nil then
		size:=0
	else
		size:=tr^.sz;
end;

// wysokosc poddrzewa
function height(tr : avl_node_ptr) : longint;
begin
	if tr=nil then
		height:=0
	else
		height:=tr^.h;
end;

// procedura pomocnicza
procedure make(tr : avl_node_ptr; l : avl_node_ptr; r : avl_node_ptr);
begin
	tr^.left:=l; tr^.right:=r;
	tr^.sz:=size(l)+size(r)+1;
	tr^.h:=max(height(l), height(r))+1;
end;

// rownowazenie poddrzewa
procedure balance(R : avl_node_ref);
var tmp1, tmp2, tmp3, res : avl_node_ptr;
begin
	res:=R^;
	if height(R^^.left)=height(R^^.right)+2 then begin
		if height(R^^.left^.left)=height(R^^.left)-1 then begin
			tmp1:=R^^.left^.right; res:=R^^.left;
			make(R^, tmp1, R^^.right);
			make(res, res^.left, R^);
		end else begin
			tmp1:=R^^.left^.right^.left; tmp2:=R^^.left^.right^.right;
			tmp3:=R^^.left; res:=R^^.left^.right;
			make(tmp3, tmp3^.left, tmp1);
			make(R^, tmp2, R^^.right);
			make(res, tmp3, R^);
		end;
	end else if height(R^^.right)=height(R^^.left)+2 then begin
		if height(R^^.right^.right)=height(R^^.right)-1 then begin
			tmp1:=R^^.right^.left; res:=R^^.right;
			make(R^, R^^.left, tmp1);
			make(res, R^, res^.right);
		end else begin
			tmp1:=R^^.right^.left^.right; tmp2:=R^^.right^.left^.left;
			tmp3:=R^^.right; res:=R^^.right^.left;
			make(tmp3, tmp1, tmp3^.right);
			make(R^, R^^.left, tmp2);
			make(res, R^, tmp3);
		end;
	end else
		make(res, res^.left, res^.right);
	R^:=res;
end;

// wstawianie do drzewa
procedure insert(tr : avl_node_ref; v : longint);
begin
	if v<tr^^.val then begin
		if tr^^.left=nil then
			tr^^.left:=init(v)
		else
			insert(@tr^^.left, v);
	end else begin
		if tr^^.right=nil then
			tr^^.right:=init(v)
		else
			insert(@tr^^.right, v);
	end;
	balance(tr);
end;

// ile wiekszych od v w drzewie
function cnt_greater(tr : avl_node_ptr; v : longint) : longint;
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
procedure erase(tr : avl_node_ptr);
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
	st : avl_node_ptr;
end;

// wczytywanie danych
procedure read_input(tr : node_ptr);
var c : longint;
begin
	Read(c);
	if c<>0 then
		tr^.st:=init(c)
	else begin
		New(tr^.left); New(tr^.right);
		read_input(tr^.left);
		read_input(tr^.right);
	end;
end;

// przejscie po elementach a i zsumowanie dla kazdego elementu a,
// ile jest wiekszych od niego elementow w b
function iter_inv(a : avl_node_ptr; b : avl_node_ptr) : Int64;
begin
	if a=nil then
		iter_inv:=0
	else
		iter_inv:=iter_inv(a^.left, b)+iter_inv(a^.right, b)+cnt_greater(b, a^.val);
end;

// przejscie po elementach a i wstawienie kazdego z nich do b
procedure iter_merge(a : avl_node_ptr; b : avl_node_ref);
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

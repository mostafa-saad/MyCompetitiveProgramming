(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Smieci                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(2^n)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Przechodze wszystkimi mozliwosciami dfs i szukam *
 *                      cyklu prostego, jak znajde to usuwam i szukam    *
 *                      od nowa                                          *
 *                                                                       *
 *************************************************************************)

Program smieci;
const 
	MAXN = 100005;
	MAXM = 1000005;

type
	pekst = ^ekst;
	ekst = record
		X, Y : longint;	
		next,prev : pekst;
	end;

procedure insert_first(newelement:pekst; var head:pekst);
begin
	newelement^.next:=head;
	if head <> nil then
		head^.prev:=newelement;
	head:=newelement;
end;

procedure remove_element(pos:pekst; var head:pekst);
begin
  if pos^.next<>nil then
    pos^.next^.prev:=pos^.prev;
  if pos^.prev <> nil then
    pos^.prev^.next:=pos^.next
  else
    head:=pos^.next;
  dispose(pos);
end;


var
	ile, n, m, a, b, s1, s2 : longint;
	licznik : array[0 .. MAXN] of longint;
	vis : array[0..MAXN] of boolean;
	it : array[0..2 * MAXM] of pekst;
	kraw : array[0..MAXN] of pekst;
	cykl, res, dlg : array[0..3 * MAXM] of longint;
	cykl_ind, res_ind, dlg_ind : longint;

procedure add(x, y : longint);
var
	newelement : pekst;
begin
	new(newelement);
	newelement^.X := y;
	newelement^.Y := ile;
	insert_first(newelement, kraw[x]);
	new(newelement);
	newelement^.X := x;
	newelement^.Y := ile + 1;
	insert_first(newelement, kraw[y]);
	
	it[ile] := kraw[y];
	inc(ile);
	it[ile] := kraw[x];
	inc(ile);

	inc(licznik[x]);
	inc(licznik[y]);
end;

function check() : boolean;
var 
	i : longint;
	ok : boolean;
begin
	ok := true;
	for i := 1 to n do
		if licznik[i] mod 2 = 1 then
			ok := false;
	check := ok;
end;

function go(x, ojc, papa : longint) : boolean;
var
	i : pekst;
begin
	go := false;
	if (vis[x]) and (x = papa) then
	begin
		cykl[cykl_ind] := x;
		inc(cykl_ind);
		go := true;
	end 
	else
		if vis[x] then
			go := false
		else
		begin
			vis[x] := true;
			i := kraw[x];	
			while i <> nil do
			begin
				if(i^.X <> ojc) and (go(i^.X, x, papa)) then
				begin
					cykl[cykl_ind] := x;
					inc(cykl_ind);
					remove_element(it[i^.Y], kraw[i^.X]);
					remove_element(i , kraw[x]);
					vis[x] := false;
					go := true;
					break;
				end;
				i := i^.next;
			end;
			vis[x] := false;	
		end;
end;

var 
	i, j, akt : longint;
begin
	for i := 0 to MAXN do
	begin
		licznik[i] := 0;
		vis[i] := false;
		kraw[i] := nil;
	end;
	for i:= 0 to 2 * MAXM do
		it[i] := nil;
	cykl_ind := 0;
	res_ind := 0;
	dlg_ind := 0;
	ile := 1;

	readln(n, m);
	for i := 0 to m - 1 do
	begin
		read(a, b, s1, s2);
		if s1 <> s2 then
			add(a,b);
	end;


	if not check() then
		writeln('NIE')
	else
	begin
		for i := 1 to n do
			while kraw[i] <> nil do
			begin
				go(i, 0, i);
				dlg[dlg_ind] := cykl_ind;
				inc(dlg_ind);
				for j := 0 to cykl_ind - 1 do
				begin
					res[res_ind] := cykl[j];
					inc(res_ind);
				end;
				res[res_ind] := 0;
				inc(res_ind);
				cykl_ind := 0;
			end;

		akt := 0;
		writeln(dlg_ind);
		for j := 0 to dlg_ind - 1 do
		begin
			write(dlg[j] - 1, ' ');
			while res[akt] > 0 do
			begin
				write(res[akt], ' ');
				inc(akt);
			end;
			writeln();
			inc(akt);
		end;
	end;
end.

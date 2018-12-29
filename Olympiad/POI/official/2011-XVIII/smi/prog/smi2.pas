(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Smieci                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Znajdujemy cykl Eulera w grafie i wypisujemy     *
 *                      cykle proste                                     *
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
	ile, n, m, a, b, ki, s1, s2 : longint;
	licznik : array[0 .. MAXN] of longint;
	vis : array[0..MAXN] of boolean;
	it : array[0..2 * MAXM] of pekst;
	kraw : array[0..MAXN] of pekst;
	S, cykl, temp, res, dlg : array[0..3 * MAXM] of longint;
	S_ind, cykl_ind, temp_ind, res_ind, dlg_ind : longint;

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

procedure go(x : longint);
var
	y : longint;
begin
	while kraw[x] <> nil do
	begin
		S[S_ind] := x;
		inc(S_ind);
		y := kraw[x]^.X;
		remove_element(it[kraw[x]^.Y], kraw[y]);
		remove_element(kraw[x], kraw[x]);
		x := y;
	end;	
end;

procedure wypisz();
var
	akt, i : longint;
begin
	for i := 0 to cykl_ind - 1 do 
	begin
		if vis[cykl[i]] then
		begin
			res[res_ind] := cykl[i];
			inc(res_ind);
			ki := 1;
			while vis[cykl[i]] do
			begin
				akt := temp[temp_ind - 1];
				dec(temp_ind);
				res[res_ind] := akt;
				inc(res_ind);
				inc(ki);
				vis[akt] := false;
			end;
			res[res_ind] := 0;
			inc(res_ind);	
			dlg[dlg_ind] := ki;
			inc(dlg_ind);
		end;
		temp[temp_ind] := cykl[i];
		inc(temp_ind);
		vis[cykl[i]] := true;
	end;
	
	akt := 0;
	writeln(dlg_ind);
	for i := 0 to dlg_ind - 1 do
	begin
		write(dlg[i] - 1, ' ');
		while res[akt] > 0 do 
		begin
			write(res[akt], ' ');
			inc(akt);
		end;
		writeln();
		inc(akt);
	end;
end;

var 
	i, x : longint;
begin
	for i := 0 to MAXN do
	begin
		licznik[i] := 0;
		vis[i] := false;
		kraw[i] := nil;
	end;
	for i:= 0 to 2 * MAXM do
		it[i] := nil;
	S_ind := 0;
	cykl_ind := 0;
	temp_ind := 0;
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
			if kraw[i] <> nil then
			begin
				S[S_ind] := i;
				inc(S_ind);
				while S_ind > 0 do
				begin
					x := S[S_ind - 1]; 
					dec(S_ind);
					cykl[cykl_ind] := x;
					inc(cykl_ind);
					go(x);
				end;
			end;
		wypisz();
	end;
end.

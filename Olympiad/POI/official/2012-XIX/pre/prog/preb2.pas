(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie alternatywne, haszowanie             *
 *                                                                       *
 *************************************************************************)

const
	MAXN = 1000005;
	X = 44321;
	MD = 1000000007;
	HASH_TRIES = 5;

var
	n: longint;
	word: ansistring;
	p, s, hash, pw: array[0..MAXN] of longint;
	k: longint;
	b: longint;
	i: longint;
	res: longint;
	m: longint;

function mul(a, b: longint): longint;
var
	x, y: int64;
	res: int64;
begin
	x := a;
	y := b;
	res := (x*y) mod MD;
	mul := longint(res);
end;

function getHash(i, j: longint): longint;
var
	tmp: longint;
begin
	tmp := mul(hash[i-1],pw[j-i+1]);
	getHash := ((hash[j] - tmp) mod MD + MD) mod MD;
end;

function equal(a, b, c, d: longint): boolean;
var
	i: longint;
	ok: boolean;
begin
	if getHash(a, b) <> getHash(c, d) then
		equal := false
	else
	begin
		ok := true;
		for i:=1 to HASH_TRIES do
		begin
			
		end;
		equal := ok;
	end;
end;

begin
	readln(n);
	readln(word);
	word := word + 'a';
	if n mod 2 = 0 then
	begin
		for i:=n+1 downto n div 2+2 do
		begin
			word[i] := word[i-1];
		end;
		inc(n);
	end;
	word[n div 2 + 1] := '#';
	{writeln(n div 2 + 1);
	for i:=1 to n do
		writeln(word[i]);}
	p[1] := 0;
	k := 0;
	for i:=2 to n do
	begin
		while (k>0) and (word[i] <> word[k+1]) do k:=p[k];
		if word[i] = word[k+1] then inc(k);
		p[i] := k;
	end;
	hash[0] := 0;
	for i:=1 to n do hash[i] := (mul(hash[i-1],X)+ord(word[i])-ord('a')+1) mod MD;
	pw[0] := 1;
	for i:=1 to n do pw[i] := mul(pw[i-1],X);
	m := n div 2 + 1;
	s[m] := 0;
	k := 0;
	for b:=m-1 downto 1 do
	begin
		k := k + 2;
		while b+k-1>=m do dec(k);
		while (k>0) and (not equal(b,b+k-1,2*m-(b+k-1),2*m-b)) do
			dec(k);
		s[b] := k;
	end;
	res := 0;
	k := p[n];
	while k>0 do
	begin
		if k+s[k+1] > res then res := k+s[k+1];
		k := p[k];
	end;
	writeln(res);
end.

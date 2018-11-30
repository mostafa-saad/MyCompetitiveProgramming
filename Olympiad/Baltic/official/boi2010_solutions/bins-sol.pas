Program bins;
const
	maxM=1001;
	maxN=20000;
var
	m,n:longint;
	s:array[1..maxN] of longint;{input}
	i,x,k,k2: longint;
	L,R,D:array[0..maxM] of longint;

procedure ReadIn;
var 
	infile:text;
	i:longint;
begin
	assign(infile, 'bins.in'); reset(infile);
	readln(infile, m, n);
	for i:=1 to n do begin
		read(infile, s[i]);
	end;
	close(infile)
end{ReadIn};
var
	outf:text;
begin{prog}
	ReadIn; 
	k:=n div 2;
	k2:=2*k;
	for i:=0 to m+1 do begin 
		L[i]:=0; R[i]:=0;
	end;
	for i:=1 to k do
		inc(L[s[i]]);
	for i:=k+1 to k2 do
		inc(R[s[i]]);
	D[m+1]:=0;
	x:=m; 
	while (k>0) do begin
		while x>0 do begin
			D[x]:=D[x+1]+R[x+1]-L[x];
			if D[x]<0 then begin
				dec(R[s[k2]]);
				dec(R[s[k2-1]]);
				dec(L[s[k]]);
				inc(R[s[k]]);
				if s[k2]>x then x:=s[k2];
				if s[k2-1]>x then x:=s[k2-1];
				if s[k]>x then x:=s[k];	
				dec(k); dec(k2,2);
				break;		
			end else
				dec(x);
		end{while x>0};
		if x=0 then break;
	end{while k>0};
	
	assign(outf,'bins.out'); rewrite(outf);
 	writeln(outf, k);
	close(outf)
end.

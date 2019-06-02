(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Liczby B-g³adkie                               *
 *   Plik:                lic.pas                                        *
 *   Autor:               Marcin Stefaniak                               *
 *************************************************************************)
program LiczbyB_Gladkie;

type integer = longint;

const MAX_P=100000; MAX_B=1000000;

var p:array[1..MAX_P] of integer; { liczby pierwsze }
    nP: integer;
		rp:array[1..MAX_B] of integer; { najwieksza l. pierwsza <= danej }
    sito:array[1..MAX_B] of boolean; { eratostenes }
    n, k, B : integer; 


procedure Eratostenes(B: integer);
var i,j: integer;
begin
  fillchar(sito, B*sizeof(boolean), 0); 
  nP := 0;
  for i:= 2 to B do begin 
		if not sito[i] then begin
	    inc(nP); p[nP] := i;
  	  j := i+i; while (j<=B) do begin 
    	  sito[j] := true; 
	      j := j+i; 
  	  end;
		end;	
		rp[i] := nP;
	end;
end;

const TAB_N = 20000; TAB_D=100;
var tab:array[0..TAB_N, 0..TAB_D] of integer;

function Kanarek_rek(n, d: integer):integer; { rekurencja - ile jest p[b]-gladkich od 1 do n }
var ile, n1, b1, pr : integer;
begin
	if ((n <= TAB_N) and (d <= TAB_D) and (tab[n][d] <> -1)) then begin Kanarek_rek := tab[n][d]; exit; end;
  pr := p[d];
	if (pr >= n) then begin
		ile := n
	end else if d = 0 then begin
		ile := ord(n >= 1);
	end else if d = 1 then begin
		n1 := n; ile := 0;
    while n1 > 0 do begin n1 := n1 shr 1; inc(ile); end
	end else if (pr*pr > n) then begin
		b1 := rp[trunc(sqrt(n))];				
		ile := Kanarek_rek(n, b1);
		inc(b1); while (b1 <= d) do begin inc(ile, n div p[b1]); inc(b1); end;
	end else if (pr > n shr 1) then begin
		b1 := rp[n shr 1];
		ile := Kanarek_rek(n, b1) + d - b1;
	end else  begin
		n1 := n;
		ile := 0;
    while n1 > 0 do begin
      inc(ile, Kanarek_rek(n1, d-1)); 
      n1 := n1 div pr; 
    end;
  end;
	if ((n <= TAB_N) and (d <= TAB_D)) then tab[n][d] := ile;
  Kanarek_rek := ile;
end;

var out:text;


const INTERVAL_LEN = 100000;

var t: array[0..INTERVAL_LEN-1] of integer; { sito Guzickiego }

function Guzicki_2(n, k, B: integer) : integer;
var i, m, d, pp, ile : integer;
begin
  for i:=0 to k-1 do t[i] := n+i; 

  for d := 1 to nP do begin
    pp := p[d]; 
    m := pp - (n mod pp);
		if (m = pp) then m := 0;
		while m < k do begin
      repeat 
			  t[m] := t[m] div pp 
			until (t[m] mod pp) <> 0;
		  inc(m, pp);
	  end;
  end;

  ile := 0;
  {for i:=0 to k-1 do writeln(t[i]);}
  for i:=0 to k-1 do if (t[i] = 1) then inc(ile);
  Guzicki_2 := ile;
end;

var ile: integer;


begin
{	writeln(sizeof(t) + sizeof(tab) + sizeof(p) + sizeof(rp) + sizeof(sito));}
  assign(input, 'lic.in'); reset(input);
	assign(out, 'lic.out'); rewrite(out);


  readln(n, k, B); 
	k := k+1;
  Eratostenes(B); 
	
	if (n div 800 < k) then begin	
		{ rozwiazanie rekurencyjne }
		fillchar(tab, sizeof(tab), -1);
		{	pretablicuj(); }
	  writeln(out, Kanarek_rek(n+k-1, nP) - Kanarek_rek(n-1, nP));
	end else begin
		{ rozwiazanie sitem }
		ile := 0;
		while (k > INTERVAL_LEN) do begin
			ile := ile + Guzicki_2(n, INTERVAL_LEN, B);
			n := n + INTERVAL_LEN;
			k := k - INTERVAL_LEN;
		end;
		if (k > 0) then ile := ile + Guzicki_2(n, k, B);
	  writeln(out, ile);
	end;

  close(out);
	close(input);
end.



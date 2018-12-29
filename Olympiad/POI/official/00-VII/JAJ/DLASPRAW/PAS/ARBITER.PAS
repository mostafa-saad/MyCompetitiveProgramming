{ Program arbitra do zadania JAJKA }
{ Autor: Pawel Wolff }

program arbiter;

uses jajmod, jaj;

const MAX_LOSOWYCH_ODP = 100;

var
  wysokosc1:Longint;
  jajka1:Integer;
  min_wyt, max_wyt:Longint;
  liczba_pytan, wystarczy_pytan:Longint;
  n, k, n_po_k, t:Longint;
  ile_rozbitych:Integer;


function min(a, b:Longint):Longint;
begin
  if a < b then
    min:=a
  else
    min:=b
end;

procedure skroc(var p, q:Longint);
var a, b, c:Longint;
begin
  a:=p; b:=q;
  if a > b then begin
    c:=a; a:=b; b:=c
  end;
  while a > 0 do begin
    c:=b mod a;
    b:=a;
    a:=c
  end;
  p:=p div b;
  q:=q div b
end;

procedure zwieksz_n;
{ zwi©ksza n o 1, aktualizuje zmienne t, n_po_k }
var a, b:Longint;
begin
  t:=2*t+1-n_po_k;
  Inc(n);
  if n = k then
    n_po_k:=1;
  if n > k then begin
    a:=n; b:=n-k;
    skroc(a, b);
    n_po_k:=(n_po_k div b)*a
  end
end;

procedure zwieksz_k;
{ zwi©ksza k o 1, aktualizuje zmienne t, n_po_k }
var a, b:Longint;
begin
  Inc(k);
  if n >= k-1 then begin
    a:=n-k+1; b:=k;
    skroc(a, b);
    n_po_k:=(n_po_k div b)*a
  end;
  t:=t+n_po_k
end;

procedure zmniejsz_n;
{ zmniejsza n o 1, aktualizuje zmienne t, n_po_k; musi byc n > 0 }
var a, b:Longint;
begin
  if n >= k then begin
    a:=n-k; b:=n;
    skroc(a, b);
    n_po_k:=(n_po_k div b)*a
  end;
  Dec(n);
  t:=(t+n_po_k-1) div 2
end;

procedure zmniejsz_k;
{ zmniejsza k o 1, aktualizuje zmienne t, n_po_k; musi by† k > 0 }
var a, b:Longint;
begin
  t:=t-n_po_k;
  if n >= k then begin
    a:=k; b:=n-k+1;
    skroc(a, b);
    n_po_k:=(n_po_k div b)*a
  end;
  if n = k-1 then
    n_po_k:=1;
  Dec(k)
end;

procedure ile_pytan;
begin
  k:=jajka1;
  n:=0; n_po_k:=0; t:=0;
  while t < wysokosc1 do
    zwieksz_n
end;

procedure daj_odpowiedz(losowa_odp:Integer);
{ musi byc k > 0 }
begin
  if n = 0 then begin
    { moduˆ zawodnika ju¾ zadaˆ wi©cej pytaä ni¾ potrzeba }
    if pietro > max_wyt then
      odpowiedz:=NIE;
    if pietro <= min_wyt then
      odpowiedz:=TAK;
    if (min_wyt < pietro) and (pietro <= max_wyt) then
      { mo¾na odpowiedzie† TAK lub NIE }
      if losowa_odp = 1 then
        odpowiedz:=TAK
      else
        odpowiedz:=NIE
  end
  else begin
    zmniejsz_n;

    if pietro > max_wyt then begin
      odpowiedz:=NIE;
      zmniejsz_k
    end;
    if pietro <= min_wyt then
      odpowiedz:=TAK;
    if (min_wyt < pietro) and (pietro <= max_wyt) then
      { mo¾na odpowiedzie† TAK lub NIE }

      if t < max_wyt-pietro then
	{ zbyt nisko zrzucone jajko }
	odpowiedz:=TAK
      else begin
	zmniejsz_k;
	if t < pietro-min_wyt-1 then
	  { zbyt wysoko zrzucone jajko }
	  odpowiedz:=NIE
	else begin
	  { przy obu odpowiedziach moduˆ zawodnika zachowuje szanse na
	    wygranie }
	  if n = 0 then
	    { to byˆo ostatnie 'dozwolone' pytanie }
	    if losowa_odp = 1 then begin
	      odpowiedz:=TAK;
	      zwieksz_k
	    end
	    else
	      odpowiedz:=NIE
	  else begin
	    { zostaˆo jeszcze najmniej 1 'dozwolone' pytanie }
	    zmniejsz_n;
	    if t >= pietro-min_wyt-1 then begin
	      { odpowied« NIE umozliwiˆaby moduˆowi zawodnika zadanie
		mniejszej liczby pytaä ni¾ wystarczy_pytan }
	      odpowiedz:=TAK;
	      zwieksz_k
	    end
	    else begin
	      zwieksz_k;
	      if t >= max_wyt-pietro then begin
		{ odpowied« TAK umozliwiˆaby moduˆowi zawodnika zadanie
		  mniejszej liczby pytaä ni¾ wystarczy_pytan }
		odpowiedz:=NIE;
		zmniejsz_k
	      end
	      else
		{ obie odpowiedzi mog¥ wymusi† na module zawodnika zadanie
		  dokˆadnie wystarczy_pytan pytaä }
		if losowa_odp = 1 then
		  odpowiedz:=TAK
		else begin
		  odpowiedz:=NIE;
		  zmniejsz_k
		end
	    end;
	    zwieksz_n
	  end
	end
      end
  end;

  { aktualizacja zmiennych: rozbitych, min_wyt, max_wyt }
  if odpowiedz = NIE then begin
    Inc(ile_rozbitych);
    if pietro <= max_wyt then
      max_wyt:=pietro-1
  end
  else
    if pietro > min_wyt then
      min_wyt:=pietro
end;


var
  i, j, losowych_odp, liczba_prob:Integer;
  losowe_odp:Array [1..MAX_LOSOWYCH_ODP] of Integer;
  fin, fout:Text;
  blad:Boolean;

begin
  Assign(fin, 'JAJ.IN');
  Assign(fout, 'JAJ.OUT');
  Reset(fin);
  Rewrite(fout);

  Readln(fin, liczba_prob);
  for i:=1 to liczba_prob do begin
    Readln(fin, wysokosc1, jajka1, min_wyt, max_wyt);
    wysokosc:=wysokosc1;
    jajka:=jajka1;
    Read(fin, losowych_odp);
    for j:=1 to losowych_odp do
      Read(fin, losowe_odp[j]);
    Readln(fin);

    wiem:=NIE;

    ile_pytan;
    wystarczy_pytan:=n;

    liczba_pytan:=0;
    ile_rozbitych:=0;
    nowy_eksperyment;
    blad:=False;
    repeat
      if ile_rozbitych < jajka1 then begin
	daj_pytanie;
	Inc(liczba_pytan)
      end;

      if (pietro < 0) or (pietro > wysokosc1) or (ile_rozbitych = jajka1) then
	blad:=True
      else begin
	daj_odpowiedz(losowe_odp[((liczba_pytan-1) mod losowych_odp) + 1]);
	analizuj_odpowiedz
      end
    until (wiem = TAK) or blad;

    if (wiem = TAK) and (not blad) and (min_wyt = x) and (x = max_wyt) and
       (liczba_pytan <= wystarczy_pytan) then
      Writeln(fout, 'OK')
    else begin
      Write(fout, 'ZLE:');
      if blad then
	if ile_rozbitych = jajka1 then
	  Writeln(fout, ' za duzo rozbitych jajek!')
	else
	  Writeln(fout, ' proba zrzucenia jajka z pietra spoza zakresu!')
      else begin
	if liczba_pytan > wystarczy_pytan then
	  Write(fout, ' za duzo pytan o wytrzymalosc jajka!');
	if (min_wyt <> max_wyt) or (x <> min_wyt) then
	  Write(fout, ' zle wyznaczona wytrzymalosc!');
	Writeln(fout)
      end
    end
  end;

  Close(fin);
  Close(fout)
end.

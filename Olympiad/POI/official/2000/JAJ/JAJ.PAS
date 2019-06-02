{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi•zanie zadania: JAJKA                                          *}
{*   Plik:                JAJ.PAS                                        *}
{*   Autor:               PAWEù WOLFF                                    *}
{*************************************************************************}

unit jaj;

interface

procedure nowy_eksperyment;
procedure daj_pytanie;
procedure analizuj_odpowiedz;


implementation

uses jajmod;

var
  n, k, n_po_k, t:Longint;
  min_wyt, max_wyt, aktualne_pietro:Longint;


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
{ zmniejsza n o 1, aktualizuje zmienne t, n_po_k; musi byÜ n > 0 }
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
{ zmniejsza k o 1, aktualizuje zmienne t, n_po_k; musi byÜ k > 0 }
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


procedure nowy_eksperyment;
begin
  wiem:=NIE;

  k:=jajka;
  min_wyt:=0;
  max_wyt:=wysokosc;

  n:=0; n_po_k:=0; t:=0;
  while t < wysokosc do
    zwieksz_n
end;

procedure daj_pytanie;
begin
  zmniejsz_n;
  zmniejsz_k;
  aktualne_pietro:=min(min_wyt+t+1, max_wyt);
  pietro:=aktualne_pietro
end;

procedure analizuj_odpowiedz;
begin
  if odpowiedz = TAK then begin
    min_wyt:=aktualne_pietro;
    zwieksz_k
  end
  else
    max_wyt:=aktualne_pietro-1;

  if min_wyt = max_wyt then begin
    wiem:=TAK;
    x:=min_wyt
  end
end;


begin
end.

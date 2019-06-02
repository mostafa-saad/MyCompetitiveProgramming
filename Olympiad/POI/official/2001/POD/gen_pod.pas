{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Zadanie:             PODRӯ                                         *}
{*   Plik:                GEN_POD.PAS                                    *}
{*   Autor:               MARCIN STEFANIAK                               *}
{*************************************************************************}

{ progam do generowania losowych testy dla zadania Podroz }

{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V+,X+}
{$M 16384,0,655360}
program gen_Podroze;

const MAX_N =10000;
      cze:array[1..7] of integer = (6, 10, 12, 15, 20, 30, 60);

var f : text;
    p, max, min, t, i, j, id, n, k, s, s1, l : longint;
    st: string;

    prz: array[1..MAX_N] of byte;

begin
  randomize;
  Writeln('Generator losowych testow do zadania "Podroze"');
  write('Podaj nr testu:');  read(id); str(id, st);
  write('Podaj liczbe stacji n = '); read(n);
  write('Podaj liczbe linii  k = '); read(k);
  write('Podaj laczna liczbe przystankow l = '); read(l);
  write('Podaj max. liczbe przystankow w linii s = '); read(s);
  if s > n then s:=n;
  write('Podaj sredni czas przejazdu t = '); read(t);

  assign(f, 'pod'+st+'.in'); rewrite(f);
  writeln(f, n,' ',k,' ',random(n) + 1,' ',random(n) + 1,
               ' ',random(24),' ',random(60));

  for i := 1 to k do begin {kolejna linia}

    max := s; min := 2;
    if l-2*(k-i) {ile maksymalnie zostanie} < max then max := l-2*(k-i);
    if l-s*(k-i) > min then min := l-s*(k-i);

    (*write('i=',i,' l=',l,' min=',min,' max=',max);*)

    if max < min then writeln('BLAD max < min');

    s1 := min + random(max - min + 1);
    writeln(' s1=',s1);
    {ile przystankow ta linia ma}
    l := l - s1;

    writeln(f, s1,' ',cze[random(7)+1]);

    fillchar(prz, sizeof(prz), 0);
    for j := 1 to s1 do begin
      repeat p := random(n)+1 until prz[p] = 0;
      prz[p] := 1;
      write(f, p); if j < s1 then write(f,' ');
    end;
    writeln(f);
    for j := 1 to s1-1 do begin
      write(f, random(2*t)+1);
      if j < s1-1 then write(f,' ');
    end;
    writeln(f);
    write('.');

  end;

  close(f);
end.



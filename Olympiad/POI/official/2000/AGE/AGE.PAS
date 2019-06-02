{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: AGENCI                                         *}
{*   Plik:                AGE.PAS                                        *}
{*   Autor:               MARCIN MUCHA                                   *}
{*************************************************************************}

const
   fin_name = 'age.in';
   fout_name = 'age.out';

   N_MAX = 250;

type
   parr = ^tarr;
   tarr = array[1..N_MAX,1..N_MAX] of byte;

   pbuffer = ^tbuffer;
   tbuffer = array[1..N_MAX*N_MAX] of byte;

var
   n, a1, a2 : byte;
   m : word;
   G : array[1..N_MAX] of
          record
             deg : byte;
             next : array[1..N_MAX] of byte;
          end;

procedure read_data;
var
   fin : text;
   i, j, k : word;

begin
   assign( fin, fin_name);
   reset( fin);
   readln( fin, n, m);

   for i := 1 to n do
      G[i].deg := 0;

   readln( fin, a1, a2);

   for i := 1 to m do
      begin
         readln( fin, j, k);
         inc( G[j].deg);
         G[j].next[G[j].deg] := k
      end;
   close( fin)
end;

procedure compute;
var
   arrs: array[0..1] of parr; { Tablice par (x,y), do kt¢rych da si© doj˜†. }
   { 0 <-> x=y; 1 <-> x<>y }
   arr_from, arr_to : byte; { Na kt¢rej tablicy dziaˆamy. }
   buffer : array[0..1] of pbuffer; { Bufor na przechowywanie
                                      nowych par (x,y). }
   nbuffer : array[0..1] of pbuffer;
   buf_size, nbuf_size : word; { Ilo˜† danych w buforze. }
   mov_no : word; { Numer ruchu. }
   pair, new_pair : array[0..1] of byte;
   i, j : word;
   tmp: pbuffer;
   OK : boolean;
   fout : text;
begin
    OK := false;
    arrs[0] := new( parr); arrs[1] := new( parr);
    buffer[0] := new( pbuffer); buffer[1] := new( pbuffer);
    nbuffer[0] := new( pbuffer); nbuffer[1] := new( pbuffer);

    for i := 1 to n do
       for j := 1 to n do
          begin
             arrs[0]^[i][j] := 0;
             arrs[1]^[i][j] := 0
          end;
    arrs[0]^[a1][a2] := 1;

    buf_size := 1; buffer[0]^[1] := a1; buffer[1]^[1] := a2;
    mov_no := 0; arr_from := 1; arr_to := 0;

    repeat
       arr_from := 1 - arr_from; arr_to := 1 - arr_to;
       if arr_to = 1 then inc( mov_no);
       nbuf_size := 0;

       for i := 1 to buf_size do
          begin
             pair[0] := buffer[0]^[i]; pair[1] := buffer[1]^[i];
             new_pair[arr_to] := pair[arr_to];
             for j := 1 to G[pair[arr_from]].deg do
                                 { arr_from - kt¢ry si© rusza }
                begin
                   new_pair[arr_from] := G[pair[arr_from]].next[j];
                                                       { kolejny s¥siad }
                   if arrs[arr_to]^[new_pair[0]][new_pair[1]] = 0 then
                      begin
                         arrs[arr_to]^[new_pair[0]][new_pair[1]] := 1;
                         inc( nbuf_size);
                         nbuffer[0]^[nbuf_size] := new_pair[0];
                         nbuffer[1]^[nbuf_size] := new_pair[1];
                         if ( new_pair[0] = new_pair[1])
                              and  ( arr_to = 0) then
                            OK := true
                      end;
                end;
          end;
       buf_size := nbuf_size;
       tmp := buffer[0]; buffer[0] := nbuffer[0]; nbuffer[0] := tmp;
       tmp := buffer[1]; buffer[1] := nbuffer[1]; nbuffer[1] := tmp
    until OK or ( mov_no > n * n);

    assign( fout, fout_name);
    rewrite( fout);
    if OK then
       writeln( fout, mov_no)
    else
       writeln( fout, 'NIE');
    close( fout);

    dispose( arrs[0]); dispose( arrs[1]);
    dispose( buffer[0]); dispose( buffer[1]);
    dispose( nbuffer[0]); dispose( nbuffer[1])
end;


begin
   read_data;
   compute;
end.
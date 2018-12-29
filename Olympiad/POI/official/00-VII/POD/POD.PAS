{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: PODPISY                                        *}
{*   Plik:                POD.PAS                                        *}
{*   Autor:               Marcin Mucha                                   *}
{*************************************************************************}

const
   fin_name = 'pod.in';
   fout_name = 'pod.out';

   N_MAX = 500;

   ST_UNKNOWN = 0;
   ST_CLEAN   = N_MAX + 1; {Co najmniej dwa por©czenia.}

type
   t_array = array[1..N_MAX] of word;
   p_array = ^t_array;
   t_official =
      record
         status : word;
         cpt : boolean; {Czy jest dow¢dc¥?}
         vouchees_no : word; {Liczba por©czanych urz©dnik¢w.}
         vouchees : p_array; {Por©czani urz©dnicy.}
      end;

var
   officials : array[1..N_MAX] of t_official;
   n : word;

procedure read_data;
var
   fin : text;
   i, j, m_i, v : word;
begin
   assign( fin, fin_name);
   reset( fin);

   readln( fin, n);
   for i := 1 to n do
      with officials[i] do
         begin
            vouchees_no := 0;
            getmem( vouchees, 2 * n)
         end;

   for i := 1 to n do
      begin
         read( fin, m_i);
         officials[i].cpt := ( m_i = 0);
         for j := 1 to m_i do
            begin
               read( fin, v);
               with officials[v] do
                  begin
                     inc( vouchees_no);
                     vouchees^[vouchees_no] := i
                  end
            end
      end;
   close( fin);
end;

procedure find_suspects;
var
   i : word;

procedure go_down( no : word);
var
   i : word;
   captain : word;
begin
   captain := officials[no].status;
   for i := 1 to officials[no].vouchees_no do
      with officials[officials[no].vouchees^[i]] do
         begin
{ Je˜li pierwszy raz wchodzimy do wierzchoˆka,
to przepisujemy status z ojca.}
            if ( status = 0) then
               begin
                  status := captain;
                  go_down( officials[no].vouchees^[i])
               end
{ Je˜li znale«li˜my drugiego dow¢dc©, to ten urz©dnik jest "czysty".}
            else if ( ( status < ST_CLEAN) and ( status <> captain)) then
               begin
                  status := ST_CLEAN;
                  go_down( officials[no].vouchees^[i])
               end
         end
end; {go_down}

begin
   for i := 1 to n do
      officials[i].status := ST_UNKNOWN;

   for i := 1 to n do
      if officials[i].cpt then {Dow¢dca.}
         begin
            officials[i].status := i;
            go_down( i);
            officials[i].status := ST_CLEAN
         end
end;

procedure clean_up;
var
   i : word;
begin
   for i := 1 to n do
      freemem( officials[i].vouchees, 2 * n)
end;

procedure write_result;
var
   i : word;
   no_suspects : boolean;
   fout : text;
begin
   assign( fout, fout_name);
   rewrite( fout);
   no_suspects := true;
   for i := 1 to n do
      if officials[i].status <> ST_CLEAN then
         begin
            writeln( fout, i);
            no_suspects := false
         end;
   if no_suspects then
      writeln( fout, 'BRAK');
   close( fout)
end;

begin
   read_data;
   find_suspects;
   clean_up;
   write_result
end.
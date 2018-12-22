
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task NATRIJ
  Programming language Pascal
*)

program natrij;

var
   h1, m1, s1, h2, m2, s2 : longint;
   sekundi                : longint;

procedure ucitaj1(var hh, mm, ss : longint);
var
   red   : string;
   smece : integer;
begin
   readln(red);
   val(copy(red, 1, 2), hh, smece);
   val(copy(red, 4, 2), mm, smece);
   val(copy(red, 7, 2), ss, smece);
end;

function tostr(x : longint):string;
begin
   str(x, tostr);
   while length(tostr)<2 do
      tostr := '0'+tostr;
end;

begin
   ucitaj1(h1, m1, s1);
   ucitaj1(h2, m2, s2);

   sekundi := (h2-h1)*60*60 + (m2-m1)*60 + s2-s1;
   if sekundi <= 0 then
      sekundi := sekundi + 24*60*60;

   writeln(tostr(sekundi div 60 div 60), ':',
           tostr(sekundi div 60 mod 60), ':',
           tostr(sekundi mod 60));
end.

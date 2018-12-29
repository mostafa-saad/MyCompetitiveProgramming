(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Banknoty)                                 *
 *   Plik:                ban.cpp                                        *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Weryfikator wyj¶cia do zadania BAN (Banknoty)  *
 *                        u¿ycie:                                        *
 *                        banchk dane.in wynik_prog.out odp_wzorc.out    *
 *                                                                       *
 *************************************************************************)

var
  fin, fout, f : Text;
  s1, s2, s3 : String;
  w, w1, n, m, i, wyn, k : LongInt;
  b, c : array[1..500] of LongInt; 

function read_token(var f : Text) : String;
const
  max_token = 200;
  white     = [' ', chr(10), chr(13), chr(9)];
var
  ch  : Char;
  i   : Integer;
  tmp : String;
begin
  ch := ' ';
  while (not eof(f)) and (ch in white) do
    Read(f,ch);
  if ch in white then
    read_token := 'EOF'
  else
  begin
    tmp := ch;
    i := 0;
    while (not eof(f)) and (i < max_token) do
    begin
      Inc(i);
      Read(f,ch);
      if ch in white then
        break;
      tmp := tmp + ch;
    end; {while}
    read_token := tmp
  end {else}
end; {read_token}
    
function value(s : String) : LongInt;
var
  tmp  : LongInt;
  code : Word;
begin
  Val(s,tmp,code);
  if code <> 0 then
    tmp := - 1;
  value := tmp
end; {value}

function tostr(l : LongInt) : String;
var
  tmp : String;
begin
  Str(l,tmp);
  tostr := tmp
end; {tostr}

procedure error(info:String);
begin
    WriteLn('WRONG');
    WriteLn(info);
    Close(fout);
    Halt(1)
end; {error}

function ReadInt(var f : Text; l, u : Integer) : Integer;
var
  s : String;
  v : LongInt;
begin
  s := read_token(f);
  v := value(s);
  if (v >= l) and (v <= u) then
    ReadInt := v
  else
    error('An integer (ranged between ' + tostr(l) + ' and ' + tostr(u) + ') expected, but read ' + s)
end; {ReadInt}

begin
  s1 := ParamStr(1);
  s2 := ParamStr(2);
  s3 := ParamStr(3);
  Assign(fin,s1);
  Reset(fin);
  Assign(fout,s2);
  Reset(fout);
  Assign(f,s3);
  Reset(f);

  w:=ReadInt(fout,1,20000);
  w1:=ReadInt(f,1,20000);
  if w1<>w then
    error('Zbyt wiele u¿ytych banknotów');
  Read(fin,n);
  for i:=1 to n do
    Read(fin,b[i]);
  for i:=1 to n do
    Read(fin,c[i]);
  Read(fin,k);
  
  wyn:=0;
  w:=0;
  for i:=1 to n do
  begin
    m:=ReadInt(fout,0,20000);
    if m>c[i] then
      error('Banknot '+tostr(i)+' u¿yty wiêcej razy ni¿ jest');
    wyn:=wyn+m*b[i];
    w:=w+m;
  end;
  if w1<>w then
    error('U¿yto niew³a¶ciwej liczby monet');
  if wyn<>k then
    error('U¿yte banknoty nie daj± poprawnej sumy');
  if not eof(fout) then
    error('Plik wyj¶ciowy zawiera zbêdn± zawarto¶æ');
  WriteLn('OK');
  Close(fin);
  Close(fout);
  Close(f);
end.     

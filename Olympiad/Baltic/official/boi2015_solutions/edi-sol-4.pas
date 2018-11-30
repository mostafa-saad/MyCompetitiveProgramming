{ Jan Kanty Milczek, Jakub Radoszewski }

function max(x, y : LongInt) : LongInt;
begin
	if x > y then
		max := x
	else
		max := y;
end;

function max3(x, y, z : LongInt) : LongInt;
begin
	max3 := max(x, max(y, z));
end;

type TPersTree = ^PersTree;
  PersTree = record
  l, r : TPersTree;
  key, value, max_value : LongInt;
end;

procedure makePersTree(t, _l, _r : TPersTree; _key, _value, _max_value : LongInt);
begin
  with t^ do begin
    l := _l; r := _r;
    key := _key; value := _value; max_value := _max_value;
  end;
end;

function safe_max_value(x : TPersTree) : LongInt;
begin
	if x = NIL then
		safe_max_value := 0
  else
    safe_max_value := x^.max_value;
end;

function find(t : TPersTree; mxkey : LongInt) : LongInt;
begin
	if mxkey < t^.key then
		find := find(t^.l, mxkey)
	else if mxkey = t^.key then
		find := max(safe_max_value(t^.l), t^.value)
	else { if (mxkey > key) }
    find := max3(safe_max_value(t^.l), t^.value, find(t^.r, mxkey));
end;

function add(t : TPersTree; _key, nvalue : LongInt) : TPersTree;
var
  _l, _r, _t : TPersTree;
  _value : LongInt;
begin
	_l := t^.l;
  _r := t^.r;
	_value := t^.value;

	if _key < t^.key then
		_l := add(t^.l, _key, nvalue)
	else if _key = t^.key then
		_value := nvalue
	else { if (_key > key) }
    _r := add(t^.r, _key, nvalue);

  New(_t);
	makePersTree(_t, _l, _r, t^.key, _value, max3(safe_max_value(_l), _value, safe_max_value(_r)));
  add := _t;
end;

function create_pers_tree(left, right : LongInt) : TPersTree;
var
  s : LongInt;
  t : TPersTree;
begin
	if left > right then
    t := NIL
  else
  begin
	  s := (left + right) div 2;
    New(t);
    makePersTree(t, create_pers_tree(left, s - 1), create_pers_tree(s + 1, right), s, 0, 0);
  end;
  create_pers_tree := t;
end;

const M = 300005;
var
  n, i, op, cof : LongInt;
  wyn : array[0 .. M - 1] of LongInt;
  akt : array[0 .. M - 1] of TPersTree;

begin
  ReadLn(n);
	akt[0] := create_pers_tree(0, n);
	wyn[0] := 0;

  for i := 1 to n do
  begin
    Read(op);
		if op > 0 then
    begin
			wyn[i] := op;
			akt[i] := add(akt[i - 1], 0, i);
		end else
    begin
			cof := find(akt[i - 1], -op - 1) - 1;
			wyn[i] := wyn[cof];
			akt[i] := add(akt[cof], -op, i);
    end;
    WriteLn(wyn[i]);
  end;
end.

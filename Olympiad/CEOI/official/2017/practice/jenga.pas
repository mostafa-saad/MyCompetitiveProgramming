program jenga;
var memo: array[0..3010,0..3010,0..3] of integer;
levels,rm2,rm1,top,i,j,k:integer;
state: array[1..3010] of integer;

function opponent() : boolean;
var nivo, palica: integer;
begin
	read(nivo,palica);
	state[nivo]:=state[nivo]-(1<<(palica - 1));
	if (state[nivo]<2) or (state[nivo]=4) then opponent := false
	else
	begin
		if state[nivo]=5 then
		begin
			rm2:=rm2 - 1;
			top := top + 1;
		end;
		if state[nivo]=2 then
		begin
			rm1:=rm1 - 1;
			top:=top + 1;
		end;
		if (state[nivo]=3) or (state[nivo]=6) then
		begin
			rm2:=rm2 - 1;
			rm1:=rm1 + 1;
			top:=top + 1;
		end;
		opponent:=true;
	end;
end;

function action(r2,r1,t: integer) :integer;
begin
	if t>3 then 
	begin
		t:=t - 3;
		r2:=r2+1;
	end;
	if memo[r2,r1,t] <> -1 then action := memo[r2,r1,t]
	else
	begin
		memo[r2,r1,t]:=0;
		if (r1>0) and (action(r2,r1-1,t+1)=0) then memo[r2,r1,t]:=1;
		if (r2>0) and (action(r2-1,r1,t+1)=0) then memo[r2,r1,t]:=2;
		if (r2>0) and (action(r2-1,r1+1,t+1)=0) then memo[r2,r1,t]:=3;
		action:=memo[r2,r1,t];
	end;	
end;

procedure move();
var strategy,storey,block:integer;
begin
	storey:=1;
	strategy := action(rm2,rm1,top);
	if strategy=1 then
	begin
		while (state[storey]<>3) and (state[storey]<>6) do storey:=storey+1;
		if state[storey]=3 then block:=1 else block := 3;
		rm1:=rm1-1;
		top := top+1;
	end;
	if strategy=2 then
	begin
		while state[storey]<>7 do storey:=storey+1;
		block:=2;
		rm2:=rm2-1;
		top := top+1;
	end;
	if strategy=3 then
	begin
		while state[storey]<>7 do storey:=storey+1;
		block:=1;
		rm2:=rm2-1;
		rm1:=rm1+1;
		top:=top+1;
	end;
	state[storey]:=state[storey]-(1<<(block-1));
	writeln(storey,' ',block);
	Flush(Output);
end;

begin
	read(levels);
	for i:= 0 to 3010 do
		begin
		for j:= 0 to 3010 do
			begin
			for k:= 0 to 3 do
				memo[i,j,k]:=-1;
			end;
		end;
	if action(levels-1,0,3)=0 then writeln('second') else writeln('first');
	Flush(Output);
	for i:= 1 to 3010 do state[i]:=7;
	rm2:=levels-1;
	rm1:=0;
	top:=3;
	if action(levels-1,0,3)>0 then move();
	while opponent() do
	begin
		if top>3 then
		begin
			top:=top-3;
			rm2:=rm2+1;
			levels:=levels+1;
		end;
		move();
	end;
end.

{ Tug of War
   Autor: Piotr Smulewicz
 }
const SIZE = 30001;
const MAX_STRENGHT =20;
const BACK_PACK_SIZE =SIZE*MAX_STRENGHT+1;
var 
	persons: array[0..SIZE*2-1,0..1] of Longint;
	str: array[0..SIZE*2-1] of Longint;
	assigned: array[0..SIZE*2-1] of Boolean;
	spots: array[0..SIZE*6-1] of Longint;
	spots_size: array[0..SIZE*2-1] of Longint;
	next_spot:array[0..SIZE*6-1] of Longint;
	next_spot_ut:Longint;
	item:array[0..BACK_PACK_SIZE-1] of Longint;
	opt:array[0..SIZE*2-1] of Longint;
	back_pack:array[0..BACK_PACK_SIZE] of Boolean;
	l,mi2,st,tmp,poz,s_pe,i,n,j,s,a,b,pe,mi,k,sum_all,sum,res:Longint;
begin
	res:=BACK_PACK_SIZE;
	
	read(n,k);
	
	for i := 0 to 2*n+1 do
	begin
		assigned[i]:=false;
		opt[i]:=0;
		spots_size[i]:=0;
		next_spot[i]:=-1;
		spots[i]:=-2;
		item[i]:=0;
	end;
	sum:=0;
	sum_all:=0;
	next_spot_ut:=n*2+2;
	for i := 0 to 2*n-1 do
	begin
		read(a,b,s);
		str[i]:=s;
		persons[i,0]:=a*2;
		persons[i,1]:=b*2+1;
		for j:=0 to 1 do
		begin
			tmp:=persons[i,j];
			if spots[tmp]<> -2 then
			begin
				spots[next_spot_ut]:=spots[tmp];
				next_spot[next_spot_ut]:=next_spot[tmp];
				next_spot[tmp]:=next_spot_ut;
				next_spot_ut:=next_spot_ut+1;
			end;
			spots_size[tmp]:=spots_size[tmp]+1;
			spots[tmp]:=i;
		end
	end;
	//writeln(next_spot_ut);
	for s_pe := 0 to 2*n-1 do
	begin
		pe:=s_pe;
		while not assigned[pe] do
		begin 
			for j := 0 to 1 do
			begin
				mi:=persons[pe,j];
				if opt[mi]+1=spots_size[mi] then
				begin
					assigned[pe]:=true;
					sum:=sum+(1-2*(mi mod 2))*str[pe];
					mi:=persons[pe,1-j];
					opt[mi]:=opt[mi]+1;
					break;
				end;
			end;
			if(spots_size[mi]=opt[mi]+1)then
			begin
				poz:=mi;
				while (assigned[spots[poz]]) and (poz<>-1) do
					poz:=next_spot[poz];
				if(poz<>-1) then
					pe:=spots[poz]
				else
					break;
			end
			else
				break;
		end;
	end;
	sum:=abs(sum);
	item[sum]:=item[sum]+1;
	sum_all:=sum_all+sum;
	//writeLn('sum_ ',sum);
	for s_pe := 0 to 2*n-1 do
	begin
		sum:=0;
		pe:=s_pe;
		st:=0;
		mi2:=persons[pe,1];
		if(assigned[pe])then continue;
		while(not assigned[pe])do
		begin
			sum+=(1-2*st)*str[pe];
			assigned[pe]:=true;
			mi:=persons[pe,st];
			//writeLn('persons ',pe,' ',st);
			poz:=mi;
			while poz<>-1 do
			begin
				//writeLn('poz ',poz,' ',spots[poz]);
				if not assigned[spots[poz]] then break;
				poz:=next_spot[poz];
			end;
			if(poz<>-1) then
				pe:=spots[poz];
			st:=1-st;
			//writeLn('mi ',mi);
		end;
		//writeLn('mi ',mi,' ', mi2);
		if(mi<>mi2)then
		begin
			WriteLn('NO');
			halt;
		end;
		sum:=abs(sum);
		if(sum<>0) then
			item[sum]:=item[sum]+1;
		sum_all:=sum_all+sum;
		//WriteLn('sum ',sum);
	end;
	back_pack[0]:=true;
	for i := 0 to BACK_PACK_SIZE-1 do
	begin
		if item[i]=0 then continue;
		//WriteLn('item ',i);
		for j := BACK_PACK_SIZE div 2 downto 0 do
		begin
			if back_pack[j] then
			begin
				for l := 1 to item[i] do
				begin
					//WriteLn(j+l*i);
					if back_pack[j+l*i] then break;
					back_pack[j+l*i]:=true;
				end;
			end;
		end;
	end;
	for j := sum_all div 2 downto 0 do
	begin
		//WriteLn(j);
		if back_pack[j] then
		begin
			//writeLn(j);
			res:=sum_all-2*j;
			break;
		end;
	end;
	
	if res<=k then
		WriteLn('YES')
	else
		WriteLn('NO');	
end.

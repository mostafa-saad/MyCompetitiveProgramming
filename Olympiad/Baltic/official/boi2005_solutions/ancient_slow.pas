{
TASK: ANCIENT
LANG: PASCAL
}
{ paprasèiausias lëtas rekursinis sprendimas }

program ancient;
  const DF = 'ANCIENT.IN';
        RF = 'ANCIENT.OUT';
        MAX = 15;
        balses: set of char = ['a',  'e', 'i', 'o', 'u'];

  type mas = array [0..MAX]of integer;

  procedure spresti (VE, VC, CE, CC: integer; z: string; var kiek: int64);

    var vcs, ves, ccs, ces: mas;
        ilgis: integer;

    function tinka (z: string; i: integer): boolean;
    { tikrina, ar þodþio pradþia iki i-osios raidës neprieðtarauja
      taisyklëms }
    begin
      if z[i] in balses { jei ten balsë }
         then begin
                ccs[i] := 0; ces[i] := 0;
                if (i > 1) and (z[i-1] in balses)
                   then vcs[i] := vcs[i-1] + 1
                   else vcs[i] := 1;
                if (z[i] = z[i-1]) and (i>1)
                   then ves[i] := ves[i-1] + 1
                   else ves[i] := 1;
              end
         else begin { jei priebalsë }
                vcs[i] := 0; ves[i] := 0;
                if (i > 1) and not (z[i-1] in balses)
                   then ccs[i] := ccs[i-1] + 1
                   else ccs[i] := 1;
                if (z[i] = z[i-1]) and (i > 1)
                   then ces[i] := ces[i-1] + 1
                   else ces[i] := 1
             end;

      tinka := (ces[i] <= CE) and (ves[i] <= VE) and
               (ccs[i] <= CC) and (vcs[i] <= VC);
    end; { tinka }

    procedure formuoti (i: byte);
      var r: char;
    begin
      if i > ilgis { þodis suformuotas }
          then kiek := kiek + 1
      else if z[i] = '*' { jei raidë neáraðyta }
              then  begin
                    for r := 'a' to 'z' do
                      begin
                        z[i] := r;
                        if tinka(z, i)
                            then formuoti (i+1);
                      end;
                    z[i] := '*'; { atstatoma reikðmë }
                  end
               else if tinka (z, i) { jei raidë áraðyta }
                       then formuoti (i+1);
    end; { formuoti }

  begin
    kiek := 0;
    ves[0] := 0; vcs[0] := 0;
    ces[0] := 0; ccs[0] := 0;
    ilgis := length(z);
    formuoti (1);
  end; { spræsti }

  procedure skaityti (var VE, VC, CE, CC: integer; var z: string);
    var f: text;
  begin
    assign (f, DF);
    reset (f);
    readln (f, VE, VC, CE, CC);
    readln (f, z);
    close (f);
  end; { skaityti }

  procedure rasyti (kiek: longint);
    var f: text;
  begin
    assign (f, RF);
    rewrite (f);
    writeln (f,kiek);
    close (f);
  end;

  var VE, VC, CE, CC: integer;
      kiek: int64;
      z: string;
begin
  skaityti (VE, VC, CE, CC, z);
  spresti (VE, VC, CE, CC, z, kiek);
  rasyti (kiek);
end.

{Ejemplo 4}
PROGRAM ejemplo;
var a, c, d: boolean;
    b: integer;

function f1(p1:integer; p2:boolean): integer;
var resultado: integer;
begin
    while p2 do
    begin
        reSultAdo { Este es un comentario en medio de una instruccion} := p1 * 2;
        if $p1 = 5$ then
            p2 := false;
    end;
	f1 := RESULTADO;
end;

procedure p1;
begin
    write(3 + 4 * 5 = 8);
end;

begin
    a := not false;
    read(b);
    write(f1(b, a));
    p1;
end.

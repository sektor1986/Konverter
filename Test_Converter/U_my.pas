unit U_my;

interface

uses Forms, SysUtils;

function ApplicationFilePath():string;

implementation

function ApplicationFilePath():string;
begin
  Result := ExtractFilePath(Application.ExeName);
end;

end.

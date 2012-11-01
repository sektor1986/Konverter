program Test_Converter;

uses
  Forms,
  Unit_Glavn in 'Unit_Glavn.pas' {Form_Glavn},
  VCI3Types in 'vci_3\VCI3Types.pas',
  Vci3Can in 'vci_3\Vci3Can.pas',
  VCI3Error in 'vci_3\VCI3Error.pas',
  Vci3Lin in 'vci_3\Vci3Lin.pas',
  UnitRxThread in 'UnitRxThread.pas',
  ABOUT in 'ABOUT.pas' {AboutBox},
  U_my in 'U_my.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm_Glavn, Form_Glavn);
  Application.CreateForm(TAboutBox, AboutBox);
  Application.Run;
end.

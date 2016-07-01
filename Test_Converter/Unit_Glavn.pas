unit Unit_Glavn;

// ------------ V1.1 12.05.2015 ------------
// Добавлена кнопка Включить "СТОП" сигнал для отправки сообщения по PGN $FE4F

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, StdCtrls, Buttons, sBitBtn, ExtCtrls, sBevel, UnitRxThread, Vci3Can, VCI3Error,
  sLabel, iComponent, iVCLComponent, iCustomComponent, iPositionComponent,
  iScaleComponent, iThermometer, iThreadTimers, ComCtrls, sStatusBar, DateUtils, sCheckBox;

const
  BitTimingReg0 = CAN_BT0_250KB;
  BitTimingReg1 = CAN_BT1_250KB;
  BitTimingString = '250 kbit/s';
  F_STATUS_ERASESECTOR = 0;
  F_STATUS_SETADDRESS = 1;
  F_STATUS_DATA = 2;
  F_STATUS_END = 3;

type

  DEVICEINFO = packed record
    addr: Byte;
    typeMCU: Byte;
    flashRewrites: Word;
    identifer: Cardinal;
  end;
  TForm_Glavn = class(TForm)
    MainMenu1: TMainMenu;
    N1: TMenuItem;
    sBevel1: TsBevel;
    sBitBtn1: TsBitBtn;
    iThermometer1: TiThermometer;
    iThermometer2: TiThermometer;
    sLabel1: TsLabel;
    sLabel2: TsLabel;
    sLabelFX1: TsLabelFX;
    sLabelFX2: TsLabelFX;
    iThreadTimers1: TiThreadTimers;
    stbBottom: TsStatusBar;
    N2: TMenuItem;
    sLabelFX3: TsLabelFX;
    sLabelFX4: TsLabelFX;
    sCheckBox1: TsCheckBox;
    procedure N1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure sBitBtn1Click(Sender: TObject);
    procedure iThreadTimers1Timer1(Sender: TObject);
    procedure N2Click(Sender: TObject);
    procedure iThreadTimers1Timer2(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    m_hDeviceHandle: THandle; // the handle to the interface
    m_dwCanNo: LongLong; // the number of the can controller 0/1
    m_hCanChannel: THandle; // the handle to the can channel
    m_hCanChannelRex: THandle;
    m_hCanControl: THandle; // the handle to the can controller
    m_dwTimerResolution: LongWord; // the timer resolution of the controller
    m_dwTimerOverruns: LongWord; // number of timer overruns
    m_qwOverrunValue: Int64; // stored value to add to every timestamp
    m_ReceiveQueueThread: TReceiveQueueThread; // a thread to receive data
    DevInfo: DEVICEINFO;
    devices: array of DEVICEINFO;
    flagAirData: Boolean;
    flagFuelData: Boolean;
    intervalAirTemperature_old: Cardinal;
    intervalFuel_old: Cardinal;
    procedure InitSocket();
    procedure InitSocketRec();
    procedure ShowErrorMessage(errorText: string; hFuncResult: HResult);
    procedure CheckMessage(MSG_ID: CANMSG_ID; data: CAN_DATA);
    { Private declarations }
  public
    procedure DataReceive(CAN_MSG: CANMSG);
    function SendCANMessage(MSG_ID: CANMSG_ID; data: CAN_DATA): string;
    { Public declarations }
  end;

var
  Form_Glavn: TForm_Glavn;

implementation

uses U_my, ABOUT, VCI3Types;

{$R *.dfm}

procedure TForm_Glavn.CheckMessage(MSG_ID: CANMSG_ID; data: CAN_DATA);
begin
  if MSG_ID.PDUformat = $FE then
  begin
    case MSG_ID.PDUspecific of
      $F5:
        begin
          flagAirData := True;
          if (data[3] = $FF) and (data[4] = $FF) then
          begin
            iThermometer1.Position := 0;
            sLabelFX1.Caption := 'Датчик отключен';
          end
          else
          begin
            iThermometer1.Position := (data[3] or (data[4] shl 8)) / 32 - 273;
            sLabelFX1.Caption := FloatToStrF(iThermometer1.Position, ffFixed, 3, 1) + ' °C';
          end;
          sLabelFX3.Caption := 'Период: ' + IntToStr(MilliSecondOfTheDay(Now) - intervalAirTemperature_old) + ' мс';
          intervalAirTemperature_old := MilliSecondOfTheDay(Now);
          Application.ProcessMessages;
        end;
      $FC:
        begin
          flagFuelData := True;
          if data[1] = $FF then
           begin
            iThermometer2.Position := 0;
            sLabelFX2.Caption := 'Датчик отключен';
          end
          else
          begin
            iThermometer2.Position := data[1] / 2.5;
            sLabelFX2.Caption := FloatToStrF(iThermometer2.Position, ffFixed, 3, 1) + ' %';
          end;
          sLabelFX4.Caption := 'Период: ' + IntToStr(MilliSecondOfTheDay(Now) - intervalFuel_old) + ' мс';
          intervalFuel_old := MilliSecondOfTheDay(Now);
          Application.ProcessMessages;
        end;
    end;
  end;
end;

procedure TForm_Glavn.DataReceive(CAN_MSG: CANMSG);
var
  MSG_ID: CANMSG_ID;
  data: CAN_DATA;
  i: integer;
begin
  MSG_ID.sourceAddr := byte(CAN_MSG.dwMsgId and $000000FF);
  MSG_ID.PDUspecific := byte((CAN_MSG.dwMsgId and $0000FF00) shr 8);
  MSG_ID.PDUformat := byte((CAN_MSG.dwMsgId and $00FF0000) shr 16);
  SetLength(data, 8);
  for i := 0 to 7 do
    data[i] := CAN_MSG.abData[i + 1];
  CheckMessage(MSG_ID, data);

end;

procedure TForm_Glavn.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  iThreadTimers1.Enabled1 := False;
  iThreadTimers1.Enabled2 := False;
end;

procedure TForm_Glavn.FormCreate(Sender: TObject);
var
  hFuncResult: HResult;
  deviceInfo: VCIDEVICEINFO;
  ErrorText: string;
  hEnum: Cardinal;
begin
  // use the first CAN
  m_dwCanNo := 0;

  // set the handles to zero
  m_hDeviceHandle := 0;
  m_hCanChannel := 0;
  m_hCanControl := 0;
  m_dwTimerResolution := 0;
  m_dwTimerOverruns := 0;
  m_qwOverrunValue := 0;
  m_ReceiveQueueThread := nil;

  //***********Открытие программы без показа диалогового окна выбора устройства**********************
  hFuncResult := vciEnumDeviceOpen(hEnum);
  if (hFuncResult = VCI_OK) then
  begin
    hFuncResult := vciEnumDeviceNext(hEnum, deviceInfo);
    vciEnumDeviceClose(hEnum);
    if (hFuncResult = VCI_OK) then
    begin
      hFuncResult := vciDeviceOpen(@deviceInfo.VciObjectId, m_hDeviceHandle);
      InitSocket();
      InitSocketRec();
    end
    else
    begin
      ErrorText := 'НЕ найден CAN интерфейс';
    end;
  end;

  if (hFuncResult <> VCI_OK) then
    ShowErrorMessage(ErrorText, hFuncResult);
end;

procedure TForm_Glavn.FormDestroy(Sender: TObject);
begin
  if (m_ReceiveQueueThread <> nil) then
  begin
    // call the thread function to terminate
    m_ReceiveQueueThread.Terminate;

    // wait for the thread until it's finfished
    m_ReceiveQueueThread.WaitFor;

    // now destroy the object
    m_ReceiveQueueThread.Destroy;

    // set the object to nil
    m_ReceiveQueueThread := nil;
  end;

  if (m_hCanControl <> 0) then
  begin
    canControlClose(m_hCanControl);
    m_hCanControl := 0;
  end;

  // when a CAN channel was opened then close it now
  if (m_hCanChannel <> 0) then
  begin
    canChannelClose(m_hCanChannel);
    m_hCanChannel := 0;
  end;

  if (m_hCanChannelRex <> 0) then
  begin
    canChannelClose(m_hCanChannelRex);
    m_hCanChannelRex := 0;
  end;

  // when a device was opened the close it now
  if (m_hDeviceHandle <> 0) then
  begin
    vciDeviceClose(m_hDeviceHandle);
    m_hDeviceHandle := 0;
  end;

end;

procedure TForm_Glavn.FormShow(Sender: TObject);
begin
  iThreadTimers1.Enabled1 := True;
  iThreadTimers1.Enabled2 := True;
end;

procedure TForm_Glavn.InitSocket;
var
  hFuncResult: HResult;
  wRxFifoSize: Word;
  wRxThreshold: Word;
  wTxFifoSize: Word;
  wTxThreshold: Word;
  pCanCaps: CANCAPABILITIES;
  qwTimerTemp: Int64;
  errorText: string;
begin
  errorText := 'InitSocket was succesful';

  hFuncResult := canChannelOpen(m_hDeviceHandle, m_dwCanNo, FALSE, m_hCanChannel);
  if (hFuncResult = VCI_OK) then
  begin
    // device and CAN channel are now open, so initialize the CAN channel
    wRxFifoSize := 1024;
    wRxThreshold := 1;
    wTxFifoSize := 128;
    wTxThreshold := 1;

    hFuncResult := canChannelInitialize(m_hCanChannel,
      wRxFifoSize, wRxThreshold,
      wTxFifoSize, wTxThreshold);
    if (hFuncResult <> VCI_OK) then
      errorText := 'Error in canChannelInitialize';
  end;

  if (hFuncResult = VCI_OK) then
  begin
    // device, CAN channel are open and initialized,
    // so activate now the CAN channel
    hFuncResult := canChannelActivate(m_hCanChannel, TRUE);
    if (hFuncResult <> VCI_OK) then
      errorText := 'Error in canChannelActivate';
  end;

  if (hFuncResult = VCI_OK) then
  begin
    // the CAN channel is now activated, open now the CAN controller
    hFuncResult := canControlOpen(m_hDeviceHandle, m_dwCanNo, m_hCanControl);
    if (hFuncResult = VCI_OK) then
    begin
      stbBottom.Panels[0].Text := 'CAN контроллер: ' + IntToStr(m_dwCanNo + 1);

      hFuncResult := canControlGetCaps(m_hCanControl, pCanCaps);
      if (hFuncResult = VCI_OK) then
      begin
        // calulate the time resolution in 100 nSeconds
        qwTimerTemp := pCanCaps.dwTscDivisor * 10000000;
        m_dwTimerResolution := Round(qwTimerTemp / pCanCaps.dwClockFreq);
      end;
    end
    else
    begin
      errorText := 'Error in canControlOpen';
    end;
  end;

  if (hFuncResult = VCI_OK) then
  begin
    // the CAN control is now open, initialize it now
    hFuncResult := canControlInitialize(m_hCanControl
      , CAN_OPMODE_EXTENDED or CAN_OPMODE_ERRFRAME
      , BitTimingReg0
      , BitTimingReg1);
    if (hFuncResult = VCI_OK) then
      stbBottom.Panels[1].Text := 'Скорость: ' + BitTimingString
    else
      errorText := 'Error in canControlInitialize';
  end;

  if (hFuncResult = VCI_OK) then
  begin
    // set the acceptance filter
    hFuncResult := canControlSetAccFilter(m_hCanControl
      , True
      , CAN_ACC_CODE_ALL
      , CAN_ACC_MASK_ALL);
    if (hFuncResult <> VCI_OK) then
      errorText := 'Error in canControlSetAccFilter';
  end;

  if (hFuncResult = VCI_OK) then
  begin
    // start the CAN controller
    hFuncResult := canControlStart(m_hCanControl, TRUE);
    if (hFuncResult <> VCI_OK) then
      errorText := 'Error in canControlStart';
  end;

  if (hFuncResult <> VCI_OK) then
    ShowErrorMessage(errorText, hFuncResult);

end;

procedure TForm_Glavn.InitSocketRec;
var
  hFuncResult: HResult;
  wRxFifoSize: Word;
  wRxThreshold: Word;
  wTxFifoSize: Word;
  wTxThreshold: Word;
  errorText: string;
begin
  errorText := 'InitSocket was succesful';

  hFuncResult := canChannelOpen(m_hDeviceHandle, m_dwCanNo, FALSE, m_hCanChannelRex);
  if (hFuncResult = VCI_OK) then
  begin
    // device and CAN channel are now open, so initialize the CAN channel
    wRxFifoSize := 1024;
    wRxThreshold := 1;
    wTxFifoSize := 128;
    wTxThreshold := 1;

    hFuncResult := canChannelInitialize(m_hCanChannelRex,
      wRxFifoSize, wRxThreshold,
      wTxFifoSize, wTxThreshold);
    if (hFuncResult <> VCI_OK) then
      errorText := 'Error in canChannelInitialize';
  end;

  if (hFuncResult = VCI_OK) then
  begin
    // device, CAN channel are open and initialized,
    // so activate now the CAN channel
    hFuncResult := canChannelActivate(m_hCanChannelRex, TRUE);
    if (hFuncResult <> VCI_OK) then
      errorText := 'Error in canChannelActivate';
  end;

  if (m_hCanChannelRex <> 0) then
  begin
    // start the timer to look every 100 ms for data
    m_ReceiveQueueThread := TReceiveQueueThread.Create(m_hCanChannelRex);
  end;

  if (hFuncResult <> VCI_OK) then
    ShowErrorMessage(errorText, hFuncResult);

end;

procedure TForm_Glavn.iThreadTimers1Timer1(Sender: TObject);
begin
  if not flagAirData then
  begin
    iThermometer1.Position := 0;
    sLabelFX1.Caption := 'Нет данных';
    sLabelFX3.Caption := 'Период не определен'
  end;

  if not flagFuelData then
  begin
    iThermometer2.Position := 0;
    sLabelFX2.Caption := 'Нет данных';
    sLabelFX4.Caption := 'Период не определен'
  end;

  flagAirData := False;
  flagFuelData := False;
end;

procedure TForm_Glavn.iThreadTimers1Timer2(Sender: TObject);
var
  id: CANMSG_ID;
  data: CAN_DATA;
begin
  if sCheckBox1.Checked then
  begin
    id.priority := 6;
    id.PDUformat := $FE;
    id.PDUspecific := $4F;
    id.sourceAddr := $00;
    SetLength(data, 8);
    data[0] := $DF;
    data[1] := $FF;
    data[2] := $FF;
    data[3] := $FF;
    data[4] := $FF;
    data[5] := $FF;
    data[6] := $FF;
    data[7] := $FF;
    SendCANMessage(id, data);
  end;
end;

procedure TForm_Glavn.N1Click(Sender: TObject);
begin
  AboutBox.ShowModal;
end;

procedure TForm_Glavn.N2Click(Sender: TObject);
begin
  Close;
end;

procedure TForm_Glavn.sBitBtn1Click(Sender: TObject);
begin
  Close;
end;

function TForm_Glavn.SendCANMessage(MSG_ID: CANMSG_ID; data: CAN_DATA): string;
var
  sMsgToSend: CANMSG;
  hFuncResult: HResult;
  szResultText: PChar;
  errorText: string;
  i: Integer;
begin
  with MSG_ID do
  begin
    r := 0;
    dp := 0;
    sMsgToSend.dwMsgId := Integer(sourceAddr) or
      (Integer(PDUspecific) shl 8) or
      (Integer(PDUformat) shl 16) or
      (Integer(dp) shl 24) or
      (Integer(r) shl 25) or
      (Integer(priority) shl 26)
  end;
  for i := 0 to 7 do
    sMsgToSend.abData[i] := data[i-1];
  sMsgToSend.dwTime := 0;
  sMsgToSend.uMsgInfo.bType := CAN_MSGTYPE_DATA;
  sMsgToSend.uMsgInfo.bRes := 0;
  sMsgToSend.uMsgInfo.bAfc := 0;
  // DLC = 8 data bytes
  sMsgToSend.uMsgInfo.bFlags := 8;
  // a sample to send a extended (29 bit) CAN message
  sMsgToSend.uMsgInfo.bFlags := sMsgToSend.uMsgInfo.bFlags or CAN_MSGFLAGS_EXT;

  if (m_hCanChannel <> 0) then
  begin
    hFuncResult := canChannelPostMessage(m_hCanChannel, sMsgToSend);
  end
  else
    errorText := 'No CAN channel open';
end;

procedure TForm_Glavn.ShowErrorMessage(errorText: string; hFuncResult: HResult);
var
  szErrorText: PChar;
begin
  if (hFuncResult <> 0) then
  begin
    szErrorText := StrAlloc(255);
    vciFormatError(hFuncResult, szErrorText, 255);
    ShowMessage(errorText + ' : ' + szErrorText);
    StrDispose(szErrorText);
  end
  else
    ShowMessage(errorText);
end;

end.


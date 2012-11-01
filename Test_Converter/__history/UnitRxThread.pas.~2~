(*************************************************************************
**    IXXAT Automation GmbH
**************************************************************************
**
**   $Workfile: UnitRxThread.PAS $ UnitRxThread
**     Summary: A thread based class to receive CAN messages in
**              the thread function.
**
**   $Revision: 1 $
**     Version: @(VERSION)
**       $Date: 2006-07-24 $
**    Compiler: Delphi 5.0
**      Author: Peter Wucherer
**
**************************************************************************
**    all rights reserved
*************************************************************************)
unit UnitRxThread;

interface

uses
  SysUtils, Classes, WinTypes, Vci3Can;

type
  TReceiveQueueThread = class(TThread)
  protected
    m_hCanChn  : THANDLE;  // the CAN channel to use
    m_sCanMsg  : CANMSG;   // class internal message structure

  protected
    procedure Execute;                      override;
    procedure ShowMessageInUnitMain;

  public
    constructor Create(hCanChn : THANDLE);  virtual;

  end;


implementation

uses
  Dialogs, VCI3Error, Windows, Unit_Glavn;

(************************************************************************
**
**    Function      : TReceiveQueueThread.Create
**
**    Description   : constructor - initialize the member variables
**    Parameter     : hCanChn     - the can channel to use
**
**    Returnvalues  : -
**
************************************************************************)
constructor TReceiveQueueThread.Create( hCanChn : THANDLE );
begin
  // store the can channel which we want to use
  m_hCanChn := hCanChn;
  // we want to destroy this class object from the main unit
  freeOnTerminate := false;

  inherited Create(False);  // create the thread and start the excute function
end;

(************************************************************************
**
**    Function      : TReceiveQueueThread.Execute
**
**    Description   : The thread function itself. Here the thread runs
**                    until Terminate will be called.
**    Parameter     :
**
**    Returnvalues  : -
**
************************************************************************)
procedure TReceiveQueueThread.Execute;
begin
  repeat
    // wait 10 milli seconds for a CAN message
    if (canChannelWaitRxEvent(m_hCanChn, 10) = VCI_OK) then
    begin
      // CAN message(s) is/are available, so get it from the channel
      while (canChannelPeekMessage(m_hCanChn, m_sCanMsg) = VCI_OK ) do
      begin
        // show the message in the main form
        if m_sCanMsg.uMsgInfo.bType = CAN_MSGTYPE_DATA then
          Synchronize(ShowMessageInUnitMain);

        // Check whether thread should stop, otherwise if there is heavy
        // CAN traffic it's possible we never leave the while-loop
        if (Terminated)
         then break;
      end;
    end;
  until (Terminated);
end;

(************************************************************************
**
**    Function      : TReceiveQueueThread.ShowMessageInUnitMain
**
**    Description   : Show the last received message in the main
**                    form. We must use the Synchronize function because
**                    we call GUI controls from this thread.
**    Parameter     :
**
**    Returnvalues  : -
**
************************************************************************)
procedure TReceiveQueueThread.ShowMessageInUnitMain;
begin
  Form_Glavn.DataReceive(m_sCanMsg);
end;


end.

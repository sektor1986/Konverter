(*************************************************************************
**    IXXAT Automation GmbH
**************************************************************************
**
**   $Workfile: Vci3Can.PAS $
**     Summary: Wrapper unit for the VCI V3 C-API.
**              This unit has the CAN specific things, see Vci3Lin for
**              the LIN specific things.
**              All structures, functions and defines has the same name
**              as in the vciinpl.h for C/C++.
**              The functions and defines are descriped in the C-API
**              programmers manual.
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

unit Vci3Can;

interface

uses
  WinTypes, VCI3Types, VCI3Error;


const

  (*****************************************************************************
   * predefined CiA bit rates
   ****************************************************************************)
  CAN_BT0_10KB    = $31;
  CAN_BT1_10KB    = $1C;
  CAN_BT0_20KB    = $18;
  CAN_BT1_20KB    = $1C;
  CAN_BT0_50KB    = $09;
  CAN_BT1_50KB    = $1C;
  CAN_BT0_100KB   = $04;
  CAN_BT1_100KB   = $1C;
  CAN_BT0_125KB   = $03;
  CAN_BT1_125KB   = $1C;
  CAN_BT0_250KB   = $01;
  CAN_BT1_250KB   = $1C;
  CAN_BT0_500KB   = $00;
  CAN_BT1_500KB   = $1C;
  CAN_BT0_800KB   = $00;
  CAN_BT1_800KB   = $16;
  CAN_BT0_1000KB  = $00;
  CAN_BT1_1000KB  = $14;


  (*****************************************************************************
   * controller operating modes
   ****************************************************************************)
  CAN_OPMODE_UNDEFINED  = $00;  // undefined
  CAN_OPMODE_STANDARD   = $01;  // reception of 11-bit id messages
  CAN_OPMODE_EXTENDED   = $02;  // reception of 29-bit id messages
  CAN_OPMODE_ERRFRAME   = $04;  // enable reception of error frames
  CAN_OPMODE_LISTONLY   = $08;  // listen only mode (TX passive)
  CAN_OPMODE_LOWSPEED   = $10;  // use low speed bus interface


  (*****************************************************************************
   * controller status
   ****************************************************************************)
  CAN_STATUS_TXPEND     = $01;  // transmission pending
  CAN_STATUS_OVRRUN     = $02;  // data overrun occurred
  CAN_STATUS_ERRLIM     = $04;  // error warning limit exceeded
  CAN_STATUS_BUSOFF     = $08;  // bus off status
  CAN_STATUS_ININIT     = $10;  // init mode active


  (*****************************************************************************
   * acceptance filter settings
   ****************************************************************************)
  // acceptance code and mask to accept all CAN IDs
  CAN_ACC_MASK_ALL    = $00000000;
  CAN_ACC_CODE_ALL    = $00000000;
  // acceptance code and mask to reject all CAN IDs
  CAN_ACC_MASK_NONE   = $FFFFFFFF;
  CAN_ACC_CODE_NONE   = $80000000;

  // message types (used by <CANMSGINFO.Bytes.bType>)
  CAN_MSGTYPE_DATA    =   0;  // data frame
  CAN_MSGTYPE_INFO    =   1;  // info frame
  CAN_MSGTYPE_ERROR   =   2;  // error frame
  CAN_MSGTYPE_STATUS  =   3;  // status frame
  CAN_MSGTYPE_WAKEUP  =   4;  // wakeup frame
  CAN_MSGTYPE_TIMEOVR =   5;  // timer overrun
  CAN_MSGTYPE_TIMERST =   6;  // timer reset

  // message information flags (used by <CANMSGINFO.Bytes.bFlags>)
  CAN_MSGFLAGS_DLC    = $0F;  // data length code
  CAN_MSGFLAGS_OVR    = $10;  // data overrun flag
  CAN_MSGFLAGS_SRR    = $20;  // self reception request
  CAN_MSGFLAGS_RTR    = $40;  // remote transmission request
  CAN_MSGFLAGS_EXT    = $80;  // frame format (0=11-bit, 1=29-bit)

  // Information supplied in the abData[0] field of info frames
  // (CANMSGINFO.Bytes.bType = CAN_MSGTYPE_INFO).
  CAN_INFO_START      =   1;  // start of CAN controller
  CAN_INFO_STOP       =   2;  // stop of CAN controller
  CAN_INFO_RESET      =   3;  // reset of CAN controller

  // Error information supplied in the abData[0] field of error frames
  // (CANMSGINFO.Bytes.bType = CAN_MSGTYPE_ERROR).
  CAN_ERROR_STUFF     =   1;  // stuff error
  CAN_ERROR_FORM      =   2;  // form error
  CAN_ERROR_ACK       =   3;  // acknowledgment error
  CAN_ERROR_BIT       =   4;  // bit error
  CAN_ERROR_CRC       =   6;  // CRC error
  CAN_ERROR_OTHER     =   7;  // other (unspecified) error


type

  VCIID = packed record
    AsInt64 : Int64;
  end;
  REFVCIID = ^VCIID;

  VCIDEVICEINFO = packed record
    VciObjectId         : VCIID;  // unique VCI object identifier
    DeviceClass         : TGUID;  // device class identifier
    DriverMajorVersion  : UINT16; // major driver version number
    DriverMinorVersion  : UINT16; // minor driver version number
    HardwareMajorVersion: UINT16; // major hardware version number
    HardwareMinorVersion: UINT16; // minor hardware version number
    UniqueHardwareId    : TGUID;  // unique hardware identifier
    Description         : array[1..128] of CHAR;  // device description (e.g: "PC-I04-PCI")
    Manufacturer        : array[1..128] of CHAR;  // device manufacturer (e.g: "IXXAT Automation")
  end;

  VCIDEVICECAPS = packed record
    BusCtrlCount        : UINT16; // number of supported bus controllers
    BusCtrlTypes        : array[1..32] of UINT16  // array of supported bus controllers
  end;


  (*****************************************************************************
   * CAN capabilities
   ****************************************************************************)
  CANCAPABILITIES = packed record
    wCtrlType     : UINT16;       // Type of CAN controller (see CAN_CTRL_ const)
    wBusCoupling  : UINT16;       // Type of Bus coupling (see CAN_BUSC_ const)
    dwFeatures    : UINT32;       // supported features (see CAN_FEATURE_ constants)
    dwClockFreq   : UINT32;       // clock frequency of the primary counter in Hz
    dwTscDivisor  : UINT32;       // divisor for the message time stamp counter
    dwCmsDivisor  : UINT32;       // divisor for the cyclic message scheduler
    dwCmsMaxTicks : UINT32;       // maximum tick count value of the cyclic message
                                  // scheduler
    dwDtxDivisor  : UINT32;       // divisor for the delayed message transmitter
    dwDtxMaxTicks : UINT32;       // maximum tick count value of the delayed
                                  // message transmitter
  end;


  (*****************************************************************************
   * CAN controller status information structure
   ****************************************************************************)
  CANLINESTATUS = packed record
    bOpMode     : UINT8;    // current CAN operating mode
    bBtReg0     : UINT8;    // current bus timing register 0 value
    bBtReg1     : UINT8;    // current bus timing register 1 value
    bBusLoad    : UINT8;    // average bus load in percent (0..100)
    dwStatus    : UINT32;   // status of the CAN controller (see CAN_STATUS_)
  end;


  (*****************************************************************************
   * CAN message channel status information structure
   ****************************************************************************)
  CANCHANSTATUS = packed record
    sLineStatus : CANLINESTATUS; // current CAN line status
    fActivated  : BOOL32;   // TRUE if the channel is activated
    fRxOverrun  : BOOL32;   // TRUE if receive FIFO overrun occurs
    bRxFifoLoad : UINT8;    // receive FIFO load in percent (0..100)
    bTxFifoLoad : UINT8;    // transmit FIFO load in percent (0..100)
  end;


  (*****************************************************************************
   * CAN message information
   ****************************************************************************)
  CANMSGINFO = packed record
      bType     : UINT8;    // type (see CAN_MSGTYPE_ constants)
      bRes      : UINT8;    // reserved
      bFlags    : UINT8;    // flags (see CAN_MSGFLAGS_ constants)
      bAfc      : UINT8;    // accept code (see CAN_ACCEPT_ constants)
    (*
    struct
    {
      UINT32 type: 8;   // message type
      UINT32 res : 8;   // reserved
      UINT32 dlc : 4;   // data length code
      UINT32 ovr : 1;   // possible data overrun
      UINT32 srr : 1;   // self reception request
      UINT32 rtr : 1;   // remote transmission request
      UINT32 ext : 1;   // extended frame format (0=standard, 1=extended)
      UINT32 afc : 8;   // acceptance filter code
    } Bits;
    *)
  end;


  (*****************************************************************************
   * CAN message structure
   ****************************************************************************)
  CANMSG = packed record
    dwTime      : UINT32;     // time stamp for receive message
    dwMsgId     : UINT32;     // CAN message identifier (INTEL format)
    uMsgInfo    : CANMSGINFO; // message information (bit field)
    abData      : array[1..8] of UINT8; // message data
  end;

  CANMSG_ID = packed record
    priority    : UINT8;      //Приоритет
    r           : UINT8;      //Зарезервировано
    dp          : UINT8;      //Страница
    PDUformat   : UINT8;      //Формат PDU
    PDUspecific : UINT8;      //номер группы параметров
    sourceAddr  : UINT8;      //Адрес источника
  end;

  (*****************************************************************************
   * cyclic CAN transmit message
   ****************************************************************************)
  CANCYCLICTXMSG = packed record
    wCycleTime  : UINT16;     // cycle time for the message in ticks
    bIncrMode   : UINT8;      // auto increment mode (see CAN_CTXMSG_INC_ const)
    bByteIndex  : UINT8;      // index of the byte within abData[] to increment
    dwMsgId     : UINT32;     // CAN message identifier (INTEL format)
    uMsgInfo    : CANMSGINFO; // message information (bit field)
    abData      : array[1..8] of UINT8; // message data
  end;


  (*****************************************************************************
   * status of the cyclic message scheduler
   ****************************************************************************)
  CANSCHEDULERSTATUS = packed record
    bTaskStat   : UINT8;      // status of cyclic transmit task
    abMsgStat   : array[1..16] of UINT8; // status of all cyclic transmit messages
  end;


(*##########################################################################*)
(*##                                                                      ##*)
(*##   exported API functions                                             ##*)
(*##                                                                      ##*)
(*##########################################################################*)

(*****************************************************************************
 * general VCI functions
 ****************************************************************************)

function  vciInitialize                                 : HRESULT;    stdcall; external VCI_DLL;

procedure vciFormatError  (     hrError     : HRESULT;
                                pszText     : PCHAR;
                                dwSize      : UINT32 );               stdcall; external VCI_DLL;

procedure vciDisplayError (     hwndParent  : HWND;
                                pszCaption  : PCHAR;
                                hrError     : HRESULT );              stdcall; external VCI_DLL;

function  vciGetVersion   ( var dwMajorVersion: UINT32;
                            var dwMinorVersion: UINT32 ): HRESULT;    stdcall; external VCI_DLL;

function  vciLuidToChar   (     rVciid      : REFVCIID;
                                pszLuid     : PCHAR;
                                cbSize      : LONG )    : HRESULT;    stdcall; external VCI_DLL;

function  vciCharToLuid   (     pszLuid     : PCHAR;
                            var pVciid      : VCIID  )  : HRESULT;    stdcall; external VCI_DLL;

function  vciGuidToChar   ( var rGuid       : TGUID;
                                pszGuid     : PCHAR;
                                cbSize      : LONG )    : HRESULT;    stdcall; external VCI_DLL;

function  vciCharToGuid   (     pszGuid     : PCHAR;
                            var pGuid       : TGUID  )  : HRESULT;    stdcall; external VCI_DLL;


(*****************************************************************************
 * event specific functions
 ****************************************************************************)

function  vciEventCreate  (     fManReset   : BOOL;
                                fInitState  : BOOL;
                            var hEvent      : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  vciEventDelete  (     hEvent      : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  vciEventSignal  (     hEvent      : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  vciEventReset   (     hEvent      : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  vciEventWaitFor (     hEvent      : THANDLE;
                                dwMsTimeout : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;


(*****************************************************************************
 * device manager specific functions
 ****************************************************************************)

function  vciEnumDeviceOpen(var hEnum       : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  vciEnumDeviceClose(   hEnum       : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  vciEnumDeviceNext(    hEnum       : THANDLE;
                            var pInfo       : VCIDEVICEINFO ): HRESULT;
                                                                      stdcall; external VCI_DLL;

function  vciEnumDeviceReset(   hEnum       : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  vciEnumDeviceWaitEvent( hEnum     : THANDLE;
                                dwMsTimeout : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;

function  vciFindDeviceByHwid(var rHwid     : TGUID;
                            var pVciid      : VCIID )   : HRESULT;    stdcall; external VCI_DLL;

function  vciFindDeviceByClass(var rClass   : TGUID;
                                dwInst      : UINT32;
                            var pVciid      : VCIID )   : HRESULT;    stdcall; external VCI_DLL;

function  vciSelectDeviceDlg(   hwndParent  : HWND;
                            var pVciid      : VCIID )   : HRESULT;    stdcall; external VCI_DLL;


(*****************************************************************************
 * device specific functions
 ****************************************************************************)

function  vciDeviceOpen   (     rVciid      : REFVCIID;
                            var phDevice    : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  vciDeviceOpenDlg(     hwndParent  : HWND;
                            var phDevice    : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  vciDeviceClose  (     hDevice     : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  vciDeviceGetInfo(     hDevice     : THANDLE;
                            var pInfo       : VCIDEVICEINFO ): HRESULT;
                                                                      stdcall; external VCI_DLL;

function  vciDeviceGetCaps(     hDevice     : THANDLE;
                            var pCaps       : VCIDEVICECAPS ): HRESULT;
                                                                      stdcall; external VCI_DLL;


(*****************************************************************************
 * CAN controller specific functions
 ****************************************************************************)

function  canControlOpen  (     hDevice     : THANDLE;
                                dwCanNo     : UINT32;
                            var phCanCtl    : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  canControlClose (     hCanCtl     : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  canControlGetCaps(    hCanCtl     : THANDLE;
                            var pCanCaps    : CANCAPABILITIES ): HRESULT;
                                                                      stdcall; external VCI_DLL;

function  canControlGetStatus(  hCanCtl     : THANDLE;
                            var pStatus     : CANLINESTATUS ): HRESULT;
                                                                      stdcall; external VCI_DLL;

function  canControlDetectBitrate( hCanCtl  : THANDLE;
                                wTimeoutMs  : UINT16;
                                dwCount     : UINT32;
                                pabBtr0     : PByte;
                                pabBtr1     : PByte;
                            var plIndex     : INT32 )   : HRESULT;    stdcall; external VCI_DLL;

function  canControlInitialize( hCanCtl     : THANDLE;
                                bMode       : UINT8;
                                bBtr0       : UINT8;
                                bBtr1       : UINT8 )   : HRESULT;    stdcall; external VCI_DLL;

function  canControlReset (     hCanCtl     : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  canControlStart (     hCanCtl     : THANDLE;
                                fStart      : BOOL )    : HRESULT;    stdcall; external VCI_DLL;

function  canControlSetAccFilter( hCanCtl   : THANDLE;
                                fExtend     : BOOL;
                                dwCode      : UINT32;
                                dwMask      : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;

function  canControlAddFilterIds( hCanCtl   : THANDLE;
                                fExtend     : BOOL;
                                dwCode      : UINT32;
                                dwMask      : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;

function  canControlRemFilterIds( hCanCtl   : THANDLE;
                                fExtend     : BOOL;
                                dwCode      : UINT32;
                                dwMask      : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;


(*****************************************************************************
 * CAN message channel specific functions
 ****************************************************************************)

function  canChannelOpen  (     hDevice     : THANDLE;
                                dwCanNo     : UINT32;
                                fExclusive  : BOOL;
                            var phCanChn    : THANDLE  ): HRESULT;    stdcall; external VCI_DLL;

function  canChannelClose (     hCanChn     : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  canChannelGetCaps(    hCanChn     : THANDLE;
                            var pCanCaps    : CANCAPABILITIES ) : HRESULT;
                                                                      stdcall; external VCI_DLL;

function  canChannelGetStatus(  hCanChn     : THANDLE;
                            var pStatus     : CANCHANSTATUS  ) : HRESULT;
                                                                      stdcall; external VCI_DLL;

function  canChannelInitialize( hCanChn     : THANDLE;
                                wRxFifoSize : UINT16;
                                wRxThreshold: UINT16;
                                wTxFifoSize : UINT16;
                                wTxThreshold: UINT16 )  : HRESULT;    stdcall; external VCI_DLL;

function  canChannelActivate(   hCanChn     : THANDLE;
                                fEnable     : BOOL )    : HRESULT;    stdcall; external VCI_DLL;

function  canChannelPeekMessage(hCanChn     : THANDLE;
                            var pCanMsg     : CANMSG )  : HRESULT;    stdcall; external VCI_DLL;

function  canChannelPostMessage(hCanChn     : THANDLE;
                            var pCanMsg     : CANMSG )  : HRESULT;    stdcall; external VCI_DLL;

function  canChannelWaitRxEvent(hCanChn     : THANDLE;
                                dwMsTimeout : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;

function  canChannelWaitTxEvent(hCanChn     : THANDLE;
                                dwMsTimeout : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;

function  canChannelReadMessage(hCanChn     : THANDLE;
                                dwMsTimeout : UINT32;
                            var pCanMsg     : CANMSG )  : HRESULT;    stdcall; external VCI_DLL;

function  canChannelSendMessage(hCanChn     : THANDLE;
                                dwMsTimeout : UINT32;
                            var pCanMsg     : CANMSG )  : HRESULT;    stdcall; external VCI_DLL;


(*****************************************************************************
 * cyclic CAN message scheduler specific functions
 ****************************************************************************)

function  canSchedulerOpen(     hDevice     : THANDLE;
                                dwCanNo     : UINT32;
                            var phCanShd    : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  canSchedulerClose(    hCanShd     : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  canSchedulerGetCaps(  hCanShd     : THANDLE;
                            var pCanCaps    : CANCAPABILITIES ): HRESULT;
                                                                      stdcall; external VCI_DLL;

function  canSchedulerGetStatus(hCanShd     : THANDLE;
                            var pStatus     : CANSCHEDULERSTATUS ): HRESULT;
                                                                      stdcall; external VCI_DLL;

function  canSchedulerActivate( hCanShd     : THANDLE;
                                fEnable     : BOOL )    : HRESULT;    stdcall; external VCI_DLL;

function  canSchedulerReset(    hCanShd     : THANDLE ) : HRESULT;    stdcall; external VCI_DLL;

function  canSchedulerAddMessage( hCanShd   : THANDLE;
                            var pMessage    : CANCYCLICTXMSG;
                            var pdwIndex    : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;

function  canSchedulerRemMessage( hCanShd   : THANDLE;
                                dwIndex     : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;

function  canSchedulerStartMessage( hCanShd : THANDLE;
                                dwIndex     : UINT32;
                                wRepeat     : UINT16 )  : HRESULT;    stdcall; external VCI_DLL;

function  canSchedulerStopMessage( hCanShd  : THANDLE;
                                dwIndex     : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;


implementation

end.

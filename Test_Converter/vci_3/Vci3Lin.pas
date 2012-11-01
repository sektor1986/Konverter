(*************************************************************************
**    IXXAT Automation GmbH
**************************************************************************
**
**   $Workfile: Vci3Lin.PAS $
**     Summary: Wrapper unit for the VCI V3 C-API.
**              This unit has the LIN specific things, see Vci3Can for
**              the CAM specific things.
**              All structures, functions and defines has the same name
**              as in the vciinpl.h for C/C++.
**              The functions and defines are descriped in the C-API
**              programmers manual.
**
**   $Revision: 1 $
**     Version: @(VERSION)
**       $Date: 2006-07-27 $
**    Compiler: Delphi 5.0
**      Author: Peter Wucherer
**
**************************************************************************
**    all rights reserved
*************************************************************************)

unit Vci3Lin;

interface

uses
  WinTypes, VCI3Types;


const

  (*****************************************************************************
   * controller types
   ****************************************************************************)
  LIN_CTRL_UNKNOWN      =   0;    // unknown
  LIN_CTRL_MAXVAL       = 255;    // maximum value for controller type


  (*****************************************************************************
   * supported features
   ****************************************************************************)
  LIN_FEATURE_MASTER    = $0001;  // master mode
  LIN_FEATURE_AUTORATE  = $0002;  // automatic bitrate detection
  LIN_FEATURE_ERRFRAME  = $0004;  // reception of error frames
  LIN_FEATURE_BUSLOAD   = $0008;  // bus load measurement


  (*****************************************************************************
   * controller operating modes
   ****************************************************************************)
  LIN_OPMODE_UNDEF      = $00;    // undefined
  LIN_OPMODE_MASTER     = $01;    // enable master mode
  LIN_OPMODE_ERRORS     = $02;    // enable reception of error frames


  (*****************************************************************************
   * predefined bitrates
   ****************************************************************************)
  LIN_BITRATE_UNDEF     = 65535;  // undefined bit-rate
  LIN_BITRATE_AUTO      =     0;  // automatic bit-rate detection
  LIN_BITRATE_MIN       =  1000;  // lowest specified bit-rate
  LIN_BITRATE_MAX       = 20000;  // highest specified bit-rate

  LIN_BITRATE_1000      =  1000;  //  1000 baud
  LIN_BITRATE_1200      =  1200;  //  1200 baud
  LIN_BITRATE_2400      =  2400;  //  2400 baud
  LIN_BITRATE_4800      =  4800;  //  4800 baud
  LIN_BITRATE_9600      =  9600;  //  9600 baud
  LIN_BITRATE_10400     = 10400;  // 10400 baud
  LIN_BITRATE_19200     = 19200;  // 19200 baud
  LIN_BITRATE_20000     = 20000;  // 20000 baud


  (*****************************************************************************
   * controller status
   ****************************************************************************)
  LIN_STATUS_TXPEND     = $01;    // transmission pending
  LIN_STATUS_OVRRUN     = $02;    // data overrun occurred
  LIN_STATUS_ERRLIM     = $04;    // error warning limit exceeded
  LIN_STATUS_BUSOFF     = $08;    // bus off status
  LIN_STATUS_ININIT     = $10;    // init mode active


  //
  // message types (see <LINMSGINFO.Bytes.bType>)
  //
  LIN_MSGTYPE_DATA      = $00;    // data frame
  LIN_MSGTYPE_INFO      = $01;    // info frame
  LIN_MSGTYPE_ERROR     = $02;    // error frame
  LIN_MSGTYPE_STATUS    = $03;    // status frame
  LIN_MSGTYPE_WAKEUP    = $04;    // wakeup frame
  LIN_MSGTYPE_SLEEP     = $05;    // goto sleep frame
  LIN_MSGTYPE_TMOVR     = $06;    // timer overrun

  //
  // message flags (used by <LINMSGINFO.Bytes.bFlags>)
  //
  LIN_MSGFLAGS_ECS      = $01;    // enhanced checksum (LIN 2.0)
  LIN_MSGFLAGS_OVR      = $02;    // possible data overrun

  //
  // Information supplied in the abData[0] field of info frames
  // (LINMSGINFO.Bytes.bType = LIN_MSGTYPE_INFO).
  //
  LIN_INFO_START        =   1;    // start of LIN controller
  LIN_INFO_STOP         =   2;    // stop of LIN controller
  LIN_INFO_RESET        =   3;    // reset of LIN controller

  //
  // Error information supplied in the abData[0] field of error frames
  // (LINMSGINFO.Bytes.bType = LIN_MSGTYPE_ERROR).
  //
  LIN_ERROR_BIT         =   1;    // bit error
  LIN_ERROR_CHKSUM      =   2;    // checksum error
  LIN_ERROR_PARITY      =   3;    // identifier parity error
  LIN_ERROR_SLNORE      =   4;    // slave not responding error
  LIN_ERROR_SYNC        =   5;    // inconsistent sync field error
  LIN_ERROR_NOBUS       =   6;    // no bus activity error
  LIN_ERROR_OTHER       =   7;    // other (unspecified) error


type
  (*****************************************************************************
   * controller initialization structure
   ****************************************************************************)
  LININITLINE = packed record
    bOpMode       : UINT8;        // operating mode (see LIN_OPMODE_ constants)
    bReserved     : UINT8;        // reserved
    wBitrate      : UINT16;       // bit rate (see LIN_BITRATE_ constants)
  end;


  (*****************************************************************************
   * LIN capabilities
   ****************************************************************************)
  LINCAPABILITIES  = packed record
    dwFeatures    : UINT32;       // supported features (see LIN_FEATURE_ constants)
    dwClockFreq   : UINT32;       // clock frequency of the primary counter in Hz
    dwTscDivisor  : UINT32;       // divisor for the message time stamp counter
  end;


  (*****************************************************************************
   * controller status information structure
   ****************************************************************************)
  LINLINESTATUS = packed record
    bOpMode       : UINT8;        // current CAN operating mode
    bReserved     : UINT8;        // reserved
    wBitrate      : UINT16;       // current bit rate
    dwStatus      : UINT32;       // status of the LIN controller (see LIN_STATUS_)
  end;


  (*****************************************************************************
   * message monitor status information structure
   ****************************************************************************)
  LINMONITORSTATUS = packed record
    sLineStatus   : LINLINESTATUS;// current LIN line status
    fActivated    : BOOL32;       // TRUE if the monitor is activated
    fRxOverrun    : BOOL32;       // TRUE if receive FIFO overrun occurs
    bRxFifoLoad   : UINT8;        // receive FIFO load in percent (0..100)
  end;


  (*****************************************************************************
   * CAN message information
   ****************************************************************************)
  LINMSGINFO = packed record
    bPid    : UINT8;    // protected id
    bType   : UINT8;    // message type (see LIN_MSGTYPE_ constants)
    bDlen   : UINT8;    // data length
    bFlags  : UINT8;    // flags (see LIN_MSGFLAGS_ constants)
  (*
  struct
    UINT32 pid  : 8; // protected identifier
    UINT32 type : 8; // message type
    UINT32 dlen : 8; // data length
    UINT32 ecs  : 1; // enhanced checksum
    UINT32 ovr  : 1; // possible data overrun
    UINT32 res  : 6; // reserved
  } Bits;
  *)
  end;


  (*****************************************************************************
  * LIN message structure
  ****************************************************************************)
  LINMSG = packed record
    dwTime        : UINT32;       // time stamp for receive message [ms]
    uMsgInfo      : LINMSGINFO;   // message information (bit field)
    abData        : array[1..8] of UINT8; // message data
  end;


(*##########################################################################*)
(*##                                                                      ##*)
(*##   exported API functions                                             ##*)
(*##                                                                      ##*)
(*##########################################################################*)

(*****************************************************************************
 * LIN controller specific functions
 ****************************************************************************)

function  linControlOpen  (     hDevice     : THandle;
                                dwLinNo     : UINT32;
                            var phLinCtl    : THandle)  : HRESULT;    stdcall; external VCI_DLL;

function  linControlClose (     hLinCtl     : THandle ) : HRESULT;    stdcall; external VCI_DLL;

function  linControlGetCaps(    hLinCtl     : THandle;
                            var pLinCaps    : LINCAPABILITIES ): HRESULT;
                                                                      stdcall; external VCI_DLL;

function  linControlGetStatus(  hLinCtl     : THandle;
                            var pStatus     : LINLINESTATUS ): HRESULT;
                                                                      stdcall; external VCI_DLL;

function  linControlInitialize( hLinCtl     : THandle;
                                bMode       : UINT8;
                                wBitrate    : UINT16 )  : HRESULT;    stdcall; external VCI_DLL;

function  linControlReset (     hLinCtl     : THandle ) : HRESULT;    stdcall; external VCI_DLL;

function  linControlStart (     hLinCtl     : THandle;
                                fStart      : BOOL )    : HRESULT;    stdcall; external VCI_DLL;

function  linControlWriteMessage( hLinCtl   : THandle;
                                fSend       : BOOL;
                            var pLinMsg     : LINMSG  ) : HRESULT;    stdcall; external VCI_DLL;


(*****************************************************************************
 * LIN message monitor specific functions
 ****************************************************************************)

function  linMonitorOpen  (     hDevice     : THandle;
                                dwLinNo     : UINT32;
                                fExclusive  : BOOL;
                            var phLinMon    : THandle ) : HRESULT;    stdcall; external VCI_DLL;

function  linMonitorClose (     hCanChn     : THandle ) : HRESULT;    stdcall; external VCI_DLL;

function  linMonitorGetCaps(    hLinMon     : THandle;
                            var pLinCaps    : LINCAPABILITIES ): HRESULT;
                                                                      stdcall; external VCI_DLL;

function  linMonitorGetStatus(  hLinMon     : THandle;
                            var pStatus     : LINMONITORSTATUS ): HRESULT;
                                                                      stdcall; external VCI_DLL;

function  linMonitorInitialize( hLinMon     : THandle;
                                wFifoSize   : UINT16;
                                wThreshold  : UINT16 )  : HRESULT;    stdcall; external VCI_DLL;

function  linMonitorActivate(   hLinMon     : THandle;
                                fEnable     : BOOL )    : HRESULT;    stdcall; external VCI_DLL;

function  linMonitorPeekMessage(hLinMon     : THandle;
                            var pLinMsg     : LINMSG )  : HRESULT;    stdcall; external VCI_DLL;

function  linMonitorWaitRxEvent(hLinMon     : THandle;
                                dwMsTimeout : UINT32 )  : HRESULT;    stdcall; external VCI_DLL;

function  linMonitorReadMessage(hLinMon     : THandle;
                                dwMsTimeout : UINT32;
                            var pLinMsg     : LINMSG )  : HRESULT;    stdcall; external VCI_DLL;


implementation

end.

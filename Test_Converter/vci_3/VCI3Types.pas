(*************************************************************************
**    IXXAT Automation GmbH
**************************************************************************
**
**   $Workfile: VCI3Types.PAS $
**     Summary: Some data types used in C++ converted to Pascal
**              to use in the VCI V3 structures and functions.
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

unit VCI3Types;

interface

type
  UINT32 = LongWord;
  INT32  = LongInt;
  UINT16 = Word;
  LONG   = Longint;
  CHAR   = byte;
  UINT8  = byte;
  BOOL32 = LongWord;
  CANDATA = array of byte;

const
  VCI_DLL = 'vcinpl.dll';


implementation

end.

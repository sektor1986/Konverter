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

unit VCI3Error;

interface

const
(*****************************************************************************
 facility codes
*****************************************************************************)

FACILITY_STD  = HResult($00000000);     // common system error codes

SEV_INFO      = HResult($40000000);     // informational
SEV_WARN      = HResult($80000000);     // warnings
SEV_ERROR     = HResult($C0000000);    // errors
SEV_MASK      = HResult($C0000000);
SEV_SUCCESS   = HResult($00000000);

RESERVED_FLAG = HResult($10000000);
CUSTOMER_FLAG = HResult($20000000);

STATUS_MASK   = HResult($0000FFFF);
FACILITY_MASK = HResult($0FFF0000);


SEV_STD_INFO  = (SEV_INFO  or CUSTOMER_FLAG or FACILITY_STD);
SEV_STD_WARN  = (SEV_WARN  or CUSTOMER_FLAG or FACILITY_STD);
SEV_STD_ERROR = (SEV_ERROR or CUSTOMER_FLAG or FACILITY_STD);

FACILITY_VCI  = HResult($00010000);
SEV_VCI_INFO  =  (SEV_INFO or CUSTOMER_FLAG or FACILITY_VCI);
SEV_VCI_WARN  =  (SEV_WARN or CUSTOMER_FLAG or FACILITY_VCI);
SEV_VCI_ERROR = (SEV_ERROR or CUSTOMER_FLAG or FACILITY_VCI);

FACILITY_DAL  = HResult($00020000);
SEV_DAL_INFO  = (SEV_INFO  or CUSTOMER_FLAG or FACILITY_DAL);
SEV_DAL_WARN  = (SEV_WARN  or CUSTOMER_FLAG or FACILITY_DAL);
SEV_DAL_ERROR = (SEV_ERROR or CUSTOMER_FLAG or FACILITY_DAL);

FACILITY_CCL  = HResult($00030000);
SEV_CCL_INFO  = (SEV_INFO  or CUSTOMER_FLAG or FACILITY_CCL);
SEV_CCL_WARN  = (SEV_WARN  or CUSTOMER_FLAG or FACILITY_CCL);
SEV_CCL_ERROR = (SEV_ERROR or CUSTOMER_FLAG or FACILITY_CCL);

FACILITY_BAL  = HResult($00040000);
SEV_BAL_INFO  = (SEV_INFO  or CUSTOMER_FLAG or FACILITY_BAL);
SEV_BAL_WARN  = (SEV_WARN  or CUSTOMER_FLAG or FACILITY_BAL);
SEV_BAL_ERROR = (SEV_ERROR or CUSTOMER_FLAG or FACILITY_BAL);


(*##########################################################################*/
/*##                                                                      ##*/
/*##     VCI error codes                                                  ##*/
/*##                                                                      ##*/
/*##########################################################################*)

//
// MessageId: VCI_SUCCESS
//
// MessageText:
//
//  The operation completed successfully.
//
VCI_SUCCESS  = HResult($00000000);
VCI_OK       = VCI_SUCCESS;

//
// MessageId: VCI_E_UNEXPECTED
//
// MessageText:
//
//  Unexpected failure
//
VCI_E_UNEXPECTED = (SEV_VCI_ERROR or HResult($0001));

//
// MessageId: VCI_E_NOT_IMPLEMENTED
//
// MessageText:
//
//  Not implemented
//
VCI_E_NOT_IMPLEMENTED = (SEV_VCI_ERROR or  HResult($0002));

//
// MessageId: VCI_E_OUTOFMEMORY
//
// MessageText:
//
//  Not enough storage is available to complete this operation.
//
VCI_E_OUTOFMEMORY = (SEV_VCI_ERROR or HResult($0003));

//
// MessageId: VCI_E_INVALIDARG
//
// MessageText:
//
//  One or more parameters are invalid.
//
VCI_E_INVALIDARG = (SEV_VCI_ERROR or HResult($0004));

//
// MessageId: VCI_E_NOINTERFACE
//
// MessageText:
//
//  The object does not support the requested interface
//
VCI_E_NOINTERFACE =(SEV_VCI_ERROR or HResult($0005));

//
// MessageId: VCI_E_INVPOINTER
//
// MessageText:
//
//  Invalid pointer
//
VCI_E_INVPOINTER = (SEV_VCI_ERROR or HResult($0006));

//
// MessageId: VCI_E_INVHANDLE
//
// MessageText:
//
//  Invalid handle
//
VCI_E_INVHANDLE = (SEV_VCI_ERROR or HResult($0007));

//
// MessageId: VCI_E_ABORT
//
// MessageText:
//
//  Operation aborted
//
VCI_E_ABORT = (SEV_VCI_ERROR or HResult($0008));

//
// MessageId: VCI_E_FAIL
//
// MessageText:
//
//  Unspecified error
//
VCI_E_FAIL = (SEV_VCI_ERROR or HResult($0009));

//
// MessageId: VCI_E_ACCESSDENIED
//
// MessageText:
//
//  Access is denied.
//
VCI_E_ACCESSDENIED = (SEV_VCI_ERROR or HResult($000A));

//
// MessageId: VCI_E_TIMEOUT
//
// MessageText:
//
//  This operation returned because the timeout period expired.
//
VCI_E_TIMEOUT = (SEV_VCI_ERROR or HResult($000B));

//
// MessageId: VCI_E_BUSY
//
// MessageText:
//
//  The requested resource is in use.
//
VCI_E_BUSY = (SEV_VCI_ERROR or HResult($000C));

//
// MessageId: VCI_E_PENDING
//
// MessageText:
//
//  The data necessary to complete this operation is not yet available.
//
VCI_E_PENDING = (SEV_VCI_ERROR or HResult($000D));

//
// MessageId: VCI_E_NO_DATA
//
// MessageText:
//
//  No more data available.
//
VCI_E_NO_DATA = (SEV_VCI_ERROR or HResult($000E));

//
// MessageId: VCI_E_NO_MORE_ITEMS
//
// MessageText:
//
//  No more entries are available from an enumeration operation.
//
VCI_E_NO_MORE_ITEMS = (SEV_VCI_ERROR or HResult($000F));

//
// MessageId: VCI_E_NOTINITIALIZED
//
// MessageText:
//
//  The component is not initialized.
//
VCI_E_NOT_INITIALIZED = (SEV_VCI_ERROR or HResult($0010));

//
// MessageId: VCI_E_ALREADY_INITIALIZED
//
// MessageText:
//
//  An attempt was made to reinitialize an already initialized component.
//
VCI_E_ALREADY_INITIALIZED = (SEV_VCI_ERROR or HResult($00011));

//
// MessageId: VCI_E_RXQUEUE_EMPTY
//
// MessageText:
//
//  Receive queue empty.
//
VCI_E_RXQUEUE_EMPTY = (SEV_VCI_ERROR or HResult($00012));

//
// MessageId: VCI_E_TXQUEUE_FULL
//
// MessageText:
//
//  Transmit queue full.
//
VCI_E_TXQUEUE_FULL = (SEV_VCI_ERROR or HResult($0013));

//
// MessageId: VCI_E_BUFFER_OVERFLOW
//
// MessageText:
//
//  The data was too large to fit into the specified buffer.
//
VCI_E_BUFFER_OVERFLOW = (SEV_VCI_ERROR or HResult($0014));

//
// MessageId: VCI_E_INVALID_STATE
//
// MessageText:
//
//  The component is not in a valid state to perform this request.
//
VCI_E_INVALID_STATE = (SEV_VCI_ERROR or HResult($0015));

//
// MessageId: VCI_E_OBJECT_ALREADY_EXISTS
//
// MessageText:
//
//  The object already exists.
//
VCI_E_OBJECT_ALREADY_EXISTS = (SEV_VCI_ERROR or HResult($0016));

//
// MessageId: VCI_E_INVALID_INDEX
//
// MessageText:
//
//  Invalid index.
//
VCI_E_INVALID_INDEX  = (SEV_VCI_ERROR or HResult($0017));

//
// MessageId: VCI_E_END_OF_FILE
//
// MessageText:
//
//  The end-of-file marker has been reached.
//  There is no valid data in the file beyond this marker.
//
VCI_E_END_OF_FILE = (SEV_VCI_ERROR or HResult($0018));


implementation

end.

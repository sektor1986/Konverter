#ifndef __canRegs_h__
#define __canRegs_h__

extern volatile far  unsigned char       RXF0SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} RXF0SIDHbits;
extern volatile far  unsigned char       RXF0SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXIDEN:1;
  unsigned :1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} RXF0SIDLbits;
extern volatile far  unsigned char       RXF0EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} RXF0EIDHbits;
extern volatile far  unsigned char       RXF0EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} RXF0EIDLbits;
extern volatile far  unsigned char       RXF1SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} RXF1SIDHbits;
extern volatile far  unsigned char       RXF1SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXIDEN:1;
  unsigned :1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} RXF1SIDLbits;
extern volatile far  unsigned char       RXF1EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} RXF1EIDHbits;
extern volatile far  unsigned char       RXF1EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} RXF1EIDLbits;
extern volatile far  unsigned char       RXF2SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} RXF2SIDHbits;
extern volatile far  unsigned char       RXF2SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXIDEN:1;
  unsigned :1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} RXF2SIDLbits;
extern volatile far  unsigned char       RXF2EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} RXF2EIDHbits;
extern volatile far  unsigned char       RXF2EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} RXF2EIDLbits;
extern volatile far  unsigned char       RXF3SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} RXF3SIDHbits;
extern volatile far  unsigned char       RXF3SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXIDEN:1;
  unsigned :1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} RXF3SIDLbits;
extern volatile far  unsigned char       RXF3EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} RXF3EIDHbits;
extern volatile far  unsigned char       RXF3EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} RXF3EIDLbits;
extern volatile far  unsigned char       RXF4SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} RXF4SIDHbits;
extern volatile far  unsigned char       RXF4SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXIDEN:1;
  unsigned :1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} RXF4SIDLbits;
extern volatile far  unsigned char       RXF4EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} RXF4EIDHbits;
extern volatile far  unsigned char       RXF4EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} RXF4EIDLbits;
extern volatile far  unsigned char       RXF5SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} RXF5SIDHbits;
extern volatile far  unsigned char       RXF5SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXIDEN:1;
  unsigned :1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} RXF5SIDLbits;
extern volatile far  unsigned char       RXF5EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} RXF5EIDHbits;
extern volatile far  unsigned char       RXF5EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} RXF5EIDLbits;
extern volatile far  unsigned char       RXM0SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} RXM0SIDHbits;
extern volatile far  unsigned char       RXM0SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :3;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} RXM0SIDLbits;
extern volatile far  unsigned char       RXM0EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} RXM0EIDHbits;
extern volatile far  unsigned char       RXM0EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} RXM0EIDLbits;
extern volatile far  unsigned char       RXM1SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} RXM1SIDHbits;
extern volatile far  unsigned char       RXM1SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :3;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} RXM1SIDLbits;
extern volatile far  unsigned char       RXM1EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} RXM1EIDHbits;
extern volatile far  unsigned char       RXM1EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} RXM1EIDLbits;
extern volatile far  unsigned char       TXB2CON;
extern volatile far  struct {
  unsigned TXPRI0:1;
  unsigned TXPRI1:1;
  unsigned :1;
  unsigned TXREQ:1;
  unsigned TXERR:1;
  unsigned TXLARB:1;
  unsigned TXABT:1;
} TXB2CONbits;
extern volatile far  unsigned char       TXB2SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} TXB2SIDHbits;
extern volatile far  unsigned char       TXB2SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXIDE:1;
  unsigned :1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} TXB2SIDLbits;
extern volatile far  unsigned char       TXB2EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} TXB2EIDHbits;
extern volatile far  unsigned char       TXB2EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} TXB2EIDLbits;
extern volatile far  unsigned char       TXB2DLC;
extern volatile far  struct {
  unsigned DLC0:1;
  unsigned DLC1:1;
  unsigned DLC2:1;
  unsigned DLC3:1;
  unsigned :2;
  unsigned TXRTR:1;
} TXB2DLCbits;
extern volatile far  unsigned char       TXB2D0;
extern volatile far  struct {
  unsigned TXB2D00:1;
  unsigned TXB2D01:1;
  unsigned TXB2D02:1;
  unsigned TXB2D03:1;
  unsigned TXB2D04:1;
  unsigned TXB2D05:1;
  unsigned TXB2D06:1;
  unsigned TXB2D07:1;
} TXB2D0bits;
extern volatile far  unsigned char       TXB2D1;
extern volatile far  struct {
  unsigned TXB2D10:1;
  unsigned TXB2D11:1;
  unsigned TXB2D12:1;
  unsigned TXB2D13:1;
  unsigned TXB2D14:1;
  unsigned TXB2D15:1;
  unsigned TXB2D16:1;
  unsigned TXB2D17:1;
} TXB2D1bits;
extern volatile far  unsigned char       TXB2D2;
extern volatile far  struct {
  unsigned TXB2D20:1;
  unsigned TXB2D21:1;
  unsigned TXB2D22:1;
  unsigned TXB2D23:1;
  unsigned TXB2D24:1;
  unsigned TXB2D25:1;
  unsigned TXB2D26:1;
  unsigned TXB2D27:1;
} TXB2D2bits;
extern volatile far  unsigned char       TXB2D3;
extern volatile far  struct {
  unsigned TXB2D30:1;
  unsigned TXB2D31:1;
  unsigned TXB2D32:1;
  unsigned TXB2D33:1;
  unsigned TXB2D34:1;
  unsigned TXB2D35:1;
  unsigned TXB2D36:1;
  unsigned TXB2D37:1;
} TXB2D3bits;
extern volatile far  unsigned char       TXB2D4;
extern volatile far  struct {
  unsigned TXB2D40:1;
  unsigned TXB2D41:1;
  unsigned TXB2D42:1;
  unsigned TXB2D43:1;
  unsigned TXB2D44:1;
  unsigned TXB2D45:1;
  unsigned TXB2D46:1;
  unsigned TXB2D47:1;
} TXB2D4bits;
extern volatile far  unsigned char       TXB2D5;
extern volatile far  struct {
  unsigned TXB2D50:1;
  unsigned TXB2D51:1;
  unsigned TXB2D52:1;
  unsigned TXB2D53:1;
  unsigned TXB2D54:1;
  unsigned TXB2D55:1;
  unsigned TXB2D56:1;
  unsigned TXB2D57:1;
} TXB2D5bits;
extern volatile far  unsigned char       TXB2D6;
extern volatile far  struct {
  unsigned TXB2D60:1;
  unsigned TXB2D61:1;
  unsigned TXB2D62:1;
  unsigned TXB2D63:1;
  unsigned TXB2D64:1;
  unsigned TXB2D65:1;
  unsigned TXB2D66:1;
  unsigned TXB2D67:1;
} TXB2D6bits;
extern volatile far  unsigned char       TXB2D7;
extern volatile far  struct {
  unsigned TXB2D70:1;
  unsigned TXB2D71:1;
  unsigned TXB2D72:1;
  unsigned TXB2D73:1;
  unsigned TXB2D74:1;
  unsigned TXB2D75:1;
  unsigned TXB2D76:1;
  unsigned TXB2D77:1;
} TXB2D7bits;
extern volatile far  unsigned char       CANSTATRO4;
extern volatile far  struct {
  unsigned :1;
  unsigned ICODE0:1;
  unsigned ICODE1:1;
  unsigned ICODE2:1;
  unsigned :1;
  unsigned OPMODE0:1;
  unsigned OPMODE1:1;
  unsigned OPMODE2:1;
} CANSTATRO4bits;
extern volatile far  unsigned char       TXB1CON;
extern volatile far  struct {
  unsigned TXPRI0:1;
  unsigned TXPRI1:1;
  unsigned :1;
  unsigned TXREQ:1;
  unsigned TXERR:1;
  unsigned TXLARB:1;
  unsigned TXABT:1;
} TXB1CONbits;
extern volatile far  unsigned char       TXB1SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} TXB1SIDHbits;
extern volatile far  unsigned char       TXB1SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXIDE:1;
  unsigned :1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} TXB1SIDLbits;
extern volatile far  unsigned char       TXB1EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} TXB1EIDHbits;
extern volatile far  unsigned char       TXB1EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} TXB1EIDLbits;
extern volatile far  unsigned char       TXB1DLC;
extern volatile far  struct {
  unsigned DLC0:1;
  unsigned DLC1:1;
  unsigned DLC2:1;
  unsigned DLC3:1;
  unsigned :2;
  unsigned TXRTR:1;
} TXB1DLCbits;
extern volatile far  unsigned char       TXB1D0;
extern volatile far  struct {
  unsigned TXB1D00:1;
  unsigned TXB1D01:1;
  unsigned TXB1D02:1;
  unsigned TXB1D03:1;
  unsigned TXB1D04:1;
  unsigned TXB1D05:1;
  unsigned TXB1D06:1;
  unsigned TXB1D07:1;
} TXB1D0bits;
extern volatile far  unsigned char       TXB1D1;
extern volatile far  struct {
  unsigned TXB1D10:1;
  unsigned TXB1D11:1;
  unsigned TXB1D12:1;
  unsigned TXB1D13:1;
  unsigned TXB1D14:1;
  unsigned TXB1D15:1;
  unsigned TXB1D16:1;
  unsigned TXB1D17:1;
} TXB1D1bits;
extern volatile far  unsigned char       TXB1D2;
extern volatile far  struct {
  unsigned TXB1D20:1;
  unsigned TXB1D21:1;
  unsigned TXB1D22:1;
  unsigned TXB1D23:1;
  unsigned TXB1D24:1;
  unsigned TXB1D25:1;
  unsigned TXB1D26:1;
  unsigned TXB1D27:1;
} TXB1D2bits;
extern volatile far  unsigned char       TXB1D3;
extern volatile far  struct {
  unsigned TXB1D30:1;
  unsigned TXB1D31:1;
  unsigned TXB1D32:1;
  unsigned TXB1D33:1;
  unsigned TXB1D34:1;
  unsigned TXB1D35:1;
  unsigned TXB1D36:1;
  unsigned TXB1D37:1;
} TXB1D3bits;
extern volatile far  unsigned char       TXB1D4;
extern volatile far  struct {
  unsigned TXB1D40:1;
  unsigned TXB1D41:1;
  unsigned TXB1D42:1;
  unsigned TXB1D43:1;
  unsigned TXB1D44:1;
  unsigned TXB1D45:1;
  unsigned TXB1D46:1;
  unsigned TXB1D47:1;
} TXB1D4bits;
extern volatile far  unsigned char       TXB1D5;
extern volatile far  struct {
  unsigned TXB1D50:1;
  unsigned TXB1D51:1;
  unsigned TXB1D52:1;
  unsigned TXB1D53:1;
  unsigned TXB1D54:1;
  unsigned TXB1D55:1;
  unsigned TXB1D56:1;
  unsigned TXB1D57:1;
} TXB1D5bits;
extern volatile far  unsigned char       TXB1D6;
extern volatile far  struct {
  unsigned TXB1D60:1;
  unsigned TXB1D61:1;
  unsigned TXB1D62:1;
  unsigned TXB1D63:1;
  unsigned TXB1D64:1;
  unsigned TXB1D65:1;
  unsigned TXB1D66:1;
  unsigned TXB1D67:1;
} TXB1D6bits;
extern volatile far  unsigned char       TXB1D7;
extern volatile far  struct {
  unsigned TXB1D70:1;
  unsigned TXB1D71:1;
  unsigned TXB1D72:1;
  unsigned TXB1D73:1;
  unsigned TXB1D74:1;
  unsigned TXB1D75:1;
  unsigned TXB1D76:1;
  unsigned TXB1D77:1;
} TXB1D7bits;
extern volatile far  unsigned char       CANSTATRO3;
extern volatile far  struct {
  unsigned :1;
  unsigned ICODE0:1;
  unsigned ICODE1:1;
  unsigned ICODE2:1;
  unsigned :1;
  unsigned OPMODE0:1;
  unsigned OPMODE1:1;
  unsigned OPMODE2:1;
} CANSTATRO3bits;
extern volatile far  unsigned char       TXB0CON;
extern volatile far  struct {
  unsigned TXPRI0:1;
  unsigned TXPRI1:1;
  unsigned :1;
  unsigned TXREQ:1;
  unsigned TXERR:1;
  unsigned TXLARB:1;
  unsigned TXABT:1;
} TXB0CONbits;
extern volatile far  unsigned char       TXB0SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} TXB0SIDHbits;
extern volatile far  unsigned char       TXB0SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXIDE:1;
  unsigned :1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} TXB0SIDLbits;
extern volatile far  unsigned char       TXB0EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} TXB0EIDHbits;
extern volatile far  unsigned char       TXB0EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} TXB0EIDLbits;
extern volatile far  unsigned char       TXB0DLC;
extern volatile far  struct {
  unsigned DLC0:1;
  unsigned DLC1:1;
  unsigned DLC2:1;
  unsigned DLC3:1;
  unsigned :2;
  unsigned TXRTR:1;
} TXB0DLCbits;
extern volatile far  unsigned char       TXB0D0;
extern volatile far  struct {
  unsigned TXB0D00:1;
  unsigned TXB0D01:1;
  unsigned TXB0D02:1;
  unsigned TXB0D03:1;
  unsigned TXB0D04:1;
  unsigned TXB0D05:1;
  unsigned TXB0D06:1;
  unsigned TXB0D07:1;
} TXB0D0bits;
extern volatile far  unsigned char       TXB0D1;
extern volatile far  struct {
  unsigned TXB0D10:1;
  unsigned TXB0D11:1;
  unsigned TXB0D12:1;
  unsigned TXB0D13:1;
  unsigned TXB0D14:1;
  unsigned TXB0D15:1;
  unsigned TXB0D16:1;
  unsigned TXB0D17:1;
} TXB0D1bits;
extern volatile far  unsigned char       TXB0D2;
extern volatile far  struct {
  unsigned TXB0D20:1;
  unsigned TXB0D21:1;
  unsigned TXB0D22:1;
  unsigned TXB0D23:1;
  unsigned TXB0D24:1;
  unsigned TXB0D25:1;
  unsigned TXB0D26:1;
  unsigned TXB0D27:1;
} TXB0D2bits;
extern volatile far  unsigned char       TXB0D3;
extern volatile far  struct {
  unsigned TXB0D30:1;
  unsigned TXB0D31:1;
  unsigned TXB0D32:1;
  unsigned TXB0D33:1;
  unsigned TXB0D34:1;
  unsigned TXB0D35:1;
  unsigned TXB0D36:1;
  unsigned TXB0D37:1;
} TXB0D3bits;
extern volatile far  unsigned char       TXB0D4;
extern volatile far  struct {
  unsigned TXB0D40:1;
  unsigned TXB0D41:1;
  unsigned TXB0D42:1;
  unsigned TXB0D43:1;
  unsigned TXB0D44:1;
  unsigned TXB0D45:1;
  unsigned TXB0D46:1;
  unsigned TXB0D47:1;
} TXB0D4bits;
extern volatile far  unsigned char       TXB0D5;
extern volatile far  struct {
  unsigned TXB0D50:1;
  unsigned TXB0D51:1;
  unsigned TXB0D52:1;
  unsigned TXB0D53:1;
  unsigned TXB0D54:1;
  unsigned TXB0D55:1;
  unsigned TXB0D56:1;
  unsigned TXB0D57:1;
} TXB0D5bits;
extern volatile far  unsigned char       TXB0D6;
extern volatile far  struct {
  unsigned TXB0D60:1;
  unsigned TXB0D61:1;
  unsigned TXB0D62:1;
  unsigned TXB0D63:1;
  unsigned TXB0D64:1;
  unsigned TXB0D65:1;
  unsigned TXB0D66:1;
  unsigned TXB0D67:1;
} TXB0D6bits;
extern volatile far  unsigned char       TXB0D7;
extern volatile far  struct {
  unsigned TXB0D70:1;
  unsigned TXB0D71:1;
  unsigned TXB0D72:1;
  unsigned TXB0D73:1;
  unsigned TXB0D74:1;
  unsigned TXB0D75:1;
  unsigned TXB0D76:1;
  unsigned TXB0D77:1;
} TXB0D7bits;
extern volatile far  unsigned char       CANSTATRO2;
extern volatile far  struct {
  unsigned :1;
  unsigned ICODE0:1;
  unsigned ICODE1:1;
  unsigned ICODE2:1;
  unsigned :1;
  unsigned OPMODE0:1;
  unsigned OPMODE1:1;
  unsigned OPMODE2:1;
} CANSTATRO2bits;


extern volatile far  unsigned char       RXFCON0;
extern volatile far  struct {
  unsigned RXF0EN:1;
  unsigned RXF1EN:1;
  unsigned RXF2EN:1;
  unsigned RXF3EN:1;
  unsigned RXF4EN:1;
  unsigned RXF5EN:1;
  unsigned RXF6EN:1;
  unsigned RXF7EN:1;
} RXFCON0bits;
extern volatile far  unsigned char       RXB1CON;
extern volatile far  struct {
  unsigned FILHIT0:1;
  unsigned FILHIT1:1;
  unsigned FILHIT2:1;
  unsigned RXRTRRO:1;
  unsigned :1;
  unsigned RXM0:1;
  unsigned RXM1:1;
  unsigned RXFUL:1;
} RXB1CONbits;
extern volatile far  unsigned char       RXB1SIDH;
extern volatile far  struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} RXB1SIDHbits;
extern volatile far  unsigned char       RXB1SIDL;
extern volatile far  struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXID:1;
  unsigned SRR:1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} RXB1SIDLbits;
extern volatile far  unsigned char       RXB1EIDH;
extern volatile far  struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} RXB1EIDHbits;
extern volatile far  unsigned char       RXB1EIDL;
extern volatile far  struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} RXB1EIDLbits;
extern volatile far  unsigned char       RXB1DLC;
extern volatile far  struct {
  unsigned DLC0:1;
  unsigned DLC1:1;
  unsigned DLC2:1;
  unsigned DLC3:1;
  unsigned RESB0:1;
  unsigned RESB1:1;
  unsigned RXRTR:1;
} RXB1DLCbits;
extern volatile far  unsigned char       RXB1D0;
extern volatile far  struct {
  unsigned RXB1D00:1;
  unsigned RXB1D01:1;
  unsigned RXB1D02:1;
  unsigned RXB1D03:1;
  unsigned RXB1D04:1;
  unsigned RXB1D05:1;
  unsigned RXB1D06:1;
  unsigned RXB1D07:1;
} RXB1D0bits;
extern volatile far  unsigned char       RXB1D1;
extern volatile far  struct {
  unsigned RXB1D10:1;
  unsigned RXB1D11:1;
  unsigned RXB1D12:1;
  unsigned RXB1D13:1;
  unsigned RXB1D14:1;
  unsigned RXB1D15:1;
  unsigned RXB1D16:1;
  unsigned RXB1D17:1;
} RXB1D1bits;
extern volatile far  unsigned char       RXB1D2;
extern volatile far  struct {
  unsigned RXB1D20:1;
  unsigned RXB1D21:1;
  unsigned RXB1D22:1;
  unsigned RXB1D23:1;
  unsigned RXB1D24:1;
  unsigned RXB1D25:1;
  unsigned RXB1D26:1;
  unsigned RXB1D27:1;
} RXB1D2bits;
extern volatile far  unsigned char       RXB1D3;
extern volatile far  struct {
  unsigned RXB1D30:1;
  unsigned RXB1D31:1;
  unsigned RXB1D32:1;
  unsigned RXB1D33:1;
  unsigned RXB1D34:1;
  unsigned RXB1D35:1;
  unsigned RXB1D36:1;
  unsigned RXB1D37:1;
} RXB1D3bits;
extern volatile far  unsigned char       RXB1D4;
extern volatile far  struct {
  unsigned RXB1D40:1;
  unsigned RXB1D41:1;
  unsigned RXB1D42:1;
  unsigned RXB1D43:1;
  unsigned RXB1D44:1;
  unsigned RXB1D45:1;
  unsigned RXB1D46:1;
  unsigned RXB1D47:1;
} RXB1D4bits;
extern volatile far  unsigned char       RXB1D5;
extern volatile far  struct {
  unsigned RXB1D50:1;
  unsigned RXB1D51:1;
  unsigned RXB1D52:1;
  unsigned RXB1D53:1;
  unsigned RXB1D54:1;
  unsigned RXB1D55:1;
  unsigned RXB1D56:1;
  unsigned RXB1D57:1;
} RXB1D5bits;
extern volatile far  unsigned char       RXB1D6;
extern volatile far  struct {
  unsigned RXB1D60:1;
  unsigned RXB1D61:1;
  unsigned RXB1D62:1;
  unsigned RXB1D63:1;
  unsigned RXB1D64:1;
  unsigned RXB1D65:1;
  unsigned RXB1D66:1;
  unsigned RXB1D67:1;
} RXB1D6bits;
extern volatile far  unsigned char       RXB1D7;
extern volatile far  struct {
  unsigned RXB1D70:1;
  unsigned RXB1D71:1;
  unsigned RXB1D72:1;
  unsigned RXB1D73:1;
  unsigned RXB1D74:1;
  unsigned RXB1D75:1;
  unsigned RXB1D76:1;
  unsigned RXB1D77:1;
} RXB1D7bits;
extern volatile far  unsigned char       CANSTATRO1;
extern volatile far  struct {
  unsigned :1;
  unsigned ICODE0:1;
  unsigned ICODE1:1;
  unsigned ICODE2:1;
  unsigned :1;
  unsigned OPMODE0:1;
  unsigned OPMODE1:1;
  unsigned OPMODE2:1;
} CANSTATRO1bits;
extern volatile near unsigned char       RXB0CON;
extern volatile near struct {
  unsigned FILHIT0:1;
  unsigned JTOFF:1;
  unsigned RXB0DBEN:1;
  unsigned RXRTRRO:1;
  unsigned :1;
  unsigned RXM0:1;
  unsigned RXM1:1;
  unsigned RXFUL:1;
} RXB0CONbits;
extern volatile near unsigned char       RXB0SIDH;
extern volatile near struct {
  unsigned SID3:1;
  unsigned SID4:1;
  unsigned SID5:1;
  unsigned SID6:1;
  unsigned SID7:1;
  unsigned SID8:1;
  unsigned SID9:1;
  unsigned SID10:1;
} RXB0SIDHbits;
extern volatile near unsigned char       RXB0SIDL;
extern volatile near struct {
  unsigned EID16:1;
  unsigned EID17:1;
  unsigned :1;
  unsigned EXID:1;
  unsigned SRR:1;
  unsigned SID0:1;
  unsigned SID1:1;
  unsigned SID2:1;
} RXB0SIDLbits;
extern volatile near unsigned char       RXB0EIDH;
extern volatile near struct {
  unsigned EID8:1;
  unsigned EID9:1;
  unsigned EID10:1;
  unsigned EID11:1;
  unsigned EID12:1;
  unsigned EID13:1;
  unsigned EID14:1;
  unsigned EID15:1;
} RXB0EIDHbits;
extern volatile near unsigned char       RXB0EIDL;
extern volatile near struct {
  unsigned EID0:1;
  unsigned EID1:1;
  unsigned EID2:1;
  unsigned EID3:1;
  unsigned EID4:1;
  unsigned EID5:1;
  unsigned EID6:1;
  unsigned EID7:1;
} RXB0EIDLbits;
extern volatile near unsigned char       RXB0DLC;
extern volatile near struct {
  unsigned DLC0:1;
  unsigned DLC1:1;
  unsigned DLC2:1;
  unsigned DLC3:1;
  unsigned RESB0:1;
  unsigned RESB1:1;
  unsigned RXRTR:1;
} RXB0DLCbits;
extern volatile near unsigned char       RXB0D0;
extern volatile near struct {
  unsigned RXB0D00:1;
  unsigned RXB0D01:1;
  unsigned RXB0D02:1;
  unsigned RXB0D03:1;
  unsigned RXB0D04:1;
  unsigned RXB0D05:1;
  unsigned RXB0D06:1;
  unsigned RXB0D07:1;
} RXB0D0bits;
extern volatile near unsigned char       RXB0D1;
extern volatile near struct {
  unsigned RXB0D10:1;
  unsigned RXB0D11:1;
  unsigned RXB0D12:1;
  unsigned RXB0D13:1;
  unsigned RXB0D14:1;
  unsigned RXB0D15:1;
  unsigned RXB0D16:1;
  unsigned RXB0D17:1;
} RXB0D1bits;
extern volatile near unsigned char       RXB0D2;
extern volatile near struct {
  unsigned RXB0D20:1;
  unsigned RXB0D21:1;
  unsigned RXB0D22:1;
  unsigned RXB0D23:1;
  unsigned RXB0D24:1;
  unsigned RXB0D25:1;
  unsigned RXB0D26:1;
  unsigned RXB0D27:1;
} RXB0D2bits;
extern volatile near unsigned char       RXB0D3;
extern volatile near struct {
  unsigned RXB0D30:1;
  unsigned RXB0D31:1;
  unsigned RXB0D32:1;
  unsigned RXB0D33:1;
  unsigned RXB0D34:1;
  unsigned RXB0D35:1;
  unsigned RXB0D36:1;
  unsigned RXB0D37:1;
} RXB0D3bits;
extern volatile near unsigned char       RXB0D4;
extern volatile near struct {
  unsigned RXB0D40:1;
  unsigned RXB0D41:1;
  unsigned RXB0D42:1;
  unsigned RXB0D43:1;
  unsigned RXB0D44:1;
  unsigned RXB0D45:1;
  unsigned RXB0D46:1;
  unsigned RXB0D47:1;
} RXB0D4bits;
extern volatile near unsigned char       RXB0D5;
extern volatile near struct {
  unsigned RXB0D50:1;
  unsigned RXB0D51:1;
  unsigned RXB0D52:1;
  unsigned RXB0D53:1;
  unsigned RXB0D54:1;
  unsigned RXB0D55:1;
  unsigned RXB0D56:1;
  unsigned RXB0D57:1;
} RXB0D5bits;
extern volatile near unsigned char       RXB0D6;
extern volatile near struct {
  unsigned RXB0D60:1;
  unsigned RXB0D61:1;
  unsigned RXB0D62:1;
  unsigned RXB0D63:1;
  unsigned RXB0D64:1;
  unsigned RXB0D65:1;
  unsigned RXB0D66:1;
  unsigned RXB0D67:1;
} RXB0D6bits;
extern volatile near unsigned char       RXB0D7;
extern volatile near struct {
  unsigned RXB0D70:1;
  unsigned RXB0D71:1;
  unsigned RXB0D72:1;
  unsigned RXB0D73:1;
  unsigned RXB0D74:1;
  unsigned RXB0D75:1;
  unsigned RXB0D76:1;
  unsigned RXB0D77:1;
} RXB0D7bits;
extern volatile near unsigned char       CANSTAT;
extern volatile near struct {
  unsigned :1;
  unsigned ICODE0:1;
  unsigned ICODE1:1;
  unsigned ICODE2:1;
  unsigned :1;
  unsigned OPMODE0:1;
  unsigned OPMODE1:1;
  unsigned OPMODE2:1;
} CANSTATbits;
extern volatile near unsigned char       CANCON;
extern volatile near struct {
  unsigned :1;
  unsigned WIN0:1;
  unsigned WIN1:1;
  unsigned WIN2:1;
  unsigned ABAT:1;
  unsigned REQOP0:1;
  unsigned REQOP1:1;
  unsigned REQOP2:1;
} CANCONbits;
extern volatile near unsigned char       BRGCON1;
extern volatile near struct {
  unsigned BRP0:1;
  unsigned BRP1:1;
  unsigned BRP2:1;
  unsigned BRP3:1;
  unsigned BRP4:1;
  unsigned BRP5:1;
  unsigned SJW0:1;
  unsigned SJW1:1;
} BRGCON1bits;
extern volatile near unsigned char       BRGCON2;
extern volatile near struct {
  unsigned PRSEG0:1;
  unsigned PRSEG1:1;
  unsigned PRSEG2:1;
  unsigned SEG1PH0:1;
  unsigned SEG1PH1:1;
  unsigned SEG1PH2:1;
  unsigned SAM:1;
  unsigned SEG2PHTS:1;
} BRGCON2bits;
extern volatile near unsigned char       BRGCON3;
extern volatile near struct {
  unsigned SEG2PH0:1;
  unsigned SEG2PH1:1;
  unsigned SEG2PH2:1;
  unsigned :3;
  unsigned WAKFIL:1;
} BRGCON3bits;
extern volatile near unsigned char       CIOCON;
extern volatile near struct {
  unsigned :4;
  unsigned CANCAP:1;
  unsigned ENDRHI:1;
} CIOCONbits;
extern volatile near unsigned char       COMSTAT;
extern volatile near union {
  struct {
    unsigned :6;
    unsigned RX2OVFL:1;
    unsigned RX1OVFL:1;
  };
  struct {
    unsigned EWARN:1;
    unsigned RXWARN:1;
    unsigned TXWARN:1;
    unsigned RXBP:1;
    unsigned TXBP:1;
    unsigned TXBO:1;
    unsigned RXB1OVFL:1;
    unsigned RXB0OVFL:1;
  };
} COMSTATbits;
extern volatile near unsigned char       RXERRCNT;
extern volatile near struct {
  unsigned REC0:1;
  unsigned REC1:1;
  unsigned REC2:1;
  unsigned REC3:1;
  unsigned REC4:1;
  unsigned REC5:1;
  unsigned REC6:1;
  unsigned REC7:1;
} RXERRCNTbits;
extern volatile near unsigned char       TXERRCNT;
extern volatile near struct {
  unsigned TEC0:1;
  unsigned TEC1:1;
  unsigned TEC2:1;
  unsigned TEC3:1;
  unsigned TEC4:1;
  unsigned TEC5:1;
  unsigned TEC6:1;
  unsigned TEC7:1;
} TXERRCNTbits;

extern volatile near unsigned char       PORTB;
extern volatile near union {
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
  struct {
    unsigned INT0:1;
    unsigned INT1:1;
    unsigned CANTX:1;
    unsigned CANRX:1;
    unsigned :1;
    unsigned PGM:1;
    unsigned PGC:1;
    unsigned PGD:1;
  };
} PORTBbits;

extern volatile near unsigned char       LATB;
extern volatile near struct {
  unsigned LATB0:1;
  unsigned LATB1:1;
  unsigned LATB2:1;
  unsigned LATB3:1;
  unsigned LATB4:1;
  unsigned LATB5:1;
  unsigned LATB6:1;
  unsigned LATB7:1;
} LATBbits;

extern volatile near unsigned char       TRISB;
extern volatile near struct {
  unsigned TRISB0:1;
  unsigned TRISB1:1;
  unsigned TRISB2:1;
  unsigned TRISB3:1;
  unsigned TRISB4:1;
  unsigned TRISB5:1;
  unsigned TRISB6:1;
  unsigned TRISB7:1;
} TRISBbits;

extern volatile near unsigned char       PIE3;
extern volatile near union {
  struct {
    unsigned RXB0IE:1;
    unsigned RXB1IE:1;
    unsigned TXB0IE:1;
    unsigned TXB1IE:1;
    unsigned TXB2IE:1;
    unsigned :2;
    unsigned IRXIE:1;
  };
  struct {
    unsigned RX0IE:1;
    unsigned RX1IE:1;
    unsigned TX0IE:1;
    unsigned TX1IE:1;
    unsigned TX2IE:1;
    unsigned ERRIE:1;
    unsigned WAKIE:1;
    unsigned IVRE:1;
  };
} PIE3bits;
extern volatile near unsigned char       PIR3;
extern volatile near union {
  struct {
    unsigned RXB0IF:1;
    unsigned RXB1IF:1;
    unsigned TXB0IF:1;
    unsigned TXB1IF:1;
    unsigned TXB2IF:1;
    unsigned :2;
    unsigned IRXIF:1;
  };
  struct {
    unsigned RX0IF:1;
    unsigned RX1IF:1;
    unsigned TX0IF:1;
    unsigned TX1IF:1;
    unsigned TX2IF:1;
    unsigned ERRIF:1;
    unsigned WAKIF:1;
    unsigned IVRF:1;
  };
} PIR3bits;
extern volatile near unsigned char       IPR3;
extern volatile near union {
  struct {
    unsigned :7;
    unsigned IRXIP:1;
  };
  struct {
    unsigned RXB0IP:1;
    unsigned RXB1IP:1;
    unsigned TXB0IP:1;
    unsigned TXB1IP:1;
    unsigned TXB2IP:1;
    unsigned ERRIP:1;
    unsigned WAKIP:1;
    unsigned IVRP:1;
  };
} IPR3bits;
//
//extern volatile far  unsigned char       RXFCON1;
//extern volatile far  struct {
//  unsigned RXF8EN:1;
//  unsigned RXF9EN:1;
//  unsigned RXF10EN:1;
//  unsigned RXF11EN:1;
//  unsigned RXF12EN:1;
//  unsigned RXF13EN:1;
//  unsigned RXF14EN:1;
//  unsigned RXF15EN:1;
//} RXFCON1bits;
//extern volatile far  unsigned char       SDFLC;
//extern volatile far  struct {
//  unsigned DFLC0:1;
//  unsigned DFLC1:1;
//  unsigned DFLC2:1;
//  unsigned DFLC3:1;
//  unsigned DFLC4:1;
//} SDFLCbits;
//extern volatile far  unsigned char       RXFBCON0;
//extern volatile far  struct {
//  unsigned F0BP_0:1;
//  unsigned F0BP_1:1;
//  unsigned F0BP_2:1;
//  unsigned F0BP_3:1;
//  unsigned F1BP_0:1;
//  unsigned F1BP_1:1;
//  unsigned F1BP_2:1;
//  unsigned F1BP_3:1;
//} RXFBCON0bits;
//extern volatile far  unsigned char       RXFBCON1;
//extern volatile far  struct {
//  unsigned F2BP_0:1;
//  unsigned F2BP_1:1;
//  unsigned F2BP_2:1;
//  unsigned F2BP_3:1;
//  unsigned F3BP_0:1;
//  unsigned F3BP_1:1;
//  unsigned F3BP_2:1;
//  unsigned F3BP_3:1;
//} RXFBCON1bits;
//extern volatile far  unsigned char       RXFBCON2;
//extern volatile far  struct {
//  unsigned F4BP_0:1;
//  unsigned F4BP_1:1;
//  unsigned F4BP_2:1;
//  unsigned F4BP_3:1;
//  unsigned F5BP_0:1;
//  unsigned F5BP_1:1;
//  unsigned F5BP_2:1;
//  unsigned F5BP_3:1;
//} RXFBCON2bits;
//extern volatile far  unsigned char       RXFBCON3;
//extern volatile far  struct {
//  unsigned F6BP_0:1;
//  unsigned F6BP_1:1;
//  unsigned F6BP_2:1;
//  unsigned F6BP_3:1;
//  unsigned F7BP_0:1;
//  unsigned F7BP_1:1;
//  unsigned F7BP_2:1;
//  unsigned F7BP_3:1;
//} RXFBCON3bits;
//extern volatile far  unsigned char       RXFBCON4;
//extern volatile far  struct {
//  unsigned F8BP_0:1;
//  unsigned F8BP_1:1;
//  unsigned F8BP_2:1;
//  unsigned F8BP_3:1;
//  unsigned F9BP_0:1;
//  unsigned F9BP_1:1;
//  unsigned F9BP_2:1;
//  unsigned F9BP_3:1;
//} RXFBCON4bits;
//extern volatile far  unsigned char       RXFBCON5;
//extern volatile far  struct {
//  unsigned F10BP_0:1;
//  unsigned F10BP_1:1;
//  unsigned F10BP_2:1;
//  unsigned F10BP_3:1;
//  unsigned F11BP_0:1;
//  unsigned F11BP_1:1;
//  unsigned F11BP_2:1;
//  unsigned F11BP_3:1;
//} RXFBCON5bits;
//extern volatile far  unsigned char       RXFBCON6;
//extern volatile far  struct {
//  unsigned F12BP_0:1;
//  unsigned F12BP_1:1;
//  unsigned F12BP_2:1;
//  unsigned F12BP_3:1;
//  unsigned F13BP_0:1;
//  unsigned F13BP_1:1;
//  unsigned F13BP_2:1;
//  unsigned F13BP_3:1;
//} RXFBCON6bits;
//extern volatile far  unsigned char       RXFBCON7;
//extern volatile far  struct {
//  unsigned F14BP_0:1;
//  unsigned F14BP_1:1;
//  unsigned F14BP_2:1;
//  unsigned F14BP_3:1;
//  unsigned F15BP_0:1;
//  unsigned F15BP_1:1;
//  unsigned F15BP_2:1;
//  unsigned F15BP_3:1;
//} RXFBCON7bits;
//extern volatile far  unsigned char       MSEL0;
//extern volatile far  struct {
//  unsigned FIL0_0:1;
//  unsigned FIL0_1:1;
//  unsigned FIL1_0:1;
//  unsigned FIL1_1:1;
//  unsigned FIL2_0:1;
//  unsigned FIL2_1:1;
//  unsigned FIL3_0:1;
//  unsigned FIL3_1:1;
//} MSEL0bits;
//extern volatile far  unsigned char       MSEL1;
//extern volatile far  struct {
//  unsigned FIL4_0:1;
//  unsigned FIL4_1:1;
//  unsigned FIL5_0:1;
//  unsigned FIL5_1:1;
//  unsigned FIL6_0:1;
//  unsigned FIL6_1:1;
//  unsigned FIL7_0:1;
//  unsigned FIL7_1:1;
//} MSEL1bits;
//extern volatile far  unsigned char       MSEL2;
//extern volatile far  struct {
//  unsigned FIL8_0:1;
//  unsigned FIL8_1:1;
//  unsigned FIL9_0:1;
//  unsigned FIL9_1:1;
//  unsigned FIL10_0:1;
//  unsigned FIL10_1:1;
//  unsigned FIL11_0:1;
//  unsigned FIL11_1:1;
//} MSEL2bits;
//extern volatile far  unsigned char       MSEL3;
//extern volatile far  struct {
//  unsigned FIL12_0:1;
//  unsigned FIL12_1:1;
//  unsigned FIL13_0:1;
//  unsigned FIL13_1:1;
//  unsigned FIL14_0:1;
//  unsigned FIL14_1:1;
//  unsigned FIL15_0:1;
//  unsigned FIL15_1:1;
//} MSEL3bits;
//
#endif
object Form_Glavn: TForm_Glavn
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Test_Converter V 1.0'
  ClientHeight = 416
  ClientWidth = 506
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    506
    416)
  PixelsPerInch = 96
  TextHeight = 13
  object sBevel1: TsBevel
    Left = 8
    Top = 358
    Width = 487
    Height = 16
    Anchors = [akLeft, akRight, akBottom]
    Shape = bsTopLine
    ExplicitTop = 354
  end
  object sLabel1: TsLabel
    Left = 72
    Top = 8
    Width = 167
    Height = 32
    BiDiMode = bdLeftToRight
    Caption = #1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072' '#1085#1072#1088#1091#1078#1085#1086#1075#1086#13#10'         '#1074#1086#1079#1076#1091#1093#1072', '#176'C'
    ParentBiDiMode = False
    ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
  end
  object sLabel2: TsLabel
    Left = 304
    Top = 17
    Width = 137
    Height = 16
    Hint = 'SPN 96 Fuel Level 1 '
    Caption = #1059#1088#1086#1074#1077#1085#1100' '#1090#1086#1087#1083#1080#1074#1072', %'
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
  end
  object sLabelFX1: TsLabelFX
    Left = 88
    Top = 287
    Width = 100
    Height = 27
    Alignment = taCenter
    Caption = '0 '#176#1057
    ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
  end
  object sLabelFX2: TsLabelFX
    Left = 319
    Top = 287
    Width = 100
    Height = 27
    Alignment = taCenter
    Caption = '0 %'
    ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
  end
  object sLabelFX3: TsLabelFX
    Left = 88
    Top = 320
    Width = 55
    Height = 22
    Caption = #1055#1077#1088#1080#1086#1076':'
    ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    Shadow.Color = clNavy
  end
  object sLabelFX4: TsLabelFX
    Left = 319
    Top = 320
    Width = 55
    Height = 22
    Caption = #1055#1077#1088#1080#1086#1076':'
    ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    Shadow.Color = clNavy
  end
  object sBitBtn1: TsBitBtn
    Left = 423
    Top = 366
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 0
    OnClick = sBitBtn1Click
    SkinData.SkinSection = 'BUTTON'
    ExplicitTop = 362
  end
  object iThermometer1: TiThermometer
    Left = 88
    Top = 46
    Height = 235
    PositionMax = 50.000000000000000000
    PositionMin = -50.000000000000000000
    IndicatorWidth = 3
    IndicatorBulbSize = 7
    IndicatorBackGroundColor = clWhite
    IndicatorFillReferenceStyle = ipfrsMin
    TickLabelFont.Charset = DEFAULT_CHARSET
    TickLabelFont.Color = clWindowText
    TickLabelFont.Height = -11
    TickLabelFont.Name = 'Tahoma'
    TickLabelFont.Style = []
    PositionMax_2 = 50.000000000000000000
  end
  object iThermometer2: TiThermometer
    Left = 319
    Top = 46
    Height = 235
    PositionMax = 100.000000000000000000
    IndicatorWidth = 3
    IndicatorBulbSize = 7
    IndicatorStyle = itisBar
    IndicatorColor = clBlue
    IndicatorBackGroundColor = clWhite
    IndicatorFillReferenceStyle = ipfrsMin
    TickLabelFont.Charset = DEFAULT_CHARSET
    TickLabelFont.Color = clWindowText
    TickLabelFont.Height = -11
    TickLabelFont.Name = 'Tahoma'
    TickLabelFont.Style = []
    PositionMax_2 = 100.000000000000000000
  end
  object iThreadTimers1: TiThreadTimers
    Left = 16
    Top = 32
    Enabled1 = True
    Interval1 = 2000
    OnTimer1 = iThreadTimers1Timer1
  end
  object stbBottom: TsStatusBar
    Left = 0
    Top = 397
    Width = 506
    Height = 19
    Panels = <
      item
        Width = 140
      end
      item
        Width = 50
      end>
    SkinData.SkinSection = 'STATUSBAR'
    ExplicitLeft = 240
    ExplicitTop = 352
    ExplicitWidth = 0
  end
  object MainMenu1: TMainMenu
    Left = 432
    Top = 16
    object N1: TMenuItem
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #1047#1072#1082#1088#1099#1090#1100
      OnClick = N2Click
    end
  end
end

object FormsystemSet: TFormsystemSet
  Left = 607
  Top = 408
  Width = 330
  Height = 282
  Caption = 'Detectors Setting'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDesktopCenter
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 32
    Top = 24
    Width = 225
    Height = 145
    Caption = 'GridSize Between Detectors'
    TabOrder = 0
    object RzLabelX: TRzLabel
      Left = 56
      Top = 35
      Width = 13
      Height = 15
      Caption = 'X:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzLabelY: TRzLabel
      Left = 56
      Top = 65
      Width = 11
      Height = 15
      Caption = 'Y:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzLabelZ: TRzLabel
      Left = 56
      Top = 99
      Width = 12
      Height = 15
      Caption = 'Z:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzLabelUnit1: TRzLabel
      Left = 168
      Top = 34
      Width = 20
      Height = 15
      Caption = 'mm'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzLabelUnit2: TRzLabel
      Left = 168
      Top = 66
      Width = 20
      Height = 15
      Caption = 'mm'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzLabelUnit3: TRzLabel
      Left = 168
      Top = 98
      Width = 20
      Height = 15
      Caption = 'mm'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzEditX: TRzEdit
      Left = 80
      Top = 32
      Width = 81
      Height = 21
      TabOrder = 0
    end
    object RzEditY: TRzEdit
      Left = 80
      Top = 64
      Width = 81
      Height = 21
      TabOrder = 1
    end
    object RzEditZ: TRzEdit
      Left = 80
      Top = 96
      Width = 81
      Height = 21
      TabOrder = 2
    end
  end
  object BitBtnOK: TBitBtn
    Left = 48
    Top = 192
    Width = 75
    Height = 25
    TabOrder = 1
    OnClick = BitBtnOKClick
    Kind = bkOK
  end
  object BitBtnCancel: TBitBtn
    Left = 176
    Top = 192
    Width = 75
    Height = 25
    TabOrder = 2
    OnClick = BitBtnCancelClick
    Kind = bkCancel
  end
end

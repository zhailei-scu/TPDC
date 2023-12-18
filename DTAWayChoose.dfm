object FormDTAWayChoose: TFormDTAWayChoose
  Left = 620
  Top = 323
  BorderStyle = bsDialog
  Caption = 'DTA Check Way Choose'
  ClientHeight = 249
  ClientWidth = 303
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
  PixelsPerInch = 96
  TextHeight = 13
  object RzPanelDTA: TRzPanel
    Left = 0
    Top = 0
    Width = 303
    Height = 249
    Align = alClient
    TabOrder = 0
    object RzLabelDTA: TRzLabel
      Left = 72
      Top = 16
      Width = 210
      Height = 15
      Caption = 'Please Choose the way for DTA Check.'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzRadioGroupDTA: TRzRadioGroup
      Left = 48
      Top = 48
      Width = 217
      Alignment = taCenter
      Caption = 'DTA method choose'
      Color = clMoneyGreen
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      GroupStyle = gsBanner
      ItemHotTrack = True
      ItemIndex = 1
      Items.Strings = (
        'Float Justify'
        'Middle Value'
        'Same position')
      ParentFont = False
      TabOrder = 0
    end
    object RzBitBtnOK: TRzBitBtn
      Left = 48
      Top = 184
      TabOrder = 1
      OnClick = RzBitBtnOKClick
      Kind = bkOK
    end
    object RzBitBtnCancel: TRzBitBtn
      Left = 184
      Top = 184
      TabOrder = 2
      Kind = bkCancel
    end
  end
end

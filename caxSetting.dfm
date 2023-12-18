object FormCAX: TFormCAX
  Left = 576
  Top = 196
  BorderStyle = bsDialog
  Caption = 'CAX Setting'
  ClientHeight = 296
  ClientWidth = 373
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
  PixelsPerInch = 96
  TextHeight = 13
  object RzPanelCAX: TRzPanel
    Left = 0
    Top = 0
    Width = 373
    Height = 296
    Align = alClient
    Color = clMoneyGreen
    TabOrder = 0
    object RzMemo1: TRzMemo
      Left = 32
      Top = 24
      Width = 289
      Height = 25
      Alignment = taCenter
      Color = clMoneyGreen
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      Lines.Strings = (
        'Please Set the CAX of the Measurement.')
      ParentFont = False
      TabOrder = 0
      FrameVisible = True
    end
    object RzGroupBoxCAX: TRzGroupBox
      Left = 80
      Top = 88
      Width = 201
      Height = 129
      Alignment = taCenter
      Caption = 'CAX Setting'
      Color = clSkyBlue
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      GroupStyle = gsBanner
      ParentFont = False
      TabOrder = 1
      object RzLabelCAX_X: TRzLabel
        Left = 24
        Top = 45
        Width = 41
        Height = 15
        Caption = 'X(mm):'
      end
      object RzLabelCAX_Y: TRzLabel
        Left = 24
        Top = 82
        Width = 40
        Height = 15
        Caption = 'Y(mm):'
      end
      object RzSpinEditCAX_X: TRzSpinEdit
        Left = 88
        Top = 40
        Width = 97
        Height = 23
        AllowKeyEdit = True
        Decimals = 3
        Increment = 0.1
        IntegersOnly = False
        FlatButtons = True
        FrameVisible = True
        TabOrder = 0
      end
      object RzSpinEditCAX_Y: TRzSpinEdit
        Left = 88
        Top = 80
        Width = 97
        Height = 23
        AllowKeyEdit = True
        Decimals = 3
        Increment = 0.1
        IntegersOnly = False
        FlatButtons = True
        FrameVisible = True
        TabOrder = 1
      end
    end
    object RzBitBtnOK: TRzBitBtn
      Left = 48
      Top = 240
      TabOrder = 2
      Kind = bkOK
    end
    object RzBitBtnCancel: TRzBitBtn
      Left = 264
      Top = 240
      TabOrder = 3
      OnClick = RzBitBtnCancelClick
      Kind = bkCancel
    end
    object RzBitBtnReset: TRzBitBtn
      Left = 152
      Top = 240
      Caption = 'Reset'
      TabOrder = 4
      OnClick = RzBitBtnResetClick
      ImageIndex = 462
      Images = FormMain.ImageList1
    end
  end
end

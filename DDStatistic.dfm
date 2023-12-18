object FormDDStatics: TFormDDStatics
  Left = 629
  Top = 225
  BorderStyle = bsDialog
  Caption = 'FormDDStatics'
  ClientHeight = 303
  ClientWidth = 243
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object RzPanelDD: TRzPanel
    Left = 0
    Top = 0
    Width = 243
    Height = 303
    Align = alClient
    Color = clMenuHighlight
    TabOrder = 0
    object RzMemoDD: TRzMemo
      Left = 2
      Top = 2
      Width = 239
      Height = 89
      Align = alTop
      Color = clMoneyGreen
      TabOrder = 0
      FrameVisible = True
    end
    object RzRadioGroupDD: TRzRadioGroup
      Left = 2
      Top = 91
      Width = 239
      Height = 121
      Align = alTop
      Alignment = taCenter
      Caption = 'Choose the statistic type'
      Color = clMoneyGreen
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      GroupStyle = gsBanner
      ItemHotTrack = True
      ItemIndex = 0
      Items.Strings = (
        'Average 10'
        'Manual Specical a Range')
      ParentFont = False
      TabOrder = 1
      object RzLabel1: TRzLabel
        Left = 8
        Top = 91
        Width = 29
        Height = 15
        Caption = 'From'
      end
      object RzLabel2: TRzLabel
        Left = 96
        Top = 91
        Width = 37
        Height = 15
        Caption = 'cGy To'
      end
      object RzLabel3: TRzLabel
        Left = 200
        Top = 91
        Width = 21
        Height = 15
        Caption = 'cGy'
      end
      object RzNumericEditStart: TRzNumericEdit
        Left = 40
        Top = 88
        Width = 49
        Height = 23
        FrameVisible = True
        TabOrder = 0
        IntegersOnly = False
        DisplayFormat = ',0.000;(,0.000)'
      end
      object RzNumericEditEnd: TRzNumericEdit
        Left = 144
        Top = 88
        Width = 49
        Height = 23
        FrameVisible = True
        TabOrder = 1
        IntegersOnly = False
        DisplayFormat = ',0.000;(,0.000)'
      end
    end
    object RzBitBtnOK: TRzBitBtn
      Left = 32
      Top = 240
      TabOrder = 2
      OnClick = RzBitBtnOKClick
      Kind = bkOK
    end
    object RzBitBtnCAncel: TRzBitBtn
      Left = 144
      Top = 240
      TabOrder = 3
      Kind = bkCancel
    end
  end
end

object FormAngle: TFormAngle
  Left = 588
  Top = 367
  BorderStyle = bsDialog
  Caption = 'Input Dose Angle'
  ClientHeight = 170
  ClientWidth = 297
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
  object PanelAngle: TRzPanel
    Left = 0
    Top = 0
    Width = 297
    Height = 170
    Align = alClient
    Color = clMoneyGreen
    TabOrder = 0
    object RzLabelAngle: TRzLabel
      Left = 80
      Top = 80
      Width = 37
      Height = 15
      Caption = 'Angle:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzMemoAngle: TRzMemo
      Left = 16
      Top = 8
      Width = 265
      Height = 49
      Color = clMoneyGreen
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      Lines.Strings = (
        'Please Input the dose angle(Treatment angle) '
        'before the process.')
      ParentFont = False
      TabOrder = 0
      FrameVisible = True
    end
    object RzEditAngle: TRzEdit
      Left = 136
      Top = 78
      Width = 81
      Height = 23
      Text = '0'
      Alignment = taRightJustify
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      FrameVisible = True
      ParentFont = False
      TabOrder = 1
    end
    object RzBitBtnOK: TRzBitBtn
      Left = 48
      Top = 128
      TabOrder = 2
      Kind = bkOK
    end
    object RzBitBtnCancel: TRzBitBtn
      Left = 184
      Top = 128
      TabOrder = 3
      OnClick = RzBitBtnCancelClick
      Kind = bkCancel
    end
  end
end

object BestFiveForm: TBestFiveForm
  Left = 703
  Top = 382
  BorderStyle = bsDialog
  Caption = 'Best Five'
  ClientHeight = 249
  ClientWidth = 197
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
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object RzRadioGroupBest5: TRzRadioGroup
    Left = 0
    Top = 57
    Width = 197
    Align = alTop
    Caption = 'Best Five Type Choose'
    Color = clGradientActiveCaption
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    GroupStyle = gsBanner
    ItemIndex = 1
    Items.Strings = (
      'Abs_DTA'
      'Abs_Gamma'
      'Rel_DTA'
      'Rel_Gamma')
    ParentFont = False
    TabOrder = 0
  end
  object RzMemoWords: TRzMemo
    Left = 0
    Top = 0
    Width = 197
    Height = 57
    Align = alTop
    BevelInner = bvNone
    BevelOuter = bvNone
    BorderStyle = bsNone
    Enabled = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    Lines.Strings = (
      ''
      'Select A check type for best5 '
      'algorithm.')
    ParentFont = False
    TabOrder = 1
  end
  object RzBitBtnOK: TRzBitBtn
    Left = 8
    Top = 184
    TabOrder = 2
    OnClick = RzBitBtnOKClick
    Kind = bkOK
  end
  object RzBitBtnClose: TRzBitBtn
    Left = 112
    Top = 184
    Caption = 'Close'
    TabOrder = 3
    OnClick = RzBitBtnCloseClick
    Kind = bkCancel
  end
end

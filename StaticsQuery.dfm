object FormStaticQuery: TFormStaticQuery
  Left = 663
  Top = 325
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'StaticQuery'
  ClientHeight = 243
  ClientWidth = 324
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
  object RzPanelStaticQuery: TRzPanel
    Left = 0
    Top = 0
    Width = 324
    Height = 243
    Align = alClient
    Color = clMoneyGreen
    TabOrder = 0
    object RzLabelStaticChoose: TRzLabel
      Left = 32
      Top = 24
      Width = 268
      Height = 15
      Caption = 'Please choose a type for statics analysis and show'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzRadioGroupStaticsType: TRzRadioGroup
      Left = 48
      Top = 56
      Width = 233
      Alignment = taCenter
      Caption = 'Static Type'
      Color = clGradientActiveCaption
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      GroupStyle = gsBanner
      Items.Strings = (
        'Measurement dose distribution'
        'Calculate dose distribution'
        'Analysis result distribution')
      ParentFont = False
      TabOrder = 0
    end
    object RzBitBtnOK: TRzBitBtn
      Left = 40
      Top = 184
      TabOrder = 1
      OnClick = RzBitBtnOKClick
      Kind = bkOK
    end
    object RzBitBtnCancel: TRzBitBtn
      Left = 208
      Top = 184
      TabOrder = 2
      OnClick = RzBitBtnCancelClick
      Kind = bkCancel
    end
  end
end

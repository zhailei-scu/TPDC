object ModelSettingForm: TModelSettingForm
  Left = 515
  Top = 232
  BorderStyle = bsDialog
  Caption = 'Special Model Option'
  ClientHeight = 294
  ClientWidth = 482
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
  object RzPanelNormValue: TRzPanel
    Left = 0
    Top = 0
    Width = 482
    Height = 294
    Align = alClient
    BorderOuter = fsNone
    Color = clHighlight
    TabOrder = 0
    VisualStyle = vsClassic
    object RzSeparator: TRzSeparator
      Left = -87
      Top = 216
      Width = 689
      Height = 9
      ShowGradient = True
      Color = clLime
      ParentColor = False
    end
    object RzBitBtnOK: TRzBitBtn
      Left = 104
      Top = 248
      HotTrack = True
      TabOrder = 0
      OnClick = RzBitBtnOKClick
      Kind = bkOK
    end
    object RzBitBtnCancel: TRzBitBtn
      Left = 296
      Top = 248
      TabOrder = 1
      OnClick = RzBitBtnCancelClick
      Kind = bkCancel
    end
    object RzMemoInfo: TRzMemo
      Left = 48
      Top = 40
      Width = 393
      Height = 41
      Color = clMoneyGreen
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      Lines.Strings = (
        'Note:As some dose check software own some special data handle '
        
          'methods and steps ,so please choose the model which you want to ' +
          'use.')
      ParentFont = False
      TabOrder = 2
      FrameVisible = True
    end
    object ModelGroup: TRzRadioGroup
      Left = 144
      Top = 96
      Width = 201
      Height = 81
      Alignment = taCenter
      Caption = 'Model Setting'
      Color = clMoneyGreen
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      GroupStyle = gsBanner
      ItemHeight = 25
      Items.Strings = (
        'Model ADAC'
        'Model SNDAC')
      ParentFont = False
      TabOrder = 3
    end
  end
end

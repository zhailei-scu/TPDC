object FormSegmentsSetting: TFormSegmentsSetting
  Left = 475
  Top = 48
  BorderStyle = bsDialog
  Caption = 'Segments Setting'
  ClientHeight = 279
  ClientWidth = 442
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
  object RzPanelSegments: TRzPanel
    Left = 0
    Top = 0
    Width = 442
    Height = 279
    Align = alClient
    BorderOuter = fsNone
    Color = clMenuHighlight
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object RzLabelSegments: TRzLabel
      Left = 120
      Top = 132
      Width = 58
      Height = 15
      Caption = 'Segments:'
    end
    object RzMemoSegments: TRzMemo
      Left = 88
      Top = 40
      Width = 265
      Height = 33
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      Lines.Strings = (
        'Please Select the grid line segments number.')
      ParentFont = False
      TabOrder = 0
      FrameVisible = True
    end
    object RzSpinnerSegments: TRzSpinner
      Left = 200
      Top = 128
      Min = 1
      TabOnEnter = True
      Value = 1
      ParentColor = False
      TabOrder = 1
    end
    object RzBitBtnOK: TRzBitBtn
      Left = 96
      Top = 216
      HotTrack = True
      TabOrder = 2
      OnClick = RzBitBtnOKClick
      Kind = bkOK
    end
    object RzBitBtnClose: TRzBitBtn
      Left = 272
      Top = 216
      HotTrack = True
      TabOrder = 3
      OnClick = RzBitBtnCloseClick
      Kind = bkCancel
    end
    object Recommendatory: TRzCheckBox
      Left = 112
      Top = 176
      Width = 257
      Height = 17
      Caption = 'Use the recommendatory segments value'
      State = cbUnchecked
      TabOrder = 4
      OnClick = RecommendatoryClick
    end
  end
end

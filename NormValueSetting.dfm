object NormValueSetForm: TNormValueSetForm
  Left = 366
  Top = 185
  BorderStyle = bsDialog
  Caption = 'Set Normlization Value'
  ClientHeight = 414
  ClientWidth = 586
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Times New Roman'
  Font.Style = [fsBold]
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDesktopCenter
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 15
  object RzPanelNormValue: TRzPanel
    Left = 0
    Top = 0
    Width = 586
    Height = 414
    Align = alClient
    BorderOuter = fsNone
    Color = clHighlight
    TabOrder = 0
    VisualStyle = vsClassic
    object RzSeparatorNormValue: TRzSeparator
      Left = 0
      Top = 152
      Width = 689
      Height = 9
      ShowGradient = True
      Color = clLime
      ParentColor = False
    end
    object RzSeparator2: TRzSeparator
      Left = -95
      Top = 304
      Width = 689
      Height = 9
      ShowGradient = True
      Color = clLime
      ParentColor = False
    end
    object RzCheckBoxMeasure: TRzCheckBox
      Left = 16
      Top = 24
      Width = 265
      Height = 17
      Caption = 'Specialize the Measure Normlization value'
      State = cbUnchecked
      TabOrder = 0
      OnMouseDown = RzCheckBoxMeasureMouseDown
    end
    object RzCheckBoxCalculate: TRzCheckBox
      Left = 16
      Top = 192
      Width = 273
      Height = 17
      Caption = 'Specialize the Calculate Normlization value'
      State = cbUnchecked
      TabOrder = 1
      OnMouseDown = RzCheckBoxCalculateMouseDown
    end
    object MeasureNormValueSetting: TRzRadioGroup
      Left = 296
      Top = 24
      Width = 273
      Height = 81
      Alignment = taCenter
      Caption = 'Measure Normlization Value Setting'
      Color = clMoneyGreen
      Enabled = False
      GroupStyle = gsBanner
      ItemHotTrack = True
      ItemIndex = 0
      Items.Strings = (
        'Actual Dose(cGy)'
        'Norm Dose(%)')
      TabOrder = 2
      OnChanging = MeasureNormValueSettingChanging
      object RzLabelMeasure: TRzLabel
        Left = 216
        Top = 37
        Width = 21
        Height = 15
        Caption = 'cGy'
        Enabled = False
      end
      object EditMeasureNormValue: TRzNumericEdit
        Left = 136
        Top = 32
        Width = 73
        Height = 23
        Enabled = False
        FrameVisible = True
        TabOrder = 0
        IntegersOnly = False
        DisplayFormat = '0.000'
      end
    end
    object RzBitBtnOK: TRzBitBtn
      Left = 120
      Top = 360
      HotTrack = True
      TabOrder = 3
      OnClick = RzBitBtnOKClick
      Kind = bkOK
    end
    object RzBitBtnCancel: TRzBitBtn
      Left = 352
      Top = 360
      TabOrder = 4
      OnClick = RzBitBtnCancelClick
      Kind = bkCancel
    end
    object CalcNormValueSetting: TRzRadioGroup
      Left = 296
      Top = 192
      Width = 273
      Height = 81
      Alignment = taCenter
      Caption = 'Calculate Normlization Value Setting'
      Color = clMoneyGreen
      Enabled = False
      GroupStyle = gsBanner
      ItemHotTrack = True
      ItemIndex = 0
      Items.Strings = (
        'Actual Dose(cGy)'
        'Norm Dose(%)')
      TabOrder = 5
      OnChanging = CalcNormValueSettingChanging
      object RzLabelCalc: TRzLabel
        Left = 216
        Top = 37
        Width = 21
        Height = 15
        Caption = 'cGy'
        Enabled = False
      end
      object EditCalculateNormValue: TRzNumericEdit
        Left = 136
        Top = 32
        Width = 73
        Height = 23
        Enabled = False
        FrameVisible = True
        TabOrder = 0
        IntegersOnly = False
        DisplayFormat = '0.000'
      end
    end
  end
end

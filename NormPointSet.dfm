object FormNormPointSet: TFormNormPointSet
  Left = 467
  Top = 236
  Width = 462
  Height = 508
  Caption = 'Normlize Point Setting'
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
  object RzPanelNormPoint: TRzPanel
    Left = 0
    Top = 0
    Width = 446
    Height = 470
    Align = alClient
    Color = clActiveCaption
    TabOrder = 0
    object RzLabelCaption: TRzLabel
      Left = 112
      Top = 8
      Width = 181
      Height = 15
      Caption = 'Please set the normlization point.'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzBitBtnOK: TRzBitBtn
      Left = 104
      Top = 424
      ModalResult = 1
      Caption = 'OK'
      HotTrack = True
      TabOrder = 0
      OnClick = RzBitBtnOKClick
      Glyph.Data = {
        36060000424D3606000000000000360400002800000020000000100000000100
        08000000000000020000630B0000630B00000001000000000000000000003300
        00006600000099000000CC000000FF0000000033000033330000663300009933
        0000CC330000FF33000000660000336600006666000099660000CC660000FF66
        000000990000339900006699000099990000CC990000FF99000000CC000033CC
        000066CC000099CC0000CCCC0000FFCC000000FF000033FF000066FF000099FF
        0000CCFF0000FFFF000000003300330033006600330099003300CC003300FF00
        330000333300333333006633330099333300CC333300FF333300006633003366
        33006666330099663300CC663300FF6633000099330033993300669933009999
        3300CC993300FF99330000CC330033CC330066CC330099CC3300CCCC3300FFCC
        330000FF330033FF330066FF330099FF3300CCFF3300FFFF3300000066003300
        66006600660099006600CC006600FF0066000033660033336600663366009933
        6600CC336600FF33660000666600336666006666660099666600CC666600FF66
        660000996600339966006699660099996600CC996600FF99660000CC660033CC
        660066CC660099CC6600CCCC6600FFCC660000FF660033FF660066FF660099FF
        6600CCFF6600FFFF660000009900330099006600990099009900CC009900FF00
        990000339900333399006633990099339900CC339900FF339900006699003366
        99006666990099669900CC669900FF6699000099990033999900669999009999
        9900CC999900FF99990000CC990033CC990066CC990099CC9900CCCC9900FFCC
        990000FF990033FF990066FF990099FF9900CCFF9900FFFF99000000CC003300
        CC006600CC009900CC00CC00CC00FF00CC000033CC003333CC006633CC009933
        CC00CC33CC00FF33CC000066CC003366CC006666CC009966CC00CC66CC00FF66
        CC000099CC003399CC006699CC009999CC00CC99CC00FF99CC0000CCCC0033CC
        CC0066CCCC0099CCCC00CCCCCC00FFCCCC0000FFCC0033FFCC0066FFCC0099FF
        CC00CCFFCC00FFFFCC000000FF003300FF006600FF009900FF00CC00FF00FF00
        FF000033FF003333FF006633FF009933FF00CC33FF00FF33FF000066FF003366
        FF006666FF009966FF00CC66FF00FF66FF000099FF003399FF006699FF009999
        FF00CC99FF00FF99FF0000CCFF0033CCFF0066CCFF0099CCFF00CCCCFF00FFCC
        FF0000FFFF0033FFFF0066FFFF0099FFFF00CCFFFF00FFFFFF00000080000080
        000000808000800000008000800080800000C0C0C00080808000191919004C4C
        4C00B2B2B200E5E5E500C8AC2800E0CC6600F2EABF00B59B2400D8E9EC009933
        6600D075A300ECC6D900646F710099A8AC00E2EFF10000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000E8E8E8E8E8E8
        E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8
        E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8180C
        E8E8E8E8E8E8E8E8E8E8E8E8E8E8E2DFE8E8E8E8E8E8E8E8E8E8E8E8E8181212
        0CE8E8E8E8E8E8E8E8E8E8E8E8E28181DFE8E8E8E8E8E8E8E8E8E8E818121212
        120CE8E8E8E8E8E8E8E8E8E8E281818181DFE8E8E8E8E8E8E8E8E81812121212
        12120CE8E8E8E8E8E8E8E8E2818181818181DFE8E8E8E8E8E8E8E81812120C18
        1212120CE8E8E8E8E8E8E8E28181DFE2818181DFE8E8E8E8E8E8E818120CE8E8
        181212120CE8E8E8E8E8E8E281DFE8E8E2818181DFE8E8E8E8E8E8180CE8E8E8
        E8181212120CE8E8E8E8E8E2DFE8E8E8E8E2818181DFE8E8E8E8E8E8E8E8E8E8
        E8E8181212120CE8E8E8E8E8E8E8E8E8E8E8E2818181DFE8E8E8E8E8E8E8E8E8
        E8E8E8181212120CE8E8E8E8E8E8E8E8E8E8E8E2818181DFE8E8E8E8E8E8E8E8
        E8E8E8E81812120CE8E8E8E8E8E8E8E8E8E8E8E8E28181DFE8E8E8E8E8E8E8E8
        E8E8E8E8E818120CE8E8E8E8E8E8E8E8E8E8E8E8E8E281DFE8E8E8E8E8E8E8E8
        E8E8E8E8E8E8180CE8E8E8E8E8E8E8E8E8E8E8E8E8E8E2DFE8E8E8E8E8E8E8E8
        E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8
        E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8E8}
      NumGlyphs = 2
    end
    object RzBitBtnCancel: TRzBitBtn
      Left = 248
      Top = 424
      HotTrack = True
      TabOrder = 1
      OnClick = RzBitBtnCancelClick
      Kind = bkCancel
    end
    object RzGroupBoxGridLine: TRzGroupBox
      Left = 82
      Top = 66
      Width = 255
      Height = 111
      Align = alCustom
      Alignment = taCenter
      Caption = 'Using the gird lines number'
      Color = clMoneyGreen
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      GroupStyle = gsBanner
      ParentFont = False
      TabOrder = 2
      object RzLabelGridLineY: TRzLabel
        Left = 144
        Top = 24
        Width = 41
        Height = 15
        Caption = 'Y(line):'
        Enabled = False
      end
      object RzLabelGridLineX: TRzLabel
        Left = 40
        Top = 24
        Width = 42
        Height = 15
        Caption = 'X(line):'
        Enabled = False
      end
      object RzCheckBoxGridLineCenter: TRzCheckBox
        Left = 64
        Top = 80
        Width = 113
        Height = 17
        Caption = 'Graphy Center'
        Enabled = False
        State = cbUnchecked
        TabOrder = 0
        OnClick = RzCheckBoxGridLineCenterClick
      end
      object RzSpinEditGridLineY: TRzSpinEdit
        Left = 137
        Top = 44
        Width = 63
        Height = 23
        Cursor = crIBeam
        BlankValue = 3
        AllowKeyEdit = True
        Max = 1000
        Min = -1000
        Enabled = False
        FlatButtons = True
        FrameVisible = True
        HideSelection = False
        TabOnEnter = True
        TabOrder = 1
      end
      object RzSpinEditGridLineX: TRzSpinEdit
        Left = 32
        Top = 44
        Width = 63
        Height = 23
        AllowKeyEdit = True
        Max = 1000
        Min = -1000
        Enabled = False
        FlatButtons = True
        FrameVisible = True
        HideSelection = False
        TabOnEnter = True
        TabOrder = 2
      end
    end
    object RzGroupBoxPos: TRzGroupBox
      Left = 82
      Top = 210
      Width = 255
      Height = 111
      Align = alCustom
      Alignment = taCenter
      Caption = 'Using physical position'
      Color = clMoneyGreen
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      GroupStyle = gsBanner
      ParentFont = False
      TabOrder = 3
      object RzLabelPosY: TRzLabel
        Left = 152
        Top = 32
        Width = 40
        Height = 15
        Caption = 'Y(mm):'
      end
      object RzLabelPosX: TRzLabel
        Left = 48
        Top = 32
        Width = 41
        Height = 15
        Caption = 'X(mm):'
      end
      object RzSpinEditPosX: TRzSpinEdit
        Left = 24
        Top = 52
        Width = 79
        Height = 23
        AllowKeyEdit = True
        Decimals = 3
        IntegersOnly = False
        Max = 1000
        Min = -1000
        FlatButtons = True
        FrameVisible = True
        TabOnEnter = True
        TabOrder = 0
      end
      object RzSpinEditPosY: TRzSpinEdit
        Left = 129
        Top = 52
        Width = 79
        Height = 23
        BlankValue = 3
        AllowKeyEdit = True
        Decimals = 3
        IntegersOnly = False
        Max = 1000
        Min = -1000
        FlatButtons = True
        FrameVisible = True
        TabOnEnter = True
        TabOrder = 1
      end
      object RzCheckBoxPosCenter: TRzCheckBox
        Left = 63
        Top = 88
        Width = 137
        Height = 17
        Caption = 'Graphy Center'
        State = cbUnchecked
        TabOrder = 2
        OnClick = RzCheckBoxPosCenterClick
      end
    end
    object UseGridLineNum: TRzRadioButton
      Left = 136
      Top = 48
      Width = 145
      Height = 17
      Caption = 'Use gridline number'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = UseGridLineNumClick
    end
    object UsePhysicalPos: TRzRadioButton
      Left = 136
      Top = 192
      Width = 137
      Height = 17
      Caption = 'Use physical position'
      Checked = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      TabStop = True
      OnClick = UsePhysicalPosClick
    end
    object RzGroupBoxOtherSetting: TRzGroupBox
      Left = 82
      Top = 346
      Width = 255
      Height = 47
      Align = alCustom
      Alignment = taCenter
      Color = clMoneyGreen
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      GroupStyle = gsBanner
      ParentFont = False
      TabOrder = 6
      object RzCheckBoxOmniProModel: TRzCheckBox
        Left = 23
        Top = 16
        Width = 226
        Height = 17
        Caption = 'Match omniPro Normlization model'
        State = cbUnchecked
        TabOrder = 0
        OnClick = RzCheckBoxPosCenterClick
      end
    end
  end
end

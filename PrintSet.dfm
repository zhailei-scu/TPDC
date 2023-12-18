object PrintForm: TPrintForm
  Left = 225
  Top = 103
  Width = 1237
  Height = 722
  VertScrollBar.Position = 447
  Caption = 'PrintForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Scaled = False
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object QuickRep1: TQuickRep
    Left = 0
    Top = -439
    Width = 794
    Height = 1123
    Frame.Color = clBlack
    Frame.DrawTop = False
    Frame.DrawBottom = False
    Frame.DrawLeft = False
    Frame.DrawRight = False
    AfterPreview = QuickRep1AfterPreview
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    Functions.Strings = (
      'PAGENUMBER'
      'COLUMNNUMBER'
      'REPORTTITLE'
      'QRSTRINGSBAND1')
    Functions.DATA = (
      '0'
      '0'
      #39#39
      #39#39)
    Options = [FirstPageHeader, LastPageFooter]
    Page.Columns = 1
    Page.Orientation = poPortrait
    Page.PaperSize = A4
    Page.Values = (
      100
      2970
      100
      2100
      100
      100
      0)
    PrinterSettings.Copies = 1
    PrinterSettings.Duplex = False
    PrinterSettings.FirstPage = 0
    PrinterSettings.LastPage = 0
    PrinterSettings.OutputBin = Auto
    PrintIfEmpty = True
    SnapToGrid = True
    Units = MM
    Zoom = 100
    object QRBand1: TQRBand
      Left = 38
      Top = 38
      Width = 718
      Height = 35
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clWhite
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        92.6041666666667
        1899.70833333333)
      BandType = rbTitle
      object QRLabel1: TQRLabel
        Left = 280
        Top = 7
        Width = 153
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          740.833333333333
          18.5208333333333
          404.8125)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'TPDC Print Informtion'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
    end
    object QRBand3: TQRBand
      Left = 38
      Top = 73
      Width = 718
      Height = 992
      Frame.Color = clBlack
      Frame.DrawTop = False
      Frame.DrawBottom = False
      Frame.DrawLeft = False
      Frame.DrawRight = False
      AlignToBottom = False
      Color = clWhite
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        2624.66666666667
        1899.70833333333)
      BandType = rbPageFooter
      object QRShape1: TQRShape
        Left = 0
        Top = 40
        Width = 169
        Height = 9
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          23.8125
          0
          105.833333333333
          447.145833333333)
        Brush.Color = clBlack
        Shape = qrsRectangle
      end
      object QRLabel2: TQRLabel
        Left = 8
        Top = 16
        Width = 80
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          42.3333333333333
          211.666666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'PatientInfo:'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object QRShape2: TQRShape
        Left = -16
        Top = 224
        Width = 729
        Height = 9
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          23.8125
          -42.3333333333333
          592.666666666667
          1928.8125)
        Brush.Color = clBlack
        Shape = qrsRectangle
      end
      object QRLabel3: TQRLabel
        Left = 8
        Top = 240
        Width = 92
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          635
          243.416666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Check Result'
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object QRShape3: TQRShape
        Left = 0
        Top = 264
        Width = 169
        Height = 9
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          23.8125
          0
          698.5
          447.145833333333)
        Brush.Color = clBlack
        Shape = qrsRectangle
      end
      object QRLabelName: TQRLabel
        Left = 8
        Top = 56
        Width = 58
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          148.166666666667
          153.458333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Name'#65306
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object QRLabelAge: TQRLabel
        Left = 8
        Top = 120
        Width = 45
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          317.5
          119.0625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Age'#65306
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object QRLabelId: TQRLabel
        Left = 8
        Top = 152
        Width = 36
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          402.166666666667
          95.25)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'ID'#65306
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object QRLabelPart: TQRLabel
        Left = 8
        Top = 184
        Width = 46
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          486.833333333333
          121.708333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Part'#65306
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object QRLabelDD: TQRLabel
        Left = 8
        Top = 280
        Width = 58
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          740.833333333333
          153.458333333333)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = '%DD'#65306
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object QRLabelDTA: TQRLabel
        Left = 8
        Top = 312
        Width = 66
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          825.5
          174.625)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = '%DTA'#65306
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object QRLabelGAMMA: TQRLabel
        Left = 8
        Top = 344
        Width = 84
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          910.166666666667
          222.25)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = '%GAMA'#65306
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object QRLabelGender: TQRLabel
        Left = 8
        Top = 88
        Width = 68
        Height = 20
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          52.9166666666667
          21.1666666666667
          232.833333333333
          179.916666666667)
        Alignment = taLeftJustify
        AlignToBand = False
        AutoSize = True
        AutoStretch = False
        Caption = 'Gender'#65306
        Color = clWhite
        Transparent = False
        WordWrap = True
        FontSize = 12
      end
      object QRShape4: TQRShape
        Left = -32
        Top = 376
        Width = 729
        Height = 9
        Frame.Color = clBlack
        Frame.DrawTop = False
        Frame.DrawBottom = False
        Frame.DrawLeft = False
        Frame.DrawRight = False
        Size.Values = (
          23.8125
          -84.6666666666667
          994.833333333333
          1928.8125)
        Brush.Color = clBlack
        Shape = qrsRectangle
      end
      object QRChartMeasureContour: TQRChart
        Left = 24
        Top = 432
        Width = 353
        Height = 233
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          616.479166666667
          63.5
          1143
          933.979166666667)
        object QRDBChartMesureContour: TQRDBChart
          Left = -1
          Top = -1
          Width = 1
          Height = 1
          Title.Text.Strings = (
            'TQRChart')
          Title.Visible = False
          AxisVisible = False
          Chart3DPercent = 100
          LeftAxis.Automatic = False
          LeftAxis.AutomaticMaximum = False
          LeftAxis.AutomaticMinimum = False
          LeftAxis.Visible = False
          Legend.LeftPercent = 90
          Legend.LegendStyle = lsValues
          Legend.PositionUnits = muPercent
          Legend.Shadow.Visible = False
          Legend.TopPos = 5
          View3DOptions.Elevation = 270
          View3DOptions.Orthogonal = False
          View3DOptions.Rotation = 0
          View3DWalls = False
          PrintMargins = (
            15
            21
            15
            21)
          ColorPaletteIndex = 13
          object SeriesPrintMeasureContour: TContourSeries
            AutomaticLevels = False
            Marks.Arrow.Visible = True
            Marks.Callout.Brush.Color = clBlack
            Marks.Callout.Arrow.Visible = True
            Marks.Transparent = True
            Marks.Visible = False
            Levels = <
              item
                Color = clBlack
                UpToValue = 10
              end
              item
                Color = clMaroon
                Pen.Color = clMaroon
                UpToValue = 20
              end
              item
                Color = clGreen
                Pen.Color = clGreen
                UpToValue = 30
              end
              item
                Color = clOlive
                Pen.Color = clOlive
                UpToValue = 40
              end
              item
                Color = clNavy
                Pen.Color = clNavy
                UpToValue = 50
              end
              item
                Color = clTeal
                Pen.Color = clTeal
                UpToValue = 60
              end
              item
                Color = clGray
                Pen.Color = clGray
                UpToValue = 70
              end
              item
                Color = clRed
                Pen.Color = clRed
                UpToValue = 80
              end
              item
                Color = clLime
                Pen.Color = clLime
                UpToValue = 90
              end
              item
                Color = clYellow
                Pen.Color = clYellow
                UpToValue = 100
              end>
            Pointer.HorizSize = 2
            Pointer.InflateMargins = True
            Pointer.Pen.Visible = False
            Pointer.Style = psRectangle
            Pointer.VertSize = 2
            Pointer.Visible = False
            XValues.Name = 'X'
            XValues.Order = loNone
            YPosition = 0.189598284286995
            YPositionLevel = True
            YValues.Name = 'Y'
            YValues.Order = loNone
            ZValues.Name = 'Z'
            ZValues.Order = loNone
            Brush.Color = clWhite
            Brush.Style = bsClear
          end
        end
      end
      object QRChartPrintMeasureHotPoint: TQRChart
        Left = 400
        Top = 432
        Width = 241
        Height = 233
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          616.479166666667
          1058.33333333333
          1143
          637.645833333333)
        object QRDBChartPrintMeasureHotPoint: TQRDBChart
          Left = -1
          Top = -1
          Width = 1
          Height = 1
          Title.Text.Strings = (
            'TQRChart')
          Title.Visible = False
          AxisVisible = False
          Chart3DPercent = 100
          LeftAxis.Automatic = False
          LeftAxis.AutomaticMaximum = False
          LeftAxis.AutomaticMinimum = False
          Legend.Visible = False
          View3DOptions.Elevation = 270
          View3DOptions.Orthogonal = False
          View3DOptions.Rotation = 0
          View3DWalls = False
          ColorPaletteIndex = 13
          object SeriesPrintMeasureHotPoint: TIsoSurfaceSeries
            Marks.Arrow.Visible = True
            Marks.Callout.Brush.Color = clBlack
            Marks.Callout.Arrow.Visible = True
            Marks.Brush.Color = clWhite
            Marks.Brush.Style = bsClear
            Marks.Frame.Visible = False
            Marks.Visible = False
            ShowInLegend = False
            Brush.Color = clWhite
            Pen.Visible = False
            SideBrush.Color = clWhite
            SideBrush.Style = bsClear
            XValues.Name = 'X'
            XValues.Order = loNone
            YValues.Name = 'Y'
            YValues.Order = loNone
            ZValues.Name = 'Z'
            ZValues.Order = loNone
            BandPen.Visible = False
            Sides.Brush.Color = clWhite
            Sides.Brush.Style = bsClear
          end
        end
      end
      object QRChartPrintCalcHotPoint: TQRChart
        Left = 399
        Top = 680
        Width = 242
        Height = 233
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          616
          1055.6875
          1799.16666666667
          640.291666666667)
        object QRDBChartPrintCalcHotPoint: TQRDBChart
          Left = -1
          Top = -1
          Width = 1
          Height = 1
          Title.Text.Strings = (
            'TQRChart')
          Title.Visible = False
          AxisVisible = False
          Chart3DPercent = 100
          LeftAxis.Automatic = False
          LeftAxis.AutomaticMaximum = False
          LeftAxis.AutomaticMinimum = False
          Legend.Visible = False
          View3DOptions.Elevation = 270
          View3DOptions.Orthogonal = False
          View3DOptions.Rotation = 0
          View3DWalls = False
          ColorPaletteIndex = 13
          object SeriesPrintCalcHotPoint: TIsoSurfaceSeries
            Marks.Arrow.Visible = True
            Marks.Callout.Brush.Color = clBlack
            Marks.Callout.Arrow.Visible = True
            Marks.Visible = False
            Pen.Visible = False
            SideBrush.Color = clWhite
            SideBrush.Style = bsClear
            XValues.Name = 'X'
            XValues.Order = loNone
            YValues.Name = 'Y'
            YValues.Order = loNone
            ZValues.Name = 'Z'
            ZValues.Order = loNone
            BandPen.Visible = False
            Sides.Brush.Color = clWhite
            Sides.Brush.Style = bsClear
          end
        end
      end
      object QRChartCalcContour: TQRChart
        Left = 24
        Top = 680
        Width = 353
        Height = 233
        Frame.Color = clBlack
        Frame.DrawTop = True
        Frame.DrawBottom = True
        Frame.DrawLeft = True
        Frame.DrawRight = True
        Size.Values = (
          616.479166666667
          63.5
          1799.16666666667
          933.979166666667)
        object QRDBChartCalcContour: TQRDBChart
          Left = -1
          Top = -1
          Width = 1
          Height = 1
          Title.Text.Strings = (
            'TQRChart')
          Title.Visible = False
          AxisVisible = False
          Chart3DPercent = 100
          LeftAxis.Automatic = False
          LeftAxis.AutomaticMaximum = False
          LeftAxis.AutomaticMinimum = False
          LeftAxis.Visible = False
          Legend.LeftPercent = 90
          Legend.LegendStyle = lsValues
          Legend.PositionUnits = muPercent
          Legend.Shadow.Visible = False
          Legend.TopPos = 5
          View3DOptions.Elevation = 270
          View3DOptions.Orthogonal = False
          View3DOptions.Rotation = 0
          View3DWalls = False
          PrintMargins = (
            15
            21
            15
            21)
          ColorPaletteIndex = 13
          object SeriesPrintCalcContour: TContourSeries
            AutomaticLevels = False
            Marks.Arrow.Visible = True
            Marks.Callout.Brush.Color = clBlack
            Marks.Callout.Arrow.Visible = True
            Marks.Transparent = True
            Marks.Visible = False
            Levels = <
              item
                Color = clBlack
                UpToValue = 10
              end
              item
                Color = clMaroon
                Pen.Color = clMaroon
                UpToValue = 20
              end
              item
                Color = clGreen
                Pen.Color = clGreen
                UpToValue = 30
              end
              item
                Color = clOlive
                Pen.Color = clOlive
                UpToValue = 40
              end
              item
                Color = clNavy
                Pen.Color = clNavy
                UpToValue = 50
              end
              item
                Color = clTeal
                Pen.Color = clTeal
                UpToValue = 60
              end
              item
                Color = clGray
                Pen.Color = clGray
                UpToValue = 70
              end
              item
                Color = clRed
                Pen.Color = clRed
                UpToValue = 80
              end
              item
                Color = clLime
                Pen.Color = clLime
                UpToValue = 90
              end
              item
                Color = clYellow
                Pen.Color = clYellow
                UpToValue = 100
              end>
            Pointer.HorizSize = 2
            Pointer.InflateMargins = True
            Pointer.Pen.Visible = False
            Pointer.Style = psRectangle
            Pointer.VertSize = 2
            Pointer.Visible = False
            XValues.Name = 'X'
            XValues.Order = loNone
            YPosition = 0.189598284286995
            YPositionLevel = True
            YValues.Name = 'Y'
            YValues.Order = loNone
            ZValues.Name = 'Z'
            ZValues.Order = loNone
            Brush.Color = clWhite
            Brush.Style = bsClear
          end
        end
      end
    end
  end
end

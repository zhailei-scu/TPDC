//---------------------------------------------------------------------------

#ifndef PrintSetH
#define PrintSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
#include "TeeSurfa.hpp"
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <QRExport.hpp>
#include <DBChart.hpp>
#include <QrTee.hpp>
#include "RzPanel.hpp"
#include "RzSplit.hpp"
//---------------------------------------------------------------------------
class TPrintForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *QuickRep1;
        TQRLabel *QRLabel1;
        TQRBand *QRBand1;
        TQRBand *QRBand3;
        TQRShape *QRShape1;
        TQRLabel *QRLabel2;
        TQRShape *QRShape2;
        TQRLabel *QRLabel3;
        TQRShape *QRShape3;
        TQRLabel *QRLabelName;
        TQRLabel *QRLabelAge;
        TQRLabel *QRLabelId;
        TQRLabel *QRLabelPart;
        TQRLabel *QRLabelDD;
        TQRLabel *QRLabelDTA;
        TQRLabel *QRLabelGAMMA;
        TQRLabel *QRLabelGender;
        TQRShape *QRShape4;
        TQRChart *QRChartMeasureContour;
        TQRDBChart *QRDBChartMesureContour;
        TContourSeries *SeriesPrintMeasureContour;
        TQRChart *QRChartPrintMeasureHotPoint;
        TQRDBChart *QRDBChartPrintMeasureHotPoint;
        TIsoSurfaceSeries *SeriesPrintMeasureHotPoint;
        TQRChart *QRChartPrintCalcHotPoint;
        TQRDBChart *QRDBChartPrintCalcHotPoint;
        TIsoSurfaceSeries *SeriesPrintCalcHotPoint;
        TQRChart *QRChartCalcContour;
        TQRDBChart *QRDBChartCalcContour;
        TContourSeries *SeriesPrintCalcContour;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall QuickRep1AfterPreview(TObject *Sender);
        void __fastcall ShowMeasureGraphy();
        void __fastcall ShowCalcGraphy();

private:	// User declarations
public:		// User declarations
        __fastcall TPrintForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrintForm *PrintForm;
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#pragma once

#ifndef doseshellH
#define doseshellH

//---------------------------------------------------------------------------
#define MainFormTempValue FormMain->temporaryValues

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "TeeSurfa.hpp"
#include "TeePageNumTool.hpp"
#include "TeeTools.hpp"
#include "TeeChartGrid.hpp"
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "TeeEdit.hpp"
#include "TeeTransposeTool.hpp"
#include "TeeDragPoint.hpp"
#include "TeeGanttTool.hpp"
#include "TeeSeriesRegion.hpp"
#include "TeeFibonacci.hpp"
#include "TeeSurfaceTool.hpp"
#include "TeeComma.hpp"
#include "TeeOpenGL.hpp"
#include <Series.hpp>
#include "TeeSubChart.hpp"
#include "TeeHistogram.hpp"
#include <TeeFunci.hpp>
#include "CurvFitt.hpp"
#include "TeePoin3.hpp"
#include <AppEvnts.hpp>
#include "TeeSpline.hpp"
#include <Buttons.hpp>
#include <Tabs.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzListVw.hpp"
#include "RzGroupBar.hpp"
#include "RzTray.hpp"
#include "RzPathBar.hpp"
#include "RzShellDialogs.hpp"
#include "RzTabs.hpp"
#include "StatChar.hpp"
#include "RzBHints.hpp"
#include "RzTreeVw.hpp"
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
//-----------------------------------------------
#include "dose.h"
#include "Paramter.h"
#include "BestFive.h"
#include "Util.h"
#include "ShowBestFiveResult.h"
#include "Info.h"
#include "Paramter.h"
#include "DTAWayChoose.h"
#include "RzCommon.hpp"
#include "RzSelDir.hpp"

#include <deque>

using namespace std;
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
  TPanel *PanelMeasure;
  TOpenDialog *OpenDialogCalculate;
  TMainMenu *MainMenu1;
        TPopupMenu *PopupMenuMeasure;
  TMenuItem *File;
  TMenuItem *Open_Measure;
  TPanel *PanelCalculate;
        TPopupMenu *PopupMenuCalculate;
        TTeeOpenGL *TeeOpenGLMeasure;
        TTeeOpenGL *TeeOpenGLCalculate;
        TStringGrid *StringGridMeasure;
        TStringGrid *StringGridCalculate;
  TMenuItem *OptionsSet;
  TMenuItem *standset;
  TMenuItem *ToolBar_Open_Measure;
  TMenuItem *ToolBar_Open_Plan;
  TMenuItem *Help1;
  TImageList *ImageList1;
  TChart *ChartCalculate;
  TContourSeries *SeriesB;
  TPoint3DSeries *SeriesBx;
  TPoint3DSeries *SeriesBy;
  TPoint3DSeries *SeriesBm;
  TSurfaceSeries *SeriesBSolid;
  TRotateTool *RotateTool2;
        TMenuItem *setMesureheight;
  TMenuItem *Open_Plan;
  TMenuItem *N1;
  TMenuItem *OpenZCdose;
        TMenuItem *OpenMatrixDose;
        TChart *ChartMeasure;
  TContourSeries *SeriesA;
  TPoint3DSeries *SeriesAx;
  TPoint3DSeries *SeriesAy;
  TPoint3DSeries *SeriesAm;
  TSurfaceSeries *SeriesASolid;
  TRotateTool *RotateTool1;
  TMenuItem *Save2;
  TMenuItem *PrintSet;
  TPanel *PanelShowAndOperation;
  TComboBox *ComboBoxGraph;
  TComboBox *ComboBoxData;
        TCheckBox *CheckBoxDTA_Abs;
        TCheckBox *CheckBoxGamma_Abs;
        TCheckBox *CheckBoxDD_Abs;
        TPanel *PanelStatus;
  TProgressBar *ProgressBar1;
  TStatusBar *StatusBar1;
        TLabel *LabelThreshold;
        TLabel *LabelDoseGap;
        TLabel *LabelDistance;
  TMenuItem *OpenMapCHECKdose;
  TMenuItem *Open_Plan_DICOM;
  TMenuItem *Open_Plan_SCU;
  TMenuItem *ToolBar_OpenZCdose;
  TMenuItem *ToolBar_OpenMapCHECKdose;
        TMenuItem *ToolBar_OpenMatrixDose;
  TMenuItem *ToolBar_Open_Plan_DICOM;
  TMenuItem *ToolBar_Open_Plan_SCU;
  TMenuItem *User1;
        TMenuItem *SaveToFile;
  TRzToolbar *RzToolbar1;
  TRzSpacer *RzSpacer2;
  TRzToolButton *RzToolButtonSave;
  TRzSpacer *RzSpacer3;
  TRzToolButton *RzToolButtonSystemSet;
  TRzSpacer *RzSpacer4;
  TRzToolButton *RzToolButtonPrint;
  TRzSpacer *RzSpacer5;
  TRzToolButton *RzToolButtonAbout;
  TRzSpacer *RzSpacer6;
  TRzToolButton *RzToolButtonExist;
  TRzSpacer *RzSpacer7;
        TRzToolButton *RzToolButtonNormPointSetting;
  TRzSpacer *RzSpacer8;
        TRzToolButton *RzToolButtonNormValueSetting;
  TRzSpacer *RzSpacer9;
  TRzSpacer *RzSpacer10;
  TRzSpacer *RzSpacer11;
  TRzSpacer *RzSpacer12;
  TRzMenuToolbarButton *RzMenuToolbarButtonOpenMeasure;
  TRzToolButton *RzToolButtonHelp;
  TRzSpacer *RzSpacer14;
  TCoolBar *CoolBar1;
  TRzPathBar *RzFilePathBarMeasure;
  TRzPathBar *RzPathBarCalc;
  TRzTrayIcon *RzTrayIcon1;
  TMenuItem *AdvanceSet;
  TMenuItem *SmoothSet;
  TMenuItem *SystemSet;
  TOpenDialog *OpenDialogMeasure;
        TRzPanel *RzPanelOperation;
        TRzPageControl *RzPageControlOperatAndCompare;
        TRzTabSheet *TabSheetOperation;
        TRzTabSheet *Compare;
        TChart *ChartCalcHotPoint;
        TIsoSurfaceSeries *SeriesCalcHotPoint;
        TRzBalloonHints *MessageHints;
        TRzBitBtn *RzButtomCompare_Abs;
        TRzTreeView *TreeResult;
        TRzSpinEdit *EditTH;
        TRzSpinEdit *EditDoseGap;
        TRzSpinEdit *EditDistance;
        TRzGroupBox *GroupBoxTypeChange;
        TRzGroupBox *GroupBoxStandard;
        TRzMemo *MemoDynamicInfo;
        TRzTreeView *MemoPatientInfo;
        TRzSpacer *RzSpacer1;
        TRzToolButton *FlushTowDataToCache;
        TRzToolbar *PanelToolMeasure;
        TRzToolButton *SpeedButtonGridMeasure;
        TRzToolButton *SpeedButtonLevelsSetMeasure;
        TRzToolButton *SpeedButtonDetMeasure;
        TRzToolButton *SpeedButtonTransforMeasure;
        TRzToolButton *SpeedButton3DMeasure;
        TRzToolButton *ButtonFlushMeasureToCache;
        TRzToolbar *PanelToolCalculate;
        TRzToolButton *SpeedButtonGridCalculate;
        TRzToolButton *SpeedButtonLevelsSetCalculate;
        TRzToolButton *SpeedButtonDetCalculate;
        TRzToolButton *SpeedButtonTransforCalculate;
        TRzToolButton *SpeedButton3DCalculate;
        TRzToolButton *ButtonFlushCalcToCache;
        TRzSpacer *RzSpacer15;
        TRzToolButton *RzToolButtonRefreshLeftGroupBars;
        TRzGroupBar *RzGroupBarCache;
        TRzMenuToolbarButton *RzMenuToolbarButtonOpenCalculate;
        TRzSpacer *RzSpacer17;
        TRzSpacer *RzSpacer13;
        TChart *ChartMeasureHotPoint;
        TIsoSurfaceSeries *SeriesMeasureHotPoint;
        TRzPanel *RzPanelHotPoint;
        TMenuItem *Setting1;
        TMenuItem *LogSetting;
        TMenuItem *ModelSetting;
        TMenuItem *SaveToCache;
        TMenuItem *PrintCurrent;
        TMenuItem *Information;
        TMenuItem *ChangeInformation1;
        TRzMemo *RzMemoMeasureFile;
        TRzMemo *RzMemoCalculateFile;
        TRzBitBtn *SetInfoBtn;
        TRzBitBtn *ButtonBest5;
        TRzPanel *GroupBoxOther;
        TRzToolButton *RzToolButtonCAX;
        TRzToolButton *RzToolButtonRotation;
        TRzToolButton *LeftToRightExcahnge;
        TRzToolButton *TopToButtomExcahnge;
        TMenuItem *setCalcheight;
        TRzSelDirDialog *RzSelDirDialogSet;
        TRzPageControl *GroupBoxCompare;
        TRzTabSheet *TabSheetAbsolute;
        TRzTabSheet *TabSheetRelative;
        TCheckBox *CheckBoxDTA_Rel;
        TCheckBox *CheckBoxGamma_Rel;
        TRzBitBtn *RzButtomCompare_Rel;
        TPoint3DSeries *SeriesMeasureNormPointX;
        TPoint3DSeries *SeriesMeasureNormPointY;
        TPoint3DSeries *SeriesCalcNormPointX;
        TPoint3DSeries *SeriesCalcNormPointY;
        TRzToolButton *RzToolButtonNormPointSet;
        TRzPageControl *RzPageControlProfileAndStatic;
        TRzTabSheet *TabSheetProfile;
        TPanel *PanelCompare;
        TChart *ChartCompare;
        TLineSeries *ProCauSeries;
        TPointSeries *ProMeaSeries;
        TLineSeries *ShowProSeries;
        TSmoothingFunction *TeeFunction1;
        TRzTabSheet *TabSheetStatistic;
        TChart *ChartStatics;
        TBarSeries *SeriesStatics;
        TRzToolButton *RzToolButtonSegments;
  void __fastcall RadioButton1Click(TObject *Sender);
  void __fastcall RadioButton2Click(TObject *Sender);
  void __fastcall RadioButton3Click(TObject *Sender);
  void __fastcall SpeedButtonTransforMeasureClick(TObject *Sender);
  void __fastcall SpeedButtonTransforCalculateClick(TObject *Sender);
  void __fastcall StringGridMeasureDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
  void __fastcall SpeedButton3DClick(TObject *Sender);
  void __fastcall SpeedButton3DMeasureClick(TObject *Sender);
  void __fastcall SpeedButton3DCalculateClick(TObject *Sender);
  void __fastcall SpeedButtonDetClick(TObject *Sender);
  void __fastcall SpeedButtonDetMeasureClick(TObject *Sender);
  void __fastcall SpeedButtonDetCalculateClick(TObject *Sender);
  void __fastcall SpeedButtonGridClick(TObject *Sender);
  void __fastcall SpeedButtonGridMeasureClick(TObject *Sender);
  void __fastcall SpeedButtonGridCalculateClick(TObject *Sender);
  void __fastcall ComboBoxGraphChange(TObject *Sender);
  void __fastcall SpeedButtonZoomoutClick(TObject *Sender);
  void __fastcall SpeedButtonZoomoutMeasureClick(TObject *Sender);
  void __fastcall SpeedButtonZoomoutCalculateClick(TObject *Sender);
  void __fastcall SpeedButtonZoominClick(TObject *Sender);
  void __fastcall SpeedButtonZoomin1Click(TObject *Sender);
  void __fastcall standsetClick(TObject *Sender);
  void __fastcall ToolButtonsettingClick(TObject *Sender);
  void __fastcall ToolButton1Click(TObject *Sender);
  void __fastcall ComboBoxDataChange(TObject *Sender);
  void __fastcall N1Click(TObject *Sender);
  void __fastcall OpenZCdoseClick(TObject *Sender);
  void __fastcall OpenMatrixDoseClick(TObject *Sender);
  void __fastcall SpeedButtonLevelsSetMeasureClick(TObject *Sender);
  void __fastcall SpeedButtonLevelsSetCalculateClick(TObject *Sender);
  void __fastcall ChartMeasureMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  void __fastcall ChartCalculateMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  void __fastcall SaveToFileClick(TObject *Sender);
  void __fastcall SetInfoBtnClick(TObject *Sender);
  void __fastcall ButtonBest5Click(TObject *Sender);
  void __fastcall OpenMapCHECKdoseClick(TObject *Sender);
  void __fastcall ToolBar_OpenZCdoseClick(TObject *Sender);
  void __fastcall ToolBar_OpenMapCHECKdoseClick(TObject *Sender);
  void __fastcall ToolBar_OpenMatrixDoseClick(TObject *Sender);
  void __fastcall ToolBar_Open_Plan_DICOMClick(TObject *Sender);
  void __fastcall ToolBar_Open_Plan_SCUClick(TObject *Sender);
  void __fastcall Open_Plan_SCUClick(TObject *Sender);
  void __fastcall RzToolButtonSaveClick(TObject *Sender);
  void __fastcall RzToolButtonSystemSetClick(TObject *Sender);
  void __fastcall RzToolButtonPrintClick(TObject *Sender);
  void __fastcall RzToolButtonExistClick(TObject *Sender);
  void __fastcall RzToolButtonAboutClick(TObject *Sender);
  void __fastcall SystemSetClick(TObject *Sender);
  void __fastcall SmoothSetClick(TObject *Sender);
  void __fastcall Open_Plan_DICOMClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall RzButtomCompare_AbsClick(TObject *Sender);
        void __fastcall EditTHButtonClick(TObject *Sender,
          TSpinButtonType Button);
        void __fastcall EditDoseGapButtonClick(TObject *Sender,
          TSpinButtonType Button);
        void __fastcall EditDistanceButtonClick(TObject *Sender,
          TSpinButtonType Button);
        void __fastcall EditDoseGapEnter(TObject *Sender);
        void __fastcall EditDistanceEnter(TObject *Sender);
        void __fastcall EditTHChange(TObject *Sender);
        void __fastcall EditTHEnter(TObject *Sender);
        void __fastcall EditDoseGapChange(TObject *Sender);
        void __fastcall EditDistanceChange(TObject *Sender);
        void __fastcall FlushTowDataToCacheClick(TObject *Sender);
        void __fastcall ButtonFlushMeasureToCacheClick(TObject *Sender);
        void __fastcall ButtonFlushCalcToCacheClick(TObject *Sender);
        void __fastcall RzToolButtonRefreshLeftGroupBarsClick(TObject *Sender);
        void __fastcall RzPageControlProfileAndStaticPageChange(
          TObject *Sender);
        void __fastcall PrintCurrentClick(TObject *Sender);
        void __fastcall ChangeInformation1Click(TObject *Sender);
        void __fastcall SaveToCacheClick(TObject *Sender);
        void __fastcall RzToolButtonCAXClick(TObject *Sender);
        void __fastcall RzToolButtonRotationClick(TObject *Sender);
        void __fastcall LeftToRightExcahngeClick(TObject *Sender);
        void __fastcall TopToButtomExcahngeClick(TObject *Sender);
        void __fastcall RzToolButtonNormPointSettingClick(TObject *Sender);
        void __fastcall setMesureheightClick(TObject *Sender);
        void __fastcall setCalcheightClick(TObject *Sender);
        void __fastcall LogSettingClick(TObject *Sender);
        void __fastcall RzButtomCompare_RelClick(TObject *Sender);
        void __fastcall RzToolButtonNormPointSetClick(TObject *Sender);
        void __fastcall RzToolButtonNormValueSettingClick(TObject *Sender);
        void __fastcall RzToolButtonSegmentsClick(TObject *Sender);
        void __fastcall User1Click(TObject *Sender);
        void __fastcall ModelSettingClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);

private:
  deque<TRzGroup*> groupDeque;
  deque<TRzTreeView*> treeViewInGroupDeque;

  void __fastcall cleanGroupBars();

public:
  GraphsicTemporaryValues temporaryValues;

private:	// User declarations
  //Deleting int DetTag[3]; //̽������/��
  //����һϵ�����飬��¼��Ӧ��ť��״̬(��-ͼ,3D-2D,������/��,�Ŵ�/��С),��̬������ʾ/����ʾ
  //int TransTag[3];int DimTag[3];int LineTag[3];int ZoomTag[4];int ShowCoordinate;
  //����һϵ�����飬��¼��Ӧ��ComboBox״̬(��������,ͼ����,��������ͼ�е�CompareType�����Դ���Tag�Ϳ�����)
  //int DatatypeTag[3];int GraphTag[3];

  DynamicArray<TPoint3DSeries *>agridlinex;    //��һ��ͼƽ����x�����������
  DynamicArray<TPoint3DSeries *>agridliney;    //��һ��ͼƽ����y�����������
  DynamicArray<TPoint3DSeries *>bgridlinex;    //�ڶ���ͼƽ����x�����������
  DynamicArray<TPoint3DSeries *>bgridliney;    //�ڶ���ͼƽ����y�����������

  int totalcompare;  //���бȽϵ�̽��������

public:		// User declarations
                                             //�ں�M_GAMA�������������ʱ��ɾ��
  
  float seczoom[3];   //������¼DICOM����֮����ӵķŴ����

  float StoreHeight; //���Ŵ�֮ǰ�ĸ߶ȺͿ�Ƚ��д洢
  float StoreWidth;

  int SeperateHeight;   //��ť֮������ֱ����ļ��
  int ButtonsWidth,ButtonsHeight;

public:
  bool __fastcall readDoseFromFile(string filename,FILETYPE fileType);

  void __fastcall ClearMeasureChart();
  bool __fastcall RefreshMeasureDoseGraphicFromDisplayValue();
  bool __fastcall RefreshMeasureDoseGraphicFromTemporyValue();

  void __fastcall resetSomeOnceOpen_ChangeVar();

  void __fastcall ClearCalcChart();
  bool __fastcall RefreshCalculateDoseGraphicFromDisplayValue();
  bool __fastcall RefreshCalculateDoseGraphicFromTemporyValue();

  void __fastcall RefreshMeasureHotPointDose();
  void __fastcall RefreshCalcHotPointDose();
  void __fastcall ShowMeasureHotPointGraphy();
  void __fastcall ShowCalcHotPointGraphy();

  void __fastcall ShowBestFiveResult();

  void __fastcall showDDResult();
  void __fastcall showGammaResult();
  void __fastcall showDTAResult();

  void __fastcall InitialCompareChart(const char* bottomAxisTitle);
  void __fastcall InitialCompareChart(int gridLineNums,double doseCentral,double gridsize,double maxPercent,const char* bottomAxisTitle);


  /*Move And Draw profile Line*/
  void __fastcall moveAndDrwaProfile(int keyboardCode);
  

  /*Set detectors Array*/
  bool __fastcall SetDetectorsArray(MatrixData<bool>& dectorArray,FILETYPE fileType);

  bool __fastcall angleSetting(FILETYPE fileType);
  bool __fastcall patientInformationSetting();
  bool __fastcall patientInformationSetting(FILETYPE fileType);
  bool __fastcall caxSetting(FILETYPE fileType);

  void __fastcall ShowBaseInfo();

  void __fastcall ShowStandardAndTH();
  void __fastcall SetStandardAndTH();

  void __fastcall ShowPatientCache();

  void __fastcall SetPatientInfo();

  //void __fastcall DetClicked(TObject *Sender);  //��̬̽���������¼�
  double __fastcall GettheValueByCoordinate(double XValue,double ZValue,FILETYPE filetype,MatrixData<double>* matrix);  //��ȡָ�����괦����ֵ


  void __fastcall LeftGroupBarItemsClicked(TObject *Sender); //


  void upDataGridSize(double gridSize[3]);

  void __fastcall ShowCalcPath(string path);
  void __fastcall ShowMeasurePath(string path);

  void __fastcall groupsClick(TObject* Sender);
  string __fastcall getTreeViewPathTrim(string path,char split);
  string __fastcall getAngleFromTreeViewPath(string path);

  void __fastcall flushFromCache(int index,string angle);
private:
  bool readZCMeasureDoseFromFile(string filename);
  bool readMapCHECKMeasureDoseFromFile(string filename);
  bool readMatrixMeasureDoseFromFile(string filename);
  bool readDICOMCalcDoseFromFile(string filename);
  bool readSCUCalcDoseFromFile(string filename);

private:

  void __fastcall Drawxprofile(int xmove);   //����ƽ����x�����profileͼ��
  void __fastcall Drawyprofile(int ymove);   //����ƽ����y�����profileͼ��

  void __fastcall moveMeasureXProfile();
  void __fastcall moveMeasureYProfile();
  void __fastcall moveCalcXProfile();
  void __fastcall moveCalcYProfile();

  void __fastcall drawMeasureXProfile();
  void __fastcall drawMeasureYProfile();
  void __fastcall drawCalcXProfile();
  void __fastcall drawCalcYProfile();

public:
  void __fastcall showMeasureDoseStatic();
  void __fastcall showCalculateDoseStatic();
  void __fastcall showCheckResultStatic();

public:
  /*Layout*/
  void __fastcall MainFormLayout();
  void __fastcall PanelShowAndOperationLayout();


  void __fastcall showNormPos(PhysicalPoint measureNormPos,PhysicalPoint calcNormPos);

  void __fastcall measureChartLayout();
  void __fastcall calcChartLayout();

  void __fastcall SetRightTopPanel();

  void __fastcall MemoResultShow();

public:
  __fastcall TFormMain(TComponent* Owner);
  __fastcall ~TFormMain();  //��������


public:  //Event
  void __fastcall ShowMeasureDialog(FILETYPE fileType);

public:
  //Message change:The non-TWinControl VCL can not respond some message,So it is
  //necessary to convert and dispatch the message mannual
  //Describe:The Software may not respond some system messages(such as Keyboard event) while some
  //VCL is add in or other function is add-in,so it is necessary to capture the system message and
  //handle or dispatch to the software
  void __fastcall Proc(TMsg &msg,bool &Handled);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;


extern string saveFileName;
//---------------------------------------------------------------------------
#endif

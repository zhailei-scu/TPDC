//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LogFrame.h"
#include "ModelSetting.h"
//---------------------------------------------------------------------------
USEFORM("doseshell.cpp", FormMain);
USEFORM("Paraset.cpp", Formparaset);
USEFORM("About.cpp", AboutBox);
USEFORM("Systemset.cpp", FormsystemSet);
USEFORM("Changelevels.cpp", FormLevels);
USEFORM("Info.cpp", InfoForm);
USEFORM("PrintSet.cpp", PrintForm);
USEFORM("BestFive.cpp", BestFiveForm);
USEFORM("ShowBestFiveResult.cpp", BestFiveResultForm);
USEFORM("Smoothing.cpp", SmoothingForm);
USEFORM("Angle.cpp", FormAngle);
USEFORM("StaticsQuery.cpp", FormStaticQuery);
USEFORM("caxSetting.cpp", FormCAX);
USEFORM("NormPointSet.cpp", FormNormPointSet);
USEFORM("DTAWayChoose.cpp", FormDTAWayChoose);
USEFORM("DDStatistic.cpp", FormDDStatics);
USEFORM("NormValueSetting.cpp", NormValueSetForm);
USEFORM("SegmentsSetting.cpp", FormSegmentsSetting);
USEFORM("ModelSetting.cpp", ModelSettingForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();

                 RunningLog::writeLog("Welcome to  TPDC...");

                 Application->CreateForm(__classid(TFormMain), &FormMain);

                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------

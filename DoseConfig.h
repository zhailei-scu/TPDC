//---------------------------------------------------------------------------
//Purpose:dose check config file.
//Created by:huangning
//Time:2015/01/12
//---------------------------------------------------------------------------
#ifndef DoseConfigH
#define DoseConfigH
//---------------------------------------------------------------------------
class TDoseConfig
{
public:
  TDoseConfig();
  float lenx,leny,lenz;
  float lenx0,leny0,lenz0;
  float lenmx,lenmy,lenmz;
  float RCUT;
  int   NSEL;
};
#endif
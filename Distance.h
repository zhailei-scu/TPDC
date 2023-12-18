//---------------------------------------------------------------------------
//Purpose:Separate the Cells to little unit,calcualte the factor of these unit
//        ,and sequence these unit by the differences of distances
//Time:2015/1/19
//---------------------------------------------------------------------------
#ifndef DistanceH
#define DistanceH

#include "DoseConfig.h"
#include "math.h"
//---------------------------------------------------------------------------
class TDistance
{
public:
  TDistance(TDoseConfig *CFG);
  //~TDistance();

  int nn;
  float *distance;
  float *x_rcut,*y_rcut,*z_rcut;
  float *factor0,*factor1,*factor2,*factor3;
  float *factor4,*factor5,*factor6,*factor7;
private:
  void runa(float *dis,int left,int right);
  float rCUT,Lenmx,Lenmy,Lenx,Leny;
  float mm_lenx,mm_leny,mm_lenz;
  float dx12,dx21,dy12,dy21,dz12,dz21;
  float dx12dy12,dx12dy21,dx21dy12,dx21dy21;
  //float dx12dy12dz12,dx12dy12dz21,dx12dy21dz12,dx12dy21dz21;
  //float dx21dy12dz12,dx21dy12dz21,dx21dy21dz12,dx21dy21dz21;
};
#endif
//---------------------------------------------------------------------------
#include "Stdio.h"
#include "Distance.h"
//---------------------------------------------------------------------------
TDistance::TDistance(TDoseConfig *CFG)
{
  /*   三维的情况
  float dx, dy, dz,dx1,dx2,dy1,dy2,dz1,dz2,dx0,dy0,dz0;
  int   x,y,z,IV,I,J,K;
  int m_offx0,m_offx1,m_offy0,m_offy1,m_offz0,m_offz1;
  m_lenmx = pcfg->lenmx;             //对应于cfg文件中第三行的参数(0.05)
  m_lenmy = pcfg->lenmy;
  m_lenmz = pcfg->lenmz;

  M_lenx = pcfg->lenx;              //对应于cfg文件中的第一行参数(0.2)
  M_leny = pcfg->leny;
  M_lenz = pcfg->lenz;

  m_offx0 = -ceil(RCUT/m_lenmx);
  m_offx1 = -m_offx0;
  m_offy0 = -ceil(RCUT/m_lenmy);
  m_offy1 = -m_offy0;
  m_offz0 = -ceil(RCUT/m_lenmz);
  m_offz1 = -m_offz0;

  x=m_offx1-m_offx0;
  y=m_offy1-m_offy0;
  z=m_offz1-m_offz0;

  clock_t  timestart=clock();

  nn=x*y*z;
  x_rcut=(float*) malloc(nn*sizeof(float));
  y_rcut=(float*) malloc(nn*sizeof(float));
  z_rcut=(float*) malloc(nn*sizeof(float));
  distance=(float*) malloc(nn*sizeof(float));

  factor0=(float*) malloc(nn*sizeof(float));
  factor1=(float*) malloc(nn*sizeof(float));
  factor2=(float*) malloc(nn*sizeof(float));
  factor3=(float*) malloc(nn*sizeof(float));
  factor4=(float*) malloc(nn*sizeof(float));
  factor5=(float*) malloc(nn*sizeof(float));
  factor6=(float*) malloc(nn*sizeof(float));
  factor7=(float*) malloc(nn*sizeof(float));

  IV=0;
  for(K=0;K<z;K++)
  {
    if(K%2==0)
    {
      dz =(K/2)*m_lenmz;

      dz1=dz-floor((dz+0.00001)/m_lenz)* m_lenz;
    }
    else
    {
      dz =-(K/2+1)*m_lenmz;
      dz0=-dz;
      dz1=dz+ceil((dz0-0.00001)/m_lenz)* m_lenz;
    }

    dz2=dz1- m_lenz;

    for(J=0;J<y;J++)
    {
      if(J%2==0)
      {
        dy = (J/2)*m_lenmy;
        dy1=dy-floor((dy+0.00001)/m_leny)* m_leny;
      }

      else
      {
        dy=-(J/2+1)*m_lenmy;
        dy0=-dy;
        dy1=dy+ceil((dy0-0.00001)/m_leny)* m_leny;
      }
      dy2=dy1- m_leny;

      for(I=0;I<x;I++)
      {
        if(I%2==0)
        {
          dx =(I/2)*m_lenmx;

          dx1=dx-floor((dx+0.00001)/m_lenx)* m_lenx;
          }
          else
          {
            dx=-(I/2+1)*m_lenmx;
            dx0=-dx;
            dx1=dx+ceil((dx0-0.00001)/m_lenx)* m_lenx;
          }
          dx2=dx1- m_lenx;

          x_rcut[IV]=dx;
          y_rcut[IV]=dy;
          z_rcut[IV]=dz;
          distance[IV]=dx*dx + dy*dy + dz*dz;


          factor0[IV]=dx2*dy2*dz2*dx12dy12dz12;
          factor1[IV]=dx2*dy2*dz1*dx12dy12dz21;
          factor2[IV]=dx2*dy1*dz2*dx12dy21dz12;
          factor3[IV]=dx2*dy1*dz1*dx12dy21dz21;
          factor4[IV]=dx1*dy2*dz2*dx21dy12dz12;
          factor5[IV]=dx1*dy2*dz1*dx21dy12dz21;
          factor6[IV]=dx1*dy1*dz2*dx21dy21dz12;
          factor7[IV]=dx1*dy1*dz1*dx21dy21dz21;


          IV++;
          }
        }
    }
  */

  float dx,dy,dz,dx0,dy0,dz0,dx1,dy1,dz1,dx2,dy2,dz2;
  float dx12dy12,dx12dy21,dx21dy12,dx21dy21;
  int x,y,z,IV,I,J,K;
  int m_offx0,m_offx1,m_offy0,m_offy1,m_offz0,m_offz1;
  rCUT = CFG->RCUT;
  Lenmx = CFG->lenmx;
  Lenmy = CFG->lenmy;
  Lenx = CFG->lenx;
  Leny = CFG->leny;

  m_offx0 = -ceil(rCUT/Lenmx);
  m_offx1 = -m_offx0;
  m_offy0 = -ceil(rCUT/Lenmy);
  m_offy1 = -m_offy0;

  x = m_offx1-m_offx0;
  y = m_offy1-m_offy0;


  dx12 = -Lenx;
  dx21 = -dx12;
  dy12 = -Leny;
  dy21 = -dy12;
  //dz12 = -mm_lenz;
  //dz21 = -dz12;
  dx12dy12 = 1.00/(dx12*dy12);
  dx12dy21 = 1.00/(dx12*dy21);
  dx21dy12 = 1.00/(dx21*dy12);
  dx21dy21 = 1.00/(dx21*dy21);

   /*
  dx12dy12dz12 = 1.00/(dx12*dy12*dz12);    //先不考虑三维
  dx12dy12dz21 = 1.00/(dx12*dy12*dz21);
  dx12dy21dz12 = 1.00/(dx12*dy21*dz12);
  dx12dy21dz21 = 1.00/(dx12*dy21*dz21);
  dx21dy12dz12 = 1.00/(dx21*dy12*dz12);
  dx21dy12dz21 = 1.00/(dx21*dy12*dz21);
  dx21dy21dz12 = 1.00/(dx21*dy21*dz12);
  dx21dy21dz21 = 1.00/(dx21*dy21*dz21);
  */

  nn=x*y;
  x_rcut=new float[nn];
  y_rcut=new float[nn];
  distance=new float[nn];

  factor0=new float[nn];
  factor2=new float[nn];
  factor4=new float[nn];
  factor6=new float[nn];

  IV=0;

  for(J=0;J<y;J++)
  {
    if(J%2==0)
    {
      dy = (J/2)*Lenmy;
      dy1=dy-floor((dy+0.00001)/Leny)*Leny;
    }
    else
    {
      dy=-(J/2+1)*Lenmy;
      dy0=-dy;
      dy1=dy+ceil((dy0-0.00001)/Leny)* Leny;
    }

    dy2=dy1- Leny;

    for(I=0;I<x;I++)
    {
      if(I%2==0)
      {
        dx =(I/2)*Lenmx;

        dx1=dx-floor((dx+0.00001)/Lenx)*Lenx;
      }
      else
      {
        dx=-(I/2+1)*Lenmx;
        dx0=-dx;
        dx1=dx+ceil((dx0-0.00001)/Lenx)*Lenx;
      }
      dx2=dx1- Lenx;

      x_rcut[IV]=dx;
      y_rcut[IV]=dy;
      distance[IV]=dx*dx + dy*dy;


      factor0[IV]=dx2*dy2*dx12dy12;
      factor2[IV]=dx2*dy1*dx12dy21;
      factor4[IV]=dx1*dy2*dx21dy12;
      factor6[IV]=dx1*dy1*dx21dy21;

      IV++;
    }
  }
  runa(distance,0,nn-1);
}


/*TDistance::~TDistance()
{
  if(x_rcut) delete[] x_rcut;
  if(y_rcut) delete[] y_rcut;
  if(distance) delete[] distance;
  if(factor0) delete[] factor0;
  if(factor2) delete[] factor2;
  if(factor4) delete[] factor4;
  if(factor6) delete[] factor6;
}
*/


void TDistance::runa(float *dis,int left,int right)
{
  int i,j;
  float middle,iTemp,t;

  i = left;
  j = right;

  middle = dis[(left+right)/2]; //求中间值

  do{
     while((dis[i]<middle) && (i<right))//从左扫描大于中值的数

     i++;

     while((dis[j]>middle) && (j>left))//从右扫描大于中值的数

     j--;

     if(i<=j)//找到了一对值
     {

       //交换

       iTemp = dis[i];

       dis[i] = dis[j];

       dis[j] = iTemp;

       t=x_rcut[i];
       x_rcut[i]=x_rcut[j];
       x_rcut[j]=t;
       t=y_rcut[i];
       y_rcut[i]=y_rcut[j];
       y_rcut[j]=t;

       t=factor0[i];
       factor0[i]=factor0[j];
       factor0[j]=t;

       t=factor2[i];
       factor2[i]=factor2[j];
       factor2[j]=t;

       t=factor4[i];
       factor4[i]=factor4[j];
       factor4[j]=t;

       t=factor6[i];
       factor6[i]=factor6[j];
       factor6[j]=t;


       i++;

       j--;

     }

  }while(i<=j);//如果两边扫描的下标交错，就停止（完成一次）

//当左边部分有值(left<j)，递归左半边
  if(left<j)
    runa(dis,left,j);

//当右边部分有值(right>i)，递归右半边
  if(right>i)
    runa(dis,i,right);
}

#ifndef SlowFastBGOresponses_vhdl_h
#define SlowFastBGOresponses_vhdl_h

#include <TF1.h>
#include <TMath.h>

using namespace std;

// Functions for energy to fast/slow output conversion

/* // ************ Slow plastic ************ */
double SLOW_fast_func(double* xx, double* p){ // Parameters (56.2275,0.612154,0.872188,51.5075,0.865177)
  double x = xx[0];
  double result = (x<p[0]?p[1]*x:0)+(x>=p[0]?p[2]*std::pow(x-p[3],p[4])+p[1]*p[0]-p[2]*std::pow(p[0]-p[3],p[4]):0);
  return result;
}
double SLOW_slow_func(double* xx, double* p){ // Parameters (0.863927)
  double x = xx[0];
  double result = p[0]*x;
  return result;
}
double SLOW_fast_spread(double* xx, double* p){ // Parameters (22.5318,0.136402,-1.26719,177.681,4.40987,157.015,0.421366)
  double x = xx[0];
  double result = (x>=p[0]&&x<p[3]?p[1]*x+p[2]:0)+(x>=p[3]?p[4]*std::pow(x-p[5],p[6])-p[4]*std::pow(p[3]-p[5],p[6])+p[1]*p[3]+p[2]:0);
  return result;
}
double SLOW_slow_spread(double* xx, double* p){ // Parameters (20.95,0.654681,20.9491,0.718411)
  double x = xx[0];
  double result = (x>=p[0]?p[1]*std::pow(x-p[2],p[3]):0);
  return result;
}
double SLOW_ratio_func(double* xx, double* p){ // Parameters (1.39442e+00,3.35869e+01,-1.78185e-01)
  double x = xx[0];
  double result = (x<p[1]+std::pow(p[0],-1/p[2])?1:p[0]*std::pow(x-p[1],p[2]));
  return result;
}
double SLOW_ratio_spread(double* xx, double* p){ // Parameters (6.71561e-01,-3.48771e+01,-2.84110e-01)
  double x = xx[0];
  double result = p[0]*std::pow(x-p[1],p[2]);
  return result;
}


/* // ************ Fast plastic ************ */
double FAST_fast_func(double* xx, double* p){ // Parameters (0.907,639.86,0.93947)
  double x = xx[0];
  double result = (x<p[1]?x*p[0]:0)+(x>=p[1]?p[2]*(x-p[1])+p[0]*p[1]:0);
  return result;
}
double FAST_slow_func(double* xx, double* p){ // Parameters (0.959,254.17,1.006)
  double x = xx[0];
  double result = (x<p[1]?x*p[0]:0)+(x>=p[1]?p[2]*(x-p[1])+p[0]*p[1]:0);
  return result;
}
double FAST_fast_spread(double* xx, double* p){ // Parameters (11.4688,0.066461,0.295592,46.8633,0.240131,77.4137,0.136704,153.009,0.181361,357.024,0.110805)
  double x = xx[0];
  double result = (x>=p[0]&&x<p[3]?p[1]*x+p[2]:0)+(x>=p[3]&&x<p[5]?p[4]*(x-p[3])+p[1]*p[3]+p[2]:0)+(x>=p[5]&&x<p[7]?p[6]*(x-p[5])+p[4]*(p[5]-p[3])+p[1]*p[3]+p[2]:0)+(x>=p[7]&&x<p[9]?p[8]*(x-p[7])+p[6]*(p[7]-p[5])+p[4]*(p[5]-p[3])+p[1]*p[3]+p[2]:0)+(x>=p[9]?p[10]*(x-p[9])+p[8]*(p[9]-p[7])+p[6]*(p[7]-p[5])+p[4]*(p[5]-p[3])+p[1]*p[3]+p[2]:0);
  return result;
}
double FAST_slow_spread(double* xx, double* p){ // Parameters (12.575,0.0437219,0.299948,52.7838,0.190632,78.2045,0.0510193,174.328,0.138426,351.006,0.0159375)
  double x = xx[0];
  double result = (x>=p[0]&&x<p[3]?p[1]*x+p[2]:0)+(x>=p[3]&&x<p[5]?p[4]*(x-p[3])+p[1]*p[3]+p[2]:0)+(x>=p[5]&&x<p[7]?p[6]*(x-p[5])+p[4]*(p[5]-p[3])+p[1]*p[3]+p[2]:0)+(x>=p[7]&&x<p[9]?p[8]*(x-p[7])+p[6]*(p[7]-p[5])+p[4]*(p[5]-p[3])+p[1]*p[3]+p[2]:0)+(x>=p[9]?p[10]*(x-p[9])+p[8]*(p[9]-p[7])+p[6]*(p[7]-p[5])+p[4]*(p[5]-p[3])+p[1]*p[3]+p[2]:0);
  return result;
}
double FAST_ratio_func(double* xx, double* p){ // Parameters (1.27646e+05,-1.11351e+00,9.58568e-01,4.64569e+01,9.38878e+01,1.21461e-05,7.09603e+01)
  double x = xx[0];
  double result = (x<p[6]?p[0]*TMath::Exp(p[1]*x)+p[2]*TMath::Gaus(x,p[3],p[4]):p[5]*(x-p[6])+p[0]*TMath::Exp(p[1]*p[6])+p[2]*TMath::Gaus(p[6],p[3],p[4]));
  return result>1?1:result;
}
double FAST_ratio_spread(double* xx, double* p){ // Parameters (2.05523e+00,5.00871e+01,-6.36315e-01,9.71479e-01,4.45404e+01,1.35108e+02,-1.68708e+01,4.32460e+01,1.10036e-03,8.05196e+01)
  double x = xx[0];
  double result = (x<p[9]?p[0]*(1-p[1]*TMath::Exp(p[2]*x)-p[3]*TMath::Gaus(x,p[4],p[5])):p[6]*std::pow(x-p[7],p[8])+p[0]*(1-p[1]*TMath::Exp(p[2]*p[9])-p[3]*TMath::Gaus(p[9],p[4],p[5]))-p[6]*std::pow(p[9]-p[7],p[8]));
  return result<0?0:result;
}


/* // ************ BGO ************ */
double BGO_fast_func(double* xx, double* p){ // Parameters (68.262,0.5958,0.5425,68.157,0.92327)
  double x = xx[0];
  double result = (x<p[0]?p[1]*x:0)+(x>=p[0]?p[2]*std::pow(x-p[3],p[4])+p[1]*p[0]-p[2]*std::pow(p[0]-p[3],p[4]):0);
  return result;
}
double BGO_slow_func(double* xx, double* p){ // Parameters (0.830268)
  double x = xx[0];
  double result = p[0]*x;
  return result;
}
double BGO_fast_spread(double* xx, double* p){ // Parameters (23.8992,0.149117,-2.30337,155.686,2.06564,-224.2,0.565293)
  double x = xx[0];
  double result = (x>=p[0]&&x<p[3]?p[1]*x+p[2]:0)+(x>=p[3]?p[4]*std::pow(x-p[5],p[6])-p[4]*std::pow(p[3]-p[5],p[6])+p[1]*p[3]+p[2]:0);
  return result;
}
double BGO_slow_spread(double* xx, double* p){ // Parameters (18.4466,0.679945,18.0553,0.712094)
  double x = xx[0];
  double result = (x>=p[0]?p[1]*std::pow(x-p[2],p[3]):0);
  return result;
}
double BGO_ratio_func(double* xx, double* p){ // Parameters (1.05087e+00,6.46327e+01,-1.37377e-01)
  double x = xx[0];
  double result = (x<p[1]+std::pow(p[0],-1/p[2])?1:p[0]*std::pow(x-p[1],p[2]));
  return result;
}
double BGO_ratio_spread(double* xx, double* p){ // Parameters (8.05395e-01,-2.23421e+01,-3.34509e-01)
  double x = xx[0];
  double result = p[0]*std::pow(x-p[1],p[2]);
  return result;
}


struct ResponseFunctions_vhdl{
  TF1  *SLOW_fast, *SLOW_slow, *SLOW_ratio, *FAST_fast, *FAST_slow, *FAST_ratio, *BGO_fast, *BGO_slow, *BGO_ratio;
  TF1  *SLOW_fast_rms, *SLOW_slow_rms, *SLOW_ratio_rms, *FAST_fast_rms, *FAST_slow_rms, *FAST_ratio_rms, *BGO_fast_rms, *BGO_slow_rms, *BGO_ratio_rms;
  ResponseFunctions_vhdl(){
  SLOW_fast = new TF1("SLOW_fast",SLOW_fast_func,0,10000,5);
  SLOW_fast->SetParameters(56.2275,0.612154,0.872188,51.5075,0.865177);
  SLOW_fast_rms = new TF1("SLOW_fast_rms",SLOW_fast_spread,0,10000,7);
  SLOW_fast_rms->SetParameters(22.5318,0.136402,-1.26719,177.681,4.40987,157.015,0.421366);

  SLOW_slow = new TF1("SLOW_slow",SLOW_slow_func,0,10000,1);
  SLOW_slow->SetParameter(0, 0.863927);
  SLOW_slow_rms = new TF1("SLOW_slow_rms",SLOW_slow_spread,0,10000,4);
  SLOW_slow_rms->SetParameters(20.95,0.654681,20.9491,0.718411);

  SLOW_ratio = new TF1("SLOW_ratio",SLOW_ratio_func,0,10000,3);
  SLOW_ratio->SetParameters(1.39442e+00,3.35869e+01,-1.78185e-01);
  SLOW_ratio_rms = new TF1("SLOW_ratio_rms",SLOW_ratio_spread,0,10000,3);
  SLOW_ratio_rms->SetParameters(6.71561e-01,-3.48771e+01,-2.84110e-01);

  FAST_fast = new TF1("FAST_fast",FAST_fast_func,0,10000,3);
  FAST_fast->SetParameters(0.907,639.86,0.93947);
  FAST_fast_rms = new TF1("FAST_fast_rms",FAST_fast_spread,0,10000,11);
  FAST_fast_rms->SetParameters(11.4688,0.066461,0.295592,46.8633,0.240131,77.4137,0.136704,153.009,0.181361,357.024,0.110805);

  FAST_slow = new TF1("FAST_slow",FAST_slow_func,0,10000,3);
  FAST_slow->SetParameters(0.959,254.17,1.006);
  FAST_slow_rms = new TF1("FAST_slow_rms",FAST_slow_spread,0,10000,11);
  FAST_slow_rms->SetParameters(12.575,0.0437219,0.299948,52.7838,0.190632,78.2045,0.0510193,174.328,0.138426,351.006,0.0159375);

  FAST_ratio = new TF1("FAST_ratio",FAST_ratio_func,0,10000,7);
  FAST_ratio->SetParameters(1.27646e+05,-1.11351e+00,9.58568e-01,4.64569e+01,9.38878e+01,1.21461e-05,7.09603e+01);
  FAST_ratio_rms = new TF1("FAST_ratio_rms",FAST_ratio_spread,0,10000,10);
  FAST_ratio_rms->SetParameters(2.05523e+00,5.00871e+01,-6.36315e-01,9.71479e-01,4.45404e+01,1.35108e+02,-1.68708e+01,4.32460e+01,1.10036e-03,8.05196e+01);

  BGO_fast = new TF1("BGO_fast",BGO_fast_func,0,10000,5);
  BGO_fast->SetParameters(68.262,0.5958,0.5425,68.157,0.92327);
  BGO_fast_rms = new TF1("BGO_fast_rms",BGO_fast_spread,0,10000,7);
  BGO_fast_rms->SetParameters(23.8992,0.149117,-2.30337,155.686,2.06564,-224.2,0.565293);

  BGO_slow = new TF1("BGO_slow",BGO_slow_func,0,10000,1);
  BGO_slow->SetParameter(0, 0.830268);
  BGO_slow_rms = new TF1("BGO_slow_rms",BGO_slow_spread,0,10000,4);
  BGO_slow_rms->SetParameters(18.4466,0.679945,18.0553,0.712094);

  BGO_ratio = new TF1("BGO_ratio",BGO_ratio_func,0,10000,3);
  BGO_ratio->SetParameters(1.05087e+00,6.46327e+01,-1.37377e-01);
  BGO_ratio_rms = new TF1("BGO_ratio_rms",BGO_ratio_spread,0,10000,3);
  BGO_ratio_rms->SetParameters(8.05395e-01,-2.23421e+01,-3.34509e-01);
  }
};

#endif

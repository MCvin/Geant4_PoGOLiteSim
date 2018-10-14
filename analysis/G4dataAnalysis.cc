//C++ libs
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

//ROOT libs
#include <TApplication.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TLegend.h>
#include <TRandom3.h>

//User libs
#include "G4data.h"
#include "SlowFastBGOresponses_vhdl.h"

using namespace std;

// user settings
bool veto_vhdl = true;
bool veto_perfect = false;
float hitThreshold = 10;
float trigThreshold = 300; // 10;
float upperD = 2400; //2500;
//float Time = 132; //1168.18 sec for 6Coll // 156 sec for 1PDC // 132s for 6coll with 4*10^8 ph
float Time = 558.4; //7317s for Crab, 3191.7s for gammas, 558.4s for neutrons

// global variables
float nPhE_keV[91];    // number of photo-electrons per keV per unit
float nADC_PhE[91];    // number of ADC channels per photo-electrons per unit
float detpos[61][2];   // position of the detector units
float Angle[61][61];   // angle between 2 detector units (0deg is x, 90deg is -y)
float LLmap[91][91];   // light leakage between 2 detector units
TRandom3 random3(1);   // "TRandom3 is the best random engine in ROOT. 0 means seed from system clock."

TH1F *EM, *EMR0, *EMR1, *EMR2, *EMR3, *EMR4;
TH1F *Sn, *SnR0, *SnR1, *SnR2, *SnR3, *SnR4;
TH1F *S1, *S1R0, *S1R1, *S1R2, *S1R3, *S1R4;
TH1F *S2, *S2P, *S2C;
TH1F *S2R0, *S2R0P, *S2R0C;
TH1F *S2R1, *S2R1P, *S2R1C;
TH1F *S2R2, *S2R2P, *S2R2C;
TH1F *S2R3, *S2R3P, *S2R3C;
TH1F *S2R4, *S2R4P, *S2R4C;
TH1F *S3, *S3R0, *S3R1, *S3R2, *S3R3, *S3R4;
TH1F *Dn, *D1, *D2T, *D2P, *D2C;
TH1F *RD2;
TH1F *M2;
TH2F *XY2, *XZ2;
TH1F *fast_acceptance, *acceptance_dummy;

void createHistos()
{
  // event multiplicity histogram
  EM = new TH1F("EM", "Event multiplicity", 10, 0, 10);
  EM->Sumw2();
  EM->GetXaxis()->SetTitle("Event multiplicity");
  EM->GetYaxis()->SetTitle("Events/s");
  EM->GetXaxis()->CenterTitle();
  EM->GetYaxis()->CenterTitle();
  EMR0 = (TH1F*)EM->Clone("EMRing0");
  EMR1 = (TH1F*)EM->Clone("EMRing1");
  EMR2 = (TH1F*)EM->Clone("EMRing2");
  EMR3 = (TH1F*)EM->Clone("EMRing3");
  EMR4 = (TH1F*)EM->Clone("EMRing4");

  // ring distribution histogram
  RD2 = new TH1F("RD2", "2hit ring distribution", 5, -0.5, 4.5);
  RD2->Sumw2();
  RD2->GetXaxis()->SetTitle("PDC ring number");
  RD2->GetYaxis()->SetTitle("Events/s per PDC");
  RD2->GetXaxis()->CenterTitle();
  RD2->GetYaxis()->CenterTitle();

  // nhits spectrum
  //Sn = new TH1F("Snhits", "G4 spectrum, all hit events", 240, 0, 240);
  Sn = new TH1F("Snhits", "G4 spectrum, all hit events", 4096, -0.5, 4095.5);
  Sn->Sumw2();
  //Sn->GetXaxis()->SetTitle("Energy (keV)");
  Sn->GetXaxis()->SetTitle("Energy (ADC channels)");
  Sn->GetYaxis()->SetTitle("Events/s");
  Sn->GetXaxis()->CenterTitle();
  Sn->GetYaxis()->CenterTitle();
  SnR0 = (TH1F*)Sn->Clone("SnhitsRing0");
  SnR1 = (TH1F*)Sn->Clone("SnhitsRing1");
  SnR2 = (TH1F*)Sn->Clone("SnhitsRing2");
  SnR3 = (TH1F*)Sn->Clone("SnhitsRing3");
  SnR4 = (TH1F*)Sn->Clone("SnhitsRing4");
  // 1hit spectrum
  S1 = (TH1F*)Sn->Clone("S1hit");
  S1->SetTitle("G4 spectrum, 1 hit events");
  S1R0 = (TH1F*)Sn->Clone("S1hitsRing0");
  S1R1 = (TH1F*)Sn->Clone("S1hitsRing1");
  S1R2 = (TH1F*)Sn->Clone("S1hitsRing2");
  S1R3 = (TH1F*)Sn->Clone("S1hitsRing3");
  S1R4 = (TH1F*)Sn->Clone("S1hitsRing4");
  // 2hits spectrum
  S2 = (TH1F*)Sn->Clone("S2hits");
  S2->SetTitle("G4 spectrum, 2 hit events");
  S2P = (TH1F*)Sn->Clone("S2hitsPhoto");
  S2C = (TH1F*)Sn->Clone("S2hitsCompton");
  S2R0 = (TH1F*)Sn->Clone("S2hitsRing0");
  S2R0P = (TH1F*)Sn->Clone("S2hitsRing0Photo");
  S2R0C = (TH1F*)Sn->Clone("S2hitsRing0Compton");
  S2R1 = (TH1F*)Sn->Clone("S2hitsRing1");
  S2R1P = (TH1F*)Sn->Clone("S2hitsRing1Photo");
  S2R1C = (TH1F*)Sn->Clone("S2hitsRing1Compton");
  S2R2 = (TH1F*)Sn->Clone("S2hitsRing2");
  S2R2P = (TH1F*)Sn->Clone("S2hitsRing2Photo");
  S2R2C = (TH1F*)Sn->Clone("S2hitsRing2Compton");
  S2R3 = (TH1F*)Sn->Clone("S2hitsRing3");
  S2R3P = (TH1F*)Sn->Clone("S2hitsRing3Photo");
  S2R3C = (TH1F*)Sn->Clone("S2hitsRing3Compton");
  S2R4 = (TH1F*)Sn->Clone("S2hitsRing4");
  S2R4P = (TH1F*)Sn->Clone("S2hitsRing4Photo");
  S2R4C = (TH1F*)Sn->Clone("S2hitsRing4Compton");
  // 3hits spectrum
  S3 = (TH1F*)Sn->Clone("S3hits");
  S3->SetTitle("G4 spectrum, 3 hit events");
  S3R0 = (TH1F*)Sn->Clone("S3hitsRing0");
  S3R1 = (TH1F*)Sn->Clone("S3hitsRing1");
  S3R2 = (TH1F*)Sn->Clone("S3hitsRing2");
  S3R3 = (TH1F*)Sn->Clone("S3hitsRing3");
  S3R4 = (TH1F*)Sn->Clone("S3hitsRing4");

  // nhits distribution
  Dn = new TH1F("Dnhits", "G4 distribution, nhit events", 61, 0, 61);
  Dn->Sumw2();
  Dn->GetXaxis()->SetTitle("Detector id");
  Dn->GetYaxis()->SetTitle("Events/s");
  Dn->GetXaxis()->CenterTitle();
  Dn->GetYaxis()->CenterTitle();
  // 1hit distribution
  D1 = (TH1F*)Dn->Clone("D1hit");
  D1->SetTitle("G4 distribution, 1hit events");
  // 2hits distribution
  D2T = (TH1F*)Dn->Clone("D2hitsTotal");
  D2T->SetTitle("G4 distribution, 2hit events");
  D2P = (TH1F*)D2T->Clone("D2hitsPhoto");
  D2C = (TH1F*)D2T->Clone("D2hitsCompton");
  // 2hits angle distribution
  M2 = new TH1F("M2", "2 hits angular distribution", 360, 0, 360);
  M2->Sumw2();
  M2->GetXaxis()->SetTitle("Angle (deg)");
  M2->GetYaxis()->SetTitle("Events");
  M2->GetXaxis()->CenterTitle();
  M2->GetYaxis()->CenterTitle();
  // 2hits map
  XY2 = new TH2F("XY2hits", "G4 map of the 2hit events (x,y)", 300, -150, 150, 300, -150, 150);
  XZ2 = new TH2F("XZ2hits", "G4 map of the 2hit events (x,z)", 300, -150, 150, 860, -50, 810);
}

void displayHistos()
{
  // print event multiplicity
  TCanvas* cEM = new TCanvas("G4eventMultiplicity","G4eventMultiplicity",0,0,400,250);
  cEM->SetGrid();
  EM->Scale(1./Time);
  EMR0->Scale(1./Time);
  EMR1->Scale(1./Time);
  EMR2->Scale(1./Time);
  EMR3->Scale(1./Time);
  EMR4->Scale(1./Time);
  EM->Draw();

  // print ring distribution
  TCanvas* cRD2 = new TCanvas("G4ringDistribution2hits","G4ringDistribution2hits",800,0,400,250);
  cRD2->SetGrid();
  RD2->Scale(1./Time);
  RD2->Draw();

  // print nHits
  TCanvas* cSn = new TCanvas("G4spectrumNhits","G4spectrumNhits",400,0,400,250);
  cSn->SetGrid();
  cSn->SetLogy();
  Sn->Scale(1./Time);
  Sn->Draw();
  SnR0->SetLineColor(kBlue);
  SnR0->Scale(1./Time);
  SnR0->Draw("sames");
  SnR1->SetLineColor(kRed);
  SnR1->Scale(1./Time);
  SnR1->Draw("sames");
  SnR2->SetLineColor(kGreen);
  SnR2->Scale(1./Time);
  SnR2->Draw("sames");
  SnR3->Scale(1./Time);
  SnR4->Scale(1./Time);
  TLegend* lSn = new TLegend(0.7, 0.6, 0.85, 0.75);
  lSn->AddEntry(Sn, "All units", "l");
  lSn->AddEntry(SnR0, "Ring 0 unit", "l");
  lSn->AddEntry(SnR1, "Ring 1 unit", "l");
  lSn->AddEntry(SnR2, "Ring 2 unit", "l");
  lSn->Draw();
  TCanvas* cDn = new TCanvas("G4distributionNhits","G4distributionNhits",0,260,400,250);
  cDn->SetGrid();
  cDn->SetLogy();
  Dn->Scale(1./Time);
  Dn->Draw();

  // print 1Hit
  TCanvas* cS1 = new TCanvas("G4spectrum1hit","G4spectrum1hit",400,260,400,250);
  cS1->SetGrid();
  cS1->SetLogy();
  S1->Scale(1./Time);
  S1->Draw();
  S1R0->SetLineColor(kBlue);
  S1R0->Scale(1./Time);
  S1R0->Draw("sames");
  S1R1->SetLineColor(kRed);
  S1R1->Scale(1./Time);
  S1R1->Draw("sames");
  S1R2->SetLineColor(kGreen);
  S1R2->Scale(1./Time);
  S1R2->Draw("sames");
  S1R3->Scale(1./Time);
  S1R4->Scale(1./Time);
  TLegend* lS1 = new TLegend(0.7, 0.6, 0.85, 0.75);
  lS1->AddEntry(S1, "All units", "l");
  lS1->AddEntry(S1R0, "Ring 0 unit", "l");
  lS1->AddEntry(S1R1, "Ring 1 unit", "l");
  lS1->AddEntry(S1R2, "Ring 2 unit", "l");
  lS1->Draw();
  TCanvas* cD1 = new TCanvas("G4distribution1hit","G4distribution1hit",0,520,400,250);
  cD1->SetGrid();
  cD1->SetLogy();
  D1->Scale(1./Time);
  D1->Draw();

  // print 2Hits
  TCanvas* cS2 = new TCanvas("G4spectrum2hits","G4spectrum2hits",400,520,400,250);
  cS2->SetGrid();
  cS2->SetLogy();
  S2->Scale(1./Time);
  S2P->Scale(1./Time);
  S2C->Scale(1./Time);
  S2->Draw();
  S2R0->SetLineColor(kBlue);
  S2R0->Scale(1./Time);
  S2R0P->Scale(1./Time);
  S2R0C->Scale(1./Time);
  S2R0->Draw("sames");
  S2R1->SetLineColor(kRed);
  S2R1->Scale(1./Time);
  S2R1P->Scale(1./Time);
  S2R1C->Scale(1./Time);
  S2R1->Draw("sames");
  S2R2->SetLineColor(kGreen);
  S2R2->Scale(1./Time);
  S2R2P->Scale(1./Time);
  S2R2C->Scale(1./Time);
  S2R2->Draw("sames");
  S2R3->Scale(1./Time);
  S2R3P->Scale(1./Time);
  S2R3C->Scale(1./Time);
  S2R4->Scale(1./Time);
  S2R4P->Scale(1./Time);
  S2R4C->Scale(1./Time);
  TLegend* lS2 = new TLegend(0.7, 0.6, 0.85, 0.75);
  lS2->AddEntry(S2, "All units", "l");
  lS2->AddEntry(S2R0, "Ring 0 unit", "l");
  lS2->AddEntry(S2R1, "Ring 1 unit", "l");
  lS2->AddEntry(S2R2, "Ring 2 unit", "l");
  lS2->Draw();
  TCanvas* cD2 = new TCanvas("G4distribution2hits","G4distribution2hits",0,780,400,250);
  cD2->SetGrid();
  cD2->SetLogy();
  D2T->Scale(1./Time);
  D2T->Draw();
  D2P->SetLineColor(kGreen);
  D2P->Scale(1./Time);
  D2P->Draw("sames");
  D2C->Scale(1./Time);
  D2C->SetLineColor(kRed);
  D2C->Draw("sames");
  TLegend* lD2 = new TLegend(0.45, 0.6, 0.85, 0.75);
  lD2->AddEntry(D2T, "Total hits in fast scintillators", "l");
  lD2->AddEntry(D2P, "Photo hits (Emax) in fast scintillators", "l");
  lD2->AddEntry(D2C, "Compton hits (Emin) in fast scintillators", "l");
  lD2->Draw();
  TCanvas* cM2 = new TCanvas("G4angulardistribution2hits","G4angulardistribution2hits",800,260,400,250);
  cM2->SetGrid();
  // modulation curve
  TF1* Mf = new TF1("Mf", "[0]*(1+[1]*cos(2*3.1415/180.0*(x-[2])))", -10,370);
  //TF1* Mf = new TF1("Mf", "[0]*(1+[1]*cos(2*3.1415/180.0*(x-[2]))+[3]*cos(3.1415/180.0*(x-[4])))", -10,370);
  //M2->Rebin(15);
  M2->Fit("Mf", "R");
  std::cout << "MF " << Mf->GetParameter(1) << " MFerr " << Mf->GetParError(1) << " N2hits " << M2->GetEntries() << " N1hit " << D1->GetEntries() << std::endl;
  Mf->Draw("sames");
  M2->Draw();
  gStyle->SetOptFit(1111);
  new TCanvas("G4XYmap2hits","G4XYmap2hits",800,520,400,250);
  XY2->Draw("COLZ");
  new TCanvas("G4XZmap2hits","G4XZmap2hits",800,780,400,250);
  XZ2->Draw("COLZ");

  // print 3Hits
  TCanvas* cS3 = new TCanvas("G4spectrum3hits","G4spectrum3hits",400,780,400,250);
  cS3->SetGrid();
  cS3->SetLogy();
  S3->Scale(1./Time);
  S3->Draw();
  S3R0->SetLineColor(kBlue);
  S3R0->Scale(1./Time);
  S3R0->Draw("sames");
  S3R1->SetLineColor(kRed);
  S3R1->Scale(1./Time);
  S3R1->Draw("sames");
  S3R2->SetLineColor(kGreen);
  S3R2->Scale(1./Time);
  S3R2->Draw("sames");
  S3R3->Scale(1./Time);
  S3R4->Scale(1./Time);
  TLegend* lS3 = new TLegend(0.7, 0.6, 0.85, 0.75);
  lS3->AddEntry(S3, "All units", "l");
  lS3->AddEntry(S3R0, "Ring 0 unit", "l");
  lS3->AddEntry(S3R1, "Ring 1 unit", "l");
  lS3->AddEntry(S3R2, "Ring 2 unit", "l");
  lS3->Draw();
}

void saveHistos(const char *path)
{
  // save event multiplicity
  TFile fileEM(Form("%sG4eventMultiplicity.root",path), "RECREATE");
  EM->Write(); EMR0->Write(); EMR1->Write(); EMR2->Write(); EMR3->Write(); EMR4->Write();
  // save ring distribution
  TFile fileRD2(Form("%sG4ringDistribution2hits.root",path), "RECREATE");
  RD2->Write();
  // save nHits
  TFile fileSn(Form("%sG4spectrumNhits.root",path), "RECREATE");
  Sn->Write(); SnR0->Write(); SnR1->Write(); SnR2->Write(); SnR3->Write(); SnR4->Write();
  TFile fileDn(Form("%sG4distributionNhits.root",path), "RECREATE");
  Dn->Write();
  // save 1Hit
  TFile fileS1(Form("%sG4spectrum1hit.root",path), "RECREATE");
  S1->Write(); S1R0->Write(); S1R1->Write(); S1R2->Write(); S1R3->Write(); S1R4->Write();
  TFile fileD1(Form("%sG4distribution1hit.root",path), "RECREATE");
  D1->Write();
  // save 2Hits
  TFile fileS2(Form("%sG4spectrum2hits.root",path), "RECREATE");
  S2->Write(); S2P->Write(); S2C->Write();
  S2R0->Write(); S2R0P->Write(); S2R0C->Write();
  S2R1->Write(); S2R1P->Write(); S2R1C->Write();
  S2R2->Write(); S2R2P->Write(); S2R2C->Write();
  S2R3->Write(); S2R3P->Write(); S2R3C->Write();
  S2R4->Write(); S2R4P->Write(); S2R4C->Write();
  TFile fileD2(Form("%sG4distribution2hits.root",path), "RECREATE");
  D2T->Write(); D2P->Write(); D2C->Write();
  TFile fileM2(Form("%sG4angulardistribution2hits.root",path), "RECREATE");
  M2->Write();
  TFile fileXYZ2(Form("%sG4map2hits.root",path), "RECREATE");
  XY2->Write(); XZ2->Write();
  // save 3Hits
  TFile fileS3(Form("%sG4spectrum3hits.root",path), "RECREATE");
  S3->Write(); S3R0->Write(); S3R1->Write(); S3R2->Write(); S3R3->Write(); S3R4->Write();
}

void ReadCalibrationParameters()
{
  //ifstream lightyield("inputs/LightYields.dat"); if (!lightyield.is_open()) cout << "Unable to open file" << endl;
  //ifstream pmtgain("inputs/PMT_gains.dat"); if (!pmtgain.is_open()) cout << "Unable to open file" << endl;
  ifstream lightyield("inputs/LightYields2015.dat"); if (!lightyield.is_open()) cout << "Unable to open file" << endl;
  ifstream pmtgain("inputs/PMT_gains2015.dat"); if (!pmtgain.is_open()) cout << "Unable to open file" << endl;

  //ifstream lightyield("inputs/LightYieldsHåkan_oldPDCs.dat"); if (!lightyield.is_open()) cout << "Unable to open file" << endl;
  //ifstream pmtgain("inputs/PMT_gainsHåkan_oldPDCs.dat"); if (!pmtgain.is_open()) cout << "Unable to open file" << endl;
  //ifstream lightyield("inputs/LightYieldsHåkan_newPDCs.dat"); if (!lightyield.is_open()) cout << "Unable to open file" << endl;
  //ifstream pmtgain("inputs/PMT_gainsHåkan_newPDCs.dat"); if (!pmtgain.is_open()) cout << "Unable to open file" << endl;
  ifstream detpositions("inputs/det_positions.dat"); if (!detpositions.is_open()) cout << "Unable to open file" << endl;
  ifstream angmatrix("inputs/angles_matrix.dat"); if (!angmatrix.is_open()) cout << "Unable to open file" << endl;
  ifstream LightLeakageMap("inputs/LightLeakage_map_NormToTotal.dat"); if (!LightLeakageMap.is_open()) cout << "Unable to open file" << endl;
  //TFile* f = new TFile("inputs/fast_acceptance.root","read");
  //fast_acceptance = (TH1F*)f->Get("hist_Acceptance");
  TFile* f = new TFile("inputs/fast_acceptance_allcuts.root","read");
  fast_acceptance = (TH1F*)f->Get("hist_Acceptance_ALL");
  fast_acceptance->Rebin(8);
  fast_acceptance->Scale(1./8);
  acceptance_dummy = (TH1F*)fast_acceptance->Clone("acceptance_dummy");

  for (int i = 0; i < 61; i++) {
    detpositions >> detpos[i][0] >> detpos[i][1];
    for (int j = 0; j < 61; j++) {
      angmatrix >> Angle[i][j];
    }
  }
  for (int i = 0; i < 91; i++) {
    lightyield >> nPhE_keV[i];
    pmtgain >> nADC_PhE[i];
  }
  float row;
  for (int i = 0; i < 91; i++) {
    LightLeakageMap >> row;
    for (int j = 0; j < 91; j++) {
      LightLeakageMap >> LLmap[i][j];
    }
  }
  lightyield.close();
  pmtgain.close();
  angmatrix.close();
  LightLeakageMap.close();
}

void LightLeakage(Processed_data *G4Pro)
{
  float E_fast, E_slow;
  for (int i = 0; i < 91; i++) {
    E_fast = G4Pro->PMT_fast->EdepTot[i];
    E_slow = G4Pro->PMT_slow->EdepTot[i];
    if (E_fast > 0) {
      G4Pro->PMT_fast->EdepTot[i] = E_fast * (1-(1-LLmap[i][i])); // assuming that light lost = 1 - cross talk
      for (int j = 0; j < 91; j++) {
	if (j != i) G4Pro->PMT_fast->EdepTot[j] += E_fast * LLmap[i][j];
      }
    }
    if (E_slow > 0) {
      G4Pro->PMT_slow->EdepTot[i] = E_slow * (1-(1-LLmap[i][i])); // assuming that light lost = 1 - cross talk
      for (int j = 0; j < 91; j++) {
	if (j != i) G4Pro->PMT_slow->EdepTot[j] += E_slow * LLmap[i][j];
      }
    }
  }
  G4Pro->PMT_fast->Update();
  G4Pro->PMT_slow->Update();
}

void EnergyResponse(G4data *G4, ResponseFunctions_vhdl *RF_vhdl, Processed_data *G4Pro)
{ // this function simulate the production and collection of optical photons in the PMTs

  int UnitId;
  float E;
  float keVtoADC;
  float ADCtot, fast, slow;

  // ---------- slow scintillator ----------
  for (int x = 0; x < G4->slow->nhits; x++) {
    UnitId = G4->slow->UnitId[x];
    E = G4->slow->Edep[x];
    // to simulate passive slow
    //E = 0;
    // correction for scintillator non-linearity response
    E = E * (1.001 - 0.486 * exp(-0.0902 * E));
    // relative light yield compare to fast
    E = E * 0.6;
    // z position dependance
    E = E * (1.0 - (G4->slow->Pz[x] - 200) * 0.75/600);
    // optical coupling
    E = E / 2;

    // sum energy deposits by unit
    G4Pro->slow->EdepTot[UnitId] += E;
  }
  G4Pro->slow->Update();
  for (int x = 0; x < G4Pro->slow->nUnits; x++) {
    UnitId = G4Pro->slow->UnitId[x];
    keVtoADC = nADC_PhE[UnitId] * nPhE_keV[UnitId];
    ADCtot = G4Pro->slow->EdepTot[UnitId] *keVtoADC;
    // estimate fast/slow output
    slow = random3.Gaus(RF_vhdl->SLOW_slow->Eval(ADCtot), RF_vhdl->SLOW_slow_rms->Eval(ADCtot));
    if (slow > ADCtot) slow = ADCtot;
    fast = slow * random3.Gaus(RF_vhdl->SLOW_ratio->Eval(ADCtot), RF_vhdl->SLOW_ratio_rms->Eval(ADCtot)/1.2);
    if (fast > ADCtot) fast = ADCtot;

    // sum fast/slow output deposits by PMT
    G4Pro->PMT_fast->EdepTot[UnitId] += fast /keVtoADC;
    G4Pro->PMT_slow->EdepTot[UnitId] += slow /keVtoADC;
  }


  // ---------- fast scintillator ----------
  for (int x = 0; x < G4->fast->nhits; x++) {
    UnitId = G4->fast->UnitId[x];
    E = G4->fast->Edep[x];
    // correction for scintillator non-linearity response
    E = E * (1.001 - 0.486 * exp(-0.0902 * E)); // Mizuno et al. 2009
    // z position dependance
    E = E * (1.0 - (G4->fast->Pz[x] - 132) * 0.13/200); // 132cm: mean photoabsorption position

    // sum energy deposits by unit
    G4Pro->fast->EdepTot[UnitId] += E;
  }
  G4Pro->fast->Update();
  for (int x = 0; x < G4Pro->fast->nUnits; x++) {
    UnitId = G4Pro->fast->UnitId[x];
    keVtoADC = nADC_PhE[UnitId] * nPhE_keV[UnitId];
    ADCtot = G4Pro->fast->EdepTot[UnitId] *keVtoADC;
    // estimate fast/slow output
    slow = random3.Gaus(RF_vhdl->FAST_slow->Eval(ADCtot), RF_vhdl->FAST_slow_rms->Eval(ADCtot));
    if (slow > ADCtot) slow = ADCtot;
    fast = slow * random3.Gaus(RF_vhdl->FAST_ratio->Eval(ADCtot), RF_vhdl->FAST_ratio_rms->Eval(ADCtot)/1.2);
    if (fast > ADCtot) fast = ADCtot;

    // sum fast/slow output deposits by PMT
    G4Pro->PMT_fast->EdepTot[UnitId] += fast /keVtoADC;
    G4Pro->PMT_slow->EdepTot[UnitId] += slow /keVtoADC;
  }

  // ---------- bottom BGO scintillator ----------
  for (int x = 0; x < G4->bottomBGO->nhits; x++) {
    UnitId = G4->bottomBGO->UnitId[x];
    E = G4->bottomBGO->Edep[x];
    // correction for scintillator non-linearity response (empirical formula)
    E = E * (1.1 - 1.0 * exp(-0.04 * E));
    // relative light yield compare to fast
    E = E * 0.7;

    // sum energy deposits by unit
    G4Pro->bottomBGO->EdepTot[UnitId] += E;
  }
  G4Pro->bottomBGO->Update();
  for (int x = 0; x < G4Pro->bottomBGO->nUnits; x++) {
    UnitId = G4Pro->bottomBGO->UnitId[x];
    keVtoADC = nADC_PhE[UnitId] * nPhE_keV[UnitId];
    ADCtot = G4Pro->bottomBGO->EdepTot[UnitId] *keVtoADC;
    // estimate fast/slow output
    slow = random3.Gaus(RF_vhdl->BGO_slow->Eval(ADCtot), RF_vhdl->BGO_slow_rms->Eval(ADCtot));
    if (slow > ADCtot) slow = ADCtot;
    fast = slow * random3.Gaus(RF_vhdl->BGO_ratio->Eval(ADCtot), RF_vhdl->BGO_ratio_rms->Eval(ADCtot)/1.2);
    if (fast > ADCtot) fast = ADCtot;

    // sum fast/slow output deposits by PMT
    G4Pro->PMT_fast->EdepTot[UnitId] += fast /keVtoADC;
    G4Pro->PMT_slow->EdepTot[UnitId] += slow /keVtoADC;
  }

  // ---------- SAS ----------
  for (int x = 0; x < G4->SAS->nhits; x++) {
    UnitId = G4->SAS->UnitId[x];
    E = G4->SAS->Edep[x];
    // correction for scintillator non-linearity response (empirical formula)
    E = E * (1.1 - 1.0 * exp(-0.04 * E));
    // relative light yield compare to fast
    E = E * 0.7;
    // z position dependance
    E = E * (1.0 - (G4->SAS->Pz[x] - 260) * 0.087/600); // 260cm: mean photoabsorption position

    // sum energy deposits by unit
    G4Pro->SAS->EdepTot[UnitId] += E;
  }
  G4Pro->SAS->Update();
  for (int x = 0; x < G4Pro->SAS->nUnits; x++) {
    UnitId = G4Pro->SAS->UnitId[x];

    // ! change that for pogo+ !
    keVtoADC = nADC_PhE[UnitId] * nPhE_keV[UnitId];
    ADCtot = G4Pro->SAS->EdepTot[UnitId] *keVtoADC;
    // estimate fast/slow output
    slow = random3.Gaus(RF_vhdl->BGO_slow->Eval(ADCtot), RF_vhdl->BGO_slow_rms->Eval(ADCtot));
    if (slow > ADCtot) slow = ADCtot;
    fast = slow * random3.Gaus(RF_vhdl->BGO_ratio->Eval(ADCtot), RF_vhdl->BGO_ratio_rms->Eval(ADCtot)/1.2);
    if (fast > ADCtot) fast = ADCtot;

    // sum fast/slow output deposits by PMT
    G4Pro->PMT_fast->EdepTot[UnitId+61] += fast /keVtoADC;
    G4Pro->PMT_slow->EdepTot[UnitId+61] += slow /keVtoADC;

    //E = G4Pro->SAS->EdepTot[UnitId];
    //G4Pro->PMT_fast->EdepTot[UnitId+61] += E;
    //G4Pro->PMT_slow->EdepTot[UnitId+61] += E;
  }

  // update nUnits and UnitId based on EdepTot[x]
  G4Pro->PMT_fast->Update();
  G4Pro->PMT_slow->Update();
}

void EnergyConversion_keV2ADC(Processed_data *G4Pro)
{
  int UnitId;
  float E_fast, E_slow;
  int nPhE_fast, ADC_fast, ADC_slow;

  for (int x = 0; x < G4Pro->PMT_fast->nUnits; x++) {
    UnitId = G4Pro->PMT_fast->UnitId[x];
    E_fast = G4Pro->PMT_fast->EdepTot[UnitId];
    E_slow = G4Pro->PMT_slow->EdepTot[UnitId];

    // correction for PMT photon-electron production (low energy cutoff)
    nPhE_fast = random3.Poisson(E_fast * nPhE_keV[UnitId]);
    // correction for PMT gain fluctuation (empirical formula, see PMTgainFluctuation.png)
    ADC_fast = random3.Gaus(nPhE_fast, 0.5*sqrt(nPhE_fast-0.5)) * nADC_PhE[UnitId];
    ADC_slow = ADC_fast *E_slow/E_fast;

    G4Pro->PMT_fast->EdepTot[UnitId] = ADC_fast;
    G4Pro->PMT_slow->EdepTot[UnitId] = ADC_slow;
  }

  //for (int x = 7; x < 91; x++) { // Hakan set-up
  //  G4Pro->PMT_fast->EdepTot[x] = 0;
  //  G4Pro->PMT_slow->EdepTot[x] = 0;
  //}

  //G4Pro->PMT_fast->EdepTot[8] = 0; // dead PMT number 8
  //G4Pro->PMT_slow->EdepTot[8] = 0; // dead PMT number 8
  // update nUnits and UnitId based on EdepTot[x]
  G4Pro->PMT_fast->Update();
  G4Pro->PMT_slow->Update();
}

bool EventsSelection(Processed_data *G4Pro)
{
  bool valid = false;

  for (int x = 0; x < G4Pro->PMT_fast->nUnits; x++) {
    int UnitId = G4Pro->PMT_fast->UnitId[x];
    float E_fast = G4Pro->PMT_fast->EdepTot[UnitId];
    float E_slow = G4Pro->PMT_slow->EdepTot[UnitId];
    float G4_slow_Edep = G4Pro->slow->EdepTot[UnitId] + G4Pro->bottomBGO->EdepTot[UnitId];

    float keVtoADC = nADC_PhE[UnitId] * nPhE_keV[UnitId];
    //float uni = random3.Uniform();

    // tests
    //if ((E_fast < trigThreshold) && (UnitId > 36)) return false;
    //if (UnitId > 36) return false;

    // hit threshold
    if ((E_fast < hitThreshold) && (E_slow < hitThreshold)) {
      G4Pro->PMT_fast->EdepTot[UnitId] = 0;
      G4Pro->PMT_slow->EdepTot[UnitId] = 0;
    }
    // trigger threshold (only on PDCs)
    if ((E_fast > trigThreshold) && (UnitId < 61)) valid = true;

    // ---------- veto system ----------
    if ((veto_vhdl) || (veto_perfect)) {
      // saturation (upper discrimator)
      if (E_fast > upperD) return false;
      if (E_slow > upperD) return false;
      // SAS veto
      if ((E_fast > 0) && (UnitId > 60)) return false;
      if ((E_slow > 0) && (UnitId > 60)) return false;
      // VHDL veto (waveform discrimator)
      if ((veto_vhdl) && (E_slow > E_fast + 100)) return false; // online veto
      // Perfect veto system (above 1 photoelectron)
      if ((veto_perfect) && (E_slow > 0) && (G4_slow_Edep*keVtoADC > hitThreshold)) return false;
      // Instrument efficiency
      //if (uni > fast_acceptance->GetBinContent(acceptance_dummy->Fill(E_fast))) return false;

    } else {
      // non SAS PMTs only
      if ((E_fast > 0) && (UnitId > 60)) G4Pro->PMT_fast->EdepTot[UnitId] = 0;
      if ((E_slow > 0) && (UnitId > 60)) G4Pro->PMT_slow->EdepTot[UnitId] = 0;
    }
  }

  // update the number of hitten units and UnitId
  G4Pro->PMT_fast->Update();
  G4Pro->PMT_slow->Update();

  return valid;
}

void EnergyReconstruction_ADC2keV(Processed_data* G4Pro)
{
  for (int x = 0; x < G4Pro->PMT_fast->nUnits; x++) {
    int UnitId = G4Pro->PMT_fast->UnitId[x];
    int ADC = G4Pro->PMT_fast->EdepTot[UnitId];
    // ADC to keV
    float E = ADC / nADC_PhE[UnitId] / nPhE_keV[UnitId];
    // correction for scintillator non-linearity response
    E = E / (1.001 - 0.486 * exp(-0.0902 * E)); // not exactly correct

    G4Pro->PMT_fast->EdepTot[UnitId] = E;
  }
}

void fillnhits(Processed_data *G4Pro)
{
  float MaxE = 0;
  int UnitIdMaxE = -1;
  int nUnits = G4Pro->PMT_fast->nUnits;

  for (int x = 0; x < nUnits; x++) {
    int UnitId = G4Pro->PMT_fast->UnitId[x];
    float E = G4Pro->PMT_fast->EdepTot[UnitId];

    // get highest energy location
    if (E > MaxE) {UnitIdMaxE = UnitId; MaxE = E;}

    // spectra
    Sn->Fill(E);
    if (UnitId == 0) SnR0->Fill(E);
    if ((UnitId > 0) && (UnitId < 7)) SnR1->Fill(E);
    if ((UnitId > 6) && (UnitId < 19)) SnR2->Fill(E);
    if ((UnitId > 18) && (UnitId < 37)) SnR3->Fill(E);
    if ((UnitId > 36) && (UnitId < 61)) SnR4->Fill(E);

    // Distribution
    Dn->Fill(UnitId);
  }

  // multiplicity
  if (UnitIdMaxE > -1) EM->Fill(nUnits);
  if (UnitIdMaxE == 0) EMR0->Fill(nUnits);
  if ((UnitIdMaxE > 0) && (UnitIdMaxE < 7)) EMR1->Fill(nUnits);
  if ((UnitIdMaxE > 6) && (UnitIdMaxE < 19)) EMR2->Fill(nUnits);
  if ((UnitIdMaxE > 18) && (UnitIdMaxE < 37)) EMR3->Fill(nUnits);
  if ((UnitIdMaxE > 36) && (UnitIdMaxE < 61)) EMR4->Fill(nUnits);
}

void fill1hit(Processed_data *G4Pro)
{
  if (G4Pro->PMT_fast->nUnits == 1) {
    int UnitId = G4Pro->PMT_fast->UnitId[0];

    // spectra
    float E = G4Pro->PMT_fast->EdepTot[UnitId];
    S1->Fill(E);
    if (UnitId == 0) S1R0->Fill(E);
    if ((UnitId > 0) && (UnitId < 7)) S1R1->Fill(E);
    if ((UnitId > 6) && (UnitId < 19)) S1R2->Fill(E);
    if ((UnitId > 18) && (UnitId < 37)) S1R3->Fill(E);
    if ((UnitId > 36) && (UnitId < 61)) S1R4->Fill(E);

    // Distribution
    D1->Fill(UnitId);
  }
}

void fill2hits(G4data *G4, Processed_data *G4Pro)
{
  if (G4Pro->PMT_fast->nUnits == 2) {
    int UnitId1 = G4Pro->PMT_fast->UnitId[0];
    int UnitId2 = G4Pro->PMT_fast->UnitId[1];
    float E1 = G4Pro->PMT_fast->EdepTot[UnitId1];
    float E2 = G4Pro->PMT_fast->EdepTot[UnitId2];

    float deltaX = detpos[UnitId2][0]-detpos[UnitId1][0];
    float deltaY = detpos[UnitId2][1]-detpos[UnitId1][1];
    float dist = sqrt(deltaX*deltaX + deltaY*deltaY) * 15;

    if (dist > 0) {
      //if (dist > 31) {

    // to always have E1 < E2
    if (E2 < E1) {int Idtemp = UnitId1; UnitId1 = UnitId2; UnitId2 = Idtemp; int Etemp = E1; E1 = E2; E2 = Etemp;}

    // ring distribution
    for (int x = 0; x < 2; x++) {
      int UnitId = G4Pro->PMT_fast->UnitId[x];
      if (UnitId == 0) RD2->Fill(0);
      if ((UnitId > 0) && (UnitId < 7)) RD2->Fill(1,1./6);
      if ((UnitId > 6) && (UnitId < 19)) RD2->Fill(2,1./11);  // 11 not 12: Carolina is dead
      if ((UnitId > 18) && (UnitId < 37)) RD2->Fill(3,1./18);
      if ((UnitId > 36) && (UnitId < 61)) RD2->Fill(4,1./24);
    }

    //float E = 0;
    // spectra
    for (int x = 0; x < 2; x++) {
      int UnitId = G4Pro->PMT_fast->UnitId[x];
      float E = G4Pro->PMT_fast->EdepTot[UnitId];
      //E += G4Pro->PMT_fast->EdepTot[UnitId];
      if (UnitId == UnitId1) { // Compton
      	S2->Fill(E); S2C->Fill(E);
      	if (UnitId == 0) {S2R0->Fill(E); S2R0C->Fill(E);}
      	if ((UnitId > 0) && (UnitId < 7)) {S2R1->Fill(E); S2R1C->Fill(E);}
      	if ((UnitId > 6) && (UnitId < 19)) {S2R2->Fill(E); S2R2C->Fill(E);}
      	if ((UnitId > 18) && (UnitId < 37)) {S2R3->Fill(E); S2R3C->Fill(E);}
      	if ((UnitId > 36) && (UnitId < 61)) {S2R4->Fill(E); S2R4C->Fill(E);}
      }
      if (UnitId == UnitId2) { // Photo
      	S2->Fill(E); S2P->Fill(E);
      	if (UnitId == 0) {S2R0->Fill(E); S2R0P->Fill(E);}
      	if ((UnitId > 0) && (UnitId < 7)) {S2R1->Fill(E); S2R1P->Fill(E);}
      	if ((UnitId > 6) && (UnitId < 19)) {S2R2->Fill(E); S2R2P->Fill(E);}
      	if ((UnitId > 18) && (UnitId < 37)) {S2R3->Fill(E); S2R3P->Fill(E);}
      	if ((UnitId > 36) && (UnitId < 61)) {S2R4->Fill(E); S2R4P->Fill(E);}
      }
    }
    //S2->Fill(E);

    // distribution
      // Total energy
      D2T->Fill(UnitId1);
      D2T->Fill(UnitId2);
      // Compton
      D2C->Fill(UnitId1);
      // Photopeak
      D2P->Fill(UnitId2);

    // map of the interactions
    for (int x = 0; x < G4->slow->nhits; x++) {
      XY2->Fill(G4->slow->Px[x],G4->slow->Py[x]);
      XZ2->Fill(G4->slow->Px[x],G4->slow->Pz[x]);
    }
    for (int x = 0; x < G4->fast->nhits; x++) {
      XY2->Fill(G4->fast->Px[x],G4->fast->Py[x]);
      XZ2->Fill(G4->fast->Px[x],G4->fast->Pz[x]);
    }
    for (int x = 0; x < G4->bottomBGO->nhits; x++) {
      XY2->Fill(G4->bottomBGO->Px[x],G4->bottomBGO->Py[x]);
      XZ2->Fill(G4->bottomBGO->Px[x],G4->bottomBGO->Pz[x]);
    }

    // modulation curve
    float phi;
    //if (UnitId1 == 0) { // center scattering
    //if ((UnitId1 > 0) && (UnitId1 < 7)) { //ring1 scattering
    //if ((UnitId1 > 6) && (UnitId1 < 19)) { //ring2 scattering
    //if ((UnitId1 > 18) && (UnitId1 < 37)) { //ring3 scattering
    //if ((UnitId1 > 36) && (UnitId1 < 61)) { //ring4 scattering
      //if ((UnitId2 > 0) && (UnitId2 < 7)) { //ring1 absorption
      //if ((UnitId2 > 6) && (UnitId2 < 19)) { //ring2 absorption
      //if ((UnitId2 > 18) && (UnitId2 < 37)) { //ring3 absorption
      //if ((UnitId2 > 36) && (UnitId2 < 61)) { //ring4 absorption
	phi = Angle[UnitId1][UnitId2] + G4->Inst_roll; // low Edep to high Edep
	if (phi >= 360) phi -= 360;
	M2->Fill(phi);
      //}
    //}
    }
  }
}

void fill3hits(G4data *G4, Processed_data *G4Pro)
{
  if (G4Pro->PMT_fast->nUnits == 3) {
    // spectra
    for (int x = 0; x < 3; x++) {
      int UnitId = G4Pro->PMT_fast->UnitId[x];
      float E = G4Pro->PMT_fast->EdepTot[UnitId];
      S3->Fill(E);
      if (UnitId == 0) S3R0->Fill(E);
      if ((UnitId > 0) && (UnitId < 7)) S3R1->Fill(E);
      if ((UnitId > 6) && (UnitId < 19)) S3R2->Fill(E);
      if ((UnitId > 18) && (UnitId < 37)) S3R3->Fill(E);
      if ((UnitId > 36) && (UnitId < 61)) S3R4->Fill(E);
    }
    // int UnitId1 = G4Pro->PMT_fast->UnitId[0];
    // int UnitId2 = G4Pro->PMT_fast->UnitId[1];
    // int UnitId3 = G4Pro->PMT_fast->UnitId[2];
    // float E1 = G4Pro->PMT_fast->EdepTot[UnitId1];
    // float E2 = G4Pro->PMT_fast->EdepTot[UnitId2];
    // float E3 = G4Pro->PMT_fast->EdepTot[UnitId3];

    // float phi;
    // // to include 3hits and possible 2hits+leakage into modulation curve
    // if (E1 < E2 && E2 < E3) phi = Angle[UnitId2][UnitId3]; // low Edep to high Edep
    // if (E1 < E3 && E3 < E2) phi = Angle[UnitId3][UnitId2];
    // if (E2 < E1 && E1 < E3) phi = Angle[UnitId1][UnitId3];
    // if (E2 < E3 && E3 < E1) phi = Angle[UnitId3][UnitId1];
    // if (E3 < E1 && E1 < E2) phi = Angle[UnitId1][UnitId2];
    // if (E3 < E2 && E2 < E1) phi = Angle[UnitId2][UnitId1];
    // phi += G4->Inst_roll;
    // if (phi > 360) phi -= 360;
    // M2->Fill(phi);
  }
}

int main(int argc, char* argv[])
{
  TApplication theApp("App", 0, 0); // load every root library in memory

  // open the Tree and create objects to contain the branches
  TFile *f;
  if (argc == 2) f = new TFile(argv[1],"r");
  else f = new TFile("G4data.root","r");
  TTree *tree = (TTree*) f->Get("G4data");
  G4data *G4 = new G4data; //Declare the object for raw data
  G4->SetAddress(tree);    //Set every address explicitly (IMPORTANT!)
  Processed_data *G4Pro = new Processed_data; //Declare the object for processed data

  // Setting up the functions for energy to fast/slow output conversion
  ResponseFunctions_vhdl *RF_vhdl = new ResponseFunctions_vhdl;

  // read the characteristics of the PDCs from ascii files
  ReadCalibrationParameters();

  // create histograms
  createHistos();

  // loop over all entries in the tree
  for (long i = 0; i < tree->GetEntries(); i++){
    tree->GetEntry(i);

    // display completion
    if (i%int(tree->GetEntries()/100.) == 0) {
      //printf("Completion: %i %% \r",int(float(i)/tree->GetEntries()*100));
      //fflush(stdout);
    }

    // initialize processed data arrays to 0
    G4Pro->Init();

    // energy response
    EnergyResponse(G4, RF_vhdl, G4Pro);

    // simulate light leakage using the light leakage map measured on PoGOLite
    //LightLeakage(G4Pro);

    // energy conversion: keV to ADC
    EnergyConversion_keV2ADC(G4Pro);

    // events selection
    bool validEvent = EventsSelection(G4Pro);

    if (validEvent) {
      // energy reconstruction: ADC to keV
      //EnergyReconstruction_ADC2keV(G4Pro);

      // Nhits
      fillnhits(G4Pro);
      // 1hit
      fill1hit(G4Pro);
      // 2hits
      fill2hits(G4, G4Pro);
      // 3hits
      fill3hits(G4, G4Pro);
    }

  }

  // display histograms
  displayHistos();

  // save histograms
  saveHistos("outputs/");

  //theApp.Run();
  return 0;
}

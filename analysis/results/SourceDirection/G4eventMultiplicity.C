{
//=========Macro generated from canvas: G4eventMultiplicity/G4eventMultiplicity
//=========  (Wed Nov 13 10:08:23 2013) by ROOT version5.34/11
   TCanvas *G4eventMultiplicity = new TCanvas("G4eventMultiplicity", "G4eventMultiplicity",11,51,700,500);
   G4eventMultiplicity->SetHighLightColor(2);
   G4eventMultiplicity->Range(-1.25,-10.43049,11.25,93.87441);
   G4eventMultiplicity->SetFillColor(0);
   G4eventMultiplicity->SetBorderMode(0);
   G4eventMultiplicity->SetBorderSize(2);
   G4eventMultiplicity->SetGridx();
   G4eventMultiplicity->SetGridy();
   G4eventMultiplicity->SetFrameBorderMode(0);
   G4eventMultiplicity->SetFrameBorderMode(0);
   
   TH1F *EM = new TH1F("EM","Event multiplicity",10,0,10);
   EM->SetBinContent(2,79.4704);
   EM->SetBinContent(3,74.74014);
   EM->SetBinContent(4,61.00987);
   EM->SetBinContent(5,36.65132);
   EM->SetBinContent(6,15.75);
   EM->SetBinContent(7,5.263158);
   EM->SetBinContent(8,1.111842);
   EM->SetBinContent(9,0.1611842);
   EM->SetBinContent(10,0.02631579);
   EM->SetEntries(83352);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *text = ptstats->AddText("EM");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 83352  ");
   text = ptstats->AddText("Mean  =  2.474");
   text = ptstats->AddText("RMS   =  1.332");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   EM->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(EM);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   EM->SetLineColor(ci);
   EM->GetXaxis()->SetTitle("Event multiplicity");
   EM->GetXaxis()->CenterTitle(true);
   EM->GetXaxis()->SetLabelFont(42);
   EM->GetXaxis()->SetLabelSize(0.035);
   EM->GetXaxis()->SetTitleSize(0.035);
   EM->GetXaxis()->SetTitleFont(42);
   EM->GetYaxis()->SetTitle("Events/s");
   EM->GetYaxis()->CenterTitle(true);
   EM->GetYaxis()->SetLabelFont(42);
   EM->GetYaxis()->SetLabelSize(0.035);
   EM->GetYaxis()->SetTitleSize(0.035);
   EM->GetYaxis()->SetTitleFont(42);
   EM->GetZaxis()->SetLabelFont(42);
   EM->GetZaxis()->SetLabelSize(0.035);
   EM->GetZaxis()->SetTitleSize(0.035);
   EM->GetZaxis()->SetTitleFont(42);
   EM->Draw("");
   
   TPaveText *pt = new TPaveText(0.3470402,0.9339831,0.6529598,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText("Event multiplicity");
   pt->Draw();
   G4eventMultiplicity->Modified();
   G4eventMultiplicity->cd();
   G4eventMultiplicity->SetSelected(G4eventMultiplicity);
}

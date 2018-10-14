{
//=========Macro generated from canvas: G4eventMultiplicity/G4eventMultiplicity
//=========  (Tue Dec  3 16:22:01 2013) by ROOT version5.34/09
   TCanvas *G4eventMultiplicity = new TCanvas("G4eventMultiplicity", "G4eventMultiplicity",11,36,700,500);
   G4eventMultiplicity->SetHighLightColor(2);
   G4eventMultiplicity->Range(0,0,1,1);
   G4eventMultiplicity->SetFillColor(0);
   G4eventMultiplicity->SetBorderMode(0);
   G4eventMultiplicity->SetBorderSize(2);
   G4eventMultiplicity->SetGridx();
   G4eventMultiplicity->SetGridy();
   G4eventMultiplicity->SetFrameBorderMode(0);
   
   TH1F *EM = new TH1F("EM","Event multiplicity",10,0,10);
   EM->SetBinContent(2,62.25987);
   EM->SetBinContent(3,59.39474);
   EM->SetBinContent(4,47.66776);
   EM->SetBinContent(5,28.88816);
   EM->SetBinContent(6,12.57895);
   EM->SetBinContent(7,3.6875);
   EM->SetBinContent(8,0.8618421);
   EM->SetBinContent(9,0.1447368);
   EM->SetBinContent(10,0.02631579);
   EM->SetEntries(65515);

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
   G4eventMultiplicity->Modified();
   G4eventMultiplicity->cd();
   G4eventMultiplicity->SetSelected(G4eventMultiplicity);
}

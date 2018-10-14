{
//=========Macro generated from canvas: G4separation2hits/G4separation2hits
//=========  (Tue Dec  3 16:19:52 2013) by ROOT version5.34/09
   TCanvas *G4separation2hits = new TCanvas("G4separation2hits", "G4separation2hits",11,36,700,500);
   G4separation2hits->SetHighLightColor(2);
   G4separation2hits->Range(0,0,1,1);
   G4separation2hits->SetFillColor(0);
   G4separation2hits->SetBorderMode(0);
   G4separation2hits->SetBorderSize(2);
   G4separation2hits->SetGridx();
   G4separation2hits->SetGridy();
   G4separation2hits->SetFrameBorderMode(0);
   
   TH1F *L2hits = new TH1F("L2hits","G4 separation length, 2hit events",300,0,300);
   L2hits->SetBinContent(30,165);
   L2hits->SetBinContent(31,9963);
   L2hits->SetBinContent(52,2247);
   L2hits->SetBinContent(60,64);
   L2hits->SetBinContent(61,1723);
   L2hits->SetBinContent(80,1895);
   L2hits->SetBinContent(91,642);
   L2hits->SetBinContent(104,473);
   L2hits->SetBinContent(109,800);
   L2hits->SetBinContent(121,234);
   L2hits->SetBinContent(131,61);
   L2hits->SetBinContent(138,40);
   L2hits->SetBinContent(151,19);
   L2hits->SetBinContent(156,6);
   L2hits->SetBinContent(159,6);
   L2hits->SetBinContent(168,8);
   L2hits->SetBinContent(181,5);
   L2hits->SetBinContent(183,5);
   L2hits->SetBinContent(188,1);
   L2hits->SetEntries(18357);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   L2hits->SetLineColor(ci);
   L2hits->GetXaxis()->SetTitle("Separation (mm)");
   L2hits->GetXaxis()->CenterTitle(true);
   L2hits->GetXaxis()->SetLabelFont(42);
   L2hits->GetXaxis()->SetLabelSize(0.035);
   L2hits->GetXaxis()->SetTitleSize(0.035);
   L2hits->GetXaxis()->SetTitleFont(42);
   L2hits->GetYaxis()->SetTitle("Events/bin");
   L2hits->GetYaxis()->CenterTitle(true);
   L2hits->GetYaxis()->SetLabelFont(42);
   L2hits->GetYaxis()->SetLabelSize(0.035);
   L2hits->GetYaxis()->SetTitleSize(0.035);
   L2hits->GetYaxis()->SetTitleFont(42);
   L2hits->GetZaxis()->SetLabelFont(42);
   L2hits->GetZaxis()->SetLabelSize(0.035);
   L2hits->GetZaxis()->SetTitleSize(0.035);
   L2hits->GetZaxis()->SetTitleFont(42);
   L2hits->Draw("");
   G4separation2hits->Modified();
   G4separation2hits->cd();
   G4separation2hits->SetSelected(G4separation2hits);
}

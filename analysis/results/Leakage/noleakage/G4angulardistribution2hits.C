{
//=========Macro generated from canvas: G4angulardistribution2hits/G4angulardistribution2hits
//=========  (Tue Dec  3 16:22:02 2013) by ROOT version5.34/09
   TCanvas *G4angulardistribution2hits = new TCanvas("G4angulardistribution2hits", "G4angulardistribution2hits",11,36,700,500);
   G4angulardistribution2hits->SetHighLightColor(2);
   G4angulardistribution2hits->Range(0,0,1,1);
   G4angulardistribution2hits->SetFillColor(0);
   G4angulardistribution2hits->SetBorderMode(0);
   G4angulardistribution2hits->SetBorderSize(2);
   G4angulardistribution2hits->SetGridx();
   G4angulardistribution2hits->SetGridy();
   G4angulardistribution2hits->SetFrameBorderMode(0);
   
   TH1F *M2 = new TH1F("M2","2 hits angular distribution",6,0,360);
   M2->SetBinContent(1,2789);
   M2->SetBinContent(2,3053);
   M2->SetBinContent(3,3056);
   M2->SetBinContent(4,3030);
   M2->SetBinContent(5,3055);
   M2->SetBinContent(6,3073);
   M2->SetEntries(18056);
   
   TF1 *Mf = new TF1("Mf","[0]*(1+[1]*cos(2*3.1415/180.0*(x-[2])))",-10,370);
   Mf->SetFillColor(19);
   Mf->SetFillStyle(0);
   Mf->SetLineColor(2);
   Mf->SetLineWidth(2);
   Mf->SetChisquare(10.02891);
   Mf->SetNDF(3);
   Mf->GetXaxis()->SetLabelFont(42);
   Mf->GetXaxis()->SetLabelSize(0.035);
   Mf->GetXaxis()->SetTitleSize(0.035);
   Mf->GetXaxis()->SetTitleFont(42);
   Mf->GetYaxis()->SetLabelFont(42);
   Mf->GetYaxis()->SetLabelSize(0.035);
   Mf->GetYaxis()->SetTitleSize(0.035);
   Mf->GetYaxis()->SetTitleFont(42);
   Mf->SetParameter(0,3007.661);
   Mf->SetParError(0,22.3892);
   Mf->SetParLimits(0,0,0);
   Mf->SetParameter(1,-0.0343557);
   Mf->SetParError(1,0.01043473);
   Mf->SetParLimits(1,0,0);
   Mf->SetParameter(2,31.6747);
   Mf->SetParError(2,8.852926);
   Mf->SetParLimits(2,0,0);
   M2->GetListOfFunctions()->Add(Mf);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   M2->SetLineColor(ci);
   M2->GetXaxis()->SetTitle("Angle (deg)");
   M2->GetXaxis()->CenterTitle(true);
   M2->GetXaxis()->SetLabelFont(42);
   M2->GetXaxis()->SetLabelSize(0.035);
   M2->GetXaxis()->SetTitleSize(0.035);
   M2->GetXaxis()->SetTitleFont(42);
   M2->GetYaxis()->SetLabelFont(42);
   M2->GetYaxis()->SetLabelSize(0.035);
   M2->GetYaxis()->SetTitleSize(0.035);
   M2->GetYaxis()->SetTitleFont(42);
   M2->GetZaxis()->SetLabelFont(42);
   M2->GetZaxis()->SetLabelSize(0.035);
   M2->GetZaxis()->SetTitleSize(0.035);
   M2->GetZaxis()->SetTitleFont(42);
   M2->Draw("");
   
   TF1 *Mf = new TF1("Mf","[0]*(1+[1]*cos(2*3.1415/180.0*(x-[2])))",-10,370);
   Mf->SetFillColor(19);
   Mf->SetFillStyle(0);
   Mf->SetLineColor(2);
   Mf->SetLineWidth(2);
   Mf->SetChisquare(10.02891);
   Mf->SetNDF(3);
   Mf->GetXaxis()->SetLabelFont(42);
   Mf->GetXaxis()->SetLabelSize(0.035);
   Mf->GetXaxis()->SetTitleSize(0.035);
   Mf->GetXaxis()->SetTitleFont(42);
   Mf->GetYaxis()->SetLabelFont(42);
   Mf->GetYaxis()->SetLabelSize(0.035);
   Mf->GetYaxis()->SetTitleSize(0.035);
   Mf->GetYaxis()->SetTitleFont(42);
   Mf->SetParameter(0,3007.661);
   Mf->SetParError(0,22.3892);
   Mf->SetParLimits(0,0,0);
   Mf->SetParameter(1,-0.0343557);
   Mf->SetParError(1,0.01043473);
   Mf->SetParLimits(1,0,0);
   Mf->SetParameter(2,31.6747);
   Mf->SetParError(2,8.852926);
   Mf->SetParLimits(2,0,0);
   Mf->Draw("sames");
   
   TPaveText *pt = new TPaveText(0.1911494,0.9365254,0.8088506,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("[0]*(1+[1]*cos(2*3.1415/180.0*(x-[2])))");
   pt->Draw();
   G4angulardistribution2hits->Modified();
   G4angulardistribution2hits->cd();
   G4angulardistribution2hits->SetSelected(G4angulardistribution2hits);
}

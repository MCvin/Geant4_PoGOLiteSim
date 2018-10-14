void display(){

	TFile* f = new TFile("bottomBGO/VetoOn/G4spectrum1hit.root","read");
	TH1F* BGO_sim = (TH1F*) f->Get("S1hit");
	TFile* f = new TFile("bottomBGO/VetoOff/G4spectrum1hit.root","read");
	TH1F* BGO_sim_vetooff = (TH1F*) f->Get("S1hit");
	int rebin=4;
	BGO_sim->Divide(BGO_sim_vetooff);
	BGO_sim->Rebin(rebin);
	BGO_sim->Scale(1./rebin);
	BGO_sim->SetLineColor(kBlue);

	TFile* f = new TFile("VetoEfficiencyInstrument/BGO_contamination_3_14.root","read");
	TH1F* BGO_meas = (TH1F*) f->Get("hist_contamination");
	BGO_meas->Rebin(rebin);
	BGO_meas->Scale(1./rebin);
	BGO_meas->SetLineColor(kRed);

	TCanvas* c_BGO = new TCanvas();
	BGO_sim->SetTitle("BGO Contamination");
	BGO_sim->GetYaxis()->SetTitle("Fraction");
	BGO_sim->Draw("hist");
	BGO_meas->Draw("hist,same");
	BGO_sim->GetXaxis()->SetRangeUser(0,1000);




	TFile* f = new TFile("Fast/VetoOn/G4spectrum1hit.root","read");
	TH1F* FAST_sim = (TH1F*) f->Get("S1hit");
	TFile* f = new TFile("Fast/VetoOff/G4spectrum1hit.root","read");
	TH1F* FAST_sim_vetooff = (TH1F*) f->Get("S1hit");
	rebin=8;
	FAST_sim->Divide(FAST_sim_vetooff);
	FAST_sim->Rebin(rebin);
	FAST_sim->Scale(1./rebin);
	FAST_sim->SetLineColor(kBlue);

	TFile* f = new TFile("VetoEfficiencyInstrument/fast_contamination_3_14.root","read");
	TH1F* FAST_meas = (TH1F*) f->Get("hist_contamination");
	FAST_meas->Rebin(rebin);
	FAST_meas->Scale(1./rebin);
	FAST_meas->SetLineColor(kRed);

	TCanvas* c_FAST = new TCanvas();
	FAST_sim->SetTitle("FAST Contamination");
	FAST_sim->GetYaxis()->SetTitle("Fraction");
	FAST_sim->Draw("hist");
	FAST_meas->Draw("hist,same");
	FAST_sim->GetXaxis()->SetRangeUser(0,3000);




	TFile* f = new TFile("Slow/VetoOn/G4spectrum1hit.root","read");
	TH1F* SLOW_sim = (TH1F*) f->Get("S1hit");
	TFile* f = new TFile("Slow/VetoOff/G4spectrum1hit.root","read");
	TH1F* SLOW_sim_vetooff = (TH1F*) f->Get("S1hit");
	rebin=4;
	SLOW_sim->Divide(SLOW_sim_vetooff);
	SLOW_sim->Rebin(rebin);
	SLOW_sim->Scale(1./rebin);
	SLOW_sim->SetLineColor(kBlue);

	TFile* f = new TFile("VetoEfficiencyInstrument/SLOW_mid_contamination_3_14.root","read");
	TH1F* SLOW_meas = (TH1F*) f->Get("hist_contamination");
	SLOW_meas->Rebin(rebin);
	SLOW_meas->Scale(1./rebin);
	SLOW_meas->SetLineColor(kRed);

	TCanvas* c_SLOW = new TCanvas();
	SLOW_sim->SetTitle("SLOW sim contamination");
	SLOW_sim->GetYaxis()->SetTitle("Fraction");
	SLOW_sim->Draw("hist");
	SLOW_meas->Draw("hist,same");
	SLOW_sim->GetXaxis()->SetRangeUser(0,1000);
}

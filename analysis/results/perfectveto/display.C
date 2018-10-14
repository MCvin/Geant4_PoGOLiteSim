void display(){

	TFile* f = new TFile("crab/G4ringDistribution2hits.root","read");
	TH1F* crab_sim = (TH1F*) f->Get("RD2");
	TFile* f = new TFile("gammaBG/G4ringDistribution2hits.root","read");
	TH1F* gammaBG_sim = (TH1F*) f->Get("RD2");
	TFile* f = new TFile("neutronBG/G4ringDistribution2hits.root","read");
	TH1F* neutronBG_sim = (TH1F*) f->Get("RD2");

	crab_sim->Add(gammaBG_sim);
	crab_sim->Add(neutronBG_sim);

	TCanvas* c_sim = new TCanvas();
	crab_sim->Draw();

}

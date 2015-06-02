#include <TH2.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TString.h>
#include <TBranch.h>
#include <TTree.h>
#include <TImage.h>
#include <TCanvas.h>
int inE(double eta){
	if (abs(eta)>1.566 && abs(eta)<2.5) return 1;
	return 0;
}
int inB(double eta){
	if (abs(eta)<1.4442) return 1;
	return 0;
}

void pnger(int i){
	TH2D* hist;
	TH2D* hist2;
	TFile* f;
	TTree* h;
	TFile* output;
	TCanvas* c;
	TImage* img;
	float wpx[3]; float wpy[3]; float wpz[3]; float we[3];
	TBranch* b_wpx; TBranch* b_wpy; TBranch* b_wpz; TBranch* b_we;
	for (int dummy = 0; dummy < 1; dummy++){
		ostringstream stream; TString str; ostringstream stream2; TString str2;
		if (i == 0) int num = 1;
		else int num = i + 100;
		stream<<"/uscms_data/d3/hn99/cteq6_rootfiles/ggo_ntuple"<<num<<".root"; str = stream.str();
		std::cout<<"Accessing "<<str.Data()<<std::endl;
		f = new TFile(str.Data());
		stream.str(""); stream<<"EE2D"<<num; str = stream.str();
		stream2.str(""); stream2<<"Endcap-Endcap M-R Histogram for Eigenvector Set "<<i; str2 = stream2.str();
		hist = new TH2D(str.Data(),str2.Data(),172,0.0,8600.0,50,0.0,9.0);
		stream.str(""); stream<<"BB2D"<<num; str=stream.str();
		stream2.str(""); stream2<<"Barrel-Barrel M-R Histogram for Eigenvector Set "<<i; str2 = stream2.str();
		hist2 = new TH2D(str.Data(),str2.Data(),172,0.0,8600.0,50,0.0,9.0);
		h = (TTree*)f->Get("h10");
		h->SetBranchAddress("wpx",wpx,&b_wpx); h->SetBranchAddress("wpy",wpy,&b_wpy); h->SetBranchAddress("wpz",wpz,&b_wpz); h->SetBranchAddress("we",we,&b_we);
		long int numEvents = h->GetEntriesFast();
		for (long int j = 0; j < numEvents; j++){
			h->LoadTree(j);
			h->GetEntry(j);
			TLorentzVector v1,v2,total; double R;
			v1.SetPxPyPzE(wpx[0],wpy[0],wpz[0],we[0]); v2.SetPxPyPzE(wpx[1],wpy[1],wpz[1],we[1]); total=v1+v2;
			if (inE(v1.Eta())&&inE(v2.Eta())){
				R = sqrt((v1.Eta()-v2.Eta())**2+(v1.Phi()-v2.Phi())**2);
				hist->Fill(total.M(),R);
			}
			else if (inB(v1.Eta())&&inB(v2.Eta())){
				R = sqrt((v1.Eta()-v2.Eta())**2+(v1.Phi()-v2.Phi())**2);
				hist2->Fill(total.M(),R);
			}
		}
		stream.str(""); stream<<"/uscms_data/d3/hn99/cteq6_rootfiles/ggt_ntuple"<<num<<".root"; str = stream.str();
		std::cout<<"Accessing "<<str.Data()<<std::endl;
		f = new TFile(str.Data());
		h = (TTree*)f->Get("h10");
		h->SetBranchAddress("wpx",wpx,&b_wpx); h->SetBranchAddress("wpy",wpy,&b_wpy); h->SetBranchAddress("wpz",wpz,&b_wpz); h->SetBranchAddress("we",we,&b_we);
		long int numEvents = h->GetEntriesFast();
		for (long int j = 0; j < numEvents; j++){
			h->LoadTree(j);
			h->GetEntry(j);
			TLorentzVector v1,v2, total; double R;
			v1.SetPxPyPzE(wpx[0],wpy[0],wpz[0],we[0]); v2.SetPxPyPzE(wpx[1],wpy[1],wpz[1],we[1]); total=v1+v2;
			if (inE(v1.Eta())&&inE(v2.Eta())){
				R = sqrt((v1.Eta()-v2.Eta())**2+(v1.Phi()-v2.Phi())**2);
				hist->Fill(total.M(),R);
			}
			else if (inB(v1.Eta())&&inB(v2.Eta())){
				R = sqrt((v1.Eta()-v2.Eta())**2+(v1.Phi()-v2.Phi())**2);
				hist2->Fill(total.M(),R);
			}
		}
		c = new TCanvas; c->Divide(2,1); c->cd(1); hist->Draw(); c->cd(2); hist2->Draw();
		img=TImage::Create();
		img->FromPad(c);
		stream.str(""); stream<<"set"<<i<<".png"; str = stream.str();
		img->WriteImage(str.Data()); c->Close();
	}	
}

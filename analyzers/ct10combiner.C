#include <TString.h>
#include <TFile.h>
#include <TH2.h>
void combiner(){
	TFile f = TFile("diphox_ct10_completed.root","recreate");
	TH1D* ee;
	TH1D* bb;
	TH1D* be;
	TH1D* se;
	TFile* in;
	for (int i = 0; i < 53; i++){
		int num = i+100;
		ostringstream stream; TString str;
		stream<<num<<".root"; str = stream.str();
		in = new TFile(str.Data());
		stream.str(""); stream<<"EE "<<num; str = stream.str();
		ee = (TH1D*)in->Get(str.Data());
		stream.str(""); stream<<"BB "<<num; str = stream.str();
		bb = (TH1D*)in->Get(str.Data());
		stream.str(""); stream<<"BE "<<num; str = stream.str();
		be = (TH1D*)in->Get(str.Data());
		stream.str(""); stream<<"SE "<<num; str = stream.str();
		se = (TH1D*)in->Get(str.Data());
		stream.str(""); stream<<"SE "<<num; str = stream.str();
		stream.str(""); stream<<"BB"<<num; str = stream.str(); bb->SetName(str.Data());
		stream.str(""); stream<<"EE"<<num; str = stream.str(); ee->SetName(str.Data());
		stream.str(""); stream<<"BE"<<num; str = stream.str(); be->SetName(str.Data());
		stream.str(""); stream<<"SE"<<num; str = stream.str(); se->SetName(str.Data());
		stream.str(""); stream<<"Barrel-Barrel Diphoton Mass Distribution for Eigenvector Set "<<i; str = stream.str(); bb->SetTitle(str.Data());
		stream.str(""); stream<<"Endcap-Endcap Diphoton Mass Distribution for Eigenvector Set "<<i; str = stream.str(); ee->SetTitle(str.Data());
		stream.str(""); stream<<"Barrel-Endcap Diphoton Mass Distribution for Eigenvector Set "<<i; str = stream.str(); be->SetTitle(str.Data());
		stream.str(""); stream<<"Same-Endcap Diphoton Mass Distribution for Eigenvector Set "<<i; str = stream.str(); se->SetTitle(str.Data());
		f.cd();
		ee->Write(); bb->Write(); be->Write(); se->Write();
	}
}

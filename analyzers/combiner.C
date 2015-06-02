#include <TString.h>
#include <TFile.h>
#include <TH2.h>
void combiner(){
	TFile f = TFile("diphox_1GeVbin.root","recreate");
	TH2D* ee;
	TH2D* bb;
	TH2D* be;
	TFile* in;
	for (int i = 0; i < 41; i++){
		if (i == 0) int num =1;
		else int num = i+100;
		ostringstream stream; TString str;
		stream<<num<<".root"; str = stream.str();
		in = new TFile(str.Data());
		stream.str(""); stream<<"EE "<<num; str = stream.str();
		ee = (TH2D*)in->Get(str.Data());
		stream.str(""); stream<<"BB "<<num; str = stream.str();
		bb = (TH2D*)in->Get(str.Data());
		stream.str(""); stream<<"BE "<<num; str = stream.str();
		be = (TH2D*)in->Get(str.Data());
		stream.str(""); stream<<"BB"<<num; str = stream.str(); bb.SetName(str.Data());
		stream.str(""); stream<<"EE"<<num; str = stream.str(); ee.SetName(str.Data());
		stream.str(""); stream<<"BE"<<num; str = stream.str(); be.SetName(str.Data());
		stream.str(""); stream<<"Barrel-Barrel Diphoton Mass Distribution for Eigenvector Set "<<i; str = stream.str(); bb.SetTitle(str.Data());
		stream.str(""); stream<<"Endcap-Endcap Diphoton Mass Distribution for Eigenvector Set "<<i; str = stream.str(); ee.SetTitle(str.Data());
		stream.str(""); stream<<"Barrel-Endcap Diphoton Mass Distribution for Eigenvector Set "<<i; str = stream.str(); be.SetTitle(str.Data());
		f.cd();
		ee->Write(); bb->Write(); be->Write();
	}
}

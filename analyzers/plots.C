#include <TFile.h>
#include <TImage.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TPad.h>
#include <TLegend.h>
#include <TLegendEntry.h>

void plots(int type, int ignvctr){
	TFile f("../diphox_completed.root");
	TCanvas* c = new TCanvas; 
	TPad p1;
	p1.SetLogy();
	c->cd(); p1.Draw(); 
	TH1D h1, h2, nom;
	ostringstream stream; TString str; TString imgName;
	if (ignvctr == 0) int num = 1;
	else int num = 2*ignvctr + 99;
	if (type == 0){
		nom = (TH1D)f.Get("BB1"); nom.SetLineColor(1); nom.SetTitle("BB Nominal");
		stream.str(""); stream<<"BB"<<num; str = stream.str(); h1 = (TH1D)f.Get(str.Data()); h1.SetLineColor(2); 
		stream.str(""); stream<<"BB"<<num+1; str = stream.str(); h2 = (TH1D)f.Get(str.Data()); h2.SetLineColor(4); 
		std::cout<<"Done generating histos."<<std::endl;
		stream.str(""); stream<<"Barrel-Barrel Diphoton Mass Distributions for Eigenvector "<<ignvctr; str = stream.str(); h1.SetTitle(str.Data());
		stream.str(""); stream<<"BBset"<<ignvctr<<".png"; imgName = stream.str();
	}
	else if (type == 1){
		nom = (TH1D)f.Get("EE1"); nom.SetLineColor(1);
		stream.str(""); stream<<"EE"<<num; str = stream.str(); h1 = (TH1D)f.Get(str.Data()); h1.SetLineColor(2);
		stream.str(""); stream<<"EE"<<num+1; str = stream.str(); h2 = (TH1D)f.Get(str.Data()); h2.SetLineColor(4);
		std::cout<<"Done generating histos."<<std::endl;
		stream.str(""); stream<<"Endcap-Endcap Diphoton Mass Distributions for Eigenvector "<<ignvctr; str = stream.str(); h1.SetTitle(str.Data());
		stream.str(""); stream<<"EEset"<<ignvctr<<".png"; imgName = stream.str();
	}
	else{
		nom = (TH1D)f.Get("BE1"); nom.SetLineColor(1);
		stream.str(""); stream<<"BE"<<num; str = stream.str(); h1 = (TH1D)f.Get(str.Data()); h1.SetLineColor(2);
		stream.str(""); stream<<"BE"<<num+1; str = stream.str(); h2 = (TH1D)f.Get(str.Data()); h2.SetLineColor(4);
		std::cout<<"Done generating histos."<<std::endl;
		stream.str(""); stream<<"Barrel-Endcap Diphoton Mass Distributions for Eigenvector "<<ignvctr; str = stream.str(); h1.SetTitle(str.Data());
		stream.str(""); stream<<"BEset"<<ignvctr<<".png"; imgName = stream.str();
	}
	p1.cd(); h1.Draw(); h2.Draw("SAME"); nom.Draw("SAME"); 
	p1.BuildLegend(0.682011,0.725738,0.981322,0.936709); 
	img=TImage::Create(); img->FromPad(c); img->WriteImage(imgName.Data());
	c->Close(); 
}

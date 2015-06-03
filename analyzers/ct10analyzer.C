#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <TH1.h>
#include <TBranch.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TImage.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;	
int inB(double eta){
	if (abs(eta)<1.4442) return 1;
	return 0;
}
int inE(double eta){
	if (abs(eta)<2.5 && abs(eta)>1.566) return 1;
	return 0;
}
int inSameE(double eta1,double eta2){
	if (inE(eta1) && inE(eta2) && eta1/eta2>0) return 1;
	return 0;
}
void process(int num){
	float wpx[3];
	float wpy[3];
	float wpz[3];
	float we[3];
	int NBINS=172;
	TBranch* b_wpx;
	TBranch* b_wpy;
	TBranch* b_wpz;
	TBranch* b_we;
	TFile output;
	TFile* h;
	TTree* h10;
	TH1D* ee;
	TH1D* bb;
	TH1D* be;
	TH1D* se;
	ostringstream nums;
	ostringstream stream;
	ostringstream stream2;
	ostringstream stream3;
	TString str;
	TString str2;
	TString str3;
	TCanvas* c;
	TImage* img;
	stream.str(""); stream.clear(); stream2.str(""); stream2.clear();
	stream<<num;
	std::cout<<"Processing 1F for n="+stream.str()<<std::endl;
	stream.str(""); stream.clear();
	stream<<"/uscms_data/d3/hn99/cteq6/ggo_ct10"<<num<<".root";
	str = stream.str();
	std::cout<<"Reading from "<<str.Data()<<std::endl;
	h = new TFile(str.Data());
	h10 = (TTree*)h->Get("h10");
	h10->SetBranchAddress("wpx",wpx,&b_wpx);
	h10->SetBranchAddress("wpy",wpy,&b_wpy);
	h10->SetBranchAddress("wpz",wpz,&b_wpz);
	h10->SetBranchAddress("we",we,&b_we);
	stream.str("");
	stream.clear();
	stream<<"EE "<<num;
	stream2<<"Endcap-Endcap Invariant Mass for n="<<num;
	str = stream.str();
	str2 = stream2.str();
	ee = new TH1D(str.Data(),str2.Data(),NBINS,0.0,8600.0);
	stream.str(""); stream.clear(); stream<<"SE "<<num; str = stream.str();
	stream2.str(""); stream2.clear(); stream2<<"Same Endcap Invariant Mass for n="<<num; str2 = stream.str();
	se = new TH1D(str.Data(),str2.Data(),NBINS,0.0,8600.0);
	stream.str("");
	stream.clear();
	stream2.str("");
	stream2.clear();
	stream<<"BB "<<num;
	stream2<<"Barrel-Barrel Invariant Mass for n="<<num;
	str = stream.str();
	str2 = stream2.str();
	bb = new TH1D(str.Data(),str2.Data(),NBINS,0.0,8600.0);
	stream.str("");
	stream2.str("");
	stream.clear();
	stream2.clear();
	stream2<<"Barrel-Endcap Invariant Mass for n="<<num;
	stream<<"BE "<<num;
	str = stream.str();
	str2 = stream2.str();
	be = new TH1D(str.Data(),str2.Data(),NBINS,0.0,8600.0);
	long int numEvents = h10->GetEntries();
	for (long int j = 0; j < numEvents; j++){
		if (h10==0) break;
		long int ientry = h10->LoadTree(j);
		if (ientry < 0) break;
		h10->GetEntry(j);
		TLorentzVector v1;
		TLorentzVector v2;
		TLorentzVector total;
		v1.SetPxPyPzE(wpx[0],wpy[0],wpz[0],we[0]);
		v2.SetPxPyPzE(wpx[1],wpy[1],wpz[1],we[1]);
		total = v1+v2;
		double e1 = v1.Eta();
		double e2 = v2.Eta();
		if (inB(e1) && inB(e2)) bb->Fill(total.M());
		else if ((inB(e1) && inE(e2))||(inB(e2)&&inE(e1))) be->Fill(total.M());
		else if (inE(e1) && inE(e2)) ee->Fill(total.M());
		if (inSameE(e1,e2)) se->Fill(total.M());
	}
	stream.str(""); stream.clear();
	stream<<num;
	std::cout<<"Processing 2F for n="+stream.str()<<std::endl;
	stream.str("");
	stream.clear();
	stream<<"/uscms_data/d3/hn99/cteq6/ggt_ct10"<<num<<".root";
	str = stream.str();
	std::cout<<"Reading from "<<str.Data()<<std::endl;
	h = new TFile(str.Data());
	if (num!=126){
	h10 = (TTree*)h->Get("h10");
	h10->SetBranchAddress("wpx",wpx,&b_wpx);
	h10->SetBranchAddress("wpy",wpy,&b_wpy);
	h10->SetBranchAddress("wpz",wpz,&b_wpz);
	h10->SetBranchAddress("we",we,&b_we);
	numEvents = h10->GetEntries();
	for (long int j = 0; j < numEvents; j++){
		try{
		if (h10==0) break;
		long int ientry = h10->LoadTree(j);
		if (ientry < 0) break;
		h10->GetEntry(j);
		TLorentzVector v1;
		TLorentzVector v2;
		TLorentzVector total;
		v1.SetPxPyPzE(wpx[0],wpy[0],wpz[0],we[0]);
		v2.SetPxPyPzE(wpx[1],wpy[1],wpz[1],we[1]);
		total = v1+v2;
		double e1 = v1.Eta();
		double e2 = v2.Eta();
		if (inB(e1) && inB(e2)) bb->Fill(total.M());
		else if ((inB(e1) && inE(e2))||(inB(e2)&&inE(e1))) be->Fill(total.M());
		else if (inE(e1) && inE(e2)) ee->Fill(total.M());
		if (inSameE(e1,e2)) se->Fill(total.M());
		}catch(int e){std::cout<<"Caught bad entry."<<endl; continue;}
	}}
	stream.str(""); stream << num << ".root"; str = stream.str(); 
	TFile f = TFile(str.Data(),"RECREATE");
	f.cd();
	ee->Sumw2(); bb->Sumw2(); be->Sumw2(); se->Sumw2();
	ee->Write(); bb->Write(); be->Write(); se->Write();
	//stream.str(""); stream<<"EE "<<num<<".png"; stream2.str(""); stream2<<"BB "<<num<<".png"; stream3.str(""); stream3<<"BE "<<num<<".png";
	//str=stream.str(); str2=stream2.str(); str3=stream3.str();
	//c = new TCanvas; ee->Draw(); gSystem->ProcessEvents(); img=TImage::Create(); img->FromPad(c); img->WriteImage(str.Data()); c->Close();
	//c = new TCanvas; bb->Draw(); gSystem->ProcessEvents(); img=TImage::Create(); img->FromPad(c); img->WriteImage(str2.Data()); c->Close();
	//c = new TCanvas; be->Draw(); gSystem->ProcessEvents(); img=TImage::Create(); img->FromPad(c); img->WriteImage(str3.Data()); c->Close();
	//c->Close(); f.Close(); delete ee; delete bb; delete be; delete h; 
}
void a4(int i){
	int num;
	for (int c= 0; c < 1; c++){
		int num = i+100;
		process(num);
	}
}

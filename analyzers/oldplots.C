#include <TString.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TImage.h>
#include <TH1.h>

void plots(int it){
	if (it==0) int num = 1;
	else int num = it +100;
	TFile* source = new TFile("../diphox_completed.root");
	TH1D* eeNom = (TH1D*)source->Get("EE1"); eeNom->SetLineColor(1);
	TH1D* bbNom = (TH1D*)source->Get("BB1"); bbNom->SetLineColor(1);
	TH1D* beNom = (TH1D*)source->Get("BE1"); beNom->SetLineColor(1);
	TH1D* ee[8]; TH1D* bb[8], TH1D* be[8];
	TPad* pads[12];
	TCanvas* c[3];
	TImage* img[3];
	//for (int it = 1; it <= 33; it+=8){
		ostringstream stream; TString str;
		for (int j = 0; j<8; j++){
			stream.str(""); stream<<"BB"<<num+j; str = stream.str(); bb[j]=(TH1D*)source->Get(str.Data()); 
			stream.str(""); stream<<"EE"<<num+j; str = stream.str(); ee[j]=(TH1D*)source->Get(str.Data()); 
			stream.str(""); stream<<"BE"<<num+j; str = stream.str(); be[j]=(TH1D*)source->Get(str.Data());
			if (j%2==0){
				bb[j]->SetLineColor(2); be[j]->SetLineColor(2); ee[j]->SetLineColor(2);
			}
			else{
				bb[j]->SetLineColor(4); be[j]->SetLineColor(4); ee[j]->SetLineColor(4);
			} 
		}
		for (TPad* pad : pads){
			pad = new TPad(); pad->SetLogy();
		}
		for (int j = 0; j<3;j++){
			c[j] = new TCanvas;
			c[j]->Divide(2,2);
			img[j] = TImage::Create();
		}
		for (int j = 0; j<8;j+=2){
			stream.str(""); stream<<"Barrel-Barrel Diphoton Mass Distributions for Eigenvector "<<(j+it+1)/2; str = stream.str();
			bb[j]->SetTitle(str.Data());
			stream.str(""); stream<<"Barrel-Endcap Diphoton Mass Distributions for Eigenvector "<<(j+it+1)/2; str = stream.str();
			be[j]->SetTitle(str.Data());
			stream.str(""); stream<<"Endcap-Endcap Diphoton Mass Distributions for Eigenvector "<<(j+it+1)/2; str = stream.str();
			ee[j]->SetTitle(str.Data());
		}
		pad[0]->cd(); bb[0]->Draw(); bb[1]->Draw("SAME"); bbNom->Draw("SAME"); c[0]->cd(1); pad[0]->BuildLegend(); pad[0]->Draw();
		pad[1]->cd(); bb[2]->Draw(); bb[3]->Draw("SAME"); bbNom->Draw("SAME"); c[0]->cd(2); pad[1]->BuildLegend(); pad[1]->Draw();
		pad[2]->cd(); bb[4]->Draw(); bb[5]->Draw("SAME"); bbNom->Draw("SAME"); c[0]->cd(3); pad[2]->BuildLegend(); pad[2]->Draw();
		pad[3]->cd(); bb[6]->Draw(); bb[7]->Draw("SAME"); bbNom->Draw("SAME"); c[0]->cd(4); pad[3]->BuildLegend(); pad[3]->Draw();
		pad[4]->cd(); be[0]->Draw(); be[1]->Draw("SAME"); beNom->Draw("SAME"); c[1]->cd(1); pad[4]->BuildLegend(); pad[4]->Draw();
		pad[5]->cd(); be[2]->Draw(); be[3]->Draw("SAME"); beNom->Draw("SAME"); c[1]->cd(2); pad[5]->BuildLegend(); pad[5]->Draw();
		pad[6]->cd(); be[4]->Draw(); be[5]->Draw("SAME"); beNom->Draw("SAME"); c[1]->cd(3); pad[6]->BuildLegend(); pad[6]->Draw();
		pad[7]->cd(); be[6]->Draw(); be[7]->Draw("SAME"); beNom->Draw("SAME"); c[1]->cd(4); pad[7]->BuildLegend(); pad[7]->Draw();
		pad[8]->cd(); ee[0]->Draw(); ee[1]->Draw("SAME"); eeNom->Draw("SAME"); c[2]->cd(1); pad[8]->BuildLegend(); pad[8]->Draw();
		pad[9]->cd(); ee[2]->Draw(); ee[3]->Draw("SAME"); eeNom->Draw("SAME"); c[2]->cd(2); pad[9]->BuildLegend(); pad[9]->Draw();
		pad[10]->cd(); ee[4]->Draw(); ee[5]->Draw("SAME"); eeNom->Draw("SAME"); c[2]->cd(3); pad[10]->BuildLegend(); pad[10]->Draw();
		pad[11]->cd(); ee[6]->Draw(); ee[7]->Draw("SAME"); eeNom->Draw("SAME"); c[2]->cd(4); pad[11]->BuildLegend(); pad[11]->Draw();
		img[0]->FromPad(c[0]); img[1]->FromPad(c[1]); img[2]->FromPad(c[2]);
		stream.str(""); stream<<"BBset"<<it; str = stream.str(); img[0]->WriteImage(str.Data());
		stream.str(""); stream<<"BEset"<<it; str = stream.str(); img[1]->WriteImage(str.Data());
		stream.str(""); stream<<"EEset"<<it; str = stream.str(); img[2]->WriteImage(str.Data());
	//}
}

#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <TCanvas.h>
#include <TImage.h>
#include <TPad.h>
void report(const char* messg){
	std::cout<<messg<<std::endl;
}
void reportDouble(double i){
	std::cout<<i<<std::endl;
}
void env(int type){
	int inp;
	TFile* f = new TFile("../diphox_1GeVbin.root");
	TFile test("test.root","update");
	TH1D nom;
	TH1D* h;
	TH1D upperThres("up","Upper Excursion",2000,0.0,8600.0); 
	TH1D lowerThres("down","Lower Excursion",2000,0.0,8600.0);
	ostringstream stream; TString str;
	//TCanvas* c = new TCanvas;
	//c->cd();
	//TPad p; p.SetLogy(); p.Draw();
	//TImage* img = TImage::Create();

	if (type == 0){
		upperThres.SetTitle("Barrel-Barrel Excursion Envelope"); upperThres.GetXaxis()->SetTitle("Diphoton Invariant Mass (GeV/c^2)");
		nom = (TH1D)f->Get("BB1");
		report("Read nominal.");
		nom.SetTitle("Barrel-Barrel Diphoton Mass Distribution"); 
		report("Reset title.");
		nom.GetSumw2()->Set(0);
		report("Removed Sumw2");
		std::cout<<"Reading eigenvector set histograms."<<std::endl;
		//for (int i = 1; i <= 40; i++){
		//	stream.str(""); report("Cleared stream."); stream<<"BB"<<(i+100); str = stream.str(); report(str.Data()); h[i-1]=(TH1D)f.Get(str.Data());
		//}
		std::cout<<"Done reading eigenvector set histograms."<<std::endl;
		double move;
		for (int i = 0; i < 2000; i++){
			move = 0;
			for (int j = 0; j < 40; j++){
				stream.str(""); stream<<"BB"<<(j+101); str = stream.str();
				h = (TH1D*)f->Get(str.Data());
				if (abs(nom.GetBinContent(i)-h->GetBinContent(i))>move) move=abs(nom.GetBinContent(i)-h->GetBinContent(i));
			}
			reportDouble(move);
			upperThres.AddBinContent(i,nom.GetBinContent(i)+move);
			lowerThres.AddBinContent(i,nom.GetBinContent(i)-move);
		}
		upperThres.SetLineColor(kBlue); upperThres.SetFillColor(kBlue);
		lowerThres.SetLineColor(kBlue); lowerThres.SetFillColor(kWhite);
		//p.cd();
		//nom.Draw(); gSystem->ProcessEvents();
		//upperThres.Draw("SAME"); gSystem->ProcessEvents(); lowerThres.Draw("SAME"); gSystem->ProcessEvents();
		//img->FromPad(c); img->WriteImage("test.png");
		test.cd(); upperThres.Write(); lowerThres.Write();
	}
	else if (type == 1){	
		upperThres.SetTitle("Barrel-Endcap Excursion Envelope"); upperThres.GetXaxis()->SetTitle("Diphoton Invariant Mass (GeV/c^2)");
		nom = (TH1D)f->Get("BE1");
		report("Read nominal.");
		nom.SetTitle("Barrel-Endcap Diphoton Mass Distribution"); 
		report("Reset title.");
		nom.GetSumw2()->Set(0);
		report("Removed Sumw2");
		std::cout<<"Reading eigenvector set histograms."<<std::endl;
		//for (int i = 1; i <= 40; i++){
		//	stream.str(""); report("Cleared stream."); stream<<"BB"<<(i+100); str = stream.str(); report(str.Data()); h[i-1]=(TH1D)f.Get(str.Data());
		//}
		std::cout<<"Done reading eigenvector set histograms."<<std::endl;
		double move;
		for (int i = 0; i < 2000; i++){
			move = 0;
			for (int j = 0; j < 40; j++){
				stream.str(""); stream<<"BE"<<(j+101); str = stream.str();
				h = (TH1D*)f->Get(str.Data());
				if (abs(nom.GetBinContent(i)-h->GetBinContent(i))>move) move=abs(nom.GetBinContent(i)-h->GetBinContent(i));
			}
			reportDouble(move);
			upperThres.AddBinContent(i,nom.GetBinContent(i)+move);
			lowerThres.AddBinContent(i,nom.GetBinContent(i)-move);
		}
		upperThres.SetLineColor(kBlue); upperThres.SetFillColor(kBlue);
		lowerThres.SetLineColor(kBlue); lowerThres.SetFillColor(kWhite);
		//p.cd();
		//nom.Draw(); gSystem->ProcessEvents();
		//upperThres.Draw("SAME"); gSystem->ProcessEvents(); lowerThres.Draw("SAME"); gSystem->ProcessEvents();
		//img->FromPad(c); img->WriteImage("test.png");
		test.cd(); upperThres.Write(); lowerThres.Write();
	}
	else{
		upperThres.SetTitle("Endcap-Endcap Excursion Envelope"); upperThres.GetXaxis()->SetTitle("Diphoton Invariant Mass (GeV/c^2)");
		nom = (TH1D)f->Get("EE1");
		report("Read nominal.");
		nom.SetTitle("Endcap-Endcap Diphoton Mass Distribution"); 
		report("Reset title.");
		nom.GetSumw2()->Set(0);
		report("Removed Sumw2");
		std::cout<<"Reading eigenvector set histograms."<<std::endl;
		//for (int i = 1; i <= 40; i++){
		//	stream.str(""); report("Cleared stream."); stream<<"BB"<<(i+100); str = stream.str(); report(str.Data()); h[i-1]=(TH1D)f.Get(str.Data());
		//}
		//std::cout<<"Done reading eigenvector set histograms."<<std::endl;
		double move;
		for (int i = 0; i < 2000; i++){
			move = 0;
			for (int j = 0; j < 40; j++){
				stream.str(""); stream<<"EE"<<(j+101); str = stream.str();
				h = (TH1D*)f->Get(str.Data());
				if (abs(nom.GetBinContent(i)-h->GetBinContent(i))>move) move=abs(nom.GetBinContent(i)-h->GetBinContent(i));
			}
			reportDouble(move);
			upperThres.AddBinContent(i,nom.GetBinContent(i)+move);
			if (nom.GetBinContent(i)>=move){
				lowerThres.AddBinContent(i,nom.GetBinContent(i)-move);
			}
			lowerThres.AddBinContent(i,0.0);
		}
		upperThres.SetLineColor(kBlue); upperThres.SetFillColor(kWhite);
		lowerThres.SetLineColor(kBlue); lowerThres.SetFillColor(kBlue);
		//p.cd();
		//nom.Draw(); gSystem->ProcessEvents();
		//upperThres.Draw("SAME"); gSystem->ProcessEvents(); lowerThres.Draw("SAME"); gSystem->ProcessEvents();
		//img->FromPad(c); img->WriteImage("test.png");
		test.cd(); upperThres.Write(); lowerThres.Write();
	}
}

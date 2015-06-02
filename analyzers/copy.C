#include <TH1.h>
#include <TFile.h>

void copy(){
	TFile f("../diphox_completed.root");
	TFile t("test.root","recreate");
	TH1D h,newh;
	h = (TH1D)f.Get("BB1");
	newh = TH1D("newh","newh",172,0.0,8600.0);
	for (int i = 0; i < 172; i++){
		newh.AddBinContent(i,h.GetBinContent(i));
	}
	t.cd();
	newh.Write();
}

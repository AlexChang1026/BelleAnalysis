#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
yieldfit(int number)
{
  using namespace RooFit; 

  TCanvas *c1 = new TCanvas("c1","",700,500);

  char filename[200];

  sprintf(filename,"%s%d%s","pull_gsim",number,".root");

  TChain *chn = new TChain("h1");
  chn -> Add(filename); 

  int highrange = 270-20*(8-number) ;
  int lowrange = 20-20*(8-number) ; 

  RooRealVar Yield("Yield","",lowrange,highrange);

  RooDataSet data("data","data",chn,RooArgSet(Yield));

  RooRealVar mean("mean","mean",150,-10,270);
  RooRealVar width("width","width",20,10,40);
  
  RooGaussian gaus("gaus","",Yield,mean,width);

  RooFitResult *res = gaus.fitTo(data,Minos(true));

  RooPlot *pull_pdf = Yield.frame(Bins(80));

  data.plotOn(pull_pdf);
  gaus.plotOn(pull_pdf);

  pull_pdf ->SetTitleSize(0.05,"x");
  pull_pdf ->SetTitleOffset(0.8,"x");
  pull_pdf ->SetTitle("");
  pull_pdf ->GetXaxis()->SetTitle("N_{sig}");
  pull_pdf -> Draw();
 
  char meanl[40]; 
  char widthl[40];
  char file[200];
  char dropbox[200];

  sprintf (meanl,"%s%.2f%s%.2f","mean = ",mean.getVal(),"#pm",mean.getError());
  sprintf (widthl,"%s%.2f%s%.2f","width = ",width.getVal(),"#pm",width.getError());
  sprintf (file,"%s%d%s","yield_gsim",number,"_bin200.eps");
  sprintf (dropbox,"%s%d%s","./dropbox_uploader2.sh upload yield_gsim",number,"_bin200.eps /");

  TLegend *legend = new TLegend(0.1,0.7,0.4,0.9) ;
  
  legend -> AddEntry((TObject*)0,meanl,"");
  legend -> AddEntry((TObject*)0,widthl,"");

  legend -> SetTextSize(0.037);
  legend -> Draw();

  c1 ->SaveAs(file);
  system(dropbox);





}

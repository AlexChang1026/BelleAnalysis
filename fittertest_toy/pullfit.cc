#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
pullfit(int number)
{
  using namespace RooFit; 

  char file[200];
  sprintf(file,"%s%d%s","pull_gsim",number,".root");


  TCanvas *c1 = new TCanvas("c1","",700,500);

  TChain *chn = new TChain("h1");
  chn -> Add(file); 

  RooRealVar pull("pull","",-6,6);
  RooRealVar pull_plambda("pull_plambda","",-6,6);

  RooDataSet data("data","data",chn,RooArgSet(pull));

  RooRealVar mean("mean","mean",0,-1,1.);
  RooRealVar width("width","width",1.,0.5,1.5);
  
  RooGaussian gaus("gaus","",pull,mean,width);

  RooFitResult *res = gaus.fitTo(data,Minos(true));

  RooPlot *pull_pdf = pull.frame(Bins(100));

  data.plotOn(pull_pdf);
  gaus.plotOn(pull_pdf);

  pull_pdf ->SetTitle("");
  pull_pdf ->GetXaxis()->SetTitle("B^{0} #rightarrow p#bar{#Sigma}^{0}#pi^{-} Pull");
  pull_pdf ->SetTitleSize(0.05,"x");
  pull_pdf ->SetTitleOffset(0.8,"x");
  pull_pdf -> Draw();
 
  char meanl[40]; 
  char widthl[40];

  char plotname[200];
  char dropbox[200];
 
  sprintf (meanl,"%s%.3f%s%.3f","mean = ",mean.getVal(),"#pm",mean.getError());
  sprintf (widthl,"%s%.3f%s%.3f","width = ",width.getVal(),"#pm",width.getError());
  sprintf (plotname,"%s%d%s","pull_gsim",number,".eps");
  sprintf (dropbox,"%s%d%s","./dropbox_uploader2.sh upload pull_gsim",number,".eps /");


  TLegend *legend = new TLegend(0.1,0.7,0.4,0.9) ;
  
  legend -> AddEntry((TObject*)0,meanl,"");
  legend -> AddEntry((TObject*)0,widthl,"");
  legend -> SetTextSize(0.037);

  legend -> Draw();

  c1 ->SaveAs(plotname);
  system(dropbox);

}

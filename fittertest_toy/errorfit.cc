#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
errorfit(int number)
{
  using namespace RooFit; 

  TCanvas *c1 = new TCanvas("c1","",700,500);

  TChain *chn = new TChain("h1");

  char filename[50];

  sprintf(filename,"%s%d%s","pull_gsim",number,".root");

  chn -> Add(filename); 

  RooRealVar error("error","",13,30);
  RooRealVar error_plambda("error_plambda","",13,30);

  RooDataSet data("data","data",chn,RooArgSet(error_plambda));

  RooRealVar mean("mean","mean",15,10,27);
  RooRealVar width("width","width",1,0.,2.);
  
  RooGaussian gaus("gaus","",error_plambda,mean,width);

  RooFitResult *res = gaus.fitTo(data,Minos(true));

  RooPlot *pull_pdf = error_plambda.frame(Bins(30));

  data.plotOn(pull_pdf);
  gaus.plotOn(pull_pdf);

  pull_pdf ->SetTitleSize(0.05,"x");
  pull_pdf ->SetTitleOffset(0.8,"x");
  pull_pdf ->SetTitleOffset(1.2,"y");
  pull_pdf ->SetTitle("");
  pull_pdf ->GetXaxis()->SetTitle("error");
  pull_pdf -> Draw();
 
  char meanl[40]; 
  char widthl[40];
  char file[200];
  char dropbox[200];

  sprintf (meanl,"%s%.2f%s%.2f","mean = ",mean.getVal(),"#pm",mean.getError());
  sprintf (widthl,"%s%.3f%s%.3f","width = ",width.getVal(),"#pm",width.getError());
  sprintf (file,"%s%d%s","error_gsim_plambda",number,"_bin200.eps");
  sprintf (dropbox,"%s%d%s","./dropbox_uploader2.sh upload error_gsim_plambda",number,"_bin200.eps /");

  TLegend *legend = new TLegend(0.1,0.7,0.4,0.9) ;
  
  legend -> AddEntry((TObject*)0,meanl,"");
  legend -> AddEntry((TObject*)0,widthl,"");

  legend -> SetTextSize(0.037);
  legend -> Draw();

  c1 ->SaveAs(file);
  system(dropbox);





}

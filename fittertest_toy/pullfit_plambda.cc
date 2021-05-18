#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
pullfit_plambda()
{
  using namespace RooFit; 

  TCanvas *c1 = new TCanvas("c1","",700,500);

  TChain *chn = new TChain("h1");
  chn -> Add("pull56_gsim.root"); 

  RooRealVar pull_plambda("pull_plambda","",-7,7);

  RooDataSet data("data","data",chn,RooArgSet(pull_plambda));

  RooRealVar mean("mean","mean",0,-1,1.);
  RooRealVar width("width","width",1.,0.5,1.5);
  
  RooGaussian gaus("gaus","",pull_plambda,mean,width);

  RooFitResult *res = gaus.fitTo(data,Minos(true));

  RooPlot *pull_pdf = pull_plambda.frame(Bins(30));

  data.plotOn(pull_pdf);
  gaus.plotOn(pull_pdf);

  pull_pdf -> Draw();
 
  char meanl[40]; 
  char widthl[40];

  sprintf (meanl,"%s%.3f%s%.3f","mean = ",mean.getVal(),"#pm",mean.getError());
  sprintf (widthl,"%s%.3f%s%.3f","width = ",width.getVal(),"#pm",width.getError());

  TLegend *legend = new TLegend(0.1,0.7,0.48,0.9) ;
  
  legend -> AddEntry((TObject*)0,meanl,"");
  legend -> AddEntry((TObject*)0,widthl,"");

  legend -> Draw();

  c1 ->SaveAs("pull_3.eps");

}

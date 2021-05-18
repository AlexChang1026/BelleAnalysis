#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooArgusBG.h"
#include "RooProdPdf.h"
#include "RooHistPdf.h"
#include "RooDataHist.h"
#include "RooArgList.h"
#include "RooBifurGauss.h"
#include "RooLandau.h"
#include "RooFormula.h"
#include "RooGenericPdf.h"
void fitDminuspi()
{
    using namespace RooFit;

    TChain *chn = new TChain("h1");     

    chn ->Add("/home/belle/chuan/sample/Dminuspi/Dminuspi_cs2.root");
    
    RooRealVar mbc0("mbc0","",5.23,5.30);
    RooRealVar de("de","",-0.3,0.2);
   
    RooDataSet data("data","data",chn,RooArgSet(mbc0,de));

    //mbc pdf 

    RooRealVar mbc_mean("mbc_mean","",5.279,5.27,5.28);
    RooRealVar mbc_width("mbc_width","",0.005,0.001,0.05);
    RooRealVar mbc_width2("mbc_width2","",0.005,0.001,0.05);
    
    RooGaussian mbc_gaus("mbc_gaus","",mbc0,mbc_mean,mbc_width);
    RooGaussian mbc_gaus2("mbc_gaus2","",mbc0,mbc_mean,mbc_width2);
    
    RooRealVar frac3("frac3","",0.5,0.,1.);
    
    RooAddPdf mbc_pdf("mbc_pdf","",RooArgList(mbc_gaus,mbc_gaus2),frac3);

    //de pdf 
     
    RooRealVar de_mean("de_mean","de_mean",0,-0.1,0.1);
    RooRealVar de_width1("de_width1","de_width1",0.05,0.005,0.1);
    RooRealVar de_width2("de_width2","de_width2",0.05,0.001,0.1);
    RooRealVar de_width3("de_width3","de_width3",0.05,0.01,0.15);
    
    RooGaussian de_gaus("de_gaus","",de,de_mean,de_width1);
    RooGaussian de_gaus2("de_gaus2","",de,de_mean,de_width2);
    RooGaussian de_gaus3("de_gaus3","",de,de_mean,de_width3);
    RooRealVar frac("frac","",0.5,0.,1.);
    RooRealVar frac2("frac2","",0.5,0.,1.);
    
    RooAddPdf de_pdf("de_pdf","",RooArgList(de_gaus,de_gaus2),frac);
    RooAddPdf de_pdf2("de_pdf2","",RooArgList(de_gaus3,de_pdf),frac2);

    

    RooRealVar ns("ns","ns",84000,81000,96000);
 
    RooProdPdf plambdapi("plambdapi","plambdapi",RooArgList(mbc_pdf,de_pdf2));
    
    
    RooAddPdf plambdapi2("plambdapi2","plambdapi2",RooArgList(plambdapi),RooArgList(ns));
    
    RooFitResult *res=plambdapi2.fitTo(data,Minos(true));
    
    mbc0.setRange("Signal_box_mbc",5.23,5.3);
    de.setRange("Signal_box_de",-0.3,0.2);
    
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    
    RooPlot *mbc_projection = mbc0.frame(Bins(100),Name("mbc_projection"),Title("mbc_projection"));
    data.plotOn(mbc_projection,Name("mbc"),CutRange("Signal_box_mbc"));
    plambdapi2.plotOn(mbc_projection,Name("psigmapi_mbc"),ProjectionRange("Signal_box_mbc"),Components("plambdapi2"));
    
    mbc_projection ->GetXaxis()->SetTitle("M_{bc}[GeV/c^{2}]");
    mbc_projection ->SetTitle("");
    mbc_projection ->SetTitleSize(0.045,"x");
    mbc_projection->SetTitleOffset(1.2,"y");      

    mbc_projection->Draw("");
   
    c1 ->SaveAs("mbc_Dminuspi.eps");   
   
    TCanvas *c2 = new TCanvas("c2","c2",700,500);
      
    RooPlot *de_projection = de.frame(Bins(100),Name("de_projection"),Title("de_projection"));
    data.plotOn(de_projection,Name("de"),CutRange("Signal_box_de"));
    plambdapi2.plotOn(de_projection,Name("psigmapi_de"),ProjectionRange("Signal_box_de"),Components("plambdapi2"));
    
    de_projection ->GetXaxis()->SetTitle("#Delta E[GeV]");
    de_projection ->SetTitle("");
    de_projection->SetTitleSize(0.045,"x");
    de_projection->SetTitleOffset(1.3,"y");    

    de_projection->Draw("");
 
    c2 ->SaveAs("de_Dminuspi.eps");

    system("./dropbox_uploader2.sh upload mbc_Dminuspi.eps /");
    system("./dropbox_uploader2.sh upload de_Dminuspi.eps /");



}

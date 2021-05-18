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
void plambdapi2dfit(){

    using namespace RooFit;

    TChain *chn = new TChain("h1");
    chn ->Add("/home/belle/chuan/fittertest_gsim3/plambdapi_cs2.root");

    RooRealVar mbc0("mbc0","",5.23,5.30);
    RooRealVar de("de","",-0.3,0.2);
    RooRealVar theta("theta","theta",0,-3.14,3.14);
    RooDataSet data("data","data",chn,RooArgSet(mbc0,de));

           RooRealVar mbc_plambda_sigma("mbc_plambda_sigma","mbc_plambda_sigma",0.002586,0.001,0.005);
           RooRealVar mbc_plambda_mu("mbc_plambda_mu","mbc_plambda_mu",5.2795,5.27,5.29);
           RooRealVar mbc_plambda_alpha("mbc_plambda_alpha","mbc_plambda_alpha",2.33,1.,5.);
           RooRealVar mbc_plambda_n("mbc_plambda_n","mbc_plambda_n",2.74,1.,5.);

           RooCBShape mbc_plambda("mbc_plambda","",mbc0,mbc_plambda_mu,mbc_plambda_sigma,mbc_plambda_alpha,mbc_plambda_n);
    
    
            RooRealVar de_plambda_sigma("de_plambda_sigma","",0.0224,0.01,0.04);
            RooRealVar de_plambda_mu("de_plamda_mu","",0.00029,0.,0.1);
            RooRealVar de_plambda_alpha("de_plambda_alpha","",1.93,0.,5.);
            RooRealVar de_plambda_n("de_plambda_n","",0.79,0.,5);

            RooCBShape de_plambda("de_plambda","",de,de_plambda_mu,de_plambda_sigma,de_plambda_alpha,de_plambda_n);

            RooRealVar de_plambda_width1("de_plambda_width1","",0.009765,0.,0.1);
            RooGaussian de_plambda_gaus1("de_plambda_gaus1","",de,de_plambda_mu,de_plambda_width1);
            RooRealVar de_plambda_width2("de_plambda_width2","",0.0765,0.,0.1);
            RooGaussian de_plambda_gaus2("gaus2","",de,de_plambda_mu,de_plambda_width2);

            RooRealVar de_plambda_frac("de_plambda_frac","",0.184,0.,1.);
            RooRealVar de_plambda_frac1("de_plambda_frac1","",0.971,0.,1.);

            RooAddPdf de_plambda_2("de_plambda_2","",RooArgList(de_plambda,de_plambda_gaus1),de_plambda_frac);
            RooAddPdf de_plambda_Pdf("de_plambda_Pdf","",RooArgList(de_plambda_2,de_plambda_gaus2),de_plambda_frac1);
    
            RooRealVar ns("ns","ns",84000,81000,96000);
 
    RooProdPdf plambdapi("plambdapi","plambdapi",RooArgList(mbc_plambda,de_plambda_Pdf));
    
    
    RooAddPdf plambdapi2("plambdapi2","plambdapi2",RooArgList(plambdapi),RooArgList(ns));
    
    RooFitResult *res=plambdapi2.fitTo(data,Minos(true));
    
    mbc0.setRange("Signal_box_mbc",5.23,5.3);
    de.setRange("Signal_box_de",-0.3,0.2);
    
    TCanvas *c1 = new TCanvas("c1","c1",500,500);
    
    RooPlot *mbc_projection = mbc0.frame(Bins(100),Name("mbc_projection"),Title("mbc_projection"));
    data.plotOn(mbc_projection,Name("mbc"),CutRange("Signal_box_mbc"));
    plambdapi2.plotOn(mbc_projection,Name("psigmapi_mbc"),ProjectionRange("Signal_box_mbc"),Components("plambdapi2"));
    
    mbc_projection ->GetXaxis()->SetTitle("M_{bc}[GeV/c^{2}]");
    mbc_projection ->SetTitle("");
    mbc_projection ->SetTitleSize(0.045,"x");
      
    mbc_projection->Draw("");
      
    TCanvas *c2 = new TCanvas("c2","c2",500,500);
      
    RooPlot *de_projection = de.frame(Bins(100),Name("de_projection"),Title("de_projection"));
    data.plotOn(de_projection,Name("de"),CutRange("Signal_box_de"));
    plambdapi2.plotOn(de_projection,Name("psigmapi_de"),ProjectionRange("Signal_box_de"),Components("plambdapi2"));
    
    de_projection ->GetXaxis()->SetTitle("#Delta E[GeV]");
    de_projection ->SetTitle("");
    de_projection->SetTitleSize(0.045,"x");
    
    de_projection->Draw("");
   
    c1->SaveAs("mbc_fit.eps");
    
   system("./home/belle/chuan/dropbox_uploader2.sh upload mbc_fit.eps fig2.pdf"); 
}    





















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
    chn ->Add("/home/belle/chuan/sample/partial_pspi/plambdapi_cs_pure2.root");

    RooRealVar mbc0("mbc0","",5.23,5.30);
    RooRealVar de("de","",-0.3,0.2);
    RooRealVar theta("theta","theta",0,-3.14,3.14);
    RooDataSet data("data","data",chn,RooArgSet(mbc0,de));

    TH2D *hist = new TH2D("hist","",300,-0.3,0.2,250,5.23,5.30);
    chn->Draw("mbc0:de>>hist");
 
    RooDataHist plambda("plambda","",RooArgList(de,mbc0),hist);
  //------------------------
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
    //------------------------- no radiation part --------------------

            RooRealVar mbc_mean("mbc_mean","",5.27947e+00);
            RooRealVar mbc_width("mbc_width","",2.58194e-03);
            RooRealVar mbc_width2("mbc_width2","",0.005,0.001,0.05);
    
            RooGaussian mbc_gaus("mbc_gaus","",mbc0,mbc_mean,mbc_width);
            RooGaussian mbc_gaus2("mbc_gaus2","",mbc0,mbc_mean,mbc_width2);
    
            RooRealVar frac3("frac3","",0.5,0.,1.);
    
            RooAddPdf mbc_pdf("mbc_pdf","",RooArgList(mbc_gaus,mbc_gaus2),frac3);
   
            RooRealVar de_mean("de_mean","de_mean",4.05886e-04);
            RooRealVar de_width1("de_width1","de_width1",9.99031e-03);
            RooRealVar de_width2("de_width2","de_width2",2.33901e-02);
            RooRealVar de_width3("de_width3","de_width3",0.05,0.01,0.15);
    
            RooGaussian de_gaus("de_gaus","",de,de_mean,de_width1);
            RooGaussian de_gaus2("de_gaus2","",de,de_mean,de_width2);
            RooGaussian de_gaus3("de_gaus3","",de,de_mean,de_width3);
            RooRealVar frac("frac","",8.57158e-01);
            RooRealVar frac2("frac2","",0.5,0.,1.);
    
            RooAddPdf de_pdf("de_pdf","",RooArgList(de_gaus,de_gaus2),frac);
            RooAddPdf de_pdf2("de_pdf2","",RooArgList(de_gaus3,de_pdf),frac2);


            RooRealVar ns("ns","ns",84000,70000,96000);
 
   // RooProdPdf plambdapi("plambdapi","plambdapi",RooArgList(mbc_gaus,de_pdf));
    RooHistPdf plambdapi("plambdapi","",RooArgList(de,mbc0),plambda,1);
    
    RooAddPdf plambdapi2("plambdapi2","plambdapi2",RooArgList(plambdapi),RooArgList(ns));
    
    RooFitResult *res=plambdapi2.fitTo(data,Minos(true));
    
    mbc0.setRange("Signal_box_mbc",5.23,5.29);
    de.setRange("Signal_box_de",-0.3,0.2);
    
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    
    RooPlot *mbc_projection = mbc0.frame(Bins(100),Name("mbc_projection"),Title("mbc_projection"));
    data.plotOn(mbc_projection,Name("mbc"),CutRange("Signal_box_mbc"));
    plambdapi2.plotOn(mbc_projection,Name("psigmapi_mbc"),ProjectionRange("Signal_box_mbc"),Components("plambdapi2"));
    
    mbc_projection ->GetXaxis()->SetTitle("M_{bc}[GeV/c^{2}]");
    mbc_projection ->SetTitle("");
    mbc_projection ->SetTitleSize(0.05,"x");
    mbc_projection ->SetTitleOffset(1.3,"y");    
    mbc_projection ->GetXaxis()->CenterTitle();  

    mbc_projection->Draw("");
      
    TCanvas *c2 = new TCanvas("c2","c2",700,500);
      
    RooPlot *de_projection = de.frame(Bins(100),Name("de_projection"),Title("de_projection"));
    data.plotOn(de_projection,Name("de"),CutRange("Signal_box_de"));
    plambdapi2.plotOn(de_projection,Name("psigmapi_de"),ProjectionRange("Signal_box_de"),Components("plambdapi2"));
    
    de_projection ->GetXaxis()->SetTitle("#Delta E[GeV]");
    de_projection ->SetTitle("");
    de_projection ->SetTitleSize(0.05,"x");
    de_projection ->SetTitleOffset(1.3,"y");     
    de_projection ->GetXaxis()->CenterTitle();

    de_projection->Draw("");
   
    c1->SaveAs("mbc_plambda.eps");
    c2->SaveAs("de_plambda.eps");
//   system("cd ~");  
   system("./dropbox_uploader2.sh upload mbc_plambda.eps /"); 
   system("./dropbox_uploader2.sh upload de_plambda.eps /");
}    





















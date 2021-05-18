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
#include "RooKeysPdf.h"
void fitplambdapi_bb()
{
    using namespace RooFit;

    TChain *chn = new TChain("h1");
 //   chn ->Add("/home/belle/chuan/sample/partial_pspi/bbplambdapix10_cs3.root");
    chn ->Add("/home/belle/chuan/sample/partial_pspi/bbplambdapix10_cs4.root");
 //   gROOT->SetBatch(0);
 
    RooRealVar mbc0("mbc0","",5.23,5.30);
    RooRealVar de("de","",-0.3,0.2);
    
    RooDataSet data("data","data",chn,RooArgSet(de,mbc0));     

    TH1D *bb_hist = new TH1D("bb_hist","",15,5.23,5.30);

    chn ->Draw("mbc0>>bb_hist");

    RooDataHist bb("bb","",RooArgList(mbc0),bb_hist);

    //mbc 
 
    RooRealVar m0("m0","",5.29);
    RooRealVar k("k","",-2.7739e+01,-50.,-10.);
    RooRealVar p("p","",0.6,0.4,0.75);
    
    RooArgusBG qqbg1("qqbg1","M_{bc}",mbc0,m0,k);


    //de 

    RooRealVar a0("a0","a0",-0.3,-1.,-0.1) ;
    RooRealVar a1("a1","a1",0.2,-0.1,0.5) ;
    RooChebychev bkg1("bkg1","Background 1",de,RooArgSet(a0,a1)) ;
    
   
    RooRealVar ns("ns","ns",15000,2300,50100);
    
    RooHistPdf bbfinal3("bbfinal3","",RooArgList(mbc0),bb,1);

    RooProdPdf bbfinal2("bbfinal2","bbfinal_pdf2",RooArgList(qqbg1,bkg1));

    RooAddPdf bbfinal("bbfinal","bbfinal_pdf",RooArgList(bbfinal2),RooArgList(ns));
    
    RooFitResult *res = bbfinal.fitTo(data,Minos(true));
    
    mbc0.setRange("Signal_box_mbc",5.23,5.30);
    de.setRange("Signal_box_de",-0.3,0.2);
   
    
    TCanvas *c1 = new TCanvas("c1","c1",700,500);
  
    RooPlot *mbc_projection = mbc0.frame(Bins(20));
    data.plotOn(mbc_projection,Name("mbc"),CutRange("Signal_box_mbc"));
    bbfinal.plotOn(mbc_projection,Name("bb_mbc"),Components("bbfinal"));
    
    mbc_projection ->GetXaxis()->SetTitle("M_{bc}[GeV/c^{2}]");
    mbc_projection ->SetTitleSize(0.045,"x");
    mbc_projection ->SetTitle("");
    
    mbc_projection->Draw("");
    c1 ->SaveAs("mbc_bb.eps");
    
  
   TCanvas *c2 = new TCanvas("c2","c2",700,500);
    
    RooPlot *de_projection = de.frame(Bins(20));
    data.plotOn(de_projection,Name("de"),CutRange("Signal_box_de"));
    bbfinal.plotOn(de_projection,Name("bb_de"),Components("bbfinal"));
    
    de_projection ->GetXaxis()->SetTitle("#Delta E[GeV]");
    de_projection ->SetTitleSize(0.045,"x");
    de_projection ->SetTitle("");
    
    de_projection->Draw(""); 
    c2 ->SaveAs("de_bb.eps");  

}

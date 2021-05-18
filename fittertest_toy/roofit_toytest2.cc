#include "TROOT.h"
#include "TMath.h"
// ROOT data
 #include "TFile.h"
 #include "TChain.h"
 #include "TLeaf.h"
// // ROOT plot
 #include "TCanvas.h"
 #include "TH1.h"

 #include "TLegend.h"
 #include "TStyle.h"
 #include "TGaxis.h"
 #include "TLine.h"
 #include "TLatex.h"
 #include "THStack.h"
 #include "TRandom.h"
 // RooFit
 #include "RooAbsPdf.h"
 #include "RooAddModel.h"
 #include "RooAddPdf.h"
 #include "RooArgusBG.h"
 #include "RooBifurGauss.h"
 #include "RooBreitWigner.h"
 #include "RooCBShape.h"
 #include "RooChebychev.h"
 #include "RooDataHist.h"
 #include "RooDataSet.h"
 #include "RooFitResult.h"
 #include "RooFFTConvPdf.h"
 #include "RooGaussian.h"
 #include "RooGenericPdf.h"
 #include "RooGlobalFunc.h"
 #include "RooHist.h"
 #include "RooKeysPdf.h"
 #include "Roo2DKeysPdf.h"
 #include "RooMCStudy.h"
 #include "RooMsgService.h"
 #include "RooNumIntConfig.h"
 #include "RooPlot.h"
 #include "RooPolynomial.h"
 #include "RooPolyVar.h"
 #include "RooProdPdf.h"
 #include "RooRealVar.h"
 #include "RooWorkspace.h"
 #include "RooHistPdf.h"
 #include "TNtuple.h"
 #include "TH2.h"
 #include "TH3.h"
 #include "RooCategory.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include <fstream>
 #include <iomanip>
 #include <fstream>
 #include <iomanip>

using namespace std;
void roofit_gsim();
int main()
{    
     roofit_toytest2();
   
     return 0;

}
void  roofit_toytest2(int number) {
        
        TChain *psigmapi = new TChain("h1");
        TChain *plambdapi = new TChain("h1");
        TChain *csplambdapi = new TChain("h1");
        TChain *cspsigmapi = new TChain("h1");
        TChain *bb = new TChain("h1");
        TChain *qq = new TChain("h1");

        char filename[40];

        sprintf (filename,"%s%d%s","toytest",number,".root");

        TFile *fin2 = new TFile(filename,"recreate");
        TTree *h1 = new TTree("h1","B1");

        psigmapi->Add("/home/belle/chuan/sample/partial_pspi/rareplambdapi_cs4.root");
        plambdapi->Add("/home/belle/chuan/sample/partial_pspi/plambdapi_cs_pure2.root");
        bb->Add("/home/belle/chuan/sample/partial_pspi/bbplambdapix10_cs4.root");
        qq->Add("/home/belle/chuan/sample/partial_pspi/qqplambdapi_cs2.root");

        using namespace RooFit;
        RooRealVar mbc0("mbc0","mbc0",5.23,5.30);
        RooRealVar de("de","de",-0.3,0.2);
       
        RooArgSet *varset = new RooArgSet(de,mbc0);
    
        RooDataSet data("psigmapi","psigmapi",psigmapi,*varset);
        RooDataSet data5("plambdapi","plambdapi",plambdapi,*varset);
        RooDataSet data4("qq","qq",qq,*varset);
        RooDataSet data6("bb","bb",bb,*varset);

       
  //-------------------- Histogram fullfill for Hist PDF -----------------------------
       

        TH2D *hist = new TH2D("hist","",250,-0.3,0.2,200,5.23,5.30);

        plambdapi->Draw("mbc0:de>>hist");
      
        TH2D *hist2 = new TH2D("hist2","",60,-0.3,0.2,100,5.23,5.30);
        psigmapi->Draw("mbc0:de>>hist2");
       
        TH1D *de_psigma_hist = new TH1D("de_psigma_hist","",60,-0.3,0.2);
        TH1D *mbc_psigma_hist = new TH1D("mbc_psigma_hist","",100,5.23,5.30);

        TH1D *bb_hist = new TH1D("bb_hist","",10,5.23,5.30);

        bb->Draw("mbc0>>bb_hist");
        psigmapi->Draw("de>>de_psigma_hist");
        psigmapi->Draw("mbc0>>mbc_psigma_hist");

        RooDataHist plambda("plambda","",RooArgList(de,mbc0),hist);
        RooDataHist psigma("psigma","",RooArgList(de,mbc0),hist2);
        RooDataHist psigma_de("psigma_de","",RooArgList(de),de_psigma_hist);
        RooDataHist psigma_mbc("psigma_mbc","",RooArgList(mbc0),mbc_psigma_hist);      
        RooDataHist bb_mbc("bb_mbc","",RooArgList(mbc0),bb_hist);
  
        std::cout<<"test4"<<std::endl;

  //--------------------------  mbc Pdf ----------------------
      

        mbc0.setRange("Signal_box_mbc",5.23,5.30);
        //qq
      
       // RooRealVar mbc_qq_m0 ("mbc_qq_m0","mbc_qq_m0",5.28916e+00);
        RooRealVar mbc_qq_m0 ("mbc_qq_m0","mbc_qq_m0",5.29e+00);
        RooRealVar mbc_qq_c ("mbc_qq_c","mbc_qq_c",-3.67134e+01,-47,-20);
        
        RooArgusBG mbc_qq("mbc_qq","mbc_qq",mbc0,mbc_qq_m0,mbc_qq_c);

        //qq_toy
        RooRealVar mbc_qq_m0_toy ("mbc_qq_m0_toy","mbc_qq_m0_toy",5.28916e+00);
        RooRealVar mbc_qq_c_toy ("mbc_qq_c_toy","mbc_qq_c_toy",-3.67134e+01);

        RooArgusBG mbc_qq_toy("mbc_qq_toy","mbc_qq_toy",mbc0,mbc_qq_m0_toy,mbc_qq_c_toy);



        
        //bb
        
        RooRealVar m0("m0","",5.29e+00);
        RooRealVar k("k","",-3.51244e+01);
    
        RooArgusBG mbc_bb("mbc_bb","",mbc0,m0,k);

      //  RooHistPdf mbc_bb("mbc_bb","",RooArgList(mbc0),bb_mbc,1);
          
        //psigmapi
        
        RooHistPdf mbc_psigmapi("mbc_psigmapi","",RooArgList(mbc0),psigma_mbc,1); 
 
        //plambdapi
      
        RooRealVar mbc_mean("mbc_mean","",5.27947e+00);
        RooRealVar mbc_width("mbc_width","",1.43423e-02);
        RooRealVar mbc_width2("mbc_width2","",2.58194e-03);

        RooGaussian mbc_gaus("mbc_gaus","",mbc0,mbc_mean,mbc_width);
        RooGaussian mbc_gaus2("mbc_gaus2","",mbc0,mbc_mean,mbc_width2);

        RooRealVar mbc_frac3("mbc_frac3","",4.62076e-03);

        RooAddPdf mbc_pdf("mbc_pdf","",RooArgList(mbc_gaus,mbc_gaus2),mbc_frac3); 
     
    //---------------------de Pdf-----------------------------

       
        de.setRange("Signal_box_de",-0.3,0.2);
         
        //qq
        RooRealVar de_qq_slope("de_qq_slope","",-1.19459e+00,-1.5,-0.8);
        RooPolynomial de_qq("de_qq","",de,RooArgSet(de_qq_slope));
   
        //qq_toy
        RooRealVar de_qq_slope_toy("de_qq_slope_toy","",-1.19459e+00);
        RooPolynomial de_qq_toy("de_qq_toy","",de,RooArgSet(de_qq_slope_toy));

        //bb 
        
         RooRealVar a0("a0","a0",-3.30775e-01) ;
         RooRealVar a1("a1","a1",2.66792e-02) ;
         RooChebychev de_bb("de_bb","",de,RooArgSet(a0,a1)) ;      

        //psigmapi 
        
        RooHistPdf de_psigmapi("de_psigmapi","",RooArgList(de),psigma_de,1);

        //plambdapi
   
        RooRealVar de_mean("de_mean","de_mean",4.05886e-04);
        RooRealVar de_width1("de_width1","de_width1",9.99031e-03);
        RooRealVar de_width2("de_width2","de_width2",2.33901e-02);
        RooRealVar de_width3("de_width3","de_width3",8.60253e-02);

        RooGaussian de_gaus("de_gaus","",de,de_mean,de_width1);
        RooGaussian de_gaus2("de_gaus2","",de,de_mean,de_width2);
        RooGaussian de_gaus3("de_gaus3","",de,de_mean,de_width3);
        RooRealVar de_frac("de_frac","",8.57158e-01);
        RooRealVar de_frac2("de_frac2","",2.23619e-02);

        RooAddPdf de_pdf("de_pdf","",RooArgList(de_gaus,de_gaus2),de_frac);
        RooAddPdf de_pdf2("de_pdf2","",RooArgList(de_gaus3,de_pdf),de_frac2);
     
    //    RooProdPdf final_plambdapi("final_plambdapi","",RooArgList(de_pdf2,mbc_pdf));//plambdapi 2d PDF
        RooProdPdf final_qq("final_qq","",RooArgList(de_qq,mbc_qq)); //qq 2d PDF
        RooProdPdf final_bb("final_bb","",RooArgList(de_bb,mbc_bb)); //bb 2d PDF
    //    RooProdPdf final_psigmapi("final_psigmapi","",RooArgList(de_psigmapi,mbc_psigmapi));//psigmapi 2d PDF 
        RooHistPdf final_psigmapi("final_psigmapi","",RooArgList(de,mbc0),psigma,1); //psigmapi 2d PDF
        RooHistPdf final_plambdapi("final_plambdapi","",RooArgList(de,mbc0),plambda,1);     
        RooProdPdf final_qq_toy("final_qq_toy","",RooArgList(de_qq_toy,mbc_qq_toy));
 
        RooRealVar frac("frac","",0.5,0.,1.);
        RooAddPdf final_bkg("final_bkg","",RooArgList(final_qq,final_bb),frac);
 
        RooRealVar nsig ("nsig","signal events",150,-100,1000);
        RooRealVar nplambda ("nplambda","",293,-100,1000);
        RooRealVar nbkg ("nbkg","",5000,1000,10000);      

        RooAddPdf final_pdf("final_pdf","final_pdf",RooArgList(final_psigmapi,final_plambdapi,final_qq),RooArgList(nsig,nplambda,nbkg));
    
     for(int i = 0;i<10;i++)
  {
     //-----------------------Gsim part 1 -----------------------------  
        int plambdapi_n = plambdapi -> GetEntries();
        int psigmapi_n = psigmapi -> GetEntries();
        int qq_n = qq -> GetEntries();
        int bb_n = bb -> GetEntries();

        float de1, mbc1, de2, mbc2,de3, mbc3,de4,mbc4,de5,mbc5,de6,mbc6 ;


        double number_psigmapi_true,number_plambdapi_true,number_bb,number_qq;

        TRandom *rnd = new TRandom(0);

        number_psigmapi_true = rnd -> PoissonD(70);
        number_plambdapi_true = rnd -> PoissonD(250);
        number_bb = rnd -> PoissonD(480);
        number_qq = rnd -> PoissonD(2800);


        psigmapi -> SetBranchAddress("de",&de1);
        psigmapi -> SetBranchAddress("mbc0",&mbc1);
        plambdapi -> SetBranchAddress("de",&de3);
        plambdapi -> SetBranchAddress("mbc0",&mbc3);
        bb -> SetBranchAddress("mbc0",&mbc5);
        bb -> SetBranchAddress("de",&de5);
        qq -> SetBranchAddress("mbc0",&mbc6);
        qq -> SetBranchAddress("de",&de6);
 
        float pull_plambda ;
        float pull ;
        float error ;
        float Yield ; 
        float Yield_plambda ;
        float number_ps ;
        float number_pl;
        float error_plambda ;


        h1 -> Branch("pull_plambda",&pull_plambda,"pull_plambda");
        h1 -> Branch("pull",&pull,"pull");
        h1 -> Branch("error",&error,"error");
        h1 -> Branch("Yield",&Yield,"Yield");
        h1 -> Branch("number_ps",&number_ps,"number_ps");
        h1 -> Branch("Yield_plambda",&Yield_plambda,"Yield_plambda"); 
        h1 -> Branch("number_pl",&number_pl,"number_pl");
        h1 -> Branch("error_plambda",&error_plambda,"error_plambda");

        RooDataSet gsplambda("gsplambda","",*varset);
        RooDataSet gsqq("gsqq","",*varset);
        RooDataSet gsbb("gsbb","",*varset);
        RooDataSet gspsigma("gspsigma","",*varset);    
 
        RooDataSet *toypsigma = final_psigmapi.generate(RooArgSet(de,mbc0),number_psigmapi_true);
        RooDataSet *toyplambda = final_plambdapi.generate(RooArgSet(de,mbc0),number_plambdapi_true);          
        RooDataSet *toybb = final_bb.generate(RooArgSet(de,mbc0),number_bb);
        RooDataSet *toyqq = final_qq_toy.generate(RooArgSet(de,mbc0),number_qq);
        RooDataSet toy("toy","",RooArgSet(de,mbc0));      

        std::cout<<"test6"<<std::endl;
   
        int plambdaused[200000]={0};
        int qqused[1000000]={0};
        int bbused[1000000]={0};
        int psigmaused[200000]={0};

        srand(time(NULL));

        std::cout<<"test7"<<std::endl;

//-------------------- Fullfill gsim psudoexperiment --------------------------       
       
        for(int k1=0; k1<number_psigmapi_true;k1++)
      {

           int ii=0;

           ii=rand()%(psigmapi_n);

           psigmapi->GetEntry(ii);

           de = de1;
           mbc0 = mbc1;


           gspsigma.add(*varset);

       }
      
       for(int k1=0;k1<number_plambdapi_true;k1++)
      {

          int ii = 0;

          ii=rand()%(plambdapi_n);


          plambdapi -> GetEntry(ii);

          de = de3;
          mbc0 = mbc3;

          gsplambda.add(*varset);
      }

      for( int k1 = 0; k1<number_bb;k1++)
     {

           int ii = 0; 
   
           ii=rand()%(bb_n);

           bb->GetEntry(ii);

           de = de5;
           mbc0 = mbc5;

           gsbb.add(*varset);

     }

     for( int k1 = 0; k1<number_qq;k1++)
    {
        int ii=0;

        ii=rand()%(qq_n);

        qq -> GetEntry(ii);

        de = de6;
        mbc0 = mbc6;

        gsqq.add(*varset);

      }

  
        toy.append(gspsigma); 
        toy.append(gsplambda);
        toy.append(gsbb);
        toy.append(gsqq);

//-----------------------Fitting and Pull Calculation----------------
        
        RooFitResult *final_result = new RooFitResult("final_result","final_result");
        final_result = final_pdf.fitTo(toy,Minos(kTRUE));
       

        if(nsig.getVal() < 70)
        {
           pull = (70-nsig.getVal())/nsig.getAsymErrorHi();
        }
        else
        {
           pull = (-70+nsig.getVal())/nsig.getAsymErrorLo();

        }
 
       error = nsig.getError();
       Yield = nsig.getVal();
       number_ps = number_psigmapi_true; 
       number_pl = number_plambdapi_true;

       Yield_plambda = nplambda.getVal();
       error_plambda = nplambda.getError();

        if(nplambda.getVal() < 250)
        {
           pull_plambda = (250-nplambda.getVal())/nplambda.getAsymErrorHi();
        }
        else
        {
           pull_plambda = (-250+nplambda.getVal())/nplambda.getAsymErrorLo();
        
        }



 
       h1 -> Fill(); 
   }
       h1 ->Write();
       fin2 ->Close();
    
   /*      
        TCanvas *canvas = new TCanvas("canvas","c1");
   
        RooPlot *plot_mbc_projection = mbc0.frame(Bins(30),Name("plot_mbc_projection"),Title("plot_mbc_projection"));
        toy.plotOn(plot_mbc_projection,Name("mbc_hist"),CutRange("signal_box_mbc"),MarkerColor(kBlack));
        final_pdf.plotOn(plot_mbc_projection,Name("mbc_pdf_result"),ProjectionRange("signal_box_mbc"),Components("final_pdf"),LineColor(kBlue),LineStyle(kSolid));
        final_pdf.plotOn(plot_mbc_projection,Name("mbc_sig_result"),ProjectionRange("signal_box_mbc"),Components("final_psigmapi"),LineColor(kRed),LineStyle(kSolid));
        final_pdf.plotOn(plot_mbc_projection,Name("mbc_bg_result"),ProjectionRange("signal_box_mbc"),Components("final_plambdapi"),LineColor(kBlack),LineStyle(kSolid));
        final_pdf.plotOn(plot_mbc_projection,Name("mbc_bg_result"),ProjectionRange("signal_box_mbc"),Components("final_bkg"),LineColor(kViolet),LineStyle(kDashDotted));
  
        plot_mbc_projection -> GetXaxis()->SetTitle("M_{bc}[GeV/c^{2}]");
        plot_mbc_projection -> SetTitleSize(0.045,"x");
        plot_mbc_projection -> SetTitle("");
        plot_mbc_projection -> Draw("");
  

        TCanvas *canvas2= new TCanvas("canvas2","c2");    
    
        RooPlot *plot_de_projection = de.frame(Bins(30),Name("plot_de_projection"),Title("plot_de_projection"));
        toy.plotOn(plot_de_projection,Name("de_hist"),CutRange("signal_box_de"),MarkerColor(kBlack));
        final_pdf.plotOn(plot_de_projection,Name("de_pdf_result"),ProjectionRange("signal_box_de"),Components("final_pdf"),LineColor(kBlue),LineStyle(kSolid));
        final_pdf.plotOn(plot_de_projection,Name("de_sig_result"),ProjectionRange("signal_box_de"),Components("final_psigmapi"),LineColor(kRed),LineStyle(kSolid));
        final_pdf.plotOn(plot_de_projection,Name("de_bg_result"),ProjectionRange("signal_box_de"),Components("final_plambdapi"),LineColor(kBlack),LineStyle(kSolid));
        final_pdf.plotOn(plot_de_projection,Name("de_bg_result"),ProjectionRange("signal_box_de"),Components("final_bkg"),LineColor(kViolet),LineStyle(kDashDotted));
  
        plot_de_projection -> GetXaxis()->SetTitle("#Delta E[GeV]");
        plot_de_projection -> SetTitleSize(0.045,"x");
        plot_de_projection -> SetTitle("");  
        plot_de_projection -> Draw("");
        

 
       TLegend *legend = new TLegend(0.4,0.4,0.4,0.4);  
       
       legend -> AddEntry("final_pdf","Total","l");
       legend -> AddEntry("final_qq","Background","l");   
       legend -> AddEntry("final_plambdapi","B #to p #Lambda #pi","l");
       legend -> AddEntry("final_psigmapi","Signal","l");  

       legend -> Draw();*/
}

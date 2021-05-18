void qq_fit()
{
      
    using namespace RooFit;

    TFile *fin = new TFile("/home/belle/chuan/sample/partial_pspi/qqplambdapi_cs2.root");
    TTree *B = (TTree *)fin ->Get("h1");
    
    RooRealVar mbc0("mbc0","",5.23,5.30);
    RooRealVar de("de","",-0.3,0.2);
    
    RooDataSet data("data","data",B,RooArgSet(mbc0,de));
    
    RooRealVar m0("m0","",5.2895);
    RooRealVar k("k","",-3.57739e+01,-50.,-25.);
    RooArgusBG qqbg1("qqbg1","M_{bc}",mbc0,m0,k);
    
    RooRealVar slope("slope","",-0.3,-1.8,-0.1);
    RooPolynomial qqbg2("qqbg2","",de,RooArgSet(slope));
    
    RooProdPdf qqfinal2("qqfinal2","qqfinal_pdf",RooArgList(qqbg1,qqbg2));
    
    RooRealVar ns("ns","ns",160000,150000,300000);
    
    RooAddPdf qqfinal("qqfinal","qqfinal",RooArgList(qqfinal2),RooArgList(ns));
    
    RooFitResult *res=qqfinal.fitTo(data,Minos(true));



     TCanvas *c1 = new TCanvas("c1","c1",700,500);
  
    RooPlot *mbc_projection = mbc0.frame(Bins(15),Name("mbc_projection"),Title("mbc_projection"));
    data.plotOn(mbc_projection,Name("mbc"),CutRange("Signal_box_mbc"));
    qqfinal.plotOn(mbc_projection,Name("qq_mbc"),ProjectionRange("Signal_box_mbc"),Components("qqfinal"));
    mbc_projection ->GetXaxis()->SetTitle("M_{bc}[GeV/c^{2}]");
    mbc_projection ->SetTitle("");
    mbc_projection ->SetTitleSize(0.045,"x");
    mbc_projection->Draw("");
    
    c1->SaveAs("qqmbc2dfit.eps");
    
    TCanvas *c2 = new TCanvas("c2","c2",700,500);
    
    RooPlot *de_projection = de.frame(Bins(10),Name("de_projection"),Title("de_projection"));
    data.plotOn(de_projection,Name("de"),CutRange("Signal_box_de"));
    qqfinal.plotOn(de_projection,Name("qq_de"),ProjectionRange("Signal_box_de"),Components("qqfinal"));
    de_projection ->GetXaxis()->SetTitle("#Delta E[GeV]");
    de_projection ->SetTitle("");
    de_projection->SetTitleSize(0.045,"x");
    de_projection->Draw("");
      
    c2->SaveAs("qqde2dfit.eps");



}

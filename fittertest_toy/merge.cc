void merge()
{
    TChain *chn = new TChain("h1");

    chn ->Add("toytest*.root");
    chn ->Merge("pull56_gsim.root"); 




}

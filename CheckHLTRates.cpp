/* To compile, run this:
g++ CheckHLTRates.cpp -o ExecOnForest `root-config --cflags --glibs`
*/

#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TAxis.h"

using namespace std;

#define HFPlusMax   9.2
#define HFMinusMax  8.6
#define ZDCMinusMax 1000
#define ZDCPlusMax  1100
// Preprocessor functions
#define CheckAndSetBranch(TREE, BRANCH)     \
if(TREE->GetBranch(#BRANCH))                \
{                                           \
  TREE->SetBranchStatus(#BRANCH, 1);        \
  TREE->SetBranchAddress(#BRANCH, &BRANCH); \
}

void LabelHLTHist(
  TH1D* hist,
  TString title,
  TString sideA,
  TString sideB
) {
  hist->SetTitle(title + "; ; Entries");
  hist->GetXaxis()->SetBinLabel(1, sideA + ", ZeroBias");
  hist->GetXaxis()->SetBinLabel(2, sideB + ", ZeroBias");
  hist->GetXaxis()->SetBinLabel(3, sideA + ", ZDCOR");
  hist->GetXaxis()->SetBinLabel(4, sideB + ", ZDCOR");
}

int main(
  int argc,
  char* argv[]
) {
  TString finPath = argv[1];
  TString foutPath = argv[2];
  cout << "Input:  " << finPath.Data() << endl;
  cout << "Output: " << foutPath.Data() << endl;
  
  TFile* fin = TFile::Open(finPath, "READ");
  if (!fin || fin->IsZombie()) {
    cerr << "[ERROR] Can't open file\n";
    return 1;
  }
  
  fin->cd();
  TTree* tree = (TTree*) fin->Get("hiEvtAnalyzer/HiTree");
  if (tree == nullptr) {
    cerr << "[ERROR] Can't initialize TTrees\n";
    return 1;
  }
  
  TTree* tempTree;
  
  tempTree = (TTree*) fin->Get("zdcanalyzer/zdcrechit");
  if (tempTree != nullptr) {
    tree->AddFriend("zdcanalyzer/zdcrechit", fin);
    delete tempTree;
  } else return 1;

  tempTree = (TTree*) fin->Get("hltanalysis/HltTree");
  if (tempTree != nullptr) {
    tree->AddFriend("hltanalysis/HltTree", fin);
    delete tempTree;
  } else return 1;
  
  tempTree = (TTree*) fin->Get("PbPbTracks/trackTree");
  if (tempTree != nullptr) {
    tree->AddFriend("PbPbTracks/trackTree", fin);
    delete tempTree;
  } else return 1;
  
  tree->SetBranchStatus("*", 0);
  
  float hiHFPlus_pf;
  float hiHFMinus_pf;
  CheckAndSetBranch(tree, hiHFPlus_pf);
  CheckAndSetBranch(tree, hiHFMinus_pf);
  
  float sumPlus;
  float sumMinus;
  CheckAndSetBranch(tree, sumPlus);
  CheckAndSetBranch(tree, sumMinus);
  
  int nTrk;
  int nVtx;
  vector<float>* trkPt = new vector<float>;
  CheckAndSetBranch(tree, nTrk);
  CheckAndSetBranch(tree, nVtx);
  CheckAndSetBranch(tree, trkPt);

  int HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5;
//  int HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5_PrescaleNumerator;
//  int HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5_PrescaleDenominator;
  int HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5;
//  int HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5_PrescaleNumerator;
//  int HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5_PrescaleDenominator;
  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5_PrescaleNumerator);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5_PrescaleDenominator);
  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5_PrescaleNumerator);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5_PrescaleDenominator);
  
  int HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16;
//  int HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16_PrescaleNumerator;
//  int HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16_PrescaleDenominator;
  int HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16;
//  int HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16_PrescaleNumerator;
//  int HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16_PrescaleDenominator;
  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16_PrescaleNumerator);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16_PrescaleDenominator);
  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16_PrescaleNumerator);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16_PrescaleDenominator);
  
  int HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16;
//  int HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16_PrescaleNumerator;
//  int HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16_PrescaleDenominator;
  int HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16;
//  int HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16_PrescaleNumerator;
//  int HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16_PrescaleDenominator;
  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16_PrescaleNumerator);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16_PrescaleDenominator);
  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16_PrescaleNumerator);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16_PrescaleDenominator);
  
  int HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15;
//  int HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15_PrescaleNumerator;
//  int HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15_PrescaleDenominator;
  int HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15;
//  int HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15_PrescaleNumerator;
//  int HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15_PrescaleDenominator;
  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15_PrescaleNumerator);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15_PrescaleDenominator);
  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15_PrescaleNumerator);
//  CheckAndSetBranch(tree, HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15_PrescaleDenominator);

  TH1D* RateTemplate = new TH1D(
    "RateTemplate",
    ";;Entries",
    4, 0, 4
  );
  // XnAn || AnXn
  TH1D* hMax10000_XnAn                  = (TH1D*) RateTemplate->Clone("hMax10000_XnAn");
  TH1D* hMin400_Max10000_XnAn           = (TH1D*) RateTemplate->Clone("hMin400_Max10000_XnAn");
  TH1D* hSingleTrack_MaxTrack_XnAn      = (TH1D*) RateTemplate->Clone("hSingleTrack_MaxTrack_XnAn");
  TH1D* hSingleTrack_MaxPix400_XnAn     = (TH1D*) RateTemplate->Clone("hSingleTrack_MaxPix400_XnAn");
  TH1D* hMin400Max10000_STMP400_XnAn    = (TH1D*) RateTemplate->Clone("hMin400Max10000_STMP400_XnAn");
  LabelHLTHist(hMax10000_XnAn, "HLT_MaxPixelCluster10000", "XnAn", "AnXn");
  LabelHLTHist(hMin400_Max10000_XnAn, "HLT_MinPixelCluster400_MaxPixelCluster10000", "XnAn", "AnXn");
  LabelHLTHist(hSingleTrack_MaxTrack_XnAn, "HLT_SinglePixelTrack_MaxPixelTrack", "XnAn", "AnXn");
  LabelHLTHist(hSingleTrack_MaxPix400_XnAn, "HLT_SinglePixelTrackLowPt_MaxPixelCluster400", "XnAn", "AnXn");
  LabelHLTHist(hMin400Max10000_STMP400_XnAn, "HLT_MinPix400_MaxPix10000 OR HLT_SinPixTrkLowPt_MaxPix400", "XnAn", "AnXn");
  // Xn0n || 0nXn
  TH1D* hMax10000_Xn0n                  = (TH1D*) RateTemplate->Clone("hMax10000_Xn0n");
  TH1D* hMin400_Max10000_Xn0n           = (TH1D*) RateTemplate->Clone("hMin400_Max10000_Xn0n");
  TH1D* hSingleTrack_MaxTrack_Xn0n      = (TH1D*) RateTemplate->Clone("hSingleTrack_MaxTrack_Xn0n");
  TH1D* hSingleTrack_MaxPix400_Xn0n     = (TH1D*) RateTemplate->Clone("hSingleTrack_MaxPix400_Xn0n");
  TH1D* hMin400Max10000_STMP400_Xn0n    = (TH1D*) RateTemplate->Clone("hMin400Max10000_STMP400_Xn0n");
  LabelHLTHist(hMax10000_Xn0n, "HLT_MaxPixelCluster10000", "Xn0n", "0nXn");
  LabelHLTHist(hMin400_Max10000_Xn0n, "HLT_MinPixelCluster400_MaxPixelCluster10000", "Xn0n", "0nXn");
  LabelHLTHist(hSingleTrack_MaxTrack_Xn0n, "HLT_SinglePixelTrack_MaxPixelTrack", "Xn0n", "0nXn");
  LabelHLTHist(hSingleTrack_MaxPix400_Xn0n, "HLT_SinglePixelTrackLowPt_MaxPixelCluster400", "Xn0n", "0nXn");
  LabelHLTHist(hMin400Max10000_STMP400_Xn0n, "HLT_MinPix400_MaxPix10000 OR HLT_SinPixTrkLowPt_MaxPix400", "Xn0n", "0nXn");
  // gammaN || Ngamma
  TH1D* hMax10000_gammaN                = (TH1D*) RateTemplate->Clone("hMax10000_gammaN");
  TH1D* hMin400_Max10000_gammaN         = (TH1D*) RateTemplate->Clone("hMin400_Max10000_gammaN");
  TH1D* hSingleTrack_MaxTrack_gammaN    = (TH1D*) RateTemplate->Clone("hSingleTrack_MaxTrack_gammaN");
  TH1D* hSingleTrack_MaxPix400_gammaN   = (TH1D*) RateTemplate->Clone("hSingleTrack_MaxPix400_gammaN");
  TH1D* hMin400Max10000_STMP400_gammaN  = (TH1D*) RateTemplate->Clone("hMin400Max10000_STMP400_gammaN");
  LabelHLTHist(hMax10000_gammaN, "HLT_MaxPixelCluster10000", "gammaN", "Ngamma");
  LabelHLTHist(hMin400_Max10000_gammaN, "HLT_MinPixelCluster400_MaxPixelCluster10000", "gammaN", "Ngamma");
  LabelHLTHist(hSingleTrack_MaxTrack_gammaN, "HLT_SinglePixelTrack_MaxPixelTrack", "gammaN", "Ngamma");
  LabelHLTHist(hSingleTrack_MaxPix400_gammaN, "HLT_SinglePixelTrackLowPt_MaxPixelCluster400", "gammaN", "Ngamma");
  LabelHLTHist(hMin400Max10000_STMP400_gammaN, "HLT_MinPix400_MaxPix10000 OR HLT_SinPixTrkLowPt_MaxPix400", "gammaN", "Ngamma");
  
  TH1D* ZDCTemplate = new TH1D(
    "ZDCTemplate",
    ";ZDC Energy Sum;Entries",
    100, 0, 20000
  );
  TH1D* hZDCp_Max10000_ZB                   = (TH1D*) ZDCTemplate->Clone("hZDCp_Max10000_ZB");
  TH1D* hZDCm_Max10000_ZB                   = (TH1D*) ZDCTemplate->Clone("hZDCm_Max10000_ZB");
  TH1D* hZDCp_Min400_Max10000_ZB            = (TH1D*) ZDCTemplate->Clone("hZDCp_Min400_Max10000_ZB");
  TH1D* hZDCm_Min400_Max10000_ZB            = (TH1D*) ZDCTemplate->Clone("hZDCm_Min400_Max10000_ZB");
  TH1D* hZDCp_SingleTrack_MaxPix400_ZB      = (TH1D*) ZDCTemplate->Clone("hZDCp_SingleTrack_MaxPix400_ZB");
  TH1D* hZDCm_SingleTrack_MaxPix400_ZB      = (TH1D*) ZDCTemplate->Clone("hZDCm_SingleTrack_MaxPix400_ZB");
  TH1D* hZDCp_Min400Max10000_STMP400_ZB     = (TH1D*) ZDCTemplate->Clone("hZDCp_Min400Max10000_STMP400_ZB");
  TH1D* hZDCm_Min400Max10000_STMP400_ZB     = (TH1D*) ZDCTemplate->Clone("hZDCm_Min400Max10000_STMP400_ZB");
  
  TH1D* hZDCp_Max10000_ZDCOR                = (TH1D*) ZDCTemplate->Clone("hZDCp_Max10000_ZDCOR");
  TH1D* hZDCm_Max10000_ZDCOR                = (TH1D*) ZDCTemplate->Clone("hZDCm_Max10000_ZDCOR");
  TH1D* hZDCp_Min400_Max10000_ZDCOR         = (TH1D*) ZDCTemplate->Clone("hZDCp_Min400_Max10000_ZDCOR");
  TH1D* hZDCm_Min400_Max10000_ZDCOR         = (TH1D*) ZDCTemplate->Clone("hZDCm_Min400_Max10000_ZDCOR");
  TH1D* hZDCp_SingleTrack_MaxPix400_ZDCOR   = (TH1D*) ZDCTemplate->Clone("hZDCp_SingleTrack_MaxPix400_ZDCOR");
  TH1D* hZDCm_SingleTrack_MaxPix400_ZDCOR   = (TH1D*) ZDCTemplate->Clone("hZDCm_SingleTrack_MaxPix400_ZDCOR");
  TH1D* hZDCp_Min400Max10000_STMP400_ZDCOR  = (TH1D*) ZDCTemplate->Clone("hZDCp_Min400Max10000_STMP400_ZDCOR");
  TH1D* hZDCm_Min400Max10000_STMP400_ZDCOR  = (TH1D*) ZDCTemplate->Clone("hZDCm_Min400Max10000_STMP400_ZDCOR");
  
  TH1D* HFTemplate = new TH1D(
    "HFTemplate",
    ";HF Energy Sum;Entries",
    50, 0, 100
  );
  TH1D* hHFp_Max10000_ZB                  = (TH1D*) HFTemplate->Clone("hHFp_Max10000_ZB");
  TH1D* hHFm_Max10000_ZB                  = (TH1D*) HFTemplate->Clone("hHFm_Max10000_ZB");
  TH1D* hHFp_Min400_Max10000_ZB           = (TH1D*) HFTemplate->Clone("hHFp_Min400_Max10000_ZB");
  TH1D* hHFm_Min400_Max10000_ZB           = (TH1D*) HFTemplate->Clone("hHFm_Min400_Max10000_ZB");
  TH1D* hHFp_SingleTrack_MaxPix400_ZB     = (TH1D*) HFTemplate->Clone("hHFp_SingleTrack_MaxPix400_ZB");
  TH1D* hHFm_SingleTrack_MaxPix400_ZB     = (TH1D*) HFTemplate->Clone("hHFm_SingleTrack_MaxPix400_ZB");
  TH1D* hHFp_Min400Max10000_STMP400_ZB    = (TH1D*) HFTemplate->Clone("hHFp_Min400Max10000_STMP400_ZB");
  TH1D* hHFm_Min400Max10000_STMP400_ZB    = (TH1D*) HFTemplate->Clone("hHFm_Min400Max10000_STMP400_ZB");
  
  TH1D* hHFp_Max10000_ZDCOR               = (TH1D*) HFTemplate->Clone("hHFp_Max10000_ZDCOR");
  TH1D* hHFm_Max10000_ZDCOR               = (TH1D*) HFTemplate->Clone("hHFm_Max10000_ZDCOR");
  TH1D* hHFp_Min400_Max10000_ZDCOR        = (TH1D*) HFTemplate->Clone("hHFp_Min400_Max10000_ZDCOR");
  TH1D* hHFm_Min400_Max10000_ZDCOR        = (TH1D*) HFTemplate->Clone("hHFm_Min400_Max10000_ZDCOR");
  TH1D* hHFp_SingleTrack_MaxPix400_ZDCOR  = (TH1D*) HFTemplate->Clone("hHFp_SingleTrack_MaxPix400_ZDCOR");
  TH1D* hHFm_SingleTrack_MaxPix400_ZDCOR  = (TH1D*) HFTemplate->Clone("hHFm_SingleTrack_MaxPix400_ZDCOR");
  TH1D* hHFp_Min400Max10000_STMP400_ZDCOR = (TH1D*) HFTemplate->Clone("hHFp_Min400Max10000_STMP400_ZDCOR");
  TH1D* hHFm_Min400Max10000_STMP400_ZDCOR = (TH1D*) HFTemplate->Clone("hHFm_Min400Max10000_STMP400_ZDCOR");
  
  TH2D* TrkVtxTemplate = new TH2D(
    "TrkVtxTemplate",
    ";nTrk;nVtx",
    500, 0, 1000,
    10, 0, 10
  );
  TH2D* hTrkVtx_Max10000_ZB_ZDCm = (TH2D*) TrkVtxTemplate->Clone("hTrkVtx_Max10000_ZB_ZDCm");
  TH2D* hTrkVtx_Max10000_ZB_ZDCp = (TH2D*) TrkVtxTemplate->Clone("hTrkVtx_Max10000_ZB_ZDCp");
  TH2D* hTrkVtx_Min400_Max10000_ZB_ZDCm = (TH2D*) TrkVtxTemplate->Clone("hTrkVtx_Min400_Max10000_ZB_ZDCm");
  TH2D* hTrkVtx_Min400_Max10000_ZB_ZDCp = (TH2D*) TrkVtxTemplate->Clone("hTrkVtx_Min400_Max10000_ZB_ZDCp");
  TH2D* hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCm = (TH2D*) TrkVtxTemplate->Clone("hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCm");
  TH2D* hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCp = (TH2D*) TrkVtxTemplate->Clone("hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCp");
  TH2D* hTrkVtx_Min400Max10000_STMP400_ZB_ZDCm = (TH2D*) TrkVtxTemplate->Clone("hTrkVtx_Min400Max10000_STMP400_ZB_ZDCm");
  TH2D* hTrkVtx_Min400Max10000_STMP400_ZB_ZDCp = (TH2D*) TrkVtxTemplate->Clone("hTrkVtx_Min400Max10000_STMP400_ZB_ZDCp");
  hTrkVtx_Max10000_ZB_ZDCm->SetTitle("HLT_MaxPixelCluster10000;nTrk;nVtx");
  hTrkVtx_Max10000_ZB_ZDCp->SetTitle("HLT_MaxPixelCluster10000;nTrk;nVtx");
  hTrkVtx_Min400_Max10000_ZB_ZDCm->SetTitle("HLT_MinPixelCluster400_MaxPixelCluster10000;nTrk;nVtx");
  hTrkVtx_Min400_Max10000_ZB_ZDCp->SetTitle("HLT_MinPixelCluster400_MaxPixelCluster10000;nTrk;nVtx");
  hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCm->SetTitle("HLT_SinglePixelTrackLowPt_MaxPixelCluster400;nTrk;nVtx");
  hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCp->SetTitle("HLT_SinglePixelTrackLowPt_MaxPixelCluster400;nTrk;nVtx");
  hTrkVtx_Min400Max10000_STMP400_ZB_ZDCm->SetTitle("HLT_MinPix400_MaxPix10000 OR HLT_SinPixTrkLowPt_MaxPix400;nTrk;nVtx");
  hTrkVtx_Min400Max10000_STMP400_ZB_ZDCp->SetTitle("HLT_MinPix400_MaxPix10000 OR HLT_SinPixTrkLowPt_MaxPix400;nTrk;nVtx");
  
  TH2D* TrkEtaVtxTemplate = new TH2D(
    "TrkVtxTemplate",
    ";Track eta;nVtx",
    500, 0, 1000,
    10, 0, 10
  );
  
  long int entries = tree->GetEntries();
  for (long int i = 0; i < entries; i++) {
    tree->GetEntry(i);
    
    // ZeroBias Triggers
    if (HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5) {
      hZDCp_Max10000_ZB->Fill(sumPlus);
      hZDCm_Max10000_ZB->Fill(sumMinus);
      hHFp_Max10000_ZB->Fill(hiHFPlus_pf);
      hHFm_Max10000_ZB->Fill(hiHFMinus_pf);
    }
    if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16) {
      hZDCp_Min400_Max10000_ZB->Fill(sumPlus);
      hZDCm_Min400_Max10000_ZB->Fill(sumMinus);
      hHFp_Min400_Max10000_ZB->Fill(hiHFPlus_pf);
      hHFm_Min400_Max10000_ZB->Fill(hiHFMinus_pf);
    }
    if (HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15) {
      hZDCp_SingleTrack_MaxPix400_ZB->Fill(sumPlus);
      hZDCm_SingleTrack_MaxPix400_ZB->Fill(sumMinus);
      hHFp_SingleTrack_MaxPix400_ZB->Fill(hiHFPlus_pf);
      hHFm_SingleTrack_MaxPix400_ZB->Fill(hiHFMinus_pf);
    }
    if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16 ||
        HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15
      ) {
      hZDCp_Min400Max10000_STMP400_ZB->Fill(sumPlus);
      hZDCm_Min400Max10000_STMP400_ZB->Fill(sumMinus);
      hHFp_Min400Max10000_STMP400_ZB->Fill(hiHFPlus_pf);
      hHFm_Min400Max10000_STMP400_ZB->Fill(hiHFMinus_pf);
    }
    // ZDCOR Triggers
    if (HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5) {
      hZDCp_Max10000_ZDCOR->Fill(sumPlus);
      hZDCm_Max10000_ZDCOR->Fill(sumMinus);
      hHFp_Max10000_ZDCOR->Fill(hiHFPlus_pf);
      hHFm_Max10000_ZDCOR->Fill(hiHFMinus_pf);
    }
    if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16) {
      hZDCp_Min400_Max10000_ZDCOR->Fill(sumPlus);
      hZDCm_Min400_Max10000_ZDCOR->Fill(sumMinus);
      hHFp_Min400_Max10000_ZDCOR->Fill(hiHFPlus_pf);
      hHFm_Min400_Max10000_ZDCOR->Fill(hiHFMinus_pf);
    }
    if (HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15) {
      hZDCp_SingleTrack_MaxPix400_ZDCOR->Fill(sumPlus);
      hZDCm_SingleTrack_MaxPix400_ZDCOR->Fill(sumMinus);
      hHFp_SingleTrack_MaxPix400_ZDCOR->Fill(hiHFPlus_pf);
      hHFm_SingleTrack_MaxPix400_ZDCOR->Fill(hiHFMinus_pf);
    }
    if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16 ||
        HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15
      ) {
      hZDCp_Min400Max10000_STMP400_ZDCOR->Fill(sumPlus);
      hZDCm_Min400Max10000_STMP400_ZDCOR->Fill(sumMinus);
      hHFp_Min400Max10000_STMP400_ZDCOR->Fill(hiHFPlus_pf);
      hHFm_Min400Max10000_STMP400_ZDCOR->Fill(hiHFMinus_pf);
    }
    
    bool ZDCm_0n = sumMinus < ZDCMinusMax;
    bool ZDCp_0n = sumPlus  < ZDCPlusMax;
    bool ZDCm_Xn = sumMinus > ZDCMinusMax;
    bool ZDCp_Xn = sumPlus  > ZDCPlusMax;
    bool HFm_Gap = hiHFMinus_pf < HFMinusMax;
    bool HFp_Gap = hiHFPlus_pf  < HFPlusMax;
    
    if (ZDCm_Xn) {
      // ZeroBias
      if (HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5) {
        hMax10000_XnAn->Fill(0.5);
        hTrkVtx_Max10000_ZB_ZDCm->Fill(nTrk, nVtx);
      }
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16) {
        hMin400_Max10000_XnAn->Fill(0.5);
        hTrkVtx_Min400_Max10000_ZB_ZDCm->Fill(nTrk, nVtx);
      }
      if (HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16) {
        hSingleTrack_MaxTrack_XnAn->Fill(0.5);
      }
      if (HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15) {
        hSingleTrack_MaxPix400_XnAn->Fill(0.5);
        hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCm->Fill(nTrk, nVtx);
      }
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16 ||
          HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15
        ) {
        hMin400Max10000_STMP400_XnAn->Fill(0.5);
        hTrkVtx_Min400Max10000_STMP400_ZB_ZDCm->Fill(nTrk, nVtx);
      }
      // ZDCOR
      if (HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5)                        hMax10000_XnAn->Fill(2.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16)    hMin400_Max10000_XnAn->Fill(2.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16)             hSingleTrack_MaxTrack_XnAn->Fill(2.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15)   hSingleTrack_MaxPix400_XnAn->Fill(2.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16 ||
          HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15
        ) hMin400Max10000_STMP400_XnAn->Fill(2.5);
    }
    if (ZDCp_Xn) {
      // ZeroBias
      if (HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5) {
        hMax10000_XnAn->Fill(1.5);
      }
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16) {
        hMin400_Max10000_XnAn->Fill(1.5);
      }
      if (HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16) {
        hSingleTrack_MaxTrack_XnAn->Fill(1.5);
      }
      if (HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15)  {
        hSingleTrack_MaxPix400_XnAn->Fill(1.5);
      }
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16 ||
          HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15
        ) {
        hMin400Max10000_STMP400_XnAn->Fill(1.5);
        hTrkVtx_Min400Max10000_STMP400_ZB_ZDCp->Fill(nTrk, nVtx);
      }
      // ZDCOR
      if (HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5)                        hMax10000_XnAn->Fill(3.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16)    hMin400_Max10000_XnAn->Fill(3.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16)             hSingleTrack_MaxTrack_XnAn->Fill(3.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15)   hSingleTrack_MaxPix400_XnAn->Fill(3.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16 ||
          HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15
        ) hMin400Max10000_STMP400_XnAn->Fill(3.5);
    }
    if (ZDCm_Xn && ZDCp_0n) {
      if (HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5)                       hMax10000_Xn0n->Fill(0.5);
      if (HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5)                        hMax10000_Xn0n->Fill(2.5);
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16)   hMin400_Max10000_Xn0n->Fill(0.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16)    hMin400_Max10000_Xn0n->Fill(2.5);
      if (HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16)            hSingleTrack_MaxTrack_Xn0n->Fill(0.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16)             hSingleTrack_MaxTrack_Xn0n->Fill(2.5);
      if (HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15)  hSingleTrack_MaxPix400_Xn0n->Fill(0.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15)   hSingleTrack_MaxPix400_Xn0n->Fill(2.5);
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16 ||
        HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15
      ) hMin400Max10000_STMP400_Xn0n->Fill(0.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16 ||
        HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15
      ) hMin400Max10000_STMP400_Xn0n->Fill(2.5);
    }
    if (ZDCm_0n && ZDCp_Xn) {
      if (HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5)                       hMax10000_Xn0n->Fill(1.5);
      if (HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5)                        hMax10000_Xn0n->Fill(3.5);
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16)   hMin400_Max10000_Xn0n->Fill(1.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16)    hMin400_Max10000_Xn0n->Fill(3.5);
      if (HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16)            hSingleTrack_MaxTrack_Xn0n->Fill(1.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16)             hSingleTrack_MaxTrack_Xn0n->Fill(3.5);
      if (HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15)  hSingleTrack_MaxPix400_Xn0n->Fill(1.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15)   hSingleTrack_MaxPix400_Xn0n->Fill(3.5);
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16 ||
        HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15
      ) hMin400Max10000_STMP400_Xn0n->Fill(1.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16 ||
        HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15
      ) hMin400Max10000_STMP400_Xn0n->Fill(3.5);
    }
    if (ZDCm_Xn && ZDCp_0n && HFp_Gap) {
      if (HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5)                       hMax10000_gammaN->Fill(0.5);
      if (HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5)                        hMax10000_gammaN->Fill(2.5);
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16)   hMin400_Max10000_gammaN->Fill(0.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16)    hMin400_Max10000_gammaN->Fill(2.5);
      if (HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16)            hSingleTrack_MaxTrack_gammaN->Fill(0.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16)             hSingleTrack_MaxTrack_gammaN->Fill(2.5);
      if (HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15)  hSingleTrack_MaxPix400_gammaN->Fill(0.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15)   hSingleTrack_MaxPix400_gammaN->Fill(2.5);
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16 ||
        HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15
      ) hMin400Max10000_STMP400_gammaN->Fill(0.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16 ||
        HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15
      ) hMin400Max10000_STMP400_gammaN->Fill(2.5);
    }
    if (ZDCm_0n && ZDCp_Xn && HFm_Gap) {
      if (HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v5)                       hMax10000_gammaN->Fill(1.5);
      if (HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v5)                        hMax10000_gammaN->Fill(3.5);
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16)   hMin400_Max10000_gammaN->Fill(1.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16)    hMin400_Max10000_gammaN->Fill(3.5);
      if (HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v16)            hSingleTrack_MaxTrack_gammaN->Fill(1.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrack_MaxPixelTrack_v16)             hSingleTrack_MaxTrack_gammaN->Fill(3.5);
      if (HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15)  hSingleTrack_MaxPix400_gammaN->Fill(1.5);
      if (HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15)   hSingleTrack_MaxPix400_gammaN->Fill(3.5);
      if (HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v16 ||
        HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v15
      ) hMin400Max10000_STMP400_gammaN->Fill(1.5);
      if (HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v16 ||
        HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v15
      ) hMin400Max10000_STMP400_gammaN->Fill(3.5);
    }
  } // end entries loop
  
  TFile* fout = TFile::Open(foutPath, "RECREATE");
  fout->cd();
  
  hMax10000_XnAn->Write();
  hMin400_Max10000_XnAn->Write();
  hSingleTrack_MaxTrack_XnAn->Write();
  hSingleTrack_MaxPix400_XnAn->Write();
  hMin400Max10000_STMP400_XnAn->Write();
  
  hMax10000_Xn0n->Write();
  hMin400_Max10000_Xn0n->Write();
  hSingleTrack_MaxTrack_Xn0n->Write();
  hSingleTrack_MaxPix400_Xn0n->Write();
  hMin400Max10000_STMP400_Xn0n->Write();
  
  hMax10000_gammaN->Write();
  hMin400_Max10000_gammaN->Write();
  hSingleTrack_MaxTrack_gammaN->Write();
  hSingleTrack_MaxPix400_gammaN->Write();
  hMin400Max10000_STMP400_gammaN->Write();
  
  hZDCp_Max10000_ZB->Write();
  hZDCm_Max10000_ZB->Write();
  hZDCp_Min400_Max10000_ZB->Write();
  hZDCm_Min400_Max10000_ZB->Write();
  hZDCp_SingleTrack_MaxPix400_ZB->Write();
  hZDCm_SingleTrack_MaxPix400_ZB->Write();
  hZDCp_Min400Max10000_STMP400_ZB->Write();
  hZDCm_Min400Max10000_STMP400_ZB->Write();
  
  hZDCp_Max10000_ZDCOR->Write();
  hZDCm_Max10000_ZDCOR->Write();
  hZDCp_Min400_Max10000_ZDCOR->Write();
  hZDCm_Min400_Max10000_ZDCOR->Write();
  hZDCp_SingleTrack_MaxPix400_ZDCOR->Write();
  hZDCm_SingleTrack_MaxPix400_ZDCOR->Write();
  hZDCp_Min400Max10000_STMP400_ZDCOR->Write();
  hZDCm_Min400Max10000_STMP400_ZDCOR->Write();
  
  hHFp_Max10000_ZB->Write();
  hHFm_Max10000_ZB->Write();
  hHFp_Min400_Max10000_ZB->Write();
  hHFm_Min400_Max10000_ZB->Write();
  hHFp_SingleTrack_MaxPix400_ZB->Write();
  hHFm_SingleTrack_MaxPix400_ZB->Write();
  hHFp_Min400Max10000_STMP400_ZB->Write();
  hHFm_Min400Max10000_STMP400_ZB->Write();
  
  hHFp_Max10000_ZDCOR->Write();
  hHFm_Max10000_ZDCOR->Write();
  hHFp_Min400_Max10000_ZDCOR->Write();
  hHFm_Min400_Max10000_ZDCOR->Write();
  hHFp_SingleTrack_MaxPix400_ZDCOR->Write();
  hHFm_SingleTrack_MaxPix400_ZDCOR->Write();
  hHFp_Min400Max10000_STMP400_ZDCOR->Write();
  hHFm_Min400Max10000_STMP400_ZDCOR->Write();
  
  hTrkVtx_Max10000_ZB_ZDCm->Write();
  hTrkVtx_Max10000_ZB_ZDCp->Write();
  hTrkVtx_Min400_Max10000_ZB_ZDCm->Write();
  hTrkVtx_Min400_Max10000_ZB_ZDCp->Write();
  hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCm->Write();
  hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCp->Write();
  hTrkVtx_Min400Max10000_STMP400_ZB_ZDCm->Write();
  hTrkVtx_Min400Max10000_STMP400_ZB_ZDCp->Write();
  
  fout->Close();
  fin->Close();
  return 0;
}


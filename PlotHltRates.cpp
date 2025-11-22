#include "TROOT.h"
#include <filesystem>

void PlotHltRates(
  TString finPath = "forestCheck_2025PbPb_399588.root",
  TString foutPath = "plots_399588/"
) {
  TFile* fin = TFile::Open(finPath, "READ");
  
  system(Form("mkdir -p %s", foutPath.Data()));
  
  TH1D* hZDCp_Max10000_ZB = (TH1D*) fin->Get("hZDCp_Max10000_ZB");
  TH1D* hZDCm_Max10000_ZB = (TH1D*) fin->Get("hZDCm_Max10000_ZB");
  TH1D* hHFp_Max10000_ZB = (TH1D*) fin->Get("hHFp_Max10000_ZB");
  TH1D* hHFm_Max10000_ZB = (TH1D*) fin->Get("hHFm_Max10000_ZB");
  
  TH1D* hZDCp_Min400_Max10000_ZB = (TH1D*) fin->Get("hZDCp_Min400_Max10000_ZB");
  TH1D* hZDCm_Min400_Max10000_ZB = (TH1D*) fin->Get("hZDCm_Min400_Max10000_ZB");
  TH1D* hHFp_Min400_Max10000_ZB = (TH1D*) fin->Get("hHFp_Min400_Max10000_ZB");
  TH1D* hHFm_Min400_Max10000_ZB = (TH1D*) fin->Get("hHFm_Min400_Max10000_ZB");
  
  TH1D* hZDCp_SingleTrack_MaxPix400_ZB = (TH1D*) fin->Get("hZDCp_SingleTrack_MaxPix400_ZB");
  TH1D* hZDCm_SingleTrack_MaxPix400_ZB = (TH1D*) fin->Get("hZDCm_SingleTrack_MaxPix400_ZB");
  TH1D* hHFp_SingleTrack_MaxPix400_ZB = (TH1D*) fin->Get("hHFp_SingleTrack_MaxPix400_ZB");
  TH1D* hHFm_SingleTrack_MaxPix400_ZB = (TH1D*) fin->Get("hHFm_SingleTrack_MaxPix400_ZB");
  
  TH1D* hZDCp_Min400Max10000_STMP400_ZB = (TH1D*) fin->Get("hZDCp_Min400Max10000_STMP400_ZB");
  TH1D* hZDCm_Min400Max10000_STMP400_ZB = (TH1D*) fin->Get("hZDCm_Min400Max10000_STMP400_ZB");
  TH1D* hHFp_Min400Max10000_STMP400_ZB = (TH1D*) fin->Get("hHFp_Min400Max10000_STMP400_ZB");
  TH1D* hHFm_Min400Max10000_STMP400_ZB = (TH1D*) fin->Get("hHFm_Min400Max10000_STMP400_ZB");
  
  TH1D* hZDCp_Max10000_ZDCOR = (TH1D*) fin->Get("hZDCp_Max10000_ZDCOR");
  TH1D* hZDCm_Max10000_ZDCOR = (TH1D*) fin->Get("hZDCm_Max10000_ZDCOR");
  TH1D* hHFp_Max10000_ZDCOR = (TH1D*) fin->Get("hHFp_Max10000_ZDCOR");
  TH1D* hHFm_Max10000_ZDCOR = (TH1D*) fin->Get("hHFm_Max10000_ZDCOR");
  
  TH1D* hZDCp_Min400_Max10000_ZDCOR = (TH1D*) fin->Get("hZDCp_Min400_Max10000_ZDCOR");
  TH1D* hZDCm_Min400_Max10000_ZDCOR = (TH1D*) fin->Get("hZDCm_Min400_Max10000_ZDCOR");
  TH1D* hHFp_Min400_Max10000_ZDCOR = (TH1D*) fin->Get("hHFp_Min400_Max10000_ZDCOR");
  TH1D* hHFm_Min400_Max10000_ZDCOR = (TH1D*) fin->Get("hHFm_Min400_Max10000_ZDCOR");
  
  TH1D* hZDCp_SingleTrack_MaxPix400_ZDCOR = (TH1D*) fin->Get("hZDCp_SingleTrack_MaxPix400_ZDCOR");
  TH1D* hZDCm_SingleTrack_MaxPix400_ZDCOR = (TH1D*) fin->Get("hZDCm_SingleTrack_MaxPix400_ZDCOR");
  TH1D* hHFp_SingleTrack_MaxPix400_ZDCOR = (TH1D*) fin->Get("hHFp_SingleTrack_MaxPix400_ZDCOR");
  TH1D* hHFm_SingleTrack_MaxPix400_ZDCOR = (TH1D*) fin->Get("hHFm_SingleTrack_MaxPix400_ZDCOR");
  
  TH1D* hZDCp_Min400Max10000_STMP400_ZDCOR = (TH1D*) fin->Get("hZDCp_Min400Max10000_STMP400_ZDCOR");
  TH1D* hZDCm_Min400Max10000_STMP400_ZDCOR = (TH1D*) fin->Get("hZDCm_Min400Max10000_STMP400_ZDCOR");
  TH1D* hHFp_Min400Max10000_STMP400_ZDCOR = (TH1D*) fin->Get("hHFp_Min400Max10000_STMP400_ZDCOR");
  TH1D* hHFm_Min400Max10000_STMP400_ZDCOR = (TH1D*) fin->Get("hHFm_Min400Max10000_STMP400_ZDCOR");
  
  TH1D* hMax10000_XnAn = (TH1D*) fin->Get("hMax10000_XnAn");
  TH1D* hMin400_Max10000_XnAn = (TH1D*) fin->Get("hMin400_Max10000_XnAn");
  TH1D* hSingleTrack_MaxTrack_XnAn = (TH1D*) fin->Get("hSingleTrack_MaxTrack_XnAn");
  TH1D* hSingleTrack_MaxPix400_XnAn = (TH1D*) fin->Get("hSingleTrack_MaxPix400_XnAn");
  TH1D* hMin400Max10000_STMP400_XnAn = (TH1D*) fin->Get("hMin400Max10000_STMP400_XnAn");
  
  TH1D* hMax10000_Xn0n = (TH1D*) fin->Get("hMax10000_Xn0n");
  TH1D* hMin400_Max10000_Xn0n = (TH1D*) fin->Get("hMin400_Max10000_Xn0n");
  TH1D* hSingleTrack_MaxTrack_Xn0n = (TH1D*) fin->Get("hSingleTrack_MaxTrack_Xn0n");
  TH1D* hSingleTrack_MaxPix400_Xn0n = (TH1D*) fin->Get("hSingleTrack_MaxPix400_Xn0n");
  TH1D* hMin400Max10000_STMP400_Xn0n = (TH1D*) fin->Get("hMin400Max10000_STMP400_Xn0n");
  
  TH1D* hMax10000_gammaN = (TH1D*) fin->Get("hMax10000_gammaN");
  TH1D* hMin400_Max10000_gammaN = (TH1D*) fin->Get("hMin400_Max10000_gammaN");
  TH1D* hSingleTrack_MaxTrack_gammaN = (TH1D*) fin->Get("hSingleTrack_MaxTrack_gammaN");
  TH1D* hSingleTrack_MaxPix400_gammaN = (TH1D*) fin->Get("hSingleTrack_MaxPix400_gammaN");
  TH1D* hMin400Max10000_STMP400_gammaN = (TH1D*) fin->Get("hMin400Max10000_STMP400_gammaN");
  
  TH2D* hTrkVtx_Max10000_ZB_ZDCm;
  TH2D* hTrkVtx_Max10000_ZB_ZDCp;
  TH2D* hTrkVtx_Min400_Max10000_ZB_ZDCm;
  TH2D* hTrkVtx_Min400_Max10000_ZB_ZDCp;
  TH2D* hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCm;
  TH2D* hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCp;
  TH2D* hTrkVtx_Min400Max10000_STMP400_ZB_ZDCm;
  TH2D* hTrkVtx_Min400Max10000_STMP400_ZB_ZDCp;
  if (false) {
    hTrkVtx_Max10000_ZB_ZDCm = (TH2D*) fin->Get("hTrkVtx_Max10000_ZB_ZDCm");
    hTrkVtx_Max10000_ZB_ZDCp = (TH2D*) fin->Get("hTrkVtx_Max10000_ZB_ZDCp");
    hTrkVtx_Min400_Max10000_ZB_ZDCm = (TH2D*) fin->Get("hTrkVtx_Min400_Max10000_ZB_ZDCm");
    hTrkVtx_Min400_Max10000_ZB_ZDCp = (TH2D*) fin->Get("hTrkVtx_Min400_Max10000_ZB_ZDCp");
    hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCm = (TH2D*) fin->Get("hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCm");
    hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCp = (TH2D*) fin->Get("hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCp");
    hTrkVtx_Min400Max10000_STMP400_ZB_ZDCm = (TH2D*) fin->Get("hTrkVtx_Min400Max10000_STMP400_ZB_ZDCm");
    hTrkVtx_Min400Max10000_STMP400_ZB_ZDCp = (TH2D*) fin->Get("hTrkVtx_Min400Max10000_STMP400_ZB_ZDCp");
  }
  
  TH1D* hZDC_All = (TH1D*) hZDCp_Min400Max10000_STMP400_ZB->Clone("hZDC_All");
  hZDC_All->Clear();
  TH1D* hZDC_ZB = (TH1D*) hZDCp_Min400Max10000_STMP400_ZB->Clone("hZDC_ZB");
  hZDC_ZB->Clear();
  TH1D* hZDC_ZDCOR = (TH1D*) hZDCp_Min400Max10000_STMP400_ZDCOR->Clone("hZDC_ZDCOR");
  hZDC_ZDCOR->Clear();
  
  hZDC_All->SetMaximum(10 * TMath::Max(
    hZDCp_Max10000_ZB->GetMaximum(),
    hZDCm_Max10000_ZB->GetMaximum()
  ));
  hZDC_ZB->SetMaximum(10 * TMath::Max(
    hZDCp_Max10000_ZB->GetMaximum(),
    hZDCm_Max10000_ZB->GetMaximum()
  ));
  hZDC_ZDCOR->SetMaximum(10 * TMath::Max(
    hZDCp_Max10000_ZDCOR->GetMaximum(),
    hZDCm_Max10000_ZDCOR->GetMaximum()
  ));
  hZDC_All->SetMinimum(10);
  hZDC_ZB->SetMinimum(10);
  hZDC_ZDCOR->SetMinimum(10);
  
  TH1D* hHF_All = (TH1D*) hHFp_Min400Max10000_STMP400_ZB->Clone("hHF_All");
  hHF_All->Clear();
  TH1D* hHF_ZB = (TH1D*) hHFp_Min400Max10000_STMP400_ZB->Clone("hHF_ZB");
  hHF_ZB->Clear();
  TH1D* hHF_ZDCOR = (TH1D*) hHFp_Min400Max10000_STMP400_ZDCOR->Clone("hHF_ZDCOR");
  hHF_ZDCOR->Clear();
  
  hHF_All->SetMaximum(10 * TMath::Max(
    hHFp_Max10000_ZB->GetMaximum(),
    hHFm_Max10000_ZB->GetMaximum()
  ));
  hHF_ZB->SetMaximum(10 * TMath::Max(
    hHFp_Max10000_ZB->GetMaximum(),
    hHFm_Max10000_ZB->GetMaximum()
  ));
  hHF_ZDCOR->SetMaximum(10 * TMath::Max(
    hHFp_Max10000_ZDCOR->GetMaximum(),
    hHFm_Max10000_ZDCOR->GetMaximum()
  ));
  hHF_All->SetMinimum(10);
  hHF_ZB->SetMinimum(10);
  hHF_ZDCOR->SetMinimum(10);
  
  hZDCp_Max10000_ZB->SetLineColor(kOrange-9);
  hZDCm_Max10000_ZB->SetLineColor(kAzure-9);
  hHFp_Max10000_ZB->SetLineColor(kOrange-9);
  hHFm_Max10000_ZB->SetLineColor(kAzure-9);
  
  hZDCp_Max10000_ZDCOR->SetLineColor(kPink+1);
  hZDCm_Max10000_ZDCOR->SetLineColor(kSpring+1);
  hHFp_Max10000_ZDCOR->SetLineColor(kPink+1);
  hHFm_Max10000_ZDCOR->SetLineColor(kSpring+1);
  
  hZDCp_Min400_Max10000_ZB->SetLineColor(kOrange+1);
  hZDCm_Min400_Max10000_ZB->SetLineColor(kAzure+1);
  hHFp_Min400_Max10000_ZB->SetLineColor(kOrange+1);
  hHFm_Min400_Max10000_ZB->SetLineColor(kAzure+1);
  
  hZDCp_Min400_Max10000_ZDCOR->SetLineColor(kPink-9);
  hZDCm_Min400_Max10000_ZDCOR->SetLineColor(kSpring-9);
  hHFp_Min400_Max10000_ZDCOR->SetLineColor(kPink-9);
  hHFm_Min400_Max10000_ZDCOR->SetLineColor(kSpring-9);
  
  hZDCp_SingleTrack_MaxPix400_ZB->SetLineColor(kOrange+2);
  hZDCm_SingleTrack_MaxPix400_ZB->SetLineColor(kAzure+2);
  hHFp_SingleTrack_MaxPix400_ZB->SetLineColor(kOrange+2);
  hHFm_SingleTrack_MaxPix400_ZB->SetLineColor(kAzure+2);

  hZDCp_SingleTrack_MaxPix400_ZDCOR->SetLineColor(kPink-8);
  hZDCm_SingleTrack_MaxPix400_ZDCOR->SetLineColor(kSpring-8);
  hHFp_SingleTrack_MaxPix400_ZDCOR->SetLineColor(kPink-8);
  hHFm_SingleTrack_MaxPix400_ZDCOR->SetLineColor(kSpring-8);
  
  hZDCp_Min400Max10000_STMP400_ZB->SetLineColor(kOrange+3);
  hZDCm_Min400Max10000_STMP400_ZB->SetLineColor(kAzure+3);
  hHFp_Min400Max10000_STMP400_ZB->SetLineColor(kOrange+3);
  hHFm_Min400Max10000_STMP400_ZB->SetLineColor(kAzure+3);
  
  hZDCp_Min400Max10000_STMP400_ZDCOR->SetLineColor(kPink-7);
  hZDCm_Min400Max10000_STMP400_ZDCOR->SetLineColor(kSpring-7);
  hHFp_Min400Max10000_STMP400_ZDCOR->SetLineColor(kPink-7);
  hHFm_Min400Max10000_STMP400_ZDCOR->SetLineColor(kSpring-7);
  
  TCanvas* canvas = new TCanvas("canvas", "", 1800, 1200);
  canvas->Divide(3, 2, 0.0001, 0.0001);
  
  canvas->cd(1);
  gStyle->SetOptStat(0);
  gPad->SetLogy(1);
  hZDC_All->SetTitle("ZDC Spectrum, ZB + ZDCOR Triggers");
  hZDC_All->Draw();
  hZDCp_Max10000_ZB->Draw("same hist");
  hZDCm_Max10000_ZB->Draw("same hist");
  hZDCp_Max10000_ZDCOR->Draw("same hist");
  hZDCm_Max10000_ZDCOR->Draw("same hist");
  hZDCp_Min400Max10000_STMP400_ZB->Draw("same hist");
  hZDCm_Min400Max10000_STMP400_ZB->Draw("same hist");
  hZDCp_Min400Max10000_STMP400_ZDCOR->Draw("same hist");
  hZDCm_Min400Max10000_STMP400_ZDCOR->Draw("same hist");
  hZDCp_Min400_Max10000_ZB->Draw("same hist");
  hZDCm_Min400_Max10000_ZB->Draw("same hist");
  hZDCp_Min400_Max10000_ZDCOR->Draw("same hist");
  hZDCm_Min400_Max10000_ZDCOR->Draw("same hist");
  hZDCp_SingleTrack_MaxPix400_ZB->Draw("same hist");
  hZDCm_SingleTrack_MaxPix400_ZB->Draw("same hist");
  hZDCp_SingleTrack_MaxPix400_ZDCOR->Draw("same hist");
  hZDCm_SingleTrack_MaxPix400_ZDCOR->Draw("same hist");
  
  canvas->cd(2);
  gStyle->SetOptStat(0);
  gPad->SetLogy(1);
  hZDC_ZB->SetTitle("ZDC Spectrum, ZB Triggers");
  hZDC_ZB->Draw();
  hZDCp_Max10000_ZB->Draw("same hist");
  hZDCm_Max10000_ZB->Draw("same hist");
  hZDCp_Min400_Max10000_ZB->Draw("same hist");
  hZDCm_Min400_Max10000_ZB->Draw("same hist");
  hZDCp_Min400Max10000_STMP400_ZB->Draw("same hist");
  hZDCm_Min400Max10000_STMP400_ZB->Draw("same hist");
  hZDCp_SingleTrack_MaxPix400_ZB->Draw("same hist");
  hZDCm_SingleTrack_MaxPix400_ZB->Draw("same hist");
  TLegend* leg_ZDC_ZB = new TLegend(0.13, 0.6, 0.4, 0.87);
  leg_ZDC_ZB->SetTextSize(0.025);
  leg_ZDC_ZB->SetFillStyle(0);
  leg_ZDC_ZB->SetBorderSize(0);
  leg_ZDC_ZB->AddEntry(hZDCm_Max10000_ZB, "ZDC-, ZeroBias_MaxPix10000", "l");
  leg_ZDC_ZB->AddEntry(hZDCm_SingleTrack_MaxPix400_ZB, "ZDC-, ZeroBias_SingleTrack_MaxPix400", "l");
  leg_ZDC_ZB->AddEntry(hZDCm_Min400_Max10000_ZB, "ZDC-, ZeroBias_Min400_Max10000", "l");
  leg_ZDC_ZB->AddEntry(hZDCm_Min400Max10000_STMP400_ZB, "ZDC-, Min400_Max10000 OR SingleTrack_MaxPix400", "l");
  leg_ZDC_ZB->AddEntry(hZDCp_Max10000_ZB, "ZDC+, ZeroBias_MaxPix10000", "l");
  leg_ZDC_ZB->AddEntry(hZDCp_SingleTrack_MaxPix400_ZB, "ZDC+, ZeroBias_SingleTrack_MaxPix400", "l");
  leg_ZDC_ZB->AddEntry(hZDCp_Min400_Max10000_ZB, "ZDC+, ZeroBias_Min400_Max10000", "l");
  leg_ZDC_ZB->AddEntry(hZDCp_Min400Max10000_STMP400_ZB, "ZDC+, Min400_Max10000 OR SingleTrack_MaxPix400", "l");
  leg_ZDC_ZB->Draw();
  
  canvas->cd(3);
  gStyle->SetOptStat(0);
  gPad->SetLogy(1);
  hZDC_ZDCOR->SetTitle("ZDC Spectrum, ZDCOR Triggers");
  hZDC_ZDCOR->Draw();
  hZDCp_Max10000_ZDCOR->Draw("same hist");
  hZDCm_Max10000_ZDCOR->Draw("same hist");
  hZDCp_Min400_Max10000_ZDCOR->Draw("same hist");
  hZDCm_Min400_Max10000_ZDCOR->Draw("same hist");
  hZDCp_Min400Max10000_STMP400_ZDCOR->Draw("same hist");
  hZDCm_Min400Max10000_STMP400_ZDCOR->Draw("same hist");
  hZDCp_SingleTrack_MaxPix400_ZDCOR->Draw("same hist");
  hZDCm_SingleTrack_MaxPix400_ZDCOR->Draw("same hist");
  TLegend* leg_ZDC_ZDCOR = new TLegend(0.13, 0.6, 0.4, 0.87);
  leg_ZDC_ZDCOR->SetTextSize(0.025);
  leg_ZDC_ZDCOR->SetFillStyle(0);
  leg_ZDC_ZDCOR->SetBorderSize(0);
  leg_ZDC_ZDCOR->AddEntry(hZDCm_Max10000_ZDCOR, "ZDC-, ZDC1nOR_MaxPix10000", "l");
  leg_ZDC_ZDCOR->AddEntry(hZDCm_Min400_Max10000_ZDCOR, "ZDC-, ZDC1nOR_Min400_Max10000", "l");
  leg_ZDC_ZDCOR->AddEntry(hZDCm_SingleTrack_MaxPix400_ZDCOR, "ZDC-, ZDC1nOR_SingleTrack_MaxPix400", "l");
  leg_ZDC_ZDCOR->AddEntry(hZDCm_Min400Max10000_STMP400_ZDCOR, "ZDC-, Min400_Max10000 OR SingleTrack_MaxPix400", "l");
  leg_ZDC_ZDCOR->AddEntry(hZDCp_Max10000_ZDCOR, "ZDC+, ZDC1nOR_MaxPix10000", "l");
  leg_ZDC_ZDCOR->AddEntry(hZDCp_Min400_Max10000_ZDCOR, "ZDC+, ZDC1nOR_Min400_Max10000", "l");
  leg_ZDC_ZDCOR->AddEntry(hZDCp_SingleTrack_MaxPix400_ZDCOR, "ZDC+, ZDC1nOR_SingleTrack_MaxPix400", "l");
  leg_ZDC_ZDCOR->AddEntry(hZDCp_Min400Max10000_STMP400_ZDCOR, "ZDC+, Min400_Max10000 OR SingleTrack_MaxPix400", "l");
  leg_ZDC_ZDCOR->Draw();
  
  canvas->cd(4);
  gStyle->SetOptStat(0);
  gPad->SetLogy(1);
  hHF_All->SetTitle("HF Spectrum, ZB + ZDCOR Triggers");
  hHF_All->Draw();
  hHFp_Max10000_ZB->Draw("same hist");
  hHFm_Max10000_ZB->Draw("same hist");
  hHFp_Max10000_ZDCOR->Draw("same hist");
  hHFm_Max10000_ZDCOR->Draw("same hist");
  hHFp_Min400_Max10000_ZB->Draw("same hist");
  hHFm_Min400_Max10000_ZB->Draw("same hist");
  hHFp_Min400_Max10000_ZDCOR->Draw("same hist");
  hHFm_Min400_Max10000_ZDCOR->Draw("same hist");
  hHFp_Min400Max10000_STMP400_ZB->Draw("same hist");
  hHFm_Min400Max10000_STMP400_ZB->Draw("same hist");
  hHFp_Min400Max10000_STMP400_ZDCOR->Draw("same hist");
  hHFm_Min400Max10000_STMP400_ZDCOR->Draw("same hist");
  hHFp_SingleTrack_MaxPix400_ZB->Draw("same hist");
  hHFm_SingleTrack_MaxPix400_ZB->Draw("same hist");
  hHFp_SingleTrack_MaxPix400_ZDCOR->Draw("same hist");
  hHFm_SingleTrack_MaxPix400_ZDCOR->Draw("same hist");
  
  canvas->cd(5);
  gStyle->SetOptStat(0);
  gPad->SetLogy(1);
  hHF_ZB->SetTitle("HF Spectrum, ZB Triggers");
  hHF_ZB->Draw();
  hHFp_Max10000_ZB->Draw("same hist");
  hHFm_Max10000_ZB->Draw("same hist");
  hHFp_Min400_Max10000_ZB->Draw("same hist");
  hHFm_Min400_Max10000_ZB->Draw("same hist");
  hHFp_Min400Max10000_STMP400_ZB->Draw("same hist");
  hHFm_Min400Max10000_STMP400_ZB->Draw("same hist");
  TLegend* leg_HF_ZB = new TLegend(0.13, 0.6, 0.4, 0.87);
  leg_HF_ZB->SetTextSize(0.025);
  leg_HF_ZB->SetFillStyle(0);
  leg_HF_ZB->SetBorderSize(0);
  leg_HF_ZB->AddEntry(hHFm_Max10000_ZB, "HF-, ZeroBias_MaxPix10000", "l");
  leg_HF_ZB->AddEntry(hHFm_Min400_Max10000_ZB, "HF-, ZeroBias_Min400_Max10000", "l");
  leg_HF_ZB->AddEntry(hHFm_SingleTrack_MaxPix400_ZB, "HF-, ZeroBias_SingleTrack_MaxPix400", "l");
  leg_HF_ZB->AddEntry(hHFm_Min400Max10000_STMP400_ZB, "HF-, Min400_Max10000 OR SingleTrack_MaxPix400", "l");
  leg_HF_ZB->AddEntry(hHFp_Max10000_ZB, "HF+, ZeroBias_MaxPix10000", "l");
  leg_HF_ZB->AddEntry(hHFp_Min400_Max10000_ZB, "HF+, ZeroBias_Min400_Max10000", "l");
  leg_HF_ZB->AddEntry(hHFp_SingleTrack_MaxPix400_ZB, "HF+, ZeroBias_SingleTrack_MaxPix400", "l");
  leg_HF_ZB->AddEntry(hHFp_Min400Max10000_STMP400_ZB, "HF+, Min400_Max10000 OR SingleTrack_MaxPix400", "l");
  leg_HF_ZB->Draw();
  
  canvas->cd(6);
  gStyle->SetOptStat(0);
  gPad->SetLogy(1);
  hHF_ZDCOR->SetTitle("HF Spectrum, ZDCOR Triggers");
  hHF_ZDCOR->Draw();
  hHFp_Max10000_ZDCOR->Draw("same hist");
  hHFm_Max10000_ZDCOR->Draw("same hist");
  hHFp_Min400_Max10000_ZDCOR->Draw("same hist");
  hHFm_Min400_Max10000_ZDCOR->Draw("same hist");
  hHFp_Min400Max10000_STMP400_ZDCOR->Draw("same hist");
  hHFm_Min400Max10000_STMP400_ZDCOR->Draw("same hist");
  TLegend* leg_HF_ZDCOR = new TLegend(0.13, 0.6, 0.4, 0.87);
  leg_HF_ZDCOR->SetTextSize(0.025);
  leg_HF_ZDCOR->SetFillStyle(0);
  leg_HF_ZDCOR->SetBorderSize(0);
  leg_HF_ZDCOR->AddEntry(hHFm_Max10000_ZDCOR, "HF-, ZDC1nOR_MaxPix10000", "l");
  leg_HF_ZDCOR->AddEntry(hHFm_Min400_Max10000_ZDCOR, "HF-, ZDC1nOR_Min400_Max10000", "l");
  leg_HF_ZDCOR->AddEntry(hHFm_SingleTrack_MaxPix400_ZDCOR, "HF-, ZDC1nOR_SingleTrack_MaxPix400", "l");
  leg_HF_ZDCOR->AddEntry(hHFm_Min400Max10000_STMP400_ZDCOR, "HF-, Min400_Max10000 OR SingleTrack_MaxPix400", "l");
  leg_HF_ZDCOR->AddEntry(hHFp_Max10000_ZDCOR, "HF+, ZDC1nOR_MaxPix10000", "l");
  leg_HF_ZDCOR->AddEntry(hHFp_Min400_Max10000_ZDCOR, "HF+, ZDC1nOR_Min400_Max10000", "l");
  leg_HF_ZDCOR->AddEntry(hHFp_SingleTrack_MaxPix400_ZDCOR, "HF+, ZDC1nOR_SingleTrack_MaxPix400", "l");
  leg_HF_ZDCOR->AddEntry(hHFp_Min400Max10000_STMP400_ZDCOR, "HF+, Min400_Max10000 OR SingleTrack_MaxPix400", "l");
  leg_HF_ZDCOR->Draw();
  
  canvas->Update();
  canvas->SaveAs(foutPath + "triggerStudies_ZDC+HF_ZeroBias_ZDCOR.pdf");
  
  
  TH1D* ZDCRatio = new TH1D(
    "ZDCRatio",
    "",
    10, 0, 20000
  );
  ZDCRatio->SetMinimum(0.0);
  ZDCRatio->SetMaximum(0.025);
  
  TCanvas* canvas4 = new TCanvas("canvas4", "", 600, 300);
  canvas4->cd();
  gStyle->SetOptStat(0);
  gPad->SetLogy(0);
  
  ZDCRatio->SetTitle("ZDCOR/ZB, HLT_MaxPixelCluster10000; ZDC sum; R_{ZDCOR/ZB}/Avg(R)");
  TH1D* ZDCOR_vs_ZB_Max10000_ZDCm =
    (TH1D*) hZDCm_Max10000_ZDCOR->Clone("ZDCOR_vs_ZB_Max10000_ZDCm");
  TH1D* ZDCOR_vs_ZB_Max10000_ZDCp =
    (TH1D*) hZDCp_Max10000_ZDCOR->Clone("ZDCOR_vs_ZB_Max10000_ZDCp");
  ZDCOR_vs_ZB_Max10000_ZDCm->Sumw2();
  ZDCOR_vs_ZB_Max10000_ZDCp->Sumw2();
  ZDCOR_vs_ZB_Max10000_ZDCm->Divide(hZDCm_Max10000_ZB);
  ZDCOR_vs_ZB_Max10000_ZDCp->Divide(hZDCp_Max10000_ZB);
  ZDCOR_vs_ZB_Max10000_ZDCm->Scale(1/ZDCOR_vs_ZB_Max10000_ZDCm->Integral(2,100));
  ZDCOR_vs_ZB_Max10000_ZDCp->Scale(1/ZDCOR_vs_ZB_Max10000_ZDCp->Integral(2,100));
  ZDCOR_vs_ZB_Max10000_ZDCm->SetLineColor(kAzure+2);
  ZDCOR_vs_ZB_Max10000_ZDCp->SetLineColor(kPink-8);
  ZDCRatio->Draw();
  ZDCOR_vs_ZB_Max10000_ZDCp->Draw("same");
  ZDCOR_vs_ZB_Max10000_ZDCm->Draw("same");
  canvas4->SaveAs(foutPath + "triggerStudies_ZDC_ZDCOR_vs_ZB_Max10000.pdf");
  
  ZDCRatio->SetTitle("ZDCOR/ZB, (HLT_MinPix400 || HLT_MaxPix400); ZDC sum; R_{ZDCOR/ZB}/Avg(R)");
  TH1D* ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCm =
    (TH1D*) hZDCm_Min400Max10000_STMP400_ZDCOR->Clone("ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCm");
  TH1D* ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCp =
    (TH1D*) hZDCp_Min400Max10000_STMP400_ZDCOR->Clone("ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCp");
  ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCm->Sumw2();
  ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCp->Sumw2();
  ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCm->Divide(hZDCm_Min400Max10000_STMP400_ZB);
  ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCp->Divide(hZDCp_Min400Max10000_STMP400_ZB);
  ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCm->Scale(1/ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCm->Integral(2,100));
  ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCp->Scale(1/ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCp->Integral(2,100));
  ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCm->SetLineColor(kAzure+2);
  ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCp->SetLineColor(kPink-8);
  ZDCRatio->Draw();
  ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCp->Draw("same");
  ZDCOR_vs_ZB_Min400Max10000_STMP400_ZDCm->Draw("same");
  canvas4->SaveAs(foutPath + "triggerStudies_ZDC_ZDCOR_vs_ZB_Min400Max10000_STMP400.pdf");
  
  ZDCRatio->SetTitle("(HLT_MinPix400 || HLT_MaxPix400) / HLT_MaxPix10000, ZeroBias; ZDC sum; R_{HLT}/Avg(R)");
  TH1D* Min400Max10000STMP400_vs_Max10000_ZB_ZDCm =
    (TH1D*) hZDCm_Min400Max10000_STMP400_ZB->Clone("Min400Max10000STMP400_vs_Max10000_ZB_ZDCm");
  TH1D* Min400Max10000STMP400_vs_Max10000_ZB_ZDCp =
    (TH1D*) hZDCp_Min400Max10000_STMP400_ZB->Clone("Min400Max10000STMP400_vs_Max10000_ZB_ZDCp");
  Min400Max10000STMP400_vs_Max10000_ZB_ZDCm->Sumw2();
  Min400Max10000STMP400_vs_Max10000_ZB_ZDCp->Sumw2();
  Min400Max10000STMP400_vs_Max10000_ZB_ZDCm->Divide(hZDCm_Max10000_ZB);
  Min400Max10000STMP400_vs_Max10000_ZB_ZDCp->Divide(hZDCp_Max10000_ZB);
  Min400Max10000STMP400_vs_Max10000_ZB_ZDCm->Scale(1/Min400Max10000STMP400_vs_Max10000_ZB_ZDCm->Integral(2,100));
  Min400Max10000STMP400_vs_Max10000_ZB_ZDCp->Scale(1/Min400Max10000STMP400_vs_Max10000_ZB_ZDCp->Integral(2,100));
  Min400Max10000STMP400_vs_Max10000_ZB_ZDCm->SetLineColor(kAzure+2);
  Min400Max10000STMP400_vs_Max10000_ZB_ZDCp->SetLineColor(kPink-8);
  ZDCRatio->Draw();
  Min400Max10000STMP400_vs_Max10000_ZB_ZDCp->Draw("same");
  Min400Max10000STMP400_vs_Max10000_ZB_ZDCm->Draw("same");
  canvas4->SaveAs(foutPath + "triggerStudies_ZDC_Min400Max10000STMP400_vs_Max10000_ZB.pdf");
  
  ZDCRatio->SetTitle("(HLT_MinPix400 || HLT_MaxPix400) / HLT_MaxPix10000, ZDC1nOR; ZDC sum; R_{HLT}/Avg(R)");
  TH1D* Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCm =
    (TH1D*) hZDCm_Min400Max10000_STMP400_ZDCOR->Clone("Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCm");
  TH1D* Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCp =
    (TH1D*) hZDCp_Min400Max10000_STMP400_ZDCOR->Clone("Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCp");
  Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCm->Sumw2();
  Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCp->Sumw2();
  Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCm->Divide(hZDCm_Max10000_ZDCOR);
  Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCp->Divide(hZDCp_Max10000_ZDCOR);
  Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCm->Scale(1/Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCm->Integral(2,100));
  Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCp->Scale(1/Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCp->Integral(2,100));
  Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCp->SetLineColor(kAzure+2);
  Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCm->SetLineColor(kPink-8);
  ZDCRatio->Draw();
  Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCp->Draw("same");
  Min400Max10000STMP400_vs_Max10000_ZDCOR_ZDCm->Draw("same");
  canvas4->SaveAs(foutPath + "triggerStudies_ZDC_Min400Max10000STMP400_vs_Max10000_ZDCOR.pdf");
  
  TCanvas* canvas2 = new TCanvas("canvas2", "", 600, 600);
  canvas2->cd();
  gStyle->SetOptStat(0);
  gPad->SetLogy(1);

  hMax10000_XnAn->SetMinimum(0.1 * hMax10000_XnAn->GetMinimum(10));
  hMax10000_XnAn->SetMaximum(10  * hMax10000_XnAn->GetMaximum());
  hMin400_Max10000_XnAn->SetMinimum(0.1 * hMin400_Max10000_XnAn->GetMinimum(10));
  hMin400_Max10000_XnAn->SetMaximum(10  * hMin400_Max10000_XnAn->GetMaximum());
  hSingleTrack_MaxTrack_XnAn->SetMinimum(0.1 * hSingleTrack_MaxTrack_XnAn->GetMinimum(10));
  hSingleTrack_MaxTrack_XnAn->SetMaximum(10  * hSingleTrack_MaxTrack_XnAn->GetMaximum());
  hSingleTrack_MaxPix400_XnAn->SetMinimum(0.1 * hSingleTrack_MaxPix400_XnAn->GetMinimum(10));
  hSingleTrack_MaxPix400_XnAn->SetMaximum(10  * hSingleTrack_MaxPix400_XnAn->GetMaximum());
  hMin400Max10000_STMP400_XnAn->SetMinimum(0.1 * hMin400Max10000_STMP400_XnAn->GetMinimum(10));
  hMin400Max10000_STMP400_XnAn->SetMaximum(10  * hMin400Max10000_STMP400_XnAn->GetMaximum());
 
  hMax10000_Xn0n->SetMinimum(0.1 * hMax10000_Xn0n->GetMinimum(10));
  hMax10000_Xn0n->SetMaximum(10  * hMax10000_Xn0n->GetMaximum());
  hMin400_Max10000_Xn0n->SetMinimum(0.1 * hMin400_Max10000_Xn0n->GetMinimum(10));
  hMin400_Max10000_Xn0n->SetMaximum(10  * hMin400_Max10000_Xn0n->GetMaximum());
  hSingleTrack_MaxTrack_Xn0n->SetMinimum(0.1 * hSingleTrack_MaxTrack_Xn0n->GetMinimum(10));
  hSingleTrack_MaxTrack_Xn0n->SetMaximum(10  * hSingleTrack_MaxTrack_Xn0n->GetMaximum());
  hSingleTrack_MaxPix400_Xn0n->SetMinimum(0.1 * hSingleTrack_MaxPix400_Xn0n->GetMinimum(10));
  hSingleTrack_MaxPix400_Xn0n->SetMaximum(10  * hSingleTrack_MaxPix400_Xn0n->GetMaximum());
  hMin400Max10000_STMP400_Xn0n->SetMinimum(0.1 * hMin400Max10000_STMP400_Xn0n->GetMinimum(10));
  hMin400Max10000_STMP400_Xn0n->SetMaximum(10  * hMin400Max10000_STMP400_Xn0n->GetMaximum());
  
  hMax10000_gammaN->SetMinimum(0.1 * hMax10000_gammaN->GetMinimum(10));
  hMax10000_gammaN->SetMaximum(10  * hMax10000_gammaN->GetMaximum());
  hMin400_Max10000_gammaN->SetMinimum(0.1 * hMin400_Max10000_gammaN->GetMinimum(10));
  hMin400_Max10000_gammaN->SetMaximum(10  * hMin400_Max10000_gammaN->GetMaximum());
  hSingleTrack_MaxTrack_gammaN->SetMinimum(0.1 * hSingleTrack_MaxTrack_gammaN->GetMinimum(10));
  hSingleTrack_MaxTrack_gammaN->SetMaximum(10  * hSingleTrack_MaxTrack_gammaN->GetMaximum());
  hSingleTrack_MaxPix400_gammaN->SetMinimum(0.1 * hSingleTrack_MaxPix400_gammaN->GetMinimum(10));
  hSingleTrack_MaxPix400_gammaN->SetMaximum(10  * hSingleTrack_MaxPix400_gammaN->GetMaximum());
  hMin400Max10000_STMP400_gammaN->SetMinimum(0.1 * hMin400Max10000_STMP400_gammaN->GetMinimum(10));
  hMin400Max10000_STMP400_gammaN->SetMaximum(10  * hMin400Max10000_STMP400_gammaN->GetMaximum());
  
  hMax10000_XnAn->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_Max10000_XnAn.pdf");
  hMin400_Max10000_XnAn->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_Min400_Max10000_XnAn.pdf");
  hSingleTrack_MaxTrack_XnAn->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_SingleTrack_MaxTrack_XnAn.pdf");
  hSingleTrack_MaxPix400_XnAn->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_SingleTrack_MaxPix400_XnAn.pdf");
  hMin400Max10000_STMP400_XnAn->Draw("hist text");
  hMin400_Max10000_XnAn->Draw("same hist");
  hSingleTrack_MaxPix400_XnAn->Draw("same hist");
  canvas2->SaveAs(foutPath + "triggerStudies_Min400Max10000_STMP400_XnAn.pdf");
  
  hMax10000_Xn0n->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_Max10000_Xn0n.pdf");
  hMin400_Max10000_Xn0n->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_Min400_Max10000_Xn0n.pdf");
  hSingleTrack_MaxTrack_Xn0n->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_SingleTrack_MaxTrack_Xn0n.pdf");
  hSingleTrack_MaxPix400_Xn0n->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_SingleTrack_MaxPix400_Xn0n.pdf");
  hMin400Max10000_STMP400_Xn0n->Draw("hist text");
  hMin400_Max10000_Xn0n->Draw("same hist");
  hSingleTrack_MaxPix400_Xn0n->Draw("same hist");
  canvas2->SaveAs(foutPath + "triggerStudies_Min400Max10000_STMP400_Xn0n.pdf");
  
  hMax10000_gammaN->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_Max10000_gammaN.pdf");
  hMin400_Max10000_gammaN->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_Min400_Max10000_gammaN.pdf");
  hSingleTrack_MaxTrack_gammaN->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_SingleTrack_MaxTrack_gammaN.pdf");
  hSingleTrack_MaxPix400_gammaN->Draw("hist text");
  canvas2->SaveAs(foutPath + "triggerStudies_SingleTrack_MaxPix400_gammaN.pdf");
  hMin400Max10000_STMP400_gammaN->Draw("hist text");
  hMin400_Max10000_gammaN->Draw("same hist");
  hSingleTrack_MaxPix400_gammaN->Draw("same hist");
  canvas2->SaveAs(foutPath + "triggerStudies_Min400Max10000_STMP400_gammaN.pdf");
  
//  TCanvas* canvas3 = new TCanvas("canvas3", "", 600, 1200);
//  canvas3->cd();
//  canvas3->Divide(2, 1, 0.0001, 0.0001);
//  gStyle->SetOptStat(0);
//  gPad->SetLogy(0);
//  
//  canvas3->cd(1);
//  hTrkVtx_Max10000_ZB_ZDCm->Draw("colz");
//  canvas3->cd(2);
//  hTrkVtx_Max10000_ZB_ZDCp->Draw("colz");
//  canvas3->SaveAs(foutPath + "triggerStudies_TrkVtx_Max10000_ZB.pdf");
//  
//  canvas3->cd(1);
//  hTrkVtx_Min400_Max10000_ZB_ZDCm->Draw("colz");
//  hTrkVtx_Min400_Max10000_ZB_ZDCp->Draw("colz");
//  canvas3->SaveAs(foutPath + "triggerStudies_.pdf");
//  
//  canvas3->cd(1);
//  hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCm->Draw("colz");
//  hTrkVtx_SingleTrack_MaxPix400_ZB_ZDCp->Draw("colz");
//  canvas3->SaveAs(foutPath + "triggerStudies_.pdf");
//  
//  canvas3->cd(1);
//  hTrkVtx_Min400Max10000_STMP400_ZB_ZDCm->Draw("colz");
//  hTrkVtx_Min400Max10000_STMP400_ZB_ZDCp->Draw("colz");
//  canvas3->SaveAs(foutPath + "triggerStudies_.pdf");
  
  fin->Close();
}

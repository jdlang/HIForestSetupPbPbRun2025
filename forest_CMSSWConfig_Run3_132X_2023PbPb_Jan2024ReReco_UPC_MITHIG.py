### HiForest CMSSW Configuration
# Collisions: 2023 PbPb UPC, Jan 2024 ReReco
# Input: miniAOD
# Type: data
# SW: CMSSW_13_2_10+, forest_CMSSW_13_2_X, Dfinder_14XX_miniAOD

import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run3_2023_cff import Run3_2023
process = cms.Process('HiForest', Run3_2023)

HIFOREST_VERSION = "132X"
GLOBAL_TAG = "132X_dataRun3_Prompt_HI_LowPtPhotonReg_v2"
#GLOBAL_TAG = "132X_dataRun3_Prompt_v3"
INPUT_TEST_FILE = "root://xrootd-vanderbilt.sites.opensciencegrid.org//store/hidata/HIRun2023A/HIForward0/MINIAOD/16Jan2024-v1/2810000/3cb20bb5-a7b1-43a2-8025-9807f4f51e71.root"
INPUT_MAX_EVENTS    = 1000
OUTPUT_FILE_NAME    = "HiForest_2023PbPbUPC_Jan24Reco.root"

INCLUDE_CENTRALITY  = False
INCLUDE_DFINDER     = True
INCLUDE_EGAMMA      = False
INCLUDE_HLT_OBJ     = False
INCLUDE_HLTFILTER   = True
INCLUDE_PFJETS      = True
INCLUDE_L1_OBJ      = False
INCLUDE_MUONS       = True
INCLUDE_PF_TREE     = True
INCLUDE_TRACKS      = True
INCLUDE_ZDC         = True

DEBUG               = False

###############################################################################

# HiForest info
process.load("HeavyIonsAnalysis.EventAnalysis.HiForestInfo_cfi")
process.HiForestInfo.info = cms.vstring("HiForest, miniAOD," + HIFOREST_VERSION + ", data")

# load Global Tag, geometry, etc.
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, GLOBAL_TAG, '')
process.HiForestInfo.GlobalTagLabel = process.GlobalTag.globaltag

###############################################################################

# input files
process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = cms.untracked.vstring(
         INPUT_TEST_FILE
    ),
    lumisToProcess=cms.untracked.VLuminosityBlockRange("374804:1-375746:max")
)

# number of events to process, set to -1 to process all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(INPUT_MAX_EVENTS)
)

# root output
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string(OUTPUT_FILE_NAME)
)

# edm output for debugging purposes
if DEBUG :
    process.output = cms.OutputModule(
       "PoolOutputModule",
       fileName = cms.untracked.string('HiForestEDM.root'),
       outputCommands = cms.untracked.vstring(
           'keep *',
       )
    )
    process.output_path = cms.EndPath(process.output)

###############################################################################

# Define centrality binning
if INCLUDE_CENTRALITY :
    process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
    process.centralityBin.Centrality = cms.InputTag("hiCentrality")
    process.centralityBin.centralityVariable = cms.string("HFtowers")

# event analysis
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('L1Trigger.L1TNtuples.l1MetFilterRecoTree_cfi')
if INCLUDE_PF_TREE :
    process.load('HeavyIonsAnalysis.EventAnalysis.particleFlowAnalyser_cfi')
    process.particleFlowAnalyser.ptMin = cms.double(0.1)
    process.particleFlowAnalyser.absEtaMax = cms.double(5.2)
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.hiEvtAnalyzer.doHFfilters = cms.bool(False)
process.hiEvtAnalyzer.doCentrality = cms.bool(False) # True needed to get HF info
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
if INCLUDE_HLT_OBJ :
    process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')
    process.hltobject.triggerNames = cms.vstring()
if INCLUDE_L1_OBJ :
    process.load('HeavyIonsAnalysis.EventAnalysis.l1object_cfi')

# electrons, photons, muons
if INCLUDE_EGAMMA :
    process.load('HeavyIonsAnalysis.EGMAnalysis.ggHiNtuplizer_cfi')
    process.ggHiNtuplizer.doGenParticles = cms.bool(False)
    process.ggHiNtuplizer.doMuons = cms.bool(False)
    process.ggHiNtuplizer.useValMapIso = cms.bool(False) # True here causes seg fault
    process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

# tracks
if INCLUDE_TRACKS :
    process.load("HeavyIonsAnalysis.TrackAnalysis.TrackAnalyzers_cff")
    process.PbPbTracks.trackPtMin = cms.untracked.double(0.2)
    process.PbPbTracks.trackEtaMax = cms.untracked.double(2.4)

# muons
if INCLUDE_MUONS :
    process.load("HeavyIonsAnalysis.MuonAnalysis.unpackedMuons_cfi")
    process.load("HeavyIonsAnalysis.MuonAnalysis.muonAnalyzer_cfi")
    process.load("HeavyIonsAnalysis.MuonAnalysis.hltMuTree_cfi")
    process.unpackedMuons.muonSelectors = cms.vstring()

# PF jets
if INCLUDE_PFJETS :
#    process.load("HeavyIonsAnalysis.JetAnalysis.ak2PFJetSequence_ppref_data_cff")
#    process.load("HeavyIonsAnalysis.JetAnalysis.ak3PFJetSequence_ppref_data_cff")
    process.load("HeavyIonsAnalysis.JetAnalysis.ak4PFJetSequence_ppref_data_cff")
    process.load("HeavyIonsAnalysis.JetAnalysis.ak4CaloJetSequence_pp_data_cff")

# ZDC RecHit Producer && Analyzer
# to prevent crash related to HcalSeverityLevelComputerRcd record
process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")
if INCLUDE_ZDC :
    process.load('HeavyIonsAnalysis.ZDCAnalysis.QWZDC2018Producer_cfi')
    process.load('HeavyIonsAnalysis.ZDCAnalysis.QWZDC2018RecHit_cfi')
    process.load('HeavyIonsAnalysis.ZDCAnalysis.zdcanalyzer_cfi')

    process.zdcdigi.SOI = cms.untracked.int32(2)
    process.zdcanalyzer.doZDCRecHit = cms.bool(False)
    process.zdcanalyzer.doZDCDigi = cms.bool(True)
    process.zdcanalyzer.zdcRecHitSrc = cms.InputTag("QWzdcreco")
    process.zdcanalyzer.zdcDigiSrc = cms.InputTag("hcalDigis", "ZDC")
    process.zdcanalyzer.calZDCDigi = cms.bool(False)
    process.zdcanalyzer.verbose = cms.bool(False)
    process.zdcanalyzer.nZdcTs = cms.int32(6)

    from CondCore.CondDB.CondDB_cfi import *
    process.es_pool = cms.ESSource("PoolDBESSource",
        timetype = cms.string('runnumber'),
        toGet = cms.VPSet(
            cms.PSet(
                record = cms.string("HcalElectronicsMapRcd"),
                tag = cms.string("HcalElectronicsMap_2021_v2.0_data")
            )
        ),
        connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
        authenticationMethod = cms.untracked.uint32(1)
    )
    process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')
    process.es_ascii = cms.ESSource(
        'HcalTextCalibrations',
        input = cms.VPSet(
            cms.PSet(
                object = cms.string('ElectronicsMap'),
                file = cms.FileInPath("HeavyIonsAnalysis/Configuration/data/ZDCemap_PbPbUPC2023.txt")
            )
        )
    )

###############################################################################

# main forest sequence
process.forest = cms.Path(
    process.HiForestInfo +
    process.hltanalysis +
    process.l1MetFilterRecoTree +
    process.trackSequencePbPb +
    process.hiEvtAnalyzer
)

if INCLUDE_HLT_OBJ :
     process.forest += process.hltobject
if INCLUDE_L1_OBJ :
     process.forest += process.l1object
if INCLUDE_PF_TREE :
    process.forest += process.particleFlowAnalyser
if INCLUDE_CENTRALITY :
    process.forest += process.centralityBin
if INCLUDE_EGAMMA :
    process.forest += process.ggHiNtuplizer
if INCLUDE_MUONS :
    process.forest += process.unpackedMuons
    process.forest += process.muonAnalyzer
    process.forest += process.hltMuTree
if INCLUDE_ZDC :
    process.forest += process.zdcanalyzer
#    process.zdcSequencePbPb

###############################################################################

# jet reco sequence

# ak PF Jets
if INCLUDE_PFJETS :
    jetPtMin           = 15
    jetAbsEtaMax       = 5.2
    
    # Select the types of jets filled
    matchJets = True        # Enables q/g and heavy flavor jet identification in MC

    # Choose which additional information is added to jet trees
    doHIJetID = True        # Fill jet ID and composition information branches
    doWTARecluster = False  # Add jet phi and eta for WTA axis
    
    #The following series of analyzers is to hack in a calorimeter jet correction
    process.hltAK4CaloRelativeCorrector = cms.EDProducer(
        "LXXXCorrectorProducer",
        algorithm = cms.string('AK4Calo'),
        level = cms.string('L2Relative')
    )
    process.hltAK4CaloAbsoluteCorrector = cms.EDProducer(
        "LXXXCorrectorProducer",
        algorithm = cms.string('AK4Calo'),
        level = cms.string('L3Absolute')
    )
    process.hltAK4CaloCorrector = cms.EDProducer(
        "ChainedJetCorrectorProducer",
        correctors = cms.VInputTag("hltAK4CaloRelativeCorrector", "hltAK4CaloAbsoluteCorrector")
    )
    process.hltAK4CaloJetsCorrected = cms.EDProducer(
        "CorrectedCaloJetProducer",
        correctors = cms.VInputTag("hltAK4CaloCorrector"),
        src = cms.InputTag("slimmedCaloJets")
    )
    process.ak4CaloJetAnalyzer.jetTag = cms.InputTag("hltAK4CaloJetsCorrected")
    #End calorimeter jet correction hack
    
    process.load("HeavyIonsAnalysis.JetAnalysis.extraJets_cff")
    from HeavyIonsAnalysis.JetAnalysis.clusterJetsFromMiniAOD_cff import setupPprefJets
    process.jetsR4 = cms.Sequence()
    setupPprefJets(
        'ak04PF',
        process.jetsR4,
        process,
        isMC = 0,
        radius = 0.40,
        JECTag = 'AK4PF'
    )
    process.ak04PFpatJetCorrFactors.levels = ['L2Relative', 'L3Absolute']
    process.ak04PFpatJetCorrFactors.primaryVertices = "offlineSlimmedPrimaryVertices"
    process.load("HeavyIonsAnalysis.JetAnalysis.candidateBtaggingMiniAOD_cff")
    process.ak4PFJetAnalyzer.jetTag = 'ak04PFpatJets'
    process.ak4PFJetAnalyzer.jetName = 'ak04PF'
    process.ak4PFJetAnalyzer.doHiJetID = doHIJetID
    process.ak4PFJetAnalyzer.doWTARecluster = doWTARecluster
    process.ak4PFJetAnalyzer.jetPtMin = jetPtMin
    process.ak4PFJetAnalyzer.jetAbsEtaMax = cms.untracked.double(jetAbsEtaMax)
    process.ak4PFJetAnalyzer.doSubEvent = False # Need to disable this, since there is some issue with the gen jet constituents.
    
    process.forest += process.extraJetsData * process.jetsR4 * process.ak4PFJetAnalyzer

###############################################################################

# D finder
if INCLUDE_DFINDER :
    runOnMC       = False
    VtxLabel      = 'offlineSlimmedPrimaryVertices'
    TrkLabel      = 'packedPFCandidates'
    TrkChi2Label  = 'packedPFCandidateTrackChi2'
    GenLabel      = 'prunedGenParticles'
    from Bfinder.finderMaker.finderMaker_75X_cff import finderMaker_75X,setCutForAllChannelsDfinder
    finderMaker_75X(process, runOnMC, VtxLabel, TrkLabel, TrkChi2Label, GenLabel)
    process.Dfinder.tkPtCut = cms.double(0.2) # before fit
    process.Dfinder.tkEtaCut = cms.double(2.4) # before fit
    process.Dfinder.Dchannel = cms.vint32(
        1, # K+pi- : D0bar
        1, # K-pi+ : D0
        0, # K-pi+pi+ : D+
        0, # K+pi-pi- : D-
        0, # K-pi-pi+pi+ : D0
        0, # K+pi+pi-pi- : D0bar
        0, # K+K-(Phi)pi+ : Ds+
        0, # K+K-(Phi)pi- : Ds-
        0, # D0(K-pi+)pi+ : D+*
        0, # D0bar(K+pi-)pi- : D-*
        0, # D0(K-pi-pi+pi+)pi+ : D+*
        0, # D0bar(K+pi+pi-pi-)pi- : D-*
        0, # D0bar(K+pi+)pi+ : B+
        0, # D0(K-pi+)pi- : B-
        0, # p+k-pi+: lambdaC+
        0, # p-k+pi-: lambdaCbar-
        0, # p+Ks(pi+pi-): lambdaC+
        0  # p-Ks(pi+pi-): lambdaCbar-
    )
    setCutForAllChannelsDfinder(
        process,
        dPtCut = 0.,            # Accept if > dPtCut
        VtxChiProbCut = 0.05,   # Accept if > VtxChiProbCut
        svpvDistanceCut = 0.5,  # Accept if < svpvDistanceCut
        alphaCut = 4.           # Accept if < alphaCut (note: 0 < alpha < pi)
    )
    process.Dfinder.dPtCut = cms.vdouble( # Accept if > dPtCut
        0.,  0.,    # K+pi- : D0bar
        1.,  1.,    # K-pi+pi+ : D+
        0.,  0.,    # K-pi-pi+pi+ : D0
        0.,  0.,    # K+K-(Phi)pi+ : Ds+
        0.,  0.,    # D0(K-pi+)pi+ : D+*
        0.,  0.,    # D0(K-pi-pi+pi+)pi+ : D+*
        0.,  0.,    # D0bar(K+pi+)pi+ : B+
        0.,  0.,    # p+k-pi+: lambdaC+
        2.,  2.     # p+Ks(pi+pi-): lambdaC+
    )
    process.Dfinder.printInfo = cms.bool(False)
    process.Dfinder.dropUnusedTracks = cms.bool(True)
    process.dfinder = cms.Path(process.DfinderSequence)

###############################################################################

# Event Selection Filters
process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
process.pclusterCompatibilityFilter = cms.Path(process.clusterCompatibilityFilter)
process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter)
#process.load('HeavyIonsAnalysis.EventAnalysis.hffilterPF_cfi')
#process.load('HeavyIonsAnalysis.ZDCAnalysis.HiZDCfilter_cfi')
process.pAna = cms.EndPath(process.skimanalysis)

# HLT Filter
if INCLUDE_HLTFILTER :
    from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel
    process.hltfilter = hltHighLevel.clone(
        HLTPaths = [
            # Double muons
            "HLT_HIUPC_DoubleMuCosmic*_MaxPixelCluster1000_v*",
            "HLT_HIUPC_DoubleMuOpen*_NotMBHF*AND_v*",
            # Not MB
            "HLT_HIUPC_NotMBHF*_v*",
            # Jet triggers
            "HLT_HIUPC_SingleJet*_ZDC1n*XOR_*MaxPixelCluster*",
            "HLT_HIUPC_SingleJet*_NotMBHF2AND_*MaxPixelCluster*",
            # Single muon
            "HLT_HIUPC_SingleMu*_NotMBHF*_MaxPixelCluster*",
            # Single EG
            "HLT_HIUPC_SingleEG3_NotMBHF2AND_v*",
            "HLT_HIUPC_SingleEG5_NotMBHF2AND_v*",
            "HLT_HIUPC_SingleEG3_NotMBHF2AND_SinglePixelTrack_MaxPixelTrack_v*",
            "HLT_HIUPC_SingleEG5_NotMBHF2AND_SinglePixelTrack_MaxPixelTrack_v*",
            # ZDC 1n or, low pixel clusters
            "HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v*",
            "HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v*",
            # ZB, single pixel track
            "HLT_HIUPC_ZeroBias_SinglePixelTrack_MaxPixelTrack_v*"
        ]
    )
    process.hltfilter.andOr = cms.bool(True)  # True = OR, False = AND between the HLT paths
    process.hltfilter.throw = cms.bool(False) # throw exception on unknown path names
    process.filterSequence = cms.Sequence(
        process.hltfilter *
        process.primaryVertexFilter
#        (process.zdcrecoRun3 + process.zdcEnergyFilter0nOr)
    )

process.superFilterPath = cms.Path(process.filterSequence)
process.skimanalysis.superFilters = cms.vstring('superFilterPath')
for path in process.paths:
   getattr(process, path)._seq = process.filterSequence * getattr(process,path)._seq

if DEBUG :
    process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
        ignoreTotal = cms.untracked.int32(0),
        moduleMemorySummary = cms.untracked.bool(True),
        monitorPssAndPrivate = cms.untracked.bool(False),
        oncePerEventMode = cms.untracked.bool(False)
    )

process.MessageLogger.cerr.FwkReport.reportEvery = 100

### HiForest CMSSW Configuration
# Collisions: 2025 PbPb UPC, Prompt Reco
# Input: miniAOD
# Type: data
# SW: CMSSW_15_1_0_patch5, forest_CMSSW_15_1_X, Dfinder_14XX_miniAOD

import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run3_2025_UPC_cff import Run3_2025_UPC
process = cms.Process('HiForest', Run3_2025_UPC)

HIFOREST_VERSION = "151X"
GLOBAL_TAG = "151X_dataRun3_Prompt_v1"
INPUT_TEST_FILE = "root://eoscms.cern.ch//eos/cms/store/hidata/HIRun2025A/HIForward2/MINIAOD/PromptReco-v1/000/399/660/00000/bfaa8b34-3989-4ae1-a291-84e41b623a71.root"
INPUT_MAX_EVENTS    = 1000
OUTPUT_FILE_NAME    = "HiForest_2025PbPbUPC_PromptReco.root"

INCLUDE_CENTRALITY  = False
INCLUDE_DFINDER     = True
INCLUDE_EGAMMA      = False
INCLUDE_FSC         = True
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
    process.particleFlowAnalyser.ptMin = cms.double(0.0)
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
    process.PbPbTracks.dedxEstimators = cms.VInputTag([
      #"dedxEstimator:dedxPixelLikelihood",
      #"dedxEstimator:dedxStripLikelihood",
      "dedxEstimator:dedxAllLikelihood"
    ])

# muons
if INCLUDE_MUONS :
    process.load("HeavyIonsAnalysis.MuonAnalysis.unpackedMuons_cfi")
    process.load("HeavyIonsAnalysis.MuonAnalysis.muonAnalyzer_cfi")
    process.load("HeavyIonsAnalysis.MuonAnalysis.hltMuTree_cfi")
    process.unpackedMuons.muonSelectors = cms.vstring()

# ZDC RecHit Producer && Analyzer
# to prevent crash related to HcalSeverityLevelComputerRcd record
process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")
if INCLUDE_ZDC :
    process.load('HeavyIonsAnalysis.ZDCAnalysis.ZDCAnalyzersPbPb_cff')
if INCLUDE_FSC :
    process.load('HeavyIonsAnalysis.ZDCAnalysis.FSCAnalyzers_cff')

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
if INCLUDE_ZDC or INCLUDE_FSC :
    process.forest += process.zdcSequencePbPb
    process.zdcanalyzer.doZdcDigis = cms.bool(False)  # space-saving
if INCLUDE_FSC :
    process.forest += process.fscSequence

###############################################################################

# jet reco sequence

# ak PF Jets
if INCLUDE_PFJETS :
    process.load('HeavyIonsAnalysis.JetAnalysis.ak4PFJetSequence_ppref_data_cff')
    jetPtMin           = 15
    jetAbsEtaMax       = 5.2

    # Select the types of jets filled
    matchJets = True        # Enables q/g and heavy flavor jet identification in MC

    # Choose which additional information is added to jet trees
    doHIJetID = True        # Fill jet ID and composition information branches
    doWTARecluster = False  # Add jet phi and eta for WTA axis
    doBtagging  =  False    # Note that setting to True increases computing time a lot

    # 0 means use original mini-AOD jets, otherwise use R value, e.g., 3,4,8
    # Add all the values you want to process to the list
    jetLabels = ["0"]

    # add candidate tagging for all selected jet radii
    from HeavyIonsAnalysis.JetAnalysis.setupJets_ppRef_cff import candidateBtaggingMiniAOD

    for jetLabel in jetLabels:
        candidateBtaggingMiniAOD(
            process,
            isMC = False,
            jetPtMin = jetPtMin,
            jetCorrLevels = ['L2Relative', 'L2L3Residual'],
            doBtagging = doBtagging,
            labelR = jetLabel
        )

        # setup jet analyzer
        setattr(process,"ak"+jetLabel+"PFJetAnalyzer",process.ak4PFJetAnalyzer.clone())
        getattr(process,"ak"+jetLabel+"PFJetAnalyzer").jetTag = "selectedUpdatedPatJetsAK"+jetLabel+"PFCHSBtag"
        getattr(process,"ak"+jetLabel+"PFJetAnalyzer").jetName = 'ak'+jetLabel+'PF'
        getattr(process,"ak"+jetLabel+"PFJetAnalyzer").matchJets = matchJets
        getattr(process,"ak"+jetLabel+"PFJetAnalyzer").matchTag = 'patJetsAK'+jetLabel+'PFUnsubJets'
        getattr(process,"ak"+jetLabel+"PFJetAnalyzer").doBtagging = doBtagging
        getattr(process,"ak"+jetLabel+"PFJetAnalyzer").doHiJetID = doHIJetID
        getattr(process,"ak"+jetLabel+"PFJetAnalyzer").doWTARecluster = doWTARecluster
        getattr(process,"ak"+jetLabel+"PFJetAnalyzer").jetPtMin = jetPtMin
        getattr(process,"ak"+jetLabel+"PFJetAnalyzer").jetAbsEtaMax = cms.untracked.double(jetAbsEtaMax)
        getattr(process,"ak"+jetLabel+"PFJetAnalyzer").rParam = 0.4 if jetLabel=='0' else float(jetLabel)*0.1
        if doBtagging:
            getattr(process,"ak"+jetLabel+"PFJetAnalyzer").pfJetProbabilityBJetTag = cms.untracked.string("pfJetProbabilityBJetTagsAK"+jetLabel+"PFCHSBtag")
            getattr(process,"ak"+jetLabel+"PFJetAnalyzer").pfUnifiedParticleTransformerAK4JetTags = cms.untracked.string("pfUnifiedParticleTransformerAK4JetTagsAK"+jetLabel+"PFCHSBtag")
        process.forest += getattr(process,"ak"+jetLabel+"PFJetAnalyzer")

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
        1, # K-pi+pi+ : D+
        1, # K+pi-pi- : D-
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
process.load('HeavyIonsAnalysis.EventAnalysis.hffilterPF_cfi')
process.load('HeavyIonsAnalysis.ZDCAnalysis.HiZDCfilter_cfi')
process.pAna = cms.EndPath(process.skimanalysis)

# HLT Filter
if INCLUDE_HLTFILTER :
    from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel
    process.hltfilter = hltHighLevel.clone(
        HLTPaths = [
            # ZeroBias
            "HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v*",
            "HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v*",
            "HLT_HIUPC_ZeroBias_MaxPixelCluster10000_v*",
            # ZDCOR
            "HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v*",
            "HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v*",
            "HLT_HIUPC_ZDC1nOR_MaxPixelCluster10000_v*",
            # NotHFANDJets + ZDCORJets
            "HLT_HIUPC_SingleJet12_ZDC1nXOR_MaxPixelCluster10000_v*",
            "HLT_HIUPC_SingleJet12_ZDC1nAsymXOR_MaxPixelCluster10000_v*",
            "HLT_HIUPC_SingleJet12_NotZDC_OR_MaxPixelCluster10000_v*",
            "HLT_HIUPC_SingleJet12_NotMBHF2AND_MaxPixelCluster10000_v*",
            "HLT_HIUPC_SingleJet16_ZDC1nXOR_MaxPixelCluster10000_v*",
            "HLT_HIUPC_SingleJet16_ZDC1nAsymXOR_MaxPixelCluster10000_v*",
            "HLT_HIUPC_SingleJet16_NotZDC_OR_MaxPixelCluster10000_v*",
            "HLT_HIUPC_SingleJet16_NotMBHF2AND_MaxPixelCluster10000_v*",
            # UPCSingleMuon
            "HLT_HIUPC_SingleMuOpen_NotMBHF2OR_MaxPixelCluster1000_v*",
            "HLT_HIUPC_SingleMuOpen_NotMBHF2AND_MaxPixelCluster1000_v*",
            "HLT_HIUPC_SingleMuOpen_BptxAND_MaxPixelCluster1000_v*"
        ]
    )
    process.filterSequence = cms.Sequence(
        process.hltfilter *
        process.primaryVertexFilter *
        (process.zdcrecoRun3 + process.zdcEnergyFilter0nOr)
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

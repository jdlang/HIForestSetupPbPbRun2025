### HiForest CMSSW Configuration
# Collisions: 2025 PbPb Empty Bunch Crossing, Prompt Reco
# Input: miniAOD
# Type: data
# SW: CMSSW_15_1_0_patch4+, forest_CMSSW_15_1_X, Dfinder_14XX_miniAOD

import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run3_2025_cff import Run3_2025
process = cms.Process('HiForest', Run3_2025)

HIFOREST_VERSION = "151X"
GLOBAL_TAG = "151X_dataRun3_Prompt_v1"
INPUT_TEST_FILE = "/store/hidata/HIRun2025A/HIEmptyBX/MINIAOD/PromptReco-v1/000/398/998/00000/a16c2beb-ea9b-4bb4-81ea-3fcaba69743d.root"
INPUT_MAX_EVENTS    = 1000
OUTPUT_FILE_NAME    = "HiForest_2025PbPbEmptyBX_PromptReco.root"

INCLUDE_CENTRALITY  = False
INCLUDE_EGAMMA      = False
INCLUDE_FSC         = False
INCLUDE_HLT_OBJ     = False
INCLUDE_L1_OBJ      = False
INCLUDE_MUONS       = False
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

# Event Selection Filters
process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
process.pclusterCompatibilityFilter = cms.Path(process.clusterCompatibilityFilter)
process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter)
process.load('HeavyIonsAnalysis.EventAnalysis.hffilterPF_cfi')
process.load('HeavyIonsAnalysis.ZDCAnalysis.HiZDCfilter_cfi')
process.pAna = cms.EndPath(process.skimanalysis)

if DEBUG :
    process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
        ignoreTotal = cms.untracked.int32(0),
        moduleMemorySummary = cms.untracked.bool(True),
        monitorPssAndPrivate = cms.untracked.bool(False),
        oncePerEventMode = cms.untracked.bool(False)
    )

process.MessageLogger.cerr.FwkReport.reportEvery = 100

# 2025 PbPb UPC
# CMSSW_15_1_0_patch3
# HIForward[0-??]

from CRABClient.UserUtilities import config
from CRABClient.UserUtilities import getUsername
username = getUsername()

###############################################################################
# INPUT/OUTPUT SETTINGS

pd = '0'
run = '399966-399989'
jobTag = 'PbPbUPC_HIForward' + pd + '_' + run + '_QuickAnalysis'
cmsswConfig = 'forest_CMSSWConfig_Run3_151X_2025PbPb_UPC_MITHIG.py'

input = '/HIForward' + pd + '/HIRun2025A-PromptReco-v1/MINIAOD'
inputDatabase = 'global'

output = '/store/group/phys_heavyions/' + username + '/Run3_PbPbUPC/Forest_2025_PromptReco/'
outputServer = 'T2_CH_CERN'

###############################################################################

config = config()

config.General.requestName = jobTag
config.General.workArea = 'CrabWorkArea'
config.General.transferOutputs = True

config.JobType.psetName = cmsswConfig
config.JobType.pluginName = 'Analysis'
config.JobType.maxMemoryMB = 3000
config.JobType.maxJobRuntimeMin = 60
config.JobType.pyCfgParams = ['noprint']
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = input
config.Data.inputDBS = inputDatabase
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions25HI/DCSOnly_JSONS/dailyDCSOnlyJSON/Collisions25HI_5p36TeV_399465_400265_DCSOnly_TkPx.json'
config.Data.runRange = run
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 2000
config.Data.totalUnits = -1

config.Data.outLFNDirBase = output
config.Data.publication = False
config.Data.allowNonValidInputDataset = True

config.Site.storageSite = outputServer

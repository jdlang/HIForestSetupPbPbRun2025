# 2025 PbPb UPC
# CMSSW_15_1_0_patch3
# HIForward[0-??]

from CRABClient.UserUtilities import config
from CRABClient.UserUtilities import getUsername
username = getUsername()

###############################################################################
# INPUT/OUTPUT SETTINGS

pd = 'HIForward0'
run = '400098-400243'
jobTag = 'PbPbUPC_' + pd + '_' + run + '_QuickAnalysis'
cmsswConfig = 'forest_CMSSWConfig_Run3_151X_2025PbPb_UPC_MITHIG.py'

inputDAS = '/' + pd + '/HIRun2025A-PromptReco-v1/MINIAOD'
inputDatabase = 'global'

output = '/store/user/' + username + '/Run3_PbPbUPC/Forest_2025_PromptReco/'

outputServer = 'T2_US_Vanderbilt'

###############################################################################

config = config()

config.General.requestName = jobTag
config.General.workArea = 'CrabWorkArea'
config.General.transferOutputs = True

config.JobType.psetName = cmsswConfig
config.JobType.pluginName = 'Analysis'
config.JobType.maxMemoryMB = 3000
config.JobType.maxJobRuntimeMin = 150
config.JobType.pyCfgParams = ['noprint']
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = inputDAS
config.Data.inputDBS = inputDatabase
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions25HI/DCSOnly_JSONS/dailyDCSOnlyJSON/Collisions25HI_5p36TeV_399465_400339_DCSOnly_TkPx.json'
config.Data.runRange = run
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 5000
config.Data.totalUnits = -1

config.Data.outLFNDirBase = output
config.Data.publication = False
config.Data.allowNonValidInputDataset = True

config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = outputServer

AccountingGroup = 'group_u_CMS.u_zh.priority'

# 2025 PbPb UPC
# CMSSW_15_1_0_patch3
# HIForward[0-??]

from CRABClient.UserUtilities import config
from CRABClient.UserUtilities import getUsername
username = getUsername()

###############################################################################
# INPUT/OUTPUT SETTINGS

pd = 'HIForward0'
jobTag = 'PbPbUPC_' + pd + '_Part1'
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
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions25HI/Cert_Collisions2025_HI_399465_400007_Golden.json'
#config.Data.runRange = '399465-400007'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 2
config.Data.totalUnits = -1

config.Data.outLFNDirBase = output
config.Data.publication = False
config.Data.allowNonValidInputDataset = True

config.Site.whitelist = ['T2_US_Vanderbilt', 'T2_CH_CERN']
config.Site.storageSite = outputServer

AccountingGroup = 'group_u_CMS.u_zh.priority'

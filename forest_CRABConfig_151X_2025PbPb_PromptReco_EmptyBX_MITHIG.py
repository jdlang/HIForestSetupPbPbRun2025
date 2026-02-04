# 2025 PbPb Empty Bunch Crossing
# CMSSW_15_1_0_patch4+
# HIEmptyBX

from CRABClient.UserUtilities import config
from CRABClient.UserUtilities import getUsername
username = getUsername()

###############################################################################
# INPUT/OUTPUT SETTINGS

pd = 'HIEmptyBX'
jobTag = '2025PbPbEmptyBX_PromptReco_20260204Forest_' + pd
cmsswConfig = 'forest_CMSSWConfig_Run3_151X_2025PbPb_PromptReco_EmptyBX_MITHIG.py'

inputDAS = '/' + pd + '/HIRun2025A-PromptReco-v1/MINIAOD'
inputDatabase = 'global'

output = '/store/user/' + username + '/Run3_PbPbUPC/Forest_2025_PromptReco_Feb2025Forest/'

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
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions25HI/Cert_Collisions2025_HI_399465_400426_Golden.json'
config.Data.runRange = '399465-400426'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 5
config.Data.totalUnits = -1

config.Data.outLFNDirBase = output
config.Data.publication = False
config.Data.allowNonValidInputDataset = True

config.Site.whitelist = ['T2_US_Vanderbilt', 'T2_CH_CERN']
config.Site.storageSite = outputServer

accounting_group = 'group_u_CMS.u_zh.priority'

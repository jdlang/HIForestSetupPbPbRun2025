# 2025 PbPb UPC
# CMSSW_15_1_0_patch3
# HIForward[0-??]

from CRABClient.UserUtilities import config
from CRABClient.UserUtilities import getUsername
username = getUsername()

###############################################################################
# INPUT/OUTPUT SETTINGS

pd = 'HIForward0'
jobTag = '2026PbPbUPC_PromptReco_20260618Forest_404337-404509_' + pd
cmsswConfig = 'forest_CMSSWConfig_Run3_161X_2026PbPb_PromptReco_UPC_MITHIG.py'

inputDAS = '/' + pd + '/HIRun2026A-PromptReco-v1/MINIAOD'
inputDatabase = 'global'

output = '/store/user/' + username + '/Run3_PbPbUPC/Forest_2026_PromptReco/'

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
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions26HI/Collisions26HI_5p36TeV_404337_404509_golden.json'
config.Data.runRange = '404337-404509'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 5
config.Data.totalUnits = -1

config.Data.outLFNDirBase = output
config.Data.publication = False
config.Data.allowNonValidInputDataset = True

#config.Site.whitelist = ['T2_US_Vanderbilt', 'T2_CH_CERN']
config.Site.storageSite = outputServer

accounting_group = 'group_u_CMS.u_zh.priority'

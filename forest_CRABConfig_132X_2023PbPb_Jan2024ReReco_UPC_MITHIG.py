# 2023 PbPb UPC, Jan 2024 ReReco
# CMSSW_13_2_10+
# HIForward[0-19]

from CRABClient.UserUtilities import config
from CRABClient.UserUtilities import getUsername
username = getUsername()

###############################################################################
# INPUT/OUTPUT SETTINGS

pd = 'HIForward0'
jobTag = '2023PbPbUPC_Jan2024ReReco_20260201Forest_' + pd
cmsswConfig = 'forest_CMSSWConfig_Run3_132X_2023PbPb_Jan2024ReReco_UPC_MITHIG.py'

inputDAS = '/' + pd + '/HIRun2023A-16Jan2024-v1/MINIAOD'
inputDatabase = 'global'

output = '/store/user/' + username + '/Run3_PbPbUPC/Forest_2023_Jan2024ReReco_2025Reforest/'

outputServer = 'T2_US_Vanderbilt'

###############################################################################

config = config()

config.General.requestName = jobTag
config.General.workArea = 'CrabWorkArea'
config.General.transferOutputs = True

config.JobType.psetName = cmsswConfig
config.JobType.pluginName = 'Analysis'
config.JobType.maxMemoryMB = 2500
config.JobType.maxJobRuntimeMin = 60
config.JobType.pyCfgParams = ['noprint']
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = inputDAS
config.Data.inputDBS = inputDatabase
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions23HI/Cert_Collisions2023HI_374288_375823_Good_ZDC_Golden.json'
config.Data.runRange = '374804-375746'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.totalUnits = -1

config.Data.outLFNDirBase = output
config.Data.publication = False
config.Data.allowNonValidInputDataset = True

config.Site.whitelist = ['T2_US_Vanderbilt', 'T2_CH_CERN']
config.Site.storageSite = outputServer

accounting_group = 'group_u_CMS.u_zh.priority'

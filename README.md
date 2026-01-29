# CMS Run3 PbPb UPC Foresting
**Last updated: 28 January 2026**

--------------------------------------------------------------------------------

## Setup for 2023 PbPb, Jan 2024 ReReco

```bash
# Create CMSSW (note: 13_2_10 or higher should be fine)
cmsrel CMSSW_13_2_15
cd CMSSW_13_2_15/src
cmsenv

# Add HI foresting tools
git cms-merge-topic CmsHI:forest_CMSSW_13_2_X_v2

# Initial build to make sure that works
scram build -j4

# Add Dfinder (note: always use 14XX!)
git clone -b Dfinder_14XX_miniAOD git@github.com:boundino/Bfinder.git --depth 1

# Add fix for 2023 jet correction
git clone https://github.com/cfmcginn/production
cp production/HIRun2023/forestPPRef/ak* HeavyIonsAnalysis/JetAnalysis/python/
cp production/HIRun2023/forestPPRef/forest_miniAOD_run3_ppRECO_DATA.py HeavyIonsAnalysis/Configuration/test/
rm -rf production

# Add this repo and copy the ZDC emap into the HI foresting tools
git clone -b Run3PbPbUPC_MITHIGForwardStudies git@github.com:jdlang/HIForestSetupPbPbRun2025.git
cp HIForestSetupPbPbRun2025/ZDCemap_PbPbUPC2023.txt HeavyIonsAnalysis/Configuration/data/

# Rebuild to apply changes
scram build -j4
```


--------------------------------------------------------------------------------

# Quick Reference

## CMSSW
```bash
# Run CMSSWConfig LOCALLY:
cmsRun forest_CMSSWConfig_XXXX.py
```


## CRAB
```bash
# Submit job:
crab submit -c <CRAB_config_file.py>

# Check job status:
crab status -d <path/to/crab_status_directory/>

# Kill a job (WARNING: this is irreversible!):
crab kill -d <path/to/crab_status_directory/>

# Resubmit failed jobs:
crab resubmit -d <path/to/crab_status_directory/>
# Resubmit with max memory and max runtime
crab resubmit --maxmemory 3000 --maxruntime 450 -d <path/to/crab_status_directory/>
```


## VOMS Certificate Setup

### Obtaining Certificates

https://ca.cern.ch/ca/user/Request.aspx?template=ee2user

Use the “New Grid User Certificate” tab to get a new CERN grid. You should set a password for this, and will need to remember it.

### Linux/Unix Installation

https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookStartingGrid#BasicGrid

To **setup the certificate** in your remote workspace, you should:
1. Export the certificate from your browser to a file in p12 format. You can 
give any name to your p12 file (in the example below the name is `mycert.p12`).

2. Place the p12 certificate file in the `.globus` directory of your home area. 
If the `.globus` directory doesn't exist, create it.
```bash
cd ~
mkdir .globus
cd ~/.globus
mv /path/to/mycert.p12 .
```

3. Execute the following shell commands:
```bash
rm -f usercert.pem
rm -f userkey.pem
openssl pkcs12 -in mycert.p12 -clcerts -nokeys -out usercert.pem
openssl pkcs12 -in mycert.p12 -nocerts -out userkey.pem
chmod 400 userkey.pem
chmod 400 usercert.pem
```
> [!WARNING]
> **If you are new to VOMS, you will need to sign the Acceptable Usage Policy 
> (AUP)** before you are able to access files, tools, and servers secured by
> certificate access. Just follow instructions here to sign the CMS AUP:
> https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideLcgAccess#AUP

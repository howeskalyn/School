import numpy as np
import scipy
import scipy.io # for loadmat

# Possible Research Question:
# Can we investigate the connection between reactive Nitrogen and Phosphorus
#   created by human farming practices, and their effect on the climate?
#
# Why? - "reactive nitrogen can so easily move among the different media of air,
#   soil and water. In the air, it can contribute to higher levels of ozone in
#   the lower atmosphere, causing respiratory ailments and damaging vegetation."
#
# Method:
#   (a)  Look for highest-polluting countries.
#   (b)  Investigate which human practices might account for the excess pollution.
#   (c)  Consider changes in practices to reduce pollution.

# Definitions/Data to keep in mind:
# 1) Ndep_kgkm, Ndep, nitrogen deposition rate - describes the input of reactive
#   nitrogen from the atmosphere to the biosphere both as gases.
# 2) NUE_3dNUE, nitrogen use efficiency - the fraction of applied nitrogen that is
#   absorbed and used by the plant
# 3) Nexc_kgkm, Nsur, nitrogen lost to the environment - losses create climate
#   change and damage to ecosystems

# load in file
obj = scipy.io.loadmat("iFarmData(2015)_1_28_2019.mat")

# find highest polluting countries throught all countries over the 10 most recent years
# ** which crop would be good to focus on? or should we look at them all together **
yr2005 = int(np.where(obj['Yr'][0] == 2005)[0])
yr2015 = int(np.where(obj['Yr'][0] == 2015)[0])
numTrdYrs = yr2015 - yr2005 + 1 # range of years

# testing with just rice for now
riceIdx = int(np.where(obj['FAOSTAT_CrName_FAO'] == 'Rice; paddy')[0])

numCo = max(obj['FAOSTAT_CoName_FAO'].shape) # number of countries
numCr = max(obj['FAOSTAT_CrName_FAO'].shape) # number of crops

# ---- find highest Ndep ----
# Ndep = obj['Ndep_kgkm'][chaIdx, riceIdx, yr2010] # finds it for China and Rice in year 2010
Ndep = obj['Ndep_kgkm'][0, riceIdx, yr2015] # initalize Ndep to be first countries number (w/ rice in 2015)
i = 1
# loop through number of countries
for i in range (numCo):
    # find Ndep for current country index (w/ rice in 2015)
    temp = obj['Ndep_kgkm'][i, riceIdx, yr2015]
    # if current country Ndep is biggest, store it instead
    if (temp > Ndep):
        Ndep = temp

# ---- find highest Nsur ----
# Nsur = obj['Nexc_kgkm'][chaIdx, riceIdx, yr2010] # finds it for China and Rice in year 2010
Nsur = obj['Nexc_kgkm'][0, riceIdx, yr2015] # initalize Nsur to be first countries number (w/ rice in 2015)
i = 1
# loop through number of countries
for i in range (numCo):
    # find Nsur for current country index (w/ rice in 2015)
    temp = obj['Nexc_kgkm'][i, riceIdx, yr2015]
    # if current country Nsur is biggest, store it instead
    if (temp > Nsur):
        Nsur = temp

# ---- find highest NUE ----
# Nsur = obj['NUE_3dNUE'][chaIdx, riceIdx, yr2010] # finds it for China and Rice in year 2010
NUE = obj['NUE_3dNUE'][0, riceIdx, yr2015] # initalize NUE to be first countries number (w/ rice in 2015)
i = 1
# loop through number of countries
for i in range (numCo):
    # find NUE for current country index (w/ rice in 2015)
    temp = obj['NUE_3dNUE'][i, riceIdx, yr2015]
    # if current country NUE is biggest, store it instead
    if (temp > NUE):
        NUE = temp

import numpy as np
import scipy
import scipy.io # for loadmat

# making obj a dictionary (or a map in c++ terms)
obj = scipy.io.loadmat("iFarmData(2015)_1_28_2019.mat")

# obj["Nfer_kgkm"][39][133][49] is the kg of N for rice in china in 2010
# each index is one-less than Octave/Matlab because of 0-based indexing

# obj["FAOSTAT_CoName_FAO"]

# Testing numbers/indices
# print('China N for rice in 2010: {}'.format(obj['Nfer_kgkm'][39][133][49]))

# saving files for each dictionary element
#for k in obj.keys():
   #np.save(k, obj[k])

#######################################################################################
USIdx = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'United States')[0])
riceIdx = int(np.where(obj['FAOSTAT_CrName_FAO'] == 'Rice; paddy')[0])

print ('US Index: {}'.format(USIdx))
print ('Rice Index: {}'.format(riceIdx))

# Year indicies: (need where instead of find)
yr1986 = int(np.where(obj['Yr'][0] == 1986)[0])
yr2010 = int(np.where(obj['Yr'][0] == 2010)[0])
yr2011 = int(np.where(obj['Yr'][0] == 2011)[0])
yr2015 = int(np.where(obj['Yr'][0] == 2015)[0])
print('Years: 1986 - {}, 2010 - {}, 2011 - {}, 2015 - {}'.format(yr1986, yr2010, yr2011, yr2015))

# 'length' in matlab -> max of the shape
numCo = max(obj['FAOSTAT_CoName_FAO'].shape) # number of countries
numCr = max(obj['FAOSTAT_CrName_FAO'].shape) # number of crops
numTrdYrs = yr2015 - yr1986 + 1 # range of years
print('numCo: {} & numCr: {}'.format(numCo, numCr))
print('numTrdYrs: {}\n'.format(numTrdYrs))

# Nitrogen inputs
# chaRiceNIn2010 = nansum([Nfer_kgkm(chaInd,riceInd,yr2010), Nman_kgkm(chaInd,riceInd,yr2010),...
#   Nfix_kgkm(chaInd,riceInd,yr2010), Ndep_kgkm(chaInd,riceInd,yr2010)]);
Nfer = obj['Nfer_kgkm'][USIdx, riceIdx, yr2010]
Nman = obj['Nman_kgkm'][USIdx, riceIdx, yr2010]
Nfix = obj['Nfix_kgkm'][USIdx, riceIdx, yr2010]
Ndep = obj['Ndep_kgkm'][USIdx, riceIdx, yr2010]
USRiceIn2010 = np.nansum([Nfer],[Nman],[Nfix],[Ndep])

# Nitrogen surplus
USRiceSur2010 = USRiceIn2010 - obj['Nyield_kgkm'][USIdx, riceIdx, yr2010]
USRiceNUE2010 = obj['Nyield_kgkm'][USIdx, riceIdx, yr2010] / USRiceIn2010
print('chaRiceIn2010: {}\nchaRiceSur2010: {}\nchaRiceNUE2010: {}\n'.format(USRiceIn2010, USRiceSur2010, USRiceNUE2010))

#################
globeCropIdx = obj['Nfer_kgkm'] + obj['Nman_kgkm'] + obj['Nfix_kgkm'] + obj['Ndep_kgkm']

globeCropSur = globeCropIdx - obj['Nyield_kgkm']

tmp1 = np.nansum(globeCropSur * obj['AreaH_FAO'], axis=1, keepdims=True)
tmp2 = np.nansum(obj['AreaH_FAO'], axis=1, keepdims=True)
tmp = tmp1 / tmp2
globalCropAgg = np.reshape(tmp, newshape=[numCo, max(obj["Yr"].shape)])
print('globalCropAgg: {}\n'.format(globalCropAgg))

tmp = np.nansum(obj['Nyield_kgkm'] * obj['AreaH_FAO'], axis=1, keepdims = True) / np.nansum(globeCropIdx * obj['AreaH_FAO'], axis = 1, keepdims = True)
globalCropNUE = np.reshape(tmp, [numCo, max(obj["Yr"].shape)])
print('globalCropNUE: {}\n'.format(globalCropNUE))


#######################################################################################
tradeN = np.empty(obj['netImTrade'].shape)

for i in range(max(obj['NC_Bou'].shape)):
    tradeN[i,:,:,:] = obj['netImTrade'][i,:,:,:] * obj['NC_Bou'][0,i]

##############################
# b.) - net N input to China

netNIm_US = np.nansum(
    np.reshape(tradeN[:,:,USIdx,:], [numCr, numTrdYrs, numCo]), axis=2)

##############################
agNIm_US = np.nansum(netNIm_US, axis = 0, keepdims = True)

#######################################################################################
#chinaNUE = reshape(NUE_3d(chaInd,:,yr1986:yr2015),[numCrops numTrdYrs]);
# matlab is inclusive - need the + 1
USNUE = np.reshape(obj['NUE_3d'][USIdx,:,yr1986:(yr2015 + 1)], [numCr, numTrdYrs])

notImN_US = ( (1 / USNUE ) - 1 ) * netNIm_US
##############################
agNotImN_US = np.nansum(notImN_US, axis = 0, keepdims = True)

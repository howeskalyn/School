import numpy as np
import scipy
import scipy.io # for loadmat

# making obj a dictionary (or a map in c++ terms)
obj = scipy.io.loadmat("iFarmData(2015)_1_28_2019.mat")

# obj["Nfer_kgkm"][39][133][49] is the kg of N for rice in china in 2010
# each index is one-less than Octave/Matlab because of 0-based indexing

# obj["FAOSTAT_CoName_FAO"]

# Testing numbers/indices
print('China N for rice in 2010: {}'.format(obj['Nfer_kgkm'][39][133][49]))

# saving files for each dictionary element #for k in obj.keys():
   #np.save(k, obj[k])

#######################################################################################
# 3.2
# a.)

# find(X) returns the indices of the array X that point to nonzero elements
# ismember(A,B) - returns an array containing 1 (true) or 0 (false)
#       where the data in A is found in B
#chaInd = find(ismember(FAOSTAT_CoName_FAO, 'China'))
#riceInd = find(ismember(FOASTAT_CrName_FAO, 'Rice; paddy'))
# so chaInd = indices of array where data in A is found in B

chaIdx = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'China')[0])
riceIdx = int(np.where(obj['FAOSTAT_CrName_FAO'] == 'Rice; paddy')[0])

print ('Cha Index: {}'.format(chaIdx))
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
Nfer = obj['Nfer_kgkm'][chaIdx, riceIdx, yr2010]
Nman = obj['Nman_kgkm'][chaIdx, riceIdx, yr2010]
Nfix = obj['Nfix_kgkm'][chaIdx, riceIdx, yr2010]
Ndep = obj['Ndep_kgkm'][chaIdx, riceIdx, yr2010]
chaRiceIn2010 = np.nansum([Nfer],[Nman],[Nfix],[Ndep])
#chaRiceIn2010 = np.nansum([Nfer,Nman,Nfix,Ndep])

# Nitrogen surplus
chaRiceSur2010 = chaRiceIn2010 - obj['Nyield_kgkm'][chaIdx, riceIdx, yr2010]
chaRiceNUE2010 = obj['Nyield_kgkm'][chaIdx, riceIdx, yr2010] / chaRiceIn2010
print('chaRiceIn2010: {}\nchaRiceSur2010: {}\nchaRiceNUE2010: {}\n'.format(chaRiceIn2010, chaRiceSur2010, chaRiceNUE2010))

#################
# 3.2
# b.)

# globeCropIn = Nfer_kgkm + Nman_kgkm + Nfix_kgkm + Ndep_kgkm
# for each country crop year triple, calculate
globeCropIdx = obj['Nfer_kgkm'] + obj['Nman_kgkm'] + obj['Nfix_kgkm'] + obj['Ndep_kgkm']
# print(f"globeCropIdx: {globeCropIdx}")

# globeCropSur = globeCropIn - Nyield_kgkm # Nitrogen surplus
globeCropSur = globeCropIdx - obj['Nyield_kgkm']
# print(f"globeCropSur: {globeCropSur}")

# globalCropAgg = reshape(nansum(globeCropSur.*AreaH_FAO,2) ./ nansum(AreaH_FAO,2),... [numCos length(Yr)])
# nansum(X) - returns the sum of the elements of X, computed after removing all NaN values
#
tmp1 = np.nansum(globeCropSur * obj['AreaH_FAO'], axis=1, keepdims=True)
tmp2 = np.nansum(obj['AreaH_FAO'], axis=1, keepdims=True)
tmp = tmp1 / tmp2
# dims = [numCo, numTrdYrs]
# globalCropAgg = np.reshape(tmp, dims)
# tmp = np.nansum(globeCropSur * obj['AreaH_FAO'], axis = 2, keepdims = True) / (np.nansum(obj['AreaH_FAO'], axis = 2, keepdims = True))
globalCropAgg = np.reshape(tmp, newshape=[numCo, max(obj["Yr"].shape)])
print('globalCropAgg: {}\n'.format(globalCropAgg))

# globalCropNUE = reshape(nansum(Nyield_kgkm.*AreaH_FAO,2) ./ nansum(globeCropIn.*AreaH_FAO,2),...[numCos length(Yr)])
#
# tmp2 = np.nansum(globeCropIdx * obj['AreaH_FAO'], 2)
# tmp1 = np.nansum(obj['Nyield_kgkm'] * obj['AreaH_FAO'], 2)
# tmp = tmp1 / tmp2
# dims = [numCo, numTrdYrs]
# globalCropNUE = np.reshape(tmp0, dims)
tmp = np.nansum(obj['Nyield_kgkm'] * obj['AreaH_FAO'], axis=1, keepdims = True) / np.nansum(globeCropIdx * obj['AreaH_FAO'], axis = 1, keepdims = True)
#print(f"Tmp: {tmp.shape}")
globalCropNUE = np.reshape(tmp, [numCo, max(obj["Yr"].shape)])
print('globalCropNUE: {}\n'.format(globalCropNUE))


#######################################################################################
# 3.2.2 - How much N has China been importing?
# a.) - amount N in traded crops

# tradeN = nan(size(netImTrade));
# nan(n) - returns an n-by-n matrix of NaN values
tradeN = np.empty(obj['netImTrade'].shape)

# for i = 1:length(NC_Bou) = from i to length of NC_Bou
# 'length' = length of the largest array dimension in X
    # tradeN(i,:,:,:) = netImTrade(i,:,:,:) * NC_Bou(i);
    # (i,:,:,:) - slicing


for i in range(max(obj['NC_Bou'].shape)):
    tradeN[i,:,:,:] = obj['netImTrade'][i,:,:,:] * obj['NC_Bou'][0,i]

#print(f"tradeN: {tradeN}")

##############################
# b.) - net N input to China

# netNIm_China = nansum(reshape(tradeN(:,:,chaInd,:), [numCrops numTrdYrs numCos]), 3);
# slice = tradeN[:,:,chaIdx,:]
netNIm_China = np.nansum(
    np.reshape(tradeN[:,:,chaIdx,:], [numCr, numTrdYrs, numCo]), axis=2)
# nansum(X) - returns the sum of the elements of X, computed after removing all NaN values
print('netIm_China: {}\n'.format(netNIm_China))

##############################
# c.) - aggregate by crops

# agNIm_China = nansum(netNIm_China, 1);
agNIm_China = np.nansum(netNIm_China, axis = 0, keepdims = True)
# nansum(X, 1) takes the sum along dimension 1 of X.
print('agNIm_China: {}\n'.format(agNIm_China))


#######################################################################################
# 3.2.3 - Amount of N pollution if China did not import
# a.) amount of N surplus China would have produced without trade

#chinaNUE = reshape(NUE_3d(chaInd,:,yr1986:yr2015),[numCrops numTrdYrs]);
# matlab is inclusive - need the + 1
chinaNUE = np.reshape(obj['NUE_3d'][chaIdx,:,yr1986:(yr2015 + 1)], [numCr, numTrdYrs])
print('chinaNUE: {}\n'.format(chinaNUE))

#notImN_China = ((1./chinaNUE)-1) .* netNIm_China;
notImN_China = ( (1 / chinaNUE ) - 1 ) * netNIm_China
print('notImN_China: {}\n'.format(notImN_China))

# ./ is element-wise division & .* is element-wise multiplication

##############################
# b.) aggergate by crops

#agNotImN_China = nansum(notImN_China, 1);
agNotImN_China = np.nansum(notImN_China, axis = 0, keepdims = True)
print('agNotImN_China: {}\n'.format(agNotImN_China))

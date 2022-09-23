# use command i to run the file

import numpy as np
import scipy
import scipy.io # for loadmat

# making obj a dictionary (or a map in c++ terms)
obj = scipy.io.loadmat("iFarmData(2015)_1_28_2019.mat")

# need the following countries:
# Ecuador, Peru, Columbia, Bolivia, Brazil, French Guiana, Guyana, Suriname, Venezuela
# see if these countries exist in our data:

Bolivia = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'Bolivia (Plurinational State of)')[0])
print ('Bolivia Idx: {}'.format(Bolivia))

Brazil = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'Brazil')[0])
print ('Brazil Idx: {}'.format(Brazil))

Colombia = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'Colombia')[0])
print ('Colombia Idx: {}'.format(Colombia))

Ecuador = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'Ecuador')[0])
print ('Ecuador Idx: {}'.format(Ecuador))

FrenchGuiana = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'French Guiana')[0])
print ('FrenchGuiana Idx: {}'.format(FrenchGuiana))

Guyana = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'Guyana')[0])
print ('Guyana Idx: {}'.format(Guyana))

Peru = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'Peru')[0])
print ('Peru Idx: {}'.format(Peru))

Suriname = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'Suriname')[0])
print ('Suriname Idx: {}'.format(Suriname))

Venezuela = int(np.where(obj['FAOSTAT_CoName_FAO'] == 'Venezuela (Bolivarian Republic of)')[0])
print ('Venezuela Idx: {}'.format(Venezuela))

# time frame:
yr1986 = int(np.where(obj['Yr'][0] == 1986)[0])
yr2015 = int(np.where(obj['Yr'][0] == 2015)[0])
years = yr2015 - yr1986 + 1 # range of years
print('Years: {}\n'.format(years))

# which crops to focus on?

import scipy
import scipy.io # for loadmat
import numpy as np
from matplotlib import pyplot as plt
import pandas as pd

# without qualification, this look in the folder with the testscript.py
obj = scipy.io.loadmat("iFarmData(2015)_1_28_2019.mat")

# obj is now a dictionary, or a map in c++ terms

# obj['Nfer_kgkm'] is a 3-dim list indexed by (co, cr, yr)

print(obj['Nexc_kgkm'].shape)

# results in a 2-dim list indexed by (co, cr)
# where that index is the average Nfer_kgkm in country co and
# crop cr over all years
avgNexcPerCrop = np.mean(obj['Nexc_kgkm'], axis=1)
print(avgNexcPerCrop.shape)

crnames = [a[0][0].replace(";","") for a in obj['FAOSTAT_CrName_FAO']]
yrnames = [a[0][0] for a in obj['Yr']]

df = pd.DataFrame(avgNexcPerCrop, index=yrnames)

df.to_csv('avgNexcPerCrop.csv', index=True, header=yrnames)

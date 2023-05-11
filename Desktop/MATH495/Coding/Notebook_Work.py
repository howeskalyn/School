import numpy as np
import pandas as pd

Nfix_kgkm = np.load('Nfix_kgkm.npy')
Nman_kgkm = np.load('Nman_kgkm.npy')

# prints only Afghanistan !!
df_fix = pd.DataFrame(Nfix_kgkm[0])
df_man = pd.DataFrame(Nman_kgkm[0])
print(df_man.describe())

# prints size
print(Nfix_kgkm.shape)



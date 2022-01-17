# %%
import matplotlib.pyplot as plt
import numpy as np

N=3
values = [1.98e11, 1.775e11, 1.96e11 ]
values_errors=[1.2e10, 6.6e9,1.2e10]
ind= np.arange(N)
width = .35
x=np.linspace(-.2, 2.2, 15)
y=np.full(15, 1.759e11 )


fig, ax=plt.subplots()
ax.bar(ind, values, width, yerr=values_errors, label='valore misurato')
ax.plot(x,y, label='valore vero', color='orange')
ax.legend(loc="lower right")
ax.set_ylabel("e/m [C/kg]")
ax.set_title("confonto misure-valor vero")
ax.set_xticks(ind, labels=['Parallelo','Perpendicolare','Antiparallelo'])
# %%
plt.show()
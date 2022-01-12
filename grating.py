# %%
import matplotlib.pyplot as plt
import numpy as np

m = [2, 3, 5]
_Lambda=7.5e-7
d=3.347e-6
a=0.3e-6
x=np.linspace(-np.pi/2, np.pi/2, 1000)
fig, ax= plt.subplots()
z= lambda d , _Lambda, _Theta: np.pi*d/_Lambda*np.sin(_Theta)
#alpha= lambda a, _Lambda, _Theta: a*np.sin(_Theta)/_Lambda
#amp= lambda alpha : (np.sinc(alpha))**2 
y= lambda m , z : (np.sin(m*z)/np.sin(z))**2
for i in m:
    partY=z(d, _Lambda, x)
#    partY2=alpha(a, _Lambda, x)
    ax.plot(x,y(i,partY)"""*amp(partY2)""", label="nr Fenditure = "+str(i))
ax.set_xlabel("Angolo [rad]")
ax.set_ylabel("ampiezza")
fig.tight_layout()
ax.set_title("comportamento reticolo con nr differente di fenditure")
ax.legend(loc="upper right")
unit   = 0.25
x_tick = np.arange(-0.5, 0.5+unit, unit)
x_label = [r"$-\frac{\pi}{2}$", r"$-\frac{\pi}{4}$", r"$0$", r"$+\frac{\pi}{4}$",   r"$+\frac{\pi}{2}$"]
ax.set_xticks(x_tick*np.pi)
ax.set_xticklabels(x_label, fontsize=15)
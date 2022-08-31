import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from basic_units import radians


common_params = dict(
    marker = 'o',
    linestyle = '--',
    fillstyle = 'none'
)

def Gain(value, test):
    return 20*np.log10(value/test)

def Phase(frequency, dt):
    return dt*2*np.pi*frequency

def Bode_Plot(filename : str, th_gain : callable = None, th_phi : callable = None):
    try:
        df = pd.read_csv(filename)
    except FileNotFoundError:
        print('filename errato')
        filename = str(input('Inserire Filename corretto\n'))
        df = pd.read_csv(filename)
    
    fig, (mod, phase) = plt.subplots(2,1,sharex=True)
    # For automatic color setting 
    colors = plt.rcParams['axes.prop_cycle']()
    c = next(colors)['color']
    # plotting Gain
    mod.plot(df['freq'], Gain(df['Vout'],df['Vin']),color=c, label = 'gain', **common_params)
    if th_gain:
        c = next(colors)['color']
        x = np.logspace(np.log10(np.min(df['freq'])),np.log10(np.max(df['freq'])))
        mod.plot(x, th_gain(x), '-.', color = c, label = 'Theorical')
    
    # plotting phase
    c = next(colors)['color']
    phase.plot(df['freq'], Phase(df['freq'], df['dt']), yunits = radians ,color=c, label = 'phase', **common_params)
    if th_phi:
        c = next(colors)['color']
        x = np.logspace(np.log10(np.min(df['freq'])),np.log10(np.max(df['freq'])))
        mod.plot(x, th_phi(x), '-.', color = c, label = 'Theorical')

    # Setting Scale
    mod.set_xscale('log')
    # Setting about Style GAIN
    Bode_style(mod, 'Gain')
    # Setting about Style PHASE
    Bode_style(phase, 'Phase [rad]')
    # Setting x Label
    phase.set_xlabel('Frequency [Hz]')
    fig.suptitle('Bode Plot', fontsize = 16)
    return fig, (mod,phase)

def Bode_style(ax : plt.Axes, label : str) -> None:
    ax.grid(True,'both')
    ax.set_title(label)
    ax.set_ylabel(label)
    ax.legend()

def Nyquist_Plot(filename : str,  theo : callable = None,  *args):
    try:
        df = pd.read_csv(filename)
    except FileNotFoundError:
        print('filename errato')
        filename = str(input('Inserire Filename corretto'))
        df = pd.read_csv(filename)

    modul = df['Vout']/df['Vin'] 
    phi = Phase(df['freq'], df['dt'])
    fig, ax = plt.subplots()
    ax.plot(modul*np.cos(phi), modul*np.sin(phi),'o', label="Measured")
    
    # Se esiste inserisce il grafico teorico
    if theo :
        x = np.linspace(np.min(modul), np.max(modul), 200)
        ax.plot( x, theo(x, *args),'--', label='Theorical')

    # Rendiamo il Grafico un Filo Carino
    ax.set_xlabel("Re(H)")
    ax.set_ylabel("Im(H)")
    ax.set_title("Nyquist Graph")
    ax.axis('square')
    ax.grid(True, 'both')
    ax.legend()
    return fig, ax

def Plot_Collpits(filename : str):
    df = pd.read_csv(filename, delimiter='  ', header=None)
    plt.plot(df[0], df[1])
    plt.grid('both', True)
    plt.xlabel('Time [s]')
    plt.ylabel('Voltage [V]')


if __name__=='__main__':
    print('This is a test')
    Bode_Plot('./Elettronica/data/day3RC.csv')
    Nyquist_Plot('./Elettronica/data/day3RC.csv')
    plt.show()
    
import matplotlib.pyplot as plt
import numpy as np
import random as random

x = np.arange(0,7000*np.pi,1)   # start,stop,step
diff = 0 #random.randint(-20,20)
z = lambda f:2 * np.pi * x * (f + diff) / 44100
y = np.sin(z(440) ) * np.exp(-0.004 * 2 * np.pi * 440 * x / 44100)
#y += np.sin(z(random.randint(-2,2)))

plt.plot(x,y)
plt.show()
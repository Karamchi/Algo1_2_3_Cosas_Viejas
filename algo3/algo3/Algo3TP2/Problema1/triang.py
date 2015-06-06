from pylab import *
import math

def neg(x):return -x

import matplotlib.pyplot as plt

x = [0]
y = [100]

plt.scatter(y,x,color='#660066',lw=2)

x = [0]
y = [0]

plt.scatter(y,x,color='#666600',lw=2)

x = [100]
y = [0]

plt.scatter(y,x,color='#006666',lw=2)

x = range(100)
y = [100-i for i in x]
z= [0]*100
plt.xlim(-1,110)

plt.ylim(-1,110)
plt.ylim(plt.ylim()[::-1])
plt.xlabel('Cantidad de motos')
plt.ylabel('Cantidad de buggies')

plt.plot(x,y,color='#0000FF',lw=2)
plt.fill_between(x,y,0,color='#666666')
plt.plot(x,z,color='#FF0000',lw=2)
plt.plot(z,x,color='#00FF00',lw=2)
plt.grid('on')

plt.show()

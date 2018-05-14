from numpy import *
import numpy as np
import matplotlib.pyplot as plt

d = genfromtxt("d.txt", delimiter=' ')
q2 = d[:,0]
p2 = d[:,1]

plt.figure()
plt.plot(q2, p2)
plt.title('q2 vs p2')
plt.xlabel('q2')
plt.ylabel('p2')
plt.savefig('caos.pdf')
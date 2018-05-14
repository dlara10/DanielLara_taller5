from numpy import *
import matplotlib.pyplot as plt

d = genfromtxt("d.txt", delimiter=',')

n = int(size(d,0)/3)
x,y = meshgrid(linspace(0,n,n),linspace(0,n,n))
z = d[:,:]

plt.figure()
plt.contour(x , y, z, n)
plt.streamplot(x, y, z, z, 1.2)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Campo Electrico')
plt.savefig('placas.pdf')


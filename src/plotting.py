# import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

NCOLS = 5 # columns of output per particle

with open("data/planets.dat") as planets:
    line = planets.readline()
    line = line.split()
    NITER = int(line[2].strip())

# read the tab separated file
infile = open("data/output.dat")
lines = infile.readlines()
# split all the lines, ignore the '#' ones and transpose
cols = list(zip(*(line.strip().split('\t') for line in lines if not line.startswith('#'))))
cols = [[float(item.strip()) for item in col] for col in cols]

fig, (ax, ax2, ax3) = plt.subplots(3, 1, figsize=(8,6))

lines = []
kes = []
ams = []

for i in range(0, len(cols), NCOLS):
    print(i)
    # print(cols[i])
    # print(cols[i+1])
    line, = ax.plot(cols[i], cols[i+1])
    lines.append(line)

    ke, = ax2.plot(cols[i+4])
    am, = ax3.plot(cols[i+5])
    kes.append(ke)
    ams.append(am)

# x1, x2 = -5, 5
# y1, y2 = -120, 120
# ax.set_xlim(x1, x2)
# ax.set_ylim(y1, y2)
# x1, x2 = ax.get_xlim()
# y1, y2 = ax.get_ylim()
# ax.xaxis.set_ticks(np.arange(x1, x2, (x2-x1)/10))
# ax.yaxis.set_ticks(np.arange(y1, y2, (y2-y1)/10))
ax.set_aspect('equal', 'datalim')

plt.show()

import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Circle
from matplotlib.collections import PatchCollection

# initialise some values
NCOLS = 5 # columns of output per particle
NWALLS = 4 # num of walls. obviously 4 columns per wall at this point
WALLCOL= 4
BULK = 10

with open("data/particles.dat") as pf:
    line = pf.readline()
    line = line.split()
    NITER = int(line[1].strip())

    lines = pf.readlines()
    lines = [line.split() for line in lines]
    rads = [float(lines[i][1].strip()) for i in range(2, len(lines), 4)]
    print(rads)

# read the PARTICLES data
with open("data/output.dat") as infile:
    lines = infile.readlines()

# split all the lines, ignore the '#' ones and transpose
cols = list(zip(*(line.strip().split('\t') for line in lines if not line.startswith('#'))))
cols = [[float(item.strip()) for item in col] for col in cols]

# calculate total KE
totke = [sum([cols[i+4][j] for i in range(0, len(cols), NCOLS)]) for j in range(len(cols[0]))]

# read the WALLS data
with open("data/wallmov.dat") as wallfile:
    lines = wallfile.readlines()

walldat = list(zip(*(line.strip().split('\t') for line in lines if not line.startswith('#'))))
walldat = [[float(item.strip()) for item in col] for col in walldat]

# start plotting yay
fig, (ax, ax2) = plt.subplots(nrows=2, ncols=1, figsize=(8,6))

lines = []
circles = []
patches = []
walls = []
kes = []

for i in range(0, len(cols), NCOLS):
    print(i)
    # print(cols[i])
    # print(cols[i+1])
    line, = ax.plot(cols[i], cols[i+1])
    lines.append(line)

    circle = Circle((cols[i][0], cols[i+1][0]), radius=rads[int(i/NCOLS)])
    patch = ax.add_patch(circle)
    circles.append(circle)
    patches.append(patch)

    ke, = ax2.plot(cols[i+4])
    kes.append(ke)

tke, = ax2.plot(totke)

for i in range(NWALLS):
    xs = [walldat[i*WALLCOL][0], walldat[i*WALLCOL+2][0]]
    ys = [walldat[i*WALLCOL+1][0], walldat[i*WALLCOL+3][0]]
    wall, = ax.plot(xs, ys, 'k-')
    walls.append(wall)


# x1, x2 = -0.1, 7.1
# y1, y2 = -0.1, 5.1
# ax.set_xlim(x1, x2)
# ax.set_ylim(y1, y2)
ax.set_aspect('equal', 'datalim')
# x1, x2 = ax.get_xlim()
# y1, y2 = ax.get_ylim()
# ax.xaxis.set_ticks(np.arange(x1, x2, (x2-x1)/10))
# ax.yaxis.set_ticks(np.arange(y1, y2, (y2-y1)/10))

def animate(i):
    global lines, cols, patches, circles, walldat, walls, kes, tke

    NBACK = 100

    imax = i*BULK
    if i > NBACK:
        imin = (i-NBACK)*BULK
    else:
        imin = 0

    for j, line in enumerate(lines):
        line.set_data(cols[NCOLS*j][imin:imax], cols[NCOLS*j+1][imin:imax])
        circles[j].center = cols[NCOLS*j][imax], cols[NCOLS*j+1][imax]
        patches[j] = ax.add_patch(circles[j])
        kes[j].set_data(range(imax), cols[NCOLS*j+4][0:imax])

    tke.set_data(range(imax), totke[0:imax])

    for j, wall in enumerate(walls):
        xs = [walldat[j*WALLCOL][imax], walldat[j*WALLCOL+2][imax]]
        ys = [walldat[j*WALLCOL+1][imax], walldat[j*WALLCOL+3][imax]]
        wall.set_data(xs, ys)

    return lines + patches + walls + kes + [tke]

anim = animation.FuncAnimation(fig, animate, frames=int(NITER/BULK), interval=0.2, repeat=True, blit=True)

# # Set up formatting for the movie files
# plt.rcParams['animation.ffmpeg_path'] ='D:\\Movies\\ffmpeg-20171120-8f4702a-win64-static\\bin\\ffmpeg.exe'
# FFwriter = animation.FFMpegWriter(fps=50)

# anim.save('planet.mp4', writer=FFwriter)
fig.show()

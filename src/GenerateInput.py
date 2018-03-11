import numpy as np

npart = 20          # number of particles
dt = 1e-3           # timestep
NITER = int(10e3)   # num of iterations
nd = 2              # num of dimensions

xlim = [0.1, 6.9]
ylim = [0.3, 4.7]
dx = xlim[1] - xlim[0]
dy = ylim[1] - ylim[0]

mmin = 2
mmax = 8
rmax = 0.15

xs, ys = [], []
vxs, vys = [], []
rs, ms = [], []

def check_collision(x1, y1, r1, x2, y2, r2):
    d = np.sqrt((x1-x2)**2 + (y1-y2)**2)
    if d < r1 + r2:
        return True
    else:
        return False

fout = open('data/particles.dat', 'w')

# write the header
fout.writelines([str(dt) + '\t' + str(NITER), '\n', str(npart) + '\t' + str(nd)])

def generate_particle():
    x, y = np.random.rand() * dx + xlim[0], np.random.rand() * dy + ylim[0]
    vx = np.random.normal(loc=0, scale=dx/2)
    vy = np.random.normal(loc=0, scale=dy/2)
    m = np.random.rand() * (mmax-mmin) + mmin
    r = rmax/mmax*m

    return (x, y, vx, vy, m, r)

for i in range(npart):
    is_collision = True
    while is_collision:
        (x, y, vx, vy, m, r) = generate_particle()
        is_collision = False
        for j in range(i):
            if check_collision(xs[j], ys[j], rs[j], x, y, r):
                is_collision = True

    xs.append(x)
    ys.append(y)
    vxs.append(vx)
    vys.append(vy)
    ms.append(m)
    rs.append(r)

    fout.write("\n\n" + str(m) + "\t" + str(r) + "\n" + str(x) + "\t" + str(y) + "\n" + str(vx) + "\t" + str(vy))

fout.close()

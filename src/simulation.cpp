#include "physics.h"

int NITER;

// function that reads the simulation details (dt and number of iterations), particle and wall initial conditions and loads them into the respective variables.
void readFromFile() {
    double x, m, r;
    int np, nd, nw;

    // read in the particles and simulation details
    ifstream fin ("data/particles.dat");
    cout << "reading particles...\n";
    //read G and dt
    fin >> dt >> NITER;
    // number of particles and dimensions
    fin >> np >> nd;

    // for each particle read the mass, nd position coordinates and nd velocity coordinates
    // create the object and push it to the vector
    for(int i = 0; i < np; i++) {
        fin >> m >> r;

        // o.setCharge(q);
        Vector pos;
        for(int j = 0; j < nd; j++) {
            fin >> x;
            pos.setComp(j, x);
        }

        Vector v;
        for(int j = 0; j < nd; j++) {
            fin >> x;
            v.setComp(j, x);
        }

        Object o(pos, v, 1/m, r);
        objects.push_back(o);
    }
    cout << "done with particles\n";
    fin.close();

    // read in the walls
    ifstream ffin ("data/walls.dat");
    cout << "reading the walls...\n";
    ffin >> nw; // number of walls
    cout << "Number of walls: " << nw << endl;
    for(int i = 0; i < nw; i++) {
        Vector pos0;
        for(int j = 0; j < nd; j++) {
            ffin >> x;
            cout << x << "\t";
            pos0.setComp(j, x);
        }

        Vector pos1;
        for(int j = 0; j < nd; j++) {
            ffin >> x;
            cout << x << "\t";
            pos1.setComp(j, x);
        }

        Vector v;
        for(int j = 0; j < nd; j++) {
            ffin >> x;
            cout << x << "\t";
            v.setComp(j, x);
        }

        Wall wall(pos0, pos1, v);
        walls.push_back(wall);
        cout << "\n";
    }
    
    cout << "done with walls.\n";
    ffin.close();
}

int main() {
    ofstream fout ("data/output.dat");
    ofstream ffout ("data/wallmov.dat");
    readFromFile();

    cout << "Now some checks. Normals:\n";

    cout << walls[0].n().comp(0) << " " << walls[0].n().comp(1);

    cout << "\n\nthat looks good. now, are the particles touching the wall?\n";

    for(vector<Object>::iterator it = objects.begin(); it != objects.end(); it++) {
        cout << checkWallCollision((*it), walls[0]) << "\t";
    }

    // cout << "\n\nSomething basic. Dot products:\n";
    // double d = Vector({1, -2}) * Vector({2, 3});
    // cout << d;

    // cout << "\n\nLookin good so far. Now, are the reflected velocities correct?\n";

    // collide_wall(objects[2], walls[0]);
    // double vx = objects[2].vel().comp(0), vy = objects[2].vel().comp(1);
    // cout << vx << "\t" << vy << "\n";

    cout << "\n\n==============================\nrunning...\n";

    // run the sim NITER times
    for(int i = 0; i < NITER; i++) {
        simpleUpdate();

        // output particle positions and stuff
        for(vector<Object>::iterator it = objects.begin(); it != objects.end(); it++)
            fout << (*it).output();
        fout << "\n";

        // output wall positions
        for(vector<Wall>::iterator it = walls.begin(); it != walls.end(); it++)
            ffout << (*it).output();
        ffout << "\n";
    }

    fout.close();
    ffout.close();

    cout << "done.\n";

    // double x1 = walls[0].getEnd(0).comp(0), x2 = walls[0].getEnd(1).comp(0);
    // double y1 = walls[0].getEnd(0).comp(1), y2 = walls[0].getEnd(1).comp(1);

    // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;

    return 0;
}
#include "physics.h"

vector<Object> objects;
vector<Wall> walls;

double dt;

// update routines:

void simpleUpdate() {
    vector<Object>::iterator i, j;
    vector<Wall>::iterator wi;

    // perform collision checks and act on them
    for(i=objects.begin(); i!=objects.end(); i++) {
        // between the particles
        for(j=objects.begin(); j!=i; j++)
            if(checkCollision((*i), (*j)))
                collide((*i), (*j));
        // between particle and walls
        for(wi=walls.begin(); wi!=walls.end(); wi++)
            if(checkWallCollision((*i), (*wi)))
                collide_wall((*i), (*wi));
    }
    
    // do dr += v*dt
    for(i=objects.begin(); i!=objects.end(); i++) {
        (*i).setPosition((*i).pos() + (*i).vel()*dt);
    }

    // move da walls
    vector<Wall>::iterator it;
    for(it=walls.begin(); it!=walls.end(); it++) {
        (*it).setEnd(0, (*it).getEnd(0) + (*it).vel()*dt);
        (*it).setEnd(1, (*it).getEnd(1) + (*it).vel()*dt);
    }
}

// collision checking
bool checkCollision(Object & a, Object & b) {
    Vector dr = a.pos() - b.pos();
    double tooclose = a.r() + b.r() - dr.mod();

    // The balls would start intersecting and getting stuck together. This is clever and stupid at the same time:

    bool colliding = (tooclose >= 0);
    if(!colliding)
        return false;

    // how much the particles are going to travel relative to each other, in the direction separating their centres, over the next timestep.
    double travel = (a.vel() - b.vel()) * dr * dt;
    
    // if they are closer than that, they are intersecting too much, so move them outwards (in this case 1/2 of the distance each, but could do proportional to the speeds or masses)
    if(tooclose > travel) {
        a.setPosition(a.pos() + (tooclose / 2 / dr.mod())*dr);
        b.setPosition(b.pos() - (tooclose / 2 / dr.mod())*dr);
    }
    return true;
}

bool checkWallCollision(Object & a, Wall & w) {
    // DISCLAIMER: THIS DOESN'T TAKE INTO ACCOUNT THE ENDS OF THE WALL. IT'S TREATED AS AN INFINITE LINE.
    double dotprod = (a.pos()-w.getEnd(0)) * w.n(); // vector from particle to wall dotted with normal => signed distance to wall

    return (abs(dotprod) <= a.r());
}

// colliding stuff
void collide(Object & a, Object & b) {
    Vector vdif = a.vel() - b.vel();
    Vector pdif = a.pos() - b.pos();
    double dotprod = pdif * vdif;
    double imu = a.im() + b.im(); // inverse reduced mass
    
    // maths from https://en.wikipedia.org/wiki/Elastic_collision#Two-dimensional_collision_with_two_moving_objects
    a.setVelocity(a.vel() - (2*a.im()/imu * dotprod / pdif.mod() / pdif.mod()) * pdif);

    b.setVelocity(b.vel() + (2*b.im()/imu * dotprod / pdif.mod() / pdif.mod()) * pdif);
}

void collide_wall(Object & a, Wall & w) {
    double dotprod = (a.vel() - w.vel()) * w.n();
    Vector dv = (2*dotprod)*w.n();
    // cout << "Function collide_wall. dv = ";
    // cout << dv.comp(0) << "\t" << dv.comp(1) << "\n";
    a.setVelocity(a.vel() - dv);
}

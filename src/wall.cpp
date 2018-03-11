#include "physics.h"

Wall::Wall(const Vector x1, const Vector x2, const Vector initVelocity) {
    this->setEnd(0, Vector(x1));
    this->setEnd(1, Vector(x2));
    this->setVelocity(Vector(initVelocity));
}

// getters
Vector Wall::getEnd(int i) const {
    return ends[i];
}
Vector Wall::vel() const {
    return Vector(velocity);
}

Vector Wall::n() const {
    double x1 = this->getEnd(0).comp(0), x2 = this->getEnd(1).comp(0);
    double y1 = this->getEnd(0).comp(1), y2 = this->getEnd(1).comp(1);

    if(flequals(x1, x2))
        return Vector({1, 0});
    if(flequals(y1, y2))
        return Vector({0, 1});

    double im = (x2 - x1)/(y1 - y2); // since the perpendicular slope is -1/m
    double x = 1/sqrt(1+im*im);
    double y = im*x;

    return Vector({x, y});
}

string Wall::output() const {
    string str("");
    int dim = this->getEnd(0).getDim();
    // add the position
    for(int j = 0; j<=1; j++) {
        for(int i = 0; i < dim; i++) {
            str += to_string(this->getEnd(j).comp(i)) + "\t";
        }
    }
    
    return str;
}

// setters
void Wall::setEnd(const int i, const Vector & r) {
    ends[i] = Vector(r);
}

void Wall::setVelocity(const Vector & newVel) {
    this->velocity = Vector(newVel);
}

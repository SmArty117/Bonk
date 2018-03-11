#include "physics.cpp"

Object::Object() {
    this->position = Vector::zero();
    this->velocity = Vector::zero();
    this->imass = 0.0;
}

Object::Object(const Vector initPosition, const Vector initVelocity, double initInvMass, double initRadius) {
    if(initPosition.getDim() != initVelocity.getDim()) {
        cerr << "Different dimensions of vectors. Cannot initialize object.";
        return;
    }
    this->setPosition(Vector(initPosition));
    this->setVelocity(Vector(initVelocity));
    this->setInvMass(initInvMass);
    this->setRadius(initRadius);
}

/* Object::Object(const vector<double> & initPosition, const vector<double> & initVelocity, double initMass, double initCharge) {
    if(initPosition.size() != initVelocity.size()) {
        cerr << "Different dimensions of vectors. Cannot initialize object.";
        return;
    }
    this->position = Vector(initPosition);
    this->velocity = Vector(initVelocity);
    this->mass = initMass;
    this->charge = initCharge;
} */

// setters
void Object::setInvMass(double im) {
    if(im >= 0)
        this->imass = im;
    else throw("Negative mass!");
}

void Object::setPosition(const Vector & newPos) {
    this->position = newPos;
}

void Object::setVelocity(const Vector & newVel) {
    this->velocity = newVel;
}

void Object::setRadius(double r) {
    if(r >= 0)
        this->radius = r;
    else throw("Negative radius!");
}

// getters
double Object::im() const {
    return imass;
}
double Object::r() const {
    return radius;
}
Vector Object::pos() const {
    return Vector(position);
}
Vector Object::vel() const {
    return Vector(velocity);
}

string Object::output() const {
    string str("");
    int dim = this->pos().getDim();
    // add the position
    for(int i = 0; i < dim; i++) {
        str += to_string(this->pos().comp(i)) + "\t";
    }

    // add the velocity
    for(int i = 0; i < dim; i++) {
        str += to_string(this->vel().comp(i)) + "\t";
    }

    // add the KE
    str += to_string(this->vel().mod()*this->vel().mod()/2/this->im()) + "\t";

    return str;
}

bool operator==(const Object & lhs, const Object & rhs) {
    if(lhs.position != rhs.position)
        return false;
    if(lhs.velocity != rhs.velocity)
        return false;
    if(lhs.imass != rhs.imass)
        return false;
    if(lhs.radius != rhs.radius)
        return false;
    return true;
}

bool operator!=(const Object & lhs, const Object & rhs) {
    return !(lhs == rhs);
}
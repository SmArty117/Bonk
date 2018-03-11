#include "physics.h"
#include<algorithm>

bool flequals(double a, double b) { 
    return(abs(a-b) < EPS);
}

// constructor from array
/* Vector::Vector(double a[], int dimensions) {
    dim = dimensions;
    v = new double[dim];
    for(int i = 0; i < dim; i++) {
        v[i] = a[i];
    }
} */

// zero vector constructor
Vector::Vector(int dimensions) {
    dim = dimensions;
    v = new double[dim];
    for(int i = 0; i < dim; i++) {
        v[i] = 0.0;
    }
}

// copy constructor
Vector::Vector(const Vector & vec) {
    dim = vec.getDim();
    v = new double[dim];

    for(int i = 0; i < dim; i++)
        v[i] = vec.comp(i);
}

// constructor from vector array
Vector::Vector(const vector<double> & vec) {
    dim = vec.size();
    v = new double[dim];

    for(int i = 0; i < dim; i++)
        v[i] = vec[i];
}

Vector::~Vector() {
    delete [] v;
    dim = 0;
}

int Vector::getDim() const {
    return dim;
}

// get the modulus, sqrt(sum(v_i^2))
double Vector::mod() const {
    double sum = 0.0;
    for(int i = 0; i < dim; i++) {
        sum += v[i]*v[i];
    }
    return sqrt(sum);
}

double Vector::ang() const {
    return atan2(this->comp(1), this->comp(0));
}

// get the i-th component. Note: zero-indexed.
double Vector::comp(int i) const {
    if(i >= 0 && i < dim)
        return v[i];
    else {
        cerr << "Component index out of range\n" << i << "\n";
        return -1;
    }
}

// set the i-th component. Also zero-indexed.
void Vector::setComp(int i, double value) {
    if(i >= 0 && i < dim)
        v[i] = value;
    else {
        cerr << "Component index out of range\n" << i << "\n";
        return;
    }
}

// make a string like "[v1, v2,...,vn]"
string Vector::getString() const {
    string str("[");
    for(int i = 0; i < dim-1; i++) {
        str += to_string(v[i]) + ", ";
    }
    str += to_string(v[dim-1]) + "]";
    return str;
}

void Vector::print() const {
    printf("[");
    for(int i = 0; i < dim-1; i++)
        printf("%g, ", comp(i));
    printf("%g]\n", comp(dim-1));
}

// check if vector is zero
bool Vector::isZero() const {
    for(int i = 0; i < dim; i++)
        if(!flequals(comp(i), 0))
            return false;
    return true;
}

//a zero vector of the specified dimension 
Vector Vector::zero(int dimensions) {
    Vector zero(dimensions);
    return zero;
}

// assignment by copying
Vector & Vector::operator=(const Vector & b) {
    if(this != &b) {
        if(b.dim != dim) {
            delete [] v;
            dim = 0;
            v = nullptr;
            v = new double[b.dim];
            dim = b.dim;
        }
        copy(b.v, b.v+b.dim, v);
    }
    return *this;
}

// addition to self: increment each component and return itself.
Vector & Vector::operator+=(const Vector & b) {
    if(b.dim != dim) {
        cerr << "Different vector sizes, cannot be added;\n";
        return *this;
    }
    for(int i = 0; i < dim; i++) {
        v[i] += b.v[i];
    }
    return *this;
}

// addition of two vectors. creates a copy of self and returns it.
Vector Vector::operator+(const Vector & b) const {
    Vector result(*this);
    result += b;
    return result;
}

Vector Vector::operator-() const {
    Vector result(*this);
    for(int i = 0; i < dim; i++) {
        result.v[i] = -v[i];
    }
    return result;
}

Vector & Vector::operator-=(const Vector &b) {
    return (*this)+=(-b);
}

Vector Vector::operator-(const Vector &b) const {
    Vector result(*this);
    result -= b;
    return result;
}

Vector Vector::operator*(const double a) const {
    Vector result(*this);
    for(int i = 0; i < dim; i++) {
        result.v[i] = this->v[i] * a;
    }
    return result;
}

Vector operator*(const double a, const Vector vec) {
    return vec*a;
}

double operator*(const Vector u, const Vector v) {
    if(u.getDim() != v.getDim())
        throw("different vector dimensions in scalar product");
    
    int dim = u.getDim();
    double sum = 0;
    for(int i = 0; i < dim; i++) {
        sum += u.comp(i) * v.comp(i);
    }

    return sum;
}

bool operator==(const Vector lhs, const Vector rhs) {
    if(lhs.dim != rhs.dim)
        return false;

    else {
        for(int i = 0; i < lhs.dim; i++)
            if(!flequals(lhs.v[i], rhs.v[i]))
                return false;
        
        return true;
    } 
}

bool operator!=(const Vector lhs, const Vector rhs) {
    return !(lhs==rhs);
}
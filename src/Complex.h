#include "header.h"

#ifndef FRACTAL_EDITOR_COMPLEX_H
#define FRACTAL_EDITOR_COMPLEX_H


class Complex {
public:
    Complex(double re, double im): re_(re), im_(im) {}

    bool check() {
        return (re_*re_ + im_*im_ < 4);
    }

    Complex operator+(const Complex& first) {
        Complex copy(0, 0);
        copy.re_ = first.re_ + re_;
        copy.im_ = first.im_ + im_;
        return copy;
    }
    Complex operator*(const Complex& first) {
        Complex copy(0, 0);
        copy.re_ = first.re_*re_ - first.im_*im_;
        copy.im_ = first.re_*im_ + first.im_*re_;
        return copy;
    }
    Complex& operator=(Complex other) {
        this->re_ = other.re_;
        this->im_ = other.im_;
        return *this;
    }
private:
     double re_;
     double im_;
};


#endif //FRACTAL_EDITOR_COMPLEX_H

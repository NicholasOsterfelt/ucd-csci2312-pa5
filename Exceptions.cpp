//
// Created by Nick on 12/15/2015.
//
#include <iostream>
#include <string>

#include "Exceptions.h"

using namespace std;
namespace Gaming {
    std::ostream& operator <<(std::ostream &os, const GamingException &ex)
    {
        os << "Exception occured: " << ex.getName() << " ";
        ex.__print_args(os);
        return os;
    }
    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
        __exp_width = expWidth;
        __exp_height = expHeight;
        __width = width;
        __height = height;
    }
    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width,
                                                       unsigned height) : DimensionEx(minWidth, minHeight, width, height) {setName("InsufficientDimensionsEx"); }
    void InsufficientDimensionsEx::__print_args(std::ostream &os) const
    {
        os << "(__exp_width: " << __exp_width << ", __exp_height: " << __exp_height << ", PassedWidth: "
            << __width << ", PassedHeight: " << __height << ")";
    }
    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth, maxHeight, width, height) {setName("OutOfBoundsEx");}

    void OutOfBoundsEx::__print_args(std::ostream &os) const {
        os << "(maxWIdth: " << __exp_width << ", maxHeight: " << __exp_height << ", PassedWidth: " << __width
            << ", PassedHeight:" << __height << ")";
    }
}


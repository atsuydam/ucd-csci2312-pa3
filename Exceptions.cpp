#include<iostream>
#include "Exceptions.h"
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"

namespace Clustering{
    // Out of Bounds Exceptions
    OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r)
    {
        __current = c;
        __rhs = r;
        __name = "OutOfBoundsEx";
    }

    unsigned int OutOfBoundsEx::getCurrent() const
    {
        return __current;
    }

    int OutOfBoundsEx::getRhs() const
    {
        return __rhs;
    }

    std::string OutOfBoundsEx::getName() const
    {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const OutOfBoundsEx &ex)
    {

    }

    // Dimensionality exceptions
    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r)
    {
        __current = c;
        __rhs = r;
        __name = "DimensionalityMismatchEx";
    }

    unsigned int DimensionalityMismatchEx::getCurrent() const
    {
        return __current;
    }

    unsigned int DimensionalityMismatchEx::getRhs() const
    {
        return __rhs;
    }

    std::string DimensionalityMismatchEx::getName() const
    {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const DimensionalityMismatchEx &ex)
    {

    }

    //Zero Clusters Exceptions
    ZeroClustersEx::ZeroClustersEx()
    {

    }

    std::string ZeroClustersEx::getName() const
    {

    }

    std::ostream &operator<<(std::ostream &os, const ZeroClustersEx &ex)
    {

    }

    // Data file open exceptions
    DataFileOpenEx::DataFileOpenEx(std::string filename)
    {

    }

    std::string DataFileOpenEx::getFilename() const
    {

    }

    std::string DataFileOpenEx::getName() const
    {

    }

    std::ostream &operator<<(std::ostream &os, const DataFileOpenEx &ex)
    {

    }

    //zero Dimensions Exceptions
    ZeroDimensionsEx::ZeroDimensionsEx()
    {
        __name = "ZeroDimensionsEx";
    }

    std::string ZeroDimensionsEx::getName() const
    {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const ZeroDimensionsEx &ex)
    {

    }

    //Empty Cluster Exceptions
    EmptyClusterEx::EmptyClusterEx()
    {

    }

    std::string EmptyClusterEx::getName() const
    {

    }

    std::ostream &operator<<(std::ostream &os, const EmptyClusterEx &ex)
    {

    }

}
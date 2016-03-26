#include<iostream>
#include "Exceptions.h"
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"

namespace Clustering{
    // Out of Bounds Exceptions
    OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r)
    {

    }

    unsigned int OutOfBoundsEx::getCurrent() const
    {

    }

    int OutOfBoundsEx::getRhs() const
    {

    }

    std::string OutOfBoundsEx::getName() const
    {

    }

    std::ostream &operator<<(std::ostream &os, const OutOfBoundsEx &ex)
    {

    }

    // Dimensionality exceptions
    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r)
    {

    }

    unsigned int DimensionalityMismatchEx::getCurrent() const
    {

    }

    unsigned int DimensionalityMismatchEx::getRhs() const
    {

    }

    std::string DimensionalityMismatchEx::getName() const
    {

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

    }

    std::string ZeroDimensionsEx::getName() const
    {

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
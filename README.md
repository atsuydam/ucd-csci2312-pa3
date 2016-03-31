## CSCI 2312: Programming Assignment 3

<h> PA3 - KMeans Clustering </h>

This program takes a dynamically allocated array of points and places them in a cluster using
linked lists. The points are then used to calculate to centroid, or the center of the points.
The KMeans algorithm then moves the points into clusters while center the centroids for the best fit.

<h2>  Source Files </h2>
main.cpp
    This files contains all the calls to the tests defined in ClusteringTests.cpp

Point.h
    The header file for the Point class it includes all the function prototypes for this class

Point.cpp
    This file contains all the definitions along with constructors and deconstructors for the
    the point class.

Cluster.h
    Contains the class definitions and prototypes for the cluster class with the new point centroid.
    Also includes the inner public class move.

Cluster.cpp
    Contains the definitions for all the functions found in the Cluster class, it's private inner class
    Centroid and public inner class move.

Exceptions.h
    Contains the prototypes for the exception functions.

Exceptions.cpp
    contains the definitions for the exception functions.

KMeans.h
    contains the class and functions prototypes for the KMeans class.

KMeans.cpp
    Contains the definitions for the KMeans class

ClusteringTests.h
    I assume it contains the function prototypes for the tests. I never opened it.

ClusteringTests.cpp
    This contains all the definitions for the clustering test functions.

<h2> Circumstances of programs </h2>
    The programs compiles.  All point tests and their exceptions are working properly.
    It throws a dimension error on the overloaded >> operator
    in the clustering class.  I was unable to get the instream operator to read from
    a file. The count method demonstrated in class threw numerous errors and prevented compiling.
    Centroid is not properly calculated and fails the tests.

    The KMeans functions and constructor aren't implemented, function definitions are empty.
    Without that instream operator functioning there was no way to to run and pass those test.
    An error-ing centroid only makes it that much harder. The hours I have spent between PA2 and PA3
    have greatly exceeded the estimated time given time. Incomplete study guides notes on canvas have
    also hindered my progress.




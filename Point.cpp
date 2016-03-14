#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>
#include "Point.h"
#include "Cluster.h"

using namespace std;


namespace Clustering {

    unsigned int Point::__idGen = 0; // ID generator

    static void rewindIdGen();

    Point::Point(unsigned int size)
    {
        __id = __idGen++;
        __dim = size;
        __values = new double[size];
        for (int i = 0; i < size; i++)
        {
            __values[i] = 0;
        }
    }

    Point::Point(unsigned int size, double *p)
    {
        // __idGen++;
        // THis was option for debugging.
    }

// Big three: cpy ctor, overloaded operator=, dtor
    Point::Point(const Point &rhs) :
            __dim(rhs.__dim)
    {
        __id = __idGen++;
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++)
        {
            __values[i] = rhs.__values[i];
        }
    }

    Point &Point::operator=(const Point &rhs)
    {
        __id = __idGen++;
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            this->__dim = rhs.__dim;
            this->__values = new double[__dim];
            for (int i = 0; i < __dim; i++) {
                this->__values[i] = rhs.__values[i];
            }
        }
        return *this;
    }

    Point::~Point()
    {
        delete[] __values;
    }

// Accessors & mutators
    int Point::getId() const
    {
        return __id;
    }

    unsigned int Point::getDims() const
    {
        return __dim;
    }

    void Point::setValue(unsigned int i, double num)
    {
        __values[i] = num;
    }

    double Point::getValue(unsigned int i) const
    {
        return __values[i];
    }

// Functions
    double Point::distanceTo(const Point &rhs) const
    {
        double distance = 0;
        double squared;
        int size;
        size = rhs.__dim;
        for (int i=0; i<size; i++)
        {
            if (rhs.__values[i] == __values[i])
            {
                distance += 0;
            }
            else
            {
                squared = rhs.__values[i] - __values[i];
                distance += squared * squared;
            }
        }
        distance = sqrt(distance);
        return distance;
    }

// Overloaded operators

// Members
    Point &Point::operator*=(double num) // p *= 6; p.operator*=(6);
    {
        int size = __dim;
        for (int i=0; i < size; i++)
        {
            __values[i] *= num;
        }
    }

    Point &Point::operator/=(double num)
    {
        int size = __dim;
        for (int i=0; i < size; i++)
        {
            __values[i] /= num;
        }
    }

    const Point Point::operator*(double num) const // prevent (p1 * 2) = p2;
    {
        unsigned int size = __dim;
        Point p(size);

        for (int i=0; i<__dim; i++)
        {
            p.__values[i] = __values[i] * num;
        }
        return p;
    }

    const Point Point::operator/(double num) const // p3 = p2 / 2;
    {
        unsigned int size = __dim;
        Point p(size);

        for (int i=0; i<__dim; i++)
        {
            p.__values[i] = __values[i] / num;
        }
        return p;
    }

    double &Point::operator[](unsigned int index)
    {
        return __values[index];
    }

    const double &Point::operator[](unsigned int index) const
    {
        return __values[index];
    }

// Friends
    Point &operator+=(Point &lhs, const Point &rhs)
    {
        for (int i=0; i <rhs.__dim; i++)
        {
            lhs.__values[i] += rhs.__values[i];
        }
        return lhs;
    }

    Point &operator-=(Point &lhs, const Point &rhs)
    {
        int size = lhs.__dim;
        for (int i=0; i < size; i++)
        {
            lhs.__values[i] -= rhs.__values[i];
        }
        return lhs;
    }

    const Point operator+(const Point &lhs, const Point &rhs)
    {
        int size = (lhs.__dim + rhs.__dim);
        Point p(size);
        for (int i=0; i < size; i++)
        {
            p.__values[i] = lhs.__values[i] + rhs.__values[i];
        }
        return p;
    }

    const Point operator-(const Point &lhs, const Point &rhs)
    {
        int size = (lhs.__dim + rhs.__dim);
        Point p(size);
        for (int i=0; i < size; i++)
        {
            p.__values[i] = lhs.__values[i] - rhs.__values[i];
        }
        return p;
    }

    bool operator==(const Point &lhs, const Point &rhs)
    {
        bool answer = false;
        if (lhs.getDims() == rhs.getDims())
        {
            int dimensions = lhs.getDims();
            answer = true;
            for (int i=0; i < dimensions; i++)
            {
                if (lhs.__values[i] != rhs.__values[i])
                {
                    answer = false;
                    return answer;
                }
            }
        }
        return answer;
    }

    bool operator!=(const Point &lhs, const Point &rhs)
    {
        bool answer = false;
        // The next line is causing a break in many of the tests with clustering but works fine in the point tests.
        int dimensions = lhs.getDims();
        if (lhs.__dim != rhs.__dim)
        {
            return answer;
        }
        for (int i=0; i < dimensions; i++)
        {
            if (lhs.__values[i] != rhs.__values[i])
            {
                answer = true;
                break;
            }
        }
        return answer;
    }

    bool operator<(const Point &lhs, const Point &rhs)
    {
        bool answer = false;
        int size = lhs.__dim;
        for (int i=0; i < size; i++)
        {
            if ( lhs.__values[i] < rhs.__values[i])
            {
                answer = true;
            }

        }
        return answer;


    }

    bool operator>(const Point &lhs, const Point &rhs)
    {
        bool answer = false;
        int size = lhs.__dim;
        for (int i=0; i < size; i++)
        {
            if ( lhs.__values[i] > rhs.__values[i])
            {
                answer = true;
            }
            if ( lhs.__values[i] < rhs.__values[i])
                return false;

        }
        return answer;
    }

    bool operator<=(const Point &lhs, const Point &rhs)
    {
        bool answer = true;
        int size = lhs.__dim;
        for (int i=0; i < size; i++)
        {
            if ( lhs.__values[i] > rhs.__values[i])
            {
                answer = false;
            }
        }
        return answer;
    }

    bool operator>=(const Point &lhs, const Point &rhs)
    {
        bool answer = true;
        int size = lhs.__dim;
        for (int i=0; i < size; i++)
        {
            if ( lhs.__values[i] < rhs.__values[i])
            {
                answer = false;
            }

        }
        return answer;
    }

    std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        int i=0;
        for (; i > p.__dim-1; i++ )
        {
            os << p.__values[i] << ", ";
        }
        os << p.__values[i] << endl;
        return os;
    }

    std::istream &operator>>(std::istream &is, Point &p)
    {
        int i=0;
        for (; i > p.__dim; i++)
        {
            is >> p.__values[i];
        }
        return is;
    }
}


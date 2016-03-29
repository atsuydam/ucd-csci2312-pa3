
#include <iostream>
#include <cassert>
#include <limits>
#include "Cluster.h"
#include "Exceptions.h"
#include "Point.h"

using namespace std;


namespace Clustering {

    unsigned int Cluster::__idGenerator = 0;

    LNode::LNode(const Point &p, LNodePtr n)
            :point(p),
             next(n)
    {
    }

    Cluster::Centroid::Centroid(unsigned int d, const Cluster &c)
            : __c(c),
              __p(d) // I don't think this is the correct value being passed to p but I get an 134 error with 0
    {
        __dimensions = d;
        bool __valid = true;  // OR does this need to be true
 //       compute();        // there is something wrong with this compute function
    }

    const Point Cluster::Centroid::get() const // doesn't check for validity
    {
        return __p;
    }

    void Cluster::Centroid::set(const Clustering::Point &p) // sets to valid
    {
        __p = p;
        __valid = true;
    }

    bool Cluster::Centroid::isValid() const
    {
        return __valid;
    }

    void Cluster::Centroid::setValid(bool valid)
    {
        __valid = valid;
    }

// This isn't working
    void Cluster::Centroid::compute()
    {
        if (__c.__points == nullptr)
        {
            assert(__c.__size == 0);
            toInfinity();
            return;
        }

        LNodePtr current = __c.__points;
        Point p(__c.getDimensionality());
        unsigned int sizeCheck = 0;

        while (current != nullptr)
        {
            p += current->point/__c.getSize();
            current = current->next;
            sizeCheck++;
        }
        assert(sizeCheck == __c.getSize());

        set(p);
    }

    bool Cluster::Centroid::equal(const Point &lhs) const
    {
        bool answer = true;
        if (__p.getDims() != lhs.getDims())
        {
            throw DimensionalityMismatchEx(__p.getDims(), lhs.getDims());
        }
        int size = __p.getDims();

        for (int i=0; i < size; i++)
        {
            if (__p[i] != lhs[i])
            {
                answer = false;
            }
        }
        return answer;

    }

    void Cluster::Centroid::toInfinity()
    {
        int size = __p.getDims();
        for (int i=0; i < size; i++)
        {
            __p[i] = std::numeric_limits<double>::max();
        }
    }

    Cluster::Cluster(unsigned int d)
            :centroid(d, *this)
    {
        __dimensionality = d;
        __size = 0;
        __points = nullptr;
        __id = __idGenerator++;
    }
    // The big three: cpy ctor, overloaded operator=, dtor
    Cluster::Cluster(const Cluster &rhs)
            : centroid(__dimensionality, *this)
    {
        __size = rhs.__size;
        if (__points != NULL)
            __del();
        LNodePtr cursor = rhs.__points;
        this->__size = 0;

        while (cursor != NULL)
        {
            this->add(cursor->point);
            cursor = cursor->next;
            __size++;
        }
        __id = __idGenerator++;
    }

    Cluster &Cluster::operator=(const Cluster &rhs)
    {
        if (*this == rhs)
            return *this;
        else
        {
            LNodePtr cursor = __points;
            LNodePtr nextPnt;

            while ( cursor != nullptr )
            {
                nextPnt = cursor->next;
                delete cursor;
                cursor = nextPnt;
                __size--;
            }
        }

        LNodePtr rhsPtr = rhs.__points;
        for (int i=0; i<rhs.getSize(); i++)
        {
            add(rhsPtr->point);
            if (rhsPtr->next != nullptr)
                rhsPtr = rhsPtr->next;
            __size++;
        }
        return *this;
    }


    Cluster::~Cluster()
    {
        LNodePtr cursor = __points;
        LNodePtr nextPnt;

        while (cursor != nullptr)
        {
            nextPnt = cursor->next;
            delete cursor;
            cursor = nextPnt;
            if (nextPnt != nullptr)
            {
                nextPnt = nextPnt->next;
            }
        }
        __size = 0;
    }

    void Cluster::__del()
    {
        if (__size != 0)
        {
            LNodePtr cursor = __points;
            delete cursor;
        }
        __points = NULL;
        __size = 0;

    }

    void Cluster:: __cpy(LNodePtr pts)
    {
        LNodePtr cursor = pts;
        this->__size = 0;

        while (cursor != NULL)
        {
            this->add(cursor->point);
            cursor = cursor->next;
            __size++;
        }
        __id = __idGenerator++;
    }

    bool Cluster::__in(const Point &p) const
    {
            //NOt sure what this is looking for, is cluster's version of contains?
    }

    // Getters/setters
    unsigned int Cluster::getSize() const // TODO add to the requirements
    {
        return __size;
    }

    unsigned int Cluster::getDimensionality() const
    {
        return __dimensionality;
    }

    unsigned int Cluster::getId() const
    {
        return __id;
    }

// Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const Point &p) // TODO add asc order to the requirements
    {
        LNodePtr newPnt = new LNode(p, nullptr);
        LNodePtr cursor = __points;
        LNodePtr prev;
        newPnt->point = p;

        // Check to see if this will be the first node in the list
        if (__points == nullptr)
        {
            assert(__size == 0);
            //cout << endl << newPnt->point << " is being inserted into the head " << endl;
            __points = newPnt;
            newPnt->next = nullptr;
            __size++;
            return;
        }

        else if (__points->next == nullptr)
        {
            if (newPnt->point < __points->point)
            {
                //cout << endl << newPnt->point << " is replacing " << __points->point << endl;
                newPnt->next = __points;
                __points = newPnt;
            }
            else
            {
               // cout << endl << newPnt->point << " comes after " << __points->point << endl;
                __points->next = newPnt;
            }
            __size++;
            return;
        }

            // Or add another node to the existing list
        else
        {
            cursor = __points;
            prev = NULL;

            while (cursor != NULL && cursor->point <= p)
            {
                prev = cursor;
                cursor = cursor->next;
            }


            if (prev == NULL)
            {
                __points = newPnt;
                newPnt->next = cursor;
            }

            else
            {
                prev->next = newPnt;
                newPnt->next = cursor;
            }
        }
        __size++;
    }


    const Point &Cluster::remove(const Point &p)
    {
        LNodePtr cursor;
        LNodePtr prevPtr = __points;

        // empty list
        if (__points == NULL)
            return p;

        // head of list
        if (__points->point == p)
        {
            cursor = __points->next;
            delete __points;
            __points = cursor;
        }

            // anywhere else
        else
        {
            cursor = __points;
            while (cursor != NULL && cursor->point != p)
            {
                prevPtr = cursor;
                cursor = cursor->next;
            }
            if (cursor->point == p)
            {
                prevPtr->next = cursor->next;
                delete cursor;
            }
            else
            {
                cout << "That point wasn't found in the linked list" << endl;
            }
        }
        __size--;
        return p;
    }

    bool Cluster::contains(const Point &theWantedOne) const // I'm getting tired of p
    {
        bool answer = false;
        LNodePtr cursor;
        if (__dimensionality != theWantedOne.getDims())
            throw DimensionalityMismatchEx(__dimensionality, theWantedOne.getDims());

        for (cursor = __points; cursor != NULL; cursor = cursor->next)
        {
            if (cursor->point == theWantedOne)
                answer = true;
        }
        return answer;


    }

    void Cluster::pickCentroids(unsigned int k, Point **pointArray)
    {
        // I want to pick points far away from each other
    }
// Overloaded operators

// Members: Subscript
    const Point &Cluster::operator[](unsigned int index) const // notice: const
    {
        LNodePtr cursor = __points;

        if (__size == 0)
            throw EmptyClusterEx();
        if (index >= __size)
            throw OutOfBoundsEx(index, __size);

        if (cursor != NULL)
        {
            for (int i=0; i<index; i++)
            {
               cursor = cursor->next;
            }
        }
        return cursor->point;

    }

// Members: Compound assignment (Point argument)
    Cluster &Cluster::operator+=(const Point &more)
    {
        LNodePtr cursor = __points;
        cursor->point += more;
        __size++;
    }

    Cluster &Cluster::operator-=(const Point &less)
    {
        remove(less);
        __size--;
    }

// Members: Compound assignment (Cluster argument)
    Cluster &Cluster::operator+=(const Cluster &second) // union
    {
        LNodePtr cursor = second.__points;
        for ( ; cursor != NULL; cursor = cursor->next)
        {
            add(cursor->point);
        }
    }

    Cluster &Cluster::operator-=(const Cluster &c) // (asymmetric) difference
    {
        LNodePtr cursor = __points;
        LNodePtr cursorC = c.__points;
        while (cursor != NULL)
        {
            for ( ; cursorC != NULL; cursorC = cursorC->next)
            {
                if (cursorC->point == cursor->point)
                    remove(cursorC->point);
            }
            cursor = cursor->next;
        }
    }

// Friends: IO
    std::ostream &operator<<(std::ostream &out, const Cluster &c)
    {
        LNodePtr cursor = c.__points;
        int i=0;
        for ( ; i < c.__size; i++)
        {
            out << cursor->point << " ";
            cursor = cursor->next;
        }
        return out;
    }

    std::istream &operator>>(std::istream &in, Cluster &c)
    {
        LNodePtr cursor = c.__points;
        int i=0;

        return in;
    }

// Friends: Comparison
    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        bool answer = true;
        if (lhs.__size != rhs.__size)
            return false;

        LNodePtr Lcursor = lhs.__points;
        LNodePtr Rcursor = rhs.__points;
        while (Lcursor != NULL)
        {
            if (Lcursor->point != Rcursor->point )
            {
                answer = false;
            }
            else
            {
                Rcursor = Rcursor->next;
                Lcursor = Lcursor->next;
            }
        }
        return answer;
    }

    bool operator!=(const Cluster &lhs, const Cluster &rhs)
    {
        bool answer = false;

        if (lhs.__dimensionality != rhs.__dimensionality)
            throw DimensionalityMismatchEx(lhs.__dimensionality, rhs.__dimensionality);

        if (lhs.__size != rhs.__size)
        {
            answer = true;
            return answer;
        }

        LNodePtr Lcursor = lhs.__points;
        LNodePtr Rcursor = rhs.__points;
        while (Lcursor != NULL)
        {
            if (Lcursor->point == Rcursor->point )
            {
                Rcursor = Rcursor->next;
                Lcursor = Lcursor->next;
            }
            else if (Lcursor->point != Rcursor->point)
                answer = true;
        }
        return answer;
    }

// Friends: Arithmetic (Cluster and Point)
    const Cluster operator+(const Cluster &c, const Point &p)
    {
        Cluster added(p.getDims());
        added.__cpy(c.__points);
        added.add(p);
        return added;
    }

    const Cluster operator-(const Cluster &c, const Point &p)
    {
        Cluster subtracted(p.getDims());
        subtracted.__cpy(c.__points);
        subtracted.remove(p);
        return subtracted;
    }

// Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &one, const Cluster &two) // union
    {
        // Get the size of the new combined cluster
        unsigned int newSize = one.__dimensionality + two.__dimensionality;
        // Make it a new cluster
        Cluster allTogether(newSize);
        allTogether.__cpy(one.__points);

        LNodePtr cursor = two.__points;
        for ( ; cursor != nullptr; cursor = cursor->next)
        {
            allTogether.add(two.__points->point);
        }

        return allTogether;
    }

    const Cluster operator-(const Cluster &, const Cluster &) // (asymmetric) difference
    {

    }

    Cluster::Move::Move(const Point &p, Cluster &from, Cluster &to)
            : __p(p), __from(from), __to(to)
    {

    }

    void Cluster::Move::perform()
    {

    }

}

#include <iostream>
#include <cassert>
#include "Cluster.h"
#include "Point.h"

using namespace std;


namespace Clustering {
    LNode::LNode(const Point &p, LNodePtr n)
            :point(p)
    {

    }

    Cluster::Centroid::Centroid(unsigned int d, const Cluster &c)
            : __p(0), __c(c)
    {
        unsigned int __dimensions = d;
        Point __p = 0;
        bool __valid = true;
        const Cluster &__c = c;
    }

    const Point Cluster::Centroid::get() const // doesn't check for validity
    {

    }

    void Cluster::Centroid::set(const Clustering::Point &p) // sets to valid
    {

    }

    bool Cluster::Centroid::isValid() const
    {

    }

    void Cluster::Centroid::setValid(bool valid)
    {

    }

    void Cluster::Centroid::compute()
    {

    }

    bool Cluster::Centroid::equal(const Point &) const
    {

    }

    void Cluster::Centroid::toInfinity()
    {

    }

    Cluster::Cluster(unsigned int d)
            :centroid(__dimensionality, *this)
    {

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
        }
    }

    Cluster &Cluster::operator=(const Cluster &rhs)
    {
        if (*this == rhs)
            return *this;
        else
        {
            LNodePtr cursor = __points;
            LNodePtr nextPnt;

            while ( cursor != NULL )
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
            if (rhsPtr->next != NULL)
                rhsPtr = rhsPtr->next;
        }
        return *this;
    }


    Cluster::~Cluster()
    {
        LNodePtr cursor = __points;
        LNodePtr nextPnt;

        while (cursor != NULL)
        {
            nextPnt = cursor->next;
            delete cursor;
            cursor = nextPnt;
            if (nextPnt != NULL)
            {
                nextPnt = nextPnt->next;
            }
        }
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
        }
    }

    bool Cluster::__in(const Point &p) const
    {

    }

    // Getters/setters
    unsigned int Cluster::getSize() const // TODO add to the requirements
    {
        return __size;
    }

    unsigned int Cluster::getDimensionality() const
    {

    }

    unsigned int Cluster::getId() const
    {

    }

// Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const Point &p) // TODO add asc order to the requirements
    {
        LNodePtr newPnt = new LNode(p, NULL);
        LNodePtr cursor;
        LNodePtr prev;
        newPnt->point = p;

        // Check to see if this will be the first node in the list
        if (__points == NULL)
        {
            assert(__size == 0);
            __points = newPnt;
            newPnt->next = NULL;
        }

            // Replace the head point if p is smaller
        else if (__points->point > p)
        {
            cursor->point = __points->point;
            __points->point = p;
            __points->next = cursor;
            cursor->next = NULL;
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
        LNodePtr cursor = __points;

        for (cursor = __points; cursor != NULL; cursor = cursor->next)
        {
            if (cursor->point == theWantedOne)
                answer = true;
        }
        return answer;


    }

    void Cluster::pickCentroids(unsigned int k, Point **pointArray)
    {

    }
// Overloaded operators

// Members: Subscript
    const Point &Cluster::operator[](unsigned int index) const // notice: const
    {
        LNodePtr cursor = __points;

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
        for ( ; i<c.__size-1; i++)
        {
            out << cursor->point << " ";
            cursor = cursor->next;
        }
    }

    std::istream &operator>>(std::istream &in, Cluster &c)
    {

    }

// Friends: Comparison
    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        // Something is causing my comparisons to throw a segmentation error. So something is broken here
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
            if (Lcursor->point != Rcursor->point)
                answer = true;
        }
        return answer;
    }

// Friends: Arithmetic (Cluster and Point)
    const Cluster operator+(const Cluster &c, const Point &p)
    {
//        Cluster added;
//        added.__cpy(c.__points);
//        added.add(p);
//        return added;
    }

    const Cluster operator-(const Cluster &c, const Point &p)
    {
//        Cluster subtracted;
//        subtracted.__cpy(c.__points);
//        subtracted.remove(p);
//        return subtracted;
    }

// Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &one, const Cluster &two) // union
    {
//        Cluster allTogether;
//        allTogether.__cpy(one.__points);
//        int size = two.getSize();
//        // This isn't going to work, it will pass the first point and nothing more.
//        allTogether.add(two.__points->point);

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
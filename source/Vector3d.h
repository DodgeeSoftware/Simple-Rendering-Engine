#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <string>
#include <cmath>

/** The Vector3d class is a wrapper around two floats then comes packaged with
    typical vector functions such as dot products, cross products, magnitude and normalise. **/
class Vector3d
{
    public:
        //! Default Constructor
        Vector3d();
        //! Overloaded constructor
        Vector3d( float x, float y, float z );
        //! Overloaded constructor
        Vector3d(const Vector3d& vector);
        //! Destructor
        virtual ~Vector3d() {}
        //! Normalise this vector
        void normalise();
        //! Return what this vector would be if it were normalised
        Vector3d normalised();
        //! Return the magnitude of this vector
        float magnitude();
        //! Return the dot product of two vectors
        float dotProduct( Vector3d vector );
        //! Return the cross product of two vectors
        Vector3d crossProduct( Vector3d vector );
        //! Return the angle between two vectors
        float angleBetween( Vector3d vector );
        //! Return this vector as a string
        std::string toString();
        //! Send this vector to the console
        void toConsole();
        //! Overloaded assignment operator
        Vector3d operator=(const Vector3d vector3d);
        //! Overloaded addition operator
        Vector3d operator+(const Vector3d& vector3d);
        //! Overloaded addition operator
        Vector3d operator+=(const Vector3d& vector3d);
        //! Overloaded negation operator
        Vector3d operator-();
        //! Overloaded subtraction operator
        Vector3d operator-(const Vector3d& vector3d);
        //! Overloaded subtraction operator
        Vector3d operator-=(const Vector3d& vector3d);
        //! Overloaded multiplication operator
        Vector3d operator*(const float& scalar);
        //! Overloaded multiplication operator
        Vector3d operator*=(const Vector3d& vector3d);
        //! Overloaded division operator
        Vector3d operator/(const float& scalar);
        //! Overloaded division operator
        Vector3d operator/=(const Vector3d& vector3d);
        //! Overloaded equality operator
        bool operator==(const Vector3d& vector3d);
        //! Overloaded not operator
        bool operator!=(const Vector3d& vector3d);
        //! Components of the vector
        float x,y,z;

};

#endif // VECTOR3D_H

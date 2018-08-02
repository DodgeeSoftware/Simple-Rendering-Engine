#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <string>
#include <cmath>

/** The Vector2d class is a wrapper around two floats then comes packaged with
    typical vector functions such as dot products, cross products, magnitude and normalise. **/
class Vector2d
{
    public:
        //! Default constructor
        Vector2d();
        //! Overloaded constructor
        Vector2d( float x, float y );
        //! Overloaded constructor
        Vector2d(const Vector2d& vector);
        //! Destructor
        virtual ~Vector2d() {}
        //! Normalise this vector
        void normalise();
        //! Return what this vector would be if it were normalised
        Vector2d normalised();
        //! Return the magnitude of this vector
        float magnitude();
        //! Return the dot product of two vectors
        float dotProduct( Vector2d vector );
        //! Return the cross product of two vectors
        Vector2d crossProduct( Vector2d vector );
        //! Return the angle between two vectors
        float angleBetween( Vector2d vector );
        //! Return this vector as a string
        std::string toString();
        //! Send this vector to the console
        void toConsole();
        //! Overloaded assignment operator
        Vector2d operator=(const Vector2d vector2d);
        //! Overloaded addition operator
        Vector2d operator+(const Vector2d& vector2d);
        //! Overloaded addition operator
        Vector2d operator+=(const Vector2d& vector2d);
        //! Overloaded negation operator
        Vector2d operator-();
        //! Overloaded subtraction operator
        Vector2d operator-(const Vector2d& vector2d);
        //! Overloaded subtraction operator
        Vector2d operator-=(const Vector2d& vector2d);
        //! Overloaded multiplication operator
        Vector2d operator*(const float& scalar);
        //! Overloaded multiplication operator
        Vector2d operator*=(const float& scalar);
        //! Overloaded division operator
        Vector2d operator/(const float& scalar);
        //! Overloaded division operator
        Vector2d operator/=(const float& scalar);
        //! Overloaded equality operator
        bool operator==(const Vector2d& vector2d);
        //! Overloaded not operator
        bool operator!=(const Vector2d& vector2d);
        //! Components of the vector
        float x, y;
};

#endif // VECTOR2D_H

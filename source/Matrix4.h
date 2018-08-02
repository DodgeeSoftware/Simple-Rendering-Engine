#ifndef MATRIX4_H
#define MATRIX4_H

#include <cmath>
#include <iostream>
#include "Utils.h"
#include "Vector3d.h"

/** The matrix4 class is a wrapper around a 4x4 array of floats and comes packaged with
    typical matrix transformation functions such as translation, rotation and scaling. **/
class Matrix4
{
    public:
        //! Default constructor
        Matrix4() { makeIdentity(); }
        //! Overloaded constructor
        Matrix4(float* matrix);
        //! Destructor
        virtual ~Matrix4() {}
        //! Get translation
        Vector3d getTranslation();
        //! Set translation
        void setTranslation(Vector3d vector);
        //! Get rotation in radians
        Vector3d getRotationRadians();
        //! Set rotation in radians
        void setRotationRadians(Vector3d rotation);
        //! Get rotation in degrees
        Vector3d getRotationDegrees() { return getRotationRadians() * RAD2DEG; }
        //! Set rotation in degrees
        void setRotationDegrees(Vector3d rotation) { setRotationRadians(rotation * DEG2RAD); }
        //! Get scale
        Vector3d getScale();
        //! Set scale
        void setScale(Vector3d scale);
        //! Make this matrix an identity matrix
        void makeIdentity();
        //! Transpose this matrix
        void transpose();
        //! Get a transposition of this matrix
        Matrix4 transposed();
        //! Return a pointer to the array for this matrix
        float* toArray() { return array; }
        //! Send the contents of this matrix to the console
        void toConsole();
        //! Overloaded assignment operator
        Matrix4 operator=(const Matrix4 matrix4);
        //! Overloaded addition operator
        Matrix4 operator+(const Matrix4& matrix4);
        //! Overloaded subtraction operator
        Matrix4 operator-(const Matrix4& matrix4);
        //! Overloaded product operator
        Matrix4 operator*(const float& scalar);
        //! Overloaded product operator
        Vector3d operator*(const Vector3d& vector3d);
        //! Overloaded product operator
        Matrix4 operator*(const Matrix4& matrix4);
        //! Overloaded equality operator
        bool operator==(const Matrix4& matrix4);
        //! Overloaded inequality operator
        bool operator!=(const Matrix4& matrix4);

    private:
        //! Reset the matrix
        void reset();
        //! Handy array only utilised by the toArrayFunction
        float array[16];
};

#endif // MATRIX4_H

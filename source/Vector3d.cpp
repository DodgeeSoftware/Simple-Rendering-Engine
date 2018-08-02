#include "Vector3d.h"

Vector3d::Vector3d()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3d::Vector3d( float x, float y, float z )
{
    this->x = x;
    this->y = y;
    this->z = z;
}


Vector3d::Vector3d(const Vector3d& vector)
{
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
}

void Vector3d::normalise()
{
    if (magnitude()>0.0f)
    {
        x = x / magnitude();
        y = y / magnitude();
        z = z / magnitude();
    }
}

Vector3d Vector3d::normalised()
{
    if (magnitude()>0.0f)
        return Vector3d( x / magnitude(), y / magnitude(), z / magnitude() );
    else
        return Vector3d(0.0f, 0.0f, 0.0f);
}

float Vector3d::magnitude()
{
    return sqrtf( x * x + y * y + z * z );
}

float Vector3d::dotProduct( Vector3d vector )
{
    return ( x * vector.x ) + ( y * vector.y ) + ( z * vector.z );
}

Vector3d Vector3d::crossProduct( Vector3d vector )
{
    return Vector3d( (y*vector.z)-(z*vector.y), (z*vector.x)-(x*vector.z), (x*vector.y)-(y*vector.x) );
}

float Vector3d::angleBetween( Vector3d vector )
{
    return acos(normalised().dotProduct(vector.normalised()));
}

std::string Vector3d::toString()
{
    char buf[128];
    snprintf( buf, 128, "x: %.2f y: %.2f z: %.2f", x, y, z );
    return std::string(buf);
}

void Vector3d::toConsole()
{
    // send a message to the console
    std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
}

Vector3d Vector3d::operator=(const Vector3d vector3d)
{
    x = vector3d.x;
    y = vector3d.y;
    z = vector3d.z;
    return *this;
}

Vector3d Vector3d::operator+(const Vector3d& vector3d)
{
    return Vector3d(x + vector3d.x, y + vector3d.y, z + vector3d.z);
}

Vector3d Vector3d::operator+=(const Vector3d& vector3d)
{
    x += vector3d.x;
    y += vector3d.y;
    z += vector3d.z;
    return *this;
}

Vector3d Vector3d::operator-()
{
    return Vector3d(-x, -y, -z);
}

Vector3d Vector3d::operator-(const Vector3d& vector3d)
{
    return Vector3d(x - vector3d.x, y - vector3d.y, z - vector3d.z);
}

Vector3d Vector3d::operator-=(const Vector3d& vector3d)
{
    x -= vector3d.x;
    y -= vector3d.y;
    z -= vector3d.z;
    return *this;
}

Vector3d Vector3d::operator*(const float& scalar)
{
    return Vector3d(x * scalar, y * scalar, z * scalar);
}

Vector3d Vector3d::operator*=(const Vector3d& vector3d)
{
    x *= vector3d.x;
    y *= vector3d.y;
    z *= vector3d.z;
    return *this;
}

Vector3d Vector3d::operator/(const float& scalar)
{
    return Vector3d(x / scalar, y / scalar, z / scalar);
}

Vector3d Vector3d::operator/=(const Vector3d& vector3d)
{
    x /= vector3d.x;
    y /= vector3d.y;
    z /= vector3d.z;
    return *this;
}

bool Vector3d::operator==(const Vector3d& vector3d)
{
    return ( (x == vector3d.x) && (y == vector3d.y) && (z == vector3d.z) );
}

bool Vector3d::operator!=(const Vector3d& vector3d)
{
    return ( (x != vector3d.x) || (y != vector3d.y) || (z != vector3d.z) );
}



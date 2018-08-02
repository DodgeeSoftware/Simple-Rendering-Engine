#include "Vector2d.h"

Vector2d::Vector2d()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2d::Vector2d( float x, float y )
{
    this->x = x;
    this->y = y;
}

Vector2d::Vector2d(const Vector2d& vector)
{
    this->x = vector.x;
    this->y = vector.y;
}

void Vector2d::normalise()
{
    if(magnitude() > 0.0f)
    {
        x = x / magnitude();
        y = y / magnitude();
    }
}

Vector2d Vector2d::normalised()
{
    return Vector2d( x / magnitude(), y / magnitude() );
}

float Vector2d::magnitude()
{
    return sqrtf( x * x + y * y );
}

float Vector2d::dotProduct( Vector2d vector )
{
    return ( x * vector.x ) + ( y * vector.y );
}

Vector2d Vector2d::crossProduct( Vector2d vector )
{
    return Vector2d( (x * vector.y), -(y * vector.x ) );
}

float Vector2d::angleBetween( Vector2d vector )
{
    return acos( normalised().dotProduct(vector.normalised()) );
}

Vector2d Vector2d::operator=(const Vector2d vector2d)
{
    x = vector2d.x;
    y = vector2d.y;
    return *this;
}

Vector2d Vector2d::operator+(const Vector2d& vector2d)
{
    return Vector2d(x + vector2d.x, y + vector2d.y);
}

Vector2d Vector2d::operator+=(const Vector2d& vector2d)
{
    x += vector2d.x;
    y += vector2d.y;
    return *this;
}

Vector2d Vector2d::operator-()
{
    return Vector2d(-x, -y);
}

Vector2d Vector2d::operator-(const Vector2d& vector2d)
{
    return Vector2d(x - vector2d.x, y - vector2d.y);
}

Vector2d Vector2d::operator-=(const Vector2d& vector2d)
{
    x -= vector2d.x;
    y -= vector2d.y;
    return *this;
}

Vector2d Vector2d::operator*(const float& scalar)
{
    return Vector2d(x * scalar, y * scalar);
}

Vector2d Vector2d::operator*=(const float& scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2d Vector2d::operator/(const float& scalar)
{
    return Vector2d(x / scalar, y / scalar);
}

Vector2d Vector2d::operator/=(const float& scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

bool Vector2d::operator==(const Vector2d& vector2d)
{
    return ( (x == vector2d.x) && (y == vector2d.y) );
}

bool Vector2d::operator!=(const Vector2d& vector2d)
{
    return ( (x != vector2d.x) || (y != vector2d.y) );
}

std::string Vector2d::toString()
{
    char buf[128];
    snprintf( buf, 128, "x: %.2f y: %.2f", x, y );
    return std::string(buf);
}

void Vector2d::toConsole()
{
    // send a message to the console
    std::cout << "x: " << x << " y: " << y << std::endl;
}

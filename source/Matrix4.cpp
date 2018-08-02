#include "Matrix4.h"

Matrix4::Matrix4(float* matrix)
{
    for(unsigned int index = 0; index < 16; index++)
        array[index] = matrix[index];
}

void Matrix4::reset()
{
    for(unsigned int index = 0; index < 16; index++)
        array[index] = 0.0f;
}

Vector3d Matrix4::getTranslation()
{
    return Vector3d(array[12], array[13], array[14]);
}

void Matrix4::setTranslation(Vector3d vector)
{
    array[12] = vector.x;
    array[13] = vector.y;
    array[14] = vector.z;
}

Vector3d Matrix4::getRotationRadians()
{
    // TODO
    return Vector3d(0.0f, 0.0f, 0.0f);
}

void Matrix4::setRotationRadians(Vector3d rotation)
{
    Matrix4 roll;
    roll.makeIdentity();
    roll.array[0] = cos(rotation.z);
    roll.array[1] = sin(rotation.z);
    roll.array[4] = -sin(rotation.z);
    roll.array[5] = cos(rotation.z);

    Matrix4 yaw;
    yaw.makeIdentity();
    yaw.array[0] = cos(rotation.y);
    yaw.array[2] = -sin(rotation.y);
    yaw.array[8] = sin(rotation.y);
    yaw.array[10] = cos(rotation.y);

    Matrix4 pitch;
    pitch.makeIdentity();
    pitch.array[5] = cos(rotation.x);
    pitch.array[6] = sin(rotation.x);
    pitch.array[9] = -sin(rotation.x);
    pitch.array[10] = cos(rotation.x);

    Matrix4 result = (roll * yaw * pitch);
    (*this) = (*this) * result;
}

Vector3d Matrix4::getScale()
{
    return Vector3d(array[0], array[5], array[10]);
}

void Matrix4::setScale(Vector3d scale)
{
    array[0] = scale.x;
    array[5] = scale.y;
    array[10] = scale.z;
}

void Matrix4::makeIdentity()
{
    reset();

    array[0] = 1.0f;
    array[5] = 1.0f;
    array[10] = 1.0f;
    array[15] = 1.0f;
}

void Matrix4::transpose()
{
    float buffer[16];

    for(unsigned int index = 0; index < 16; index++)
        buffer[index] = array[index];

    for(unsigned int j = 0; j < 4; j++)
        for(unsigned int i = 0; i < 4; i++)
            array[i * 4 + j] = buffer[j * 4 + i];
}

void Matrix4::toConsole()
{
    for(unsigned int i = 0; i < 4; i++)
    {
        for(unsigned int j = 0; j < 4; j++)
        {
            std::cout << " " << array[i + j * 4] << ", ";
        }
        std::cout << std::endl;
    }
}

Matrix4 Matrix4::operator=(const Matrix4 matrix4)
{
    for(unsigned int index = 0; index < 16; index++)
        array[index] = matrix4.array[index];
    return *this;
}

Matrix4 Matrix4::operator+(const Matrix4& matrix4)
{
    for(unsigned int index = 0; index < 16; index++)
        array[index] += matrix4.array[index];
    return *this;
}

Matrix4 Matrix4::operator-(const Matrix4& matrix4)
{
    for(unsigned int index = 0; index < 16; index++)
        array[index] -= matrix4.array[index];
    return *this;
}

Matrix4 Matrix4::operator*(const float& scalar)
{
    for(unsigned int index = 0; index < 16; index++)
        array[index] *= scalar;
    return *this;
}

Vector3d Matrix4::operator*(const Vector3d& vector3d)
{
    Vector3d result;
    result.x = array[0] * vector3d.x + array[4] * vector3d.y + array[8] * vector3d.z + array[12] * 1.0f;
    result.y = array[1] * vector3d.x + array[5] * vector3d.y + array[9] * vector3d.z + array[13] * 1.0f;
    result.z = array[2] * vector3d.x + array[6] * vector3d.y + array[10] * vector3d.z + array[14] * 1.0f;
    return result;
}

Matrix4 Matrix4::operator*(const Matrix4& matrix4)
{
    float buffer[16];
    for(unsigned index = 0; index < 16; index++)
        buffer[index] = 0.0f;

    for(unsigned int i = 0; i < 4; i++)
        for(unsigned int j = 0; j < 4; j++)
            for(unsigned int k = 0; k < 4; k++)
                buffer[i + j * 4] += (array[i + k * 4] * matrix4.array[k + j * 4]);

    return Matrix4(buffer);
}

bool Matrix4::operator==(const Matrix4& matrix4)
{
    for(unsigned int j = 0; j < 4; j++ )
        for(unsigned int i = 0; i < 4; i++ )
            if(array[i + j * 4] != matrix4.array[i + j * 4])
                return false;
    return true;

}

bool Matrix4::operator!=(const Matrix4& matrix4)
{
    for(unsigned int j = 0; j < 4; j++ )
        for(unsigned int i = 0; i < 4; i++ )
            if(array[i + j * 4] != matrix4.array[i + j * 4])
                return true;
    return false;
}

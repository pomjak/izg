#include "Student.h"

#include <osg/Plane>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

osg::Vec3d projectOnPlane(const osg::Vec3d& vector, const osg::Vec3d& planeNormal)
{
    auto pp = vector - planeNormal * (vector * planeNormal);
    //get rid of round-off error
    pp[0] = std::abs(pp[0]) < 1e-6 ? 0 : pp[0];
    pp[1] = std::abs(pp[1]) < 1e-6 ? 0 : pp[1];
    pp[2] = std::abs(pp[2]) < 1e-6 ? 0 : pp[2];

    return pp;
}

double dot(const osg::Vec3d& u, const osg::Vec3d& v)
{
    auto d = u * v;

    //handle rounding errors
    d = std::clamp(d, -1.0, 1.0);

    return d;
}

osg::Vec3d cross(const osg::Vec3d& u, const osg::Vec3d& v)
{
    return u ^ v;
}

void normalize(osg::Vec3d& v)
{
    v.normalize();
}

osg::Vec3d normalized(const osg::Vec3d& v)
{
    osg::Vec3d u(v);
    u.normalize();

    return u;
}

osg::Matrix inverse(const osg::Matrix& m)
{
    return osg::Matrix::inverse(m);
}

#if USE_STUDENT_SOLUTION
osg::Matrix getScaleMatrix(const osg::Vec3d& scale)
{
    //Task 1 - fill in the scale matrix

    osg::Matrix m;
    m(0, 0) = scale.x();
    m(1, 1) = scale.y();
    m(2, 2) = scale.z();
    return m;
}

osg::Matrix getTranslationMatrix(const osg::Vec3d& translation)
{
    //Task 2 - fill in the translation matrix

    osg::Matrix m(
        1, 0, 0, translation.x(),
        0, 1, 0, translation.y(),
        0, 0, 1, translation.z(),
        0, 0, 0, 1);
    return m;
}

osg::Matrix rotateAroundX(double angle)
{

    double sina = std::sin(angle);
    double cosa = std::cos(angle);

    //Task 3 - fill in the rotation matrix around X axis
    osg::Matrix m(
        1,    0,     0, 0,
        0, cosa,  sina, 0,
        0, -sina, cosa, 0,
        0,    0,     0, 1);

    return m;
}

osg::Matrix rotateAroundY(double angle)
{
    double sina = std::sin(angle);
    double cosa = std::cos(angle);

    //Task 4 - fill in the rotation matrix around Y axis

    osg::Matrix m(
        cosa , 0,  sina, 0,
        0    , 1, 0    , 0,
        -sina, 0,  cosa, 0,
        0    , 0, 0    , 1);

    return m;
}

osg::Matrix rotateAroundZ(double angle)
{
    double sina = std::sin(angle);
    double cosa = std::cos(angle);

    //Task 5 - fill in the rotation matrix around Z axis

    osg::Matrix m(
        cosa ,  sina, 0, 0,
        -sina ,  cosa , 0, 0,
        0    ,      0, 1, 0,
        0    ,      0, 0, 1);

    return m;
}

double angleBetweenVectors(osg::Vec3d u, osg::Vec3d v)
{
    if (u.length2() == 0 || v.length2() == 0)
    {
        return 0.0;
    }

    //Task 6
    //Normalize both vectors - method normalize()
    normalize(u);
    normalize(u);
    //Compute cosine of the angle between the vectors using the dot product - function dot
    double angle = dot(u,v);
    //Return the angle using arcus cosine - function std::acos()

    return std::acos(angle);
}

osg::Matrix getRotationMatrix(const osg::Vec3d& fromVector, const osg::Vec3d& toVector)
{
    const osg::Vec3d xAxis(1, 0, 0);
    const osg::Vec3d yAxis(0, 1, 0);
    const osg::Vec3d zAxis(0, 0, 1);

    //Task 7 - compute the rotation matrix around arbitrary axis

    //Compute the angle between input vectors - function angleBetweenVectors
    double angle_between_vecs = angleBetweenVectors(fromVector,toVector);

    //7a - compute the rotation axis using the cross product - function cross
    osg::Vec3d cross_product = cross(fromVector,toVector);

    //7b - project rotation axis into XY plane
    osg::Vec3d project_rot_XY = projectOnPlane(cross_product, cross(xAxis,yAxis));

    //7c - compute the angle between projected rotation axis and X axis
    double angle_rotXY_X = angleBetweenVectors(xAxis, project_rot_XY);

    //7d - compute rotation around Z axis
    osg::Matrix rotZ = rotateAroundZ(angle_rotXY_X);

    //Rotate the rotation axis into XZ plane
    osg::Vec3d project_rot_XZ = projectOnPlane(cross_product, cross(xAxis, zAxis));

    //7e - compute angle between rotation axis in XZ and X axis and compute rotation matrix around Y corrently, hint - for Pi use M_PI
    double angle_rotXZ_X = angleBetweenVectors(xAxis, project_rot_XZ);
    if (project_rot_XZ.z() < 0)
    {
        angle_rotXZ_X = (2 * M_PI) - angle_rotXZ_X;
    }

    osg::Matrix rotY = rotateAroundY(angle_rotXZ_X);

    //7f - compute the desired rotation around X axis
    osg::Matrix rotX = rotateAroundX(angle_between_vecs);

    //7g - compute and return the final rotation - for matrix inverse use function inverse
    osg::Matrix result;
    osg::Matrix invZ = inverse(rotZ);
    osg::Matrix invY = inverse(rotY);

    result = rotZ * rotY * rotX * invZ * invY;

    return result;
}
#else

osg::Matrix getScaleMatrix(const osg::Vec3d& scale)
{
    return osg::Matrix::scale(scale);
}

osg::Matrix getTranslationMatrix(const osg::Vec3d& translation)
{
    return osg::Matrix::translate(translation);
}

osg::Matrix getRotationMatrix(const osg::Vec3d& fromVector, const osg::Vec3d& toVector)
{
    osg::Quat q;
    q.makeRotate(fromVector, toVector);

    return osg::Matrix(q);
}

osg::Matrix rotateAroundX(double angle)
{
    return {};
}

osg::Matrix rotateAroundY(double angle)
{
    return {};
}

osg::Matrix rotateAroundZ(double angle)
{
    return {};
}

double angleBetweenVectors(osg::Vec3d u, osg::Vec3d v)
{
    return 0.0;
}
#endif
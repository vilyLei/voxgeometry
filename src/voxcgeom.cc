
#include <iostream>
#include <iomanip>
#include "voxcgeomConfig.h"
#include "voxcgeom/base/Vec3D.h"
#include "voxcgeom/base/AABB.h"
#include "voxcgeom/base/Sphere.h"
#include "voxcgeom/base/StraightLine.h"
#include "voxcgeom/base/RadialLine.h"
#include "voxcgeom/base/LineSegment.h"
#include "voxcgeom/base/Plane.h"
#include "voxcgeom/calc/PlaneCalc.h"

int main (int argc, char *argv[])
{
    Vec3D va{ 1.1f,2.1f,3.3f,4.5f };
    va.coutThis();
    AABB ab0{ Vec3D{10.0f,10.0f,10.0f}, Vec3D{110.0f,110.0f,110.0f} };
    AABB ab1{ Vec3D{-30.0f,-30.0f,-30.0f}, Vec3D{-110.0f,-110.0f,-110.0f} };
    bool boo = ab0.intersect(ab1);
    std::cout << "boo: " << boo << std::endl;

    VCG_Number degree = Vec3D::DegreeBetween(Vec3D::X_AXIS, Vec3D::Y_AXIS);
    std::cout << "degree: " << degree << std::endl;
    Sphere sph;
    std::cout << "Sphere::uid: " << sph.uid << std::endl;
    //  std::cout<< std::setiosflags(std::ios::fixed);
    //  std::cout<< std::setprecision(20) << VCG_MATH_PI << std::endl;
    //  std::cout<<"boxcgeom init...\n";
    //  std::cout<< VCG_MATH_PI<<std::endl;
    //  std::cout<<"180.0f/VCG_MATH_PI: "<< 180.0f/VCG_MATH_PI<<std::endl;
    //  std::cout<<"VCG_MATH_PI/180.0f: "<< VCG_MATH_PI/180.0f<<std::endl;
    return 0;
}
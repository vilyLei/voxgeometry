
#include <iostream>
#include <iomanip>
#include "voxcgeomConfig.h"
#include "voxcgeom/math/Vec3D.h"
#include "voxcgeom/base/AABB.h"
#include "voxcgeom/base/Sphere.h"
#include "voxcgeom/base/StraightLine.h"
#include "voxcgeom/base/RadialLine.h"
#include "voxcgeom/base/LineSegment.h"
#include "voxcgeom/base/Plane.h"
#include "voxcgeom/base/Cone.h"
#include "voxcgeom/calc/PlaneCalc.h"

void testCone()
{

    Vec3D outPv;
    Cone pcone;
    pcone.position.setXYZ(0.0f, 200.0f, 0.0f);
    pcone.tv.setXYZ(0.0f, -1.0f, 0.0f);
    pcone.height = 210.0f;
    pcone.radius = 100.0f;
    Vec3D innerPv(-7.5f, 187.0f, -25.98f);
    pcone.tv.copyFrom(innerPv);
    pcone.tv.subtractBy(pcone.position);
    pcone.update();
    pcone.tv.coutThis();
    std::cout << "pcone.getHalfAngleCos: " << pcone.getHalfAngleCos() << std::endl;
    bool boo0 = pcone.containsPosition(outPv);
    std::cout << "pcone.containsPosition(): " << boo0 << std::endl;

    Vec3D pa, nearV0, nearV1;
    pa.copyFrom(pcone.position);
    Vec3D pb(100.0f, -30.0f, -340.0f);
    Vec3D dv(-50.0f, 41.072f, -50.0f);
    pa.addBy(dv);
    pb.addBy(dv);

    Vec3D tv;
    tv.copyFrom(pb);
    tv.subtractBy(pa);
    tv.normalize();

    pb.x = pa.x + tv.x * 700.0f;
    pb.y = pa.y + tv.y * 700.0f;
    pb.z = pa.z + tv.z * 700.0f;

    pa.x += tv.x * -300.0f;
    pa.y += tv.y * -300.0f;
    pa.z += tv.z * -300.0f;
    bool boo1 = pcone.intersectionSL(pa, tv, nearV0, nearV1);
    std::cout << "pcone.intersectionSL(): " << boo1 << std::endl;
}
int main (int argc, char *argv[])
{
    Vec3D va{ 1.1f,2.1f,3.3f,4.5f };
    va.coutThis();
    AABB ab0{ Vec3D{10.0f,10.0f,10.0f}, Vec3D{110.0f,110.0f,110.0f} };
    AABB ab1{ Vec3D{-30.0f,-30.0f,-30.0f}, Vec3D{-110.0f,-110.0f,-110.0f} };
    bool boo = ab0.intersect(ab1);
    std::cout << "boo: " << boo << std::endl;

    std::cout<< std::setiosflags(std::ios::fixed);
    std::cout<< std::setprecision(10) << VCG_MATH_PI << std::endl;

    VCG_Number degree = Vec3D::DegreeBetween(Vec3D::X_AXIS, Vec3D::Y_AXIS);
    std::cout << "degree: " << degree << std::endl;
    Sphere sph;
    std::cout << "Sphere::uid: " << sph.uid << std::endl;

    testCone();
    //  std::cout<< std::setiosflags(std::ios::fixed);
    //  std::cout<< std::setprecision(20) << VCG_MATH_PI << std::endl;
    //  std::cout<<"boxcgeom init...\n";
    //  std::cout<< VCG_MATH_PI<<std::endl;
    //  std::cout<<"180.0f/VCG_MATH_PI: "<< 180.0f/VCG_MATH_PI<<std::endl;
    //  std::cout<<"VCG_MATH_PI/180.0f: "<< VCG_MATH_PI/180.0f<<std::endl;
    return 0;
}
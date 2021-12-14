
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include "voxcgeomConfig.h"
#include "voxcgeom/math/Vec3D.h"
#include "voxcgeom/math/Matrix4.h"
#include "voxcgeom/base/AABB.h"
#include "voxcgeom/base/Sphere.h"
#include "voxcgeom/base/StraightLine.h"
#include "voxcgeom/base/RadialLine.h"
#include "voxcgeom/base/LineSegment.h"
#include "voxcgeom/base/Plane.h"
#include "voxcgeom/base/Cone.h"
#include "voxcgeom/calc/PlaneCalc.h"

//////////////////////////////////////////////////////////////
///
/// demo
/// 
/// /////////////////////////////////////////////////////////
#include "../demo/math/MatrixComputer.h"

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

void testSimple()
{
    Vec3D va{ 1.1f,2.1f,3.3f,4.5f };
    va.coutThis();
    AABB ab0{ Vec3D{10.0f,10.0f,10.0f}, Vec3D{110.0f,110.0f,110.0f} };
    AABB ab1{ Vec3D{-30.0f,-30.0f,-30.0f}, Vec3D{-110.0f,-110.0f,-110.0f} };
    bool boo = ab0.intersect(ab1);
    std::cout << "boo: " << boo << std::endl;

    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(10) << VCG_MATH_PI << std::endl;

    VCG_Number degree = Vec3D::DegreeBetween(Vec3D::X_AXIS, Vec3D::Y_AXIS);
    std::cout << "degree: " << degree << std::endl;
    Sphere sph;
    std::cout << "Sphere::uid: " << sph.uid << std::endl;
}
void testMatrix4()
{
    int setprecisionSize = 6;
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(setprecisionSize) << "testMatrix4" << std::endl;
    Matrix4 mat4A;
    mat4A.identity();
    mat4A.setScaleXYZ(10.0f,4.5f,2.1f);
    mat4A.setRotationEulerAngle(30.0f,20.0f,80.0f);
    mat4A.setTranslationXYZ(30.0f,20.0f,80.0f);
    mat4A.coutThis();

    mat4A.pointAt(Vec3D(), Vec3D(0.0f,0.0f,100.0f), Vec3D(0.0f,1.0f,0.0f));
    std::cout << "mat4A.pointAt: " << std::endl;
    mat4A.coutThis();
}
void testMathDemo()
{
    Matrix4 mat4A;
    mat4A.identity();
    mat4A.setScaleXYZ(10.0f, 4.5f, 2.1f);
    mat4A.setRotationEulerAngle(30.0f, 20.0f, 80.0f);
    mat4A.setTranslationXYZ(30.0f, 20.0f, 80.0f);
    mat4A.coutThis();
    unsigned int index = 0;
    ///*
    MatrixComputer matCompter;
    matCompter.allocate(16);
    matCompter.setScaleXYZParamAt(10.0f, 4.5f, 2.1f, index);
    matCompter.setRotationEulerAngleParamAt(30.0f, 20.0f, 80.0f, index);
    matCompter.setTranslationXYZParamAt(30.0f, 20.0f, 80.0f, index);
    index++;
    matCompter.setScaleXYZParamAt(10.0f, 4.5f, 2.1f, index);
    matCompter.setRotationEulerAngleParamAt(30.0f, 20.0f, 80.0f, index);
    matCompter.setTranslationXYZParamAt(30.0f, 20.0f, 80.0f, index);

    matCompter.calc(2);
    //matCompter.identityAt(0);
    std::cout << "----------- ------ ----------------- ----" << std::endl;
    matCompter.coutThisMatAt(0);
    matCompter.coutThisMatAt(1);
    matCompter.coutThis();
    //*/
}
/*
bool checkPerfectNumber(int num){
{
    //  int value = 1;
    //  for (int i = 2; i < num; ++i)
    //  {
    //      //value += (num % i) == 0 ? 0 : i;
    //  }
    //  return value == num;
    return true;
}
//*/
bool uniqueOccurrences(std::vector<int>& arr) {

    std::unordered_map<int, int> int_map;
    std::unordered_map<int, unsigned char> count_map;
    std::vector<int> keys;
    int value;
    for each (auto k in arr)
    {
        if (int_map.find(k) != int_map.end()) {
            value = int_map[k];
            int_map[k] += 1;
        }else {
            int_map.insert(std::unordered_map<int, int>::value_type(k, 1));
            keys.push_back(k);
        }
    }
    for each (auto k in keys)
    {
        value = int_map[k];
        if (count_map.find(value) != count_map.end()){
            return false;
        }
        else{
            count_map.insert(std::unordered_map<int, unsigned char>::value_type(value, 1));
        }
    }
    return true;
}
bool checkPerfectNumber(int num) {
    int value = 1;
    for (int i = 2; i < num; ++i)
    {
        value += (num % i) ? 0 : i;
    }
    return value == num;
}
void exampleTest()
{
    std::cout << "exampleTest begin..." << std::endl;

    //  bool hit = checkPerfectNumber(28);
    //  std::cout << "hit: "<< hit << std::endl;


    std::vector<int> ivs0 = {1,2,2,1,1,3};
    std::vector<int> ivs = {1,1,3,3,4,5,5,5};
    std::vector<int> ivs2 = {1,2,3,34,44,53,156,85};
    bool hit = uniqueOccurrences(ivs0);
    std::cout << "hit: "<< hit << std::endl;

}
int main (int argc, char *argv[])
{
    //  testSimple();
    //  testCone();
    //  testMatrix4();
    //  testMathDemo();
    exampleTest();
    //  std::cout<< std::setiosflags(std::ios::fixed);
    //  std::cout<< std::setprecision(20) << VCG_MATH_PI << std::endl;
    //  std::cout<<"boxcgeom init...\n";
    //  std::cout<< VCG_MATH_PI<<std::endl;
    //  std::cout<<"180.0f/VCG_MATH_PI: "<< 180.0f/VCG_MATH_PI<<std::endl;
    //  std::cout<<"VCG_MATH_PI/180.0f: "<< VCG_MATH_PI/180.0f<<std::endl;
    return 0;
}
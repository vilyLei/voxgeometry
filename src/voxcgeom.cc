
#include <iostream>
#include <iomanip>
#include "voxcgeomConfig.h"
#include "voxcgeom/base/Vec3D.h"
int main (int argc, char *argv[])
{
    Vec3D va{ 1.1f,2.1f,3.3f,4.5f };
    va.coutThis();
    VCG_Number degree = Vec3D::DegreeBetween(Vec3D::X_AXIS, Vec3D::Y_AXIS);
    std::cout << "degree: " << degree << std::endl;
    //  std::cout<< std::setiosflags(std::ios::fixed);
    //  std::cout<< std::setprecision(20) << VCG_MATH_PI << std::endl;
    //  std::cout<<"boxcgeom init...\n";
    //  std::cout<< VCG_MATH_PI<<std::endl;
    //  std::cout<<"180.0f/VCG_MATH_PI: "<< 180.0f/VCG_MATH_PI<<std::endl;
    //  std::cout<<"VCG_MATH_PI/180.0f: "<< VCG_MATH_PI/180.0f<<std::endl;
    return 0;
}
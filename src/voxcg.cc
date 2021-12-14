/**

em++ --bind -o ../../public/wasm/matDemo.js ../voxcgeom/cgeomPre.cc ../voxcgeom/math/Vec3D.cc ../voxcgeom/math/Matrix4.cc ../demo/math/MatrixComputer.cc matDemo.cc -std=c++11 -D WASM_DEV_ENV -O2 -s WASM=1

em++ --bind -o ../../public/wasm/transformDemo.js ../voxcgeom/cgeomPre.cc ../voxcgeom/math/Vec3D.cc ../voxcgeom/math/Matrix4.cc ../demo/math/MatrixComputer.cc transformDemo.cc -std=c++11 -D WASM_DEV_ENV -O2 -s WASM=1

em++ --bind -o ../../public/wasm/transformDemo.js ../voxcgeom/cgeomPre.cc ../voxcgeom/math/Vec3D.cc ../voxcgeom/math/Matrix4.cc ../voxcgeom/math/Matrix4Container.cc ../demo/math/MatrixComputer.cc ./app/trans/MatTransform.cc ../simnav/stara/StNode.cc  ../simnav/stara/BinaryHeap.cc  ../simnav/stara/StarA.cc transformDemo.cc -std=c++11 -D WASM_DEV_ENV -O2 -s WASM=1

cmake .. -DPROGType=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=D:/emsc/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -G "NMake Makefiles"

cmake .. -DPROGType=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=D:/emsc/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -G "NMake Makefiles"
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=D:/emsc/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -G "NMake Makefiles"
cmake .. -DCMAKE_TOOLCHAIN_FILE=D:/emsc/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -G "NMake Makefiles"
cmake .. -DPROGType=ON -DCMAKE_TOOLCHAIN_FILE=D:/emsc/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -G "NMake Makefiles"
cmake .. -DPROGType=ON -DCMAKE_TOOLCHAIN_FILE=D:/emsc/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -G "NMake Makefiles"
cmake --build .
*/
#include <iostream>
#include <iomanip>
#include <string>
#include "voxcgeomConfig.h"
#include "./voxcgeom/cgeomPre.h"
#include "./voxcgeom/math/Vec3D.h"
#include "./voxcgeom/math/Matrix4.h"
#include "./demo/math/MatrixComputer.h"
#include "./wasm/app/trans/MatTransform.h"

#include "./simnav/stara/StarA.h"

#ifdef WASM_DEV_ENV
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
using namespace emscripten;
#endif

void showVersion()
{
    int setprecisionSize = 6;
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(setprecisionSize) << "showVersion" << std::endl;
    std::cout<<"em++ demomain bindings version 1.0.1!\n";
    std::cout<<"VCG_MATH_E: "<< VCG_MATH_E <<"\n";
    VCG_Number pnumber = 10.012;
    std::cout<<"VCG_Number pnumber: "<< pnumber <<"\n";
    MatTransform mtf0;

    Vec3D vec3a(1.0f,2.1f,3.3f);
    Vec3D vec3b(1.0f,-2.1f,3.3f);
    Vec3D vec3c;
    vec3a.coutThis();
    Vec3D::Cross(vec3a, vec3b, vec3c);
    vec3c.coutThis();
    vec3c.normalize();
    vec3c.coutThis();

    std::cout<<"SafeACos(0.5f): "<<SafeACos(0.5f)<<std::endl;
    #ifndef WASM_DEV_ENV
    std::cout<<"WASM DEF NO..."<<std::endl;
    #else
    std::cout<<"WASM DEF YES..."<<std::endl;
    #endif

    Matrix4 mat4A;
    mat4A.identity();
    mat4A.setScaleXYZ(10.0f,4.5f,2.1f);
    mat4A.setRotationEulerAngle(30.0f,20.0f,80.0f);
    mat4A.setTranslationXYZ(30.0f,20.0f,80.0f);
    mat4A.coutThis();
}
float getVersion()
{
    return 1.02f;
}

/*
template<typename T, size_t sizeOfArray>
constexpr size_t getElementCount(T (&)[sizeOfArray])
{
    return sizeOfArray;
}
// callback
static void callWithMemoryView(val v)
{
    // static so the JS test can read the memory after callTakeMemoryView runs
    static unsigned char data[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    v(typed_memory_view(getElementCount(data), data));
    static float f[] = { 1.5f, 2.5f, 3.5f, 4.5f };
    v(typed_memory_view(getElementCount(f), f));
    static short s[] = { 1000, 100, 10, 1 };
    v(typed_memory_view(getElementCount(s), s));
}
*/

void testMathDemo()
{
    Matrix4 mat4A;
    mat4A.identity();
    mat4A.setScaleXYZ(10.0f, 4.5f, 2.1f);
    mat4A.setRotationEulerAngle(30.0f, 20.0f, 80.0f);
    mat4A.setTranslationXYZ(30.0f, 20.0f, 80.0f);
    mat4A.coutThis();
    unsigned int index = 0;

    MatrixComputer matCompter;
    matCompter.allocate(16);
    matCompter.setScaleXYZParamAt(10.0f, 4.5f, 2.1f, index);
    matCompter.setRotationEulerAngleParamAt(30.0f, 20.0f, 80.0f, index);
    matCompter.setTranslationXYZParamAt(30.0f, 20.0f, 80.0f, index);
    matCompter.calc(1);
    //matCompter.identityAt(0);
    matCompter.coutThisMatAt(0);
    matCompter.coutThis();
}
#ifdef WASM_DEV_ENV
EMSCRIPTEN_BINDINGS(pmodule)
{
    function("showVersion", &showVersion);
    function("testMathDemo", &testMathDemo);

    class_<MatrixComputer>("MatrixComputer")
    .constructor()
    .function("allocate", &MatrixComputer::allocate)
    .function("getMatData", &MatrixComputer::getMatData)
    .function("getParamData", &MatrixComputer::getParamData)
    .function("getIData", &MatrixComputer::getIData)
    .function("setScaleXYZParamAt", &MatrixComputer::setScaleXYZParamAt)
    .function("setRotationEulerAngleParamAt", &MatrixComputer::setRotationEulerAngleParamAt)
    .function("setTranslationXYZParamAt", &MatrixComputer::setTranslationXYZParamAt)
    .function("identityAt", &MatrixComputer::identityAt)
    .function("calcMotion", &MatrixComputer::calcMotion)
    .function("calc", &MatrixComputer::calc)
    .function("coutThisMatAt", &MatrixComputer::coutThisMatAt)
    .function("coutThis", &MatrixComputer::coutThis)
    ;


    class_<MatTransform>("MatTransform")
        .constructor()
        .function("allocate", &MatTransform::allocate)
        .function("allocate2", &MatTransform::allocate2)
        .function("getMatData", &MatTransform::getMatData)
        .function("getParamData", &MatTransform::getParamData)
        .function("updateParam", &MatTransform::updateParam)
        .function("updateParam2", &MatTransform::updateParam2)
        .function("identityAt", &MatTransform::identityAt)
        .function("calc", &MatTransform::calc)
        .function("coutThisMatAt", &MatTransform::coutThisMatAt)
        ;


    class_<StarA>("StarA")
        .constructor()
        .function("allocate", &StarA::allocate)
        .function("initialize", &StarA::initialize)
        .function("setGoValueByRC", &StarA::setGoValueByRC)
        .function("searchPathDataByRC", &StarA::searchPathDataByRC)
        .function("getPathData", &StarA::getPathData)
        .function("getPathDataTotal", &StarA::getPathDataTotal)
        ;
    
}
#else

void transformDemoMain()
{
    std::cout << "transformDemoMain..." << std::endl;
}
StarA* staPtr = nullptr;
int main(int argc, char* argv[])
{
    std::cout << "voxcg win: transformDemo main run()..." << std::endl;
    ///*
    MatTransform mtf0;
    //mtf0.allocate(1);
    mtf0.allocate2(1);
    VCG_Number* paramvs = mtf0.getParamData();
    paramvs[0] = 1001.0f; paramvs[1] = 0.0f; paramvs[2] = 2001.0f;
    paramvs[3] = 80.0f; paramvs[4] = -30.0f; paramvs[5] = 100.0f;
    paramvs[6] = 0.1f; paramvs[7] = 0.2f; paramvs[8] = 1.0f;
    mtf0.updateParam2();
    mtf0.calc();
    mtf0.coutThisMatAt(0);
    mtf0.coutThisMatAt(1);
    //*/
    StarA* sa = nullptr;
    //sa->Calc(1);

    StarA st;
    StarA::Calc(1);
    st.allocate(256);
    st.buildTest();
    std::cout << "transformDemo main run() end..." << std::endl;
    //*/
    return 0;
}

#endif
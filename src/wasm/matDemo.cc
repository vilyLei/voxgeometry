/**
emcc hello_world.c
//for c source code
emcc hello_world.c -o hello.html
// for c++ source code
em++ hello_world.c -o hello.html
emcc hello_world.c EXPORTED_FUNCTIONS = "['raiseOneInt']" -o hello.html

emcc hello_world.c EXTRA_EXPORTED_RUNTIME_METHOD S= '["raiseOneInt"]' -o hello.html

var _raiseOneInt = Module["_raiseOneInt"] = createExportWrapper("raiseOneInt");
-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'
//emcc hello_world.c -o hello.html

# -O2 is already a pretty high level of optimization
emcc hello.c -o hello.js -O2 -s WASM=1

var js_wrapped_fib = Module.cwrap("fib", "number", ["number"]);

emcc hello.c -o hello.js -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'
emcc hello_world.c -o hello.js -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'
emcc hello_world.c -o hello.html -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'

emcc hello.c -o hello.js -s WASM=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap']"

emcc hello_world.c -o hello.html -s "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap']"

emcc --bind -o testBind.js testBind.cpp
emcc --bind -o testBind.html testBind.cpp

em++ --bind -o testBind.js testBind.cpp
//em++ --bind -std=c++11 -o testBind.js testBind.cpp
em++ --bind -o testBind.js testBind.cc -std=c++11
error:
em++ --bind -o testBind.js testBind.cc CarDemo.cc -std=c++11
em++ --bind -o testBind.js CarDemo.cc testBind.cc -std=c++11
em++ --bind -o testBind.html CarDemo.cc testBind.cc -std=c++11
em++ --bind -o testBind.html geom/Vector3D.cc CarDemo.cc testBind.cc -std=c++11
em++ --bind -o demomain.js vox/math/mathDef.h vox/geom/Vector3D.cc CarDemo.cc demomain.cc -std=c++11
// 下面这句是错的, 因为不能有.h文件进入编译参数
em++ --bind -o demomain.js vox/math/mathDef.h vox/math/Vec3D.cc vox/geom/Vector3D.cc CarDemo.cc demomain.cc -std=c++11
em++ --bind -o demomain.js vox/math/mathDef.cc vox/math/Vec3D.cc vox/geom/Vector3D.cc CarDemo.cc demomain.cc -std=c++11
em++ --bind -o demomain.js voxcgeom/cgeomPre.cc voxcgeom/math/Vec3D.cc voxcgeom/math/Matrix4.cc CarDemo.cc demomain.cc -std=c++11
em++ --bind -o ../../public/wasm/demomain.js ../voxcgeom/cgeomPre.cc ../voxcgeom/math/Vec3D.cc ../voxcgeom/math/Matrix4.cc CarDemo.cc demomain.cc -std=c++11
em++ --bind -o ../../public/wasm/demomain.js ../voxcgeom/cgeomPre.cc ../voxcgeom/math/Vec3D.cc ../voxcgeom/math/Matrix4.cc ../demo/math/MatrixComputer.cc CarDemo.cc demomain.cc -std=c++11
em++ --bind -o ../../public/wasm/matDemo.js ../voxcgeom/cgeomPre.cc ../voxcgeom/math/Vec3D.cc ../voxcgeom/math/Matrix4.cc ../demo/math/MatrixComputer.cc CarDemo.cc matDemo.cc -std=c++11
em++ --bind -o ../../public/wasm/matDemo.js ../voxcgeom/cgeomPre.cc ../voxcgeom/math/Vec3D.cc ../voxcgeom/math/Matrix4.cc ../demo/math/MatrixComputer.cc matDemo.cc -std=c++11 -D WASM_DEV_ENV
em++ --bind -o ../../public/wasm/matDemo.js ../voxcgeom/cgeomPre.cc ../voxcgeom/math/Vec3D.cc ../voxcgeom/math/Matrix4.cc ../demo/math/MatrixComputer.cc matDemo.cc -std=c++11 -D WASM_DEV_ENV -O2 -s WASM=1

*/
#include <iostream>
#include <iomanip>
#include <string>
//#include "CarDemo.h"
#include "../voxcgeom/cgeomPre.h"
#include "../voxcgeom/math/Vec3D.h"
#include "../voxcgeom/math/Matrix4.h"
#include "../demo/math/MatrixComputer.h"
//#include <emscripten/emscripten.h> // note we added the emscripten header
// quick_example.cpp
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

void showVersion()
{
    int setprecisionSize = 6;
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(setprecisionSize) << "showVersion" << std::endl;
    std::cout<<"em++ demomain bindings version 1.0.1!\n";
    std::cout<<"VCG_MATH_E: "<< VCG_MATH_E <<"\n";
    VCG_Number pnumber = 10.012;
    std::cout<<"VCG_Number pnumber: "<< pnumber <<"\n";
    //vox::math::Vec3D vec3a(1.0,2.1,3.3);
    Vec3D vec3a(1.0,2.1,3.3);
    Vec3D vec3b(1.0,-2.1,3.3);
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
float getVersion() {
    return 1.01f;
}

size_t bufferLength = 5;
unsigned char *bytesBuffer = new unsigned char[5]{0,1,2,3,4};

val getTestBytes() {
    return val(typed_memory_view(bufferLength, bytesBuffer));
}
int getSumBytes()
{
    int value = 0;
    for(auto i = 0;i < bufferLength;++i)
    {
        value += bytesBuffer[i];

    }
    return value;
}


unsigned emval_test_sum(val v)
{
    std::cout<<"emval_test_sum v02."<<std::endl;
    unsigned length = v["length"].as<unsigned>();
    //duoble rv = 0;
    int rv = 0;
    for (unsigned i = 0; i < length; ++i) {
        //rv += v[i].as<double>();
        rv += v[i].as<int>();
    }
    return rv;
}
int emval_test_sum2(int vals, int size)
{
    std::cout<<"emval_test_sum2 size: "<<size<<std::endl;
    //unsigned length = v["length"].as<unsigned>();
    //duoble rv = 0;
    int rv = 0;
    //  for (int i = 0; i < size; ++i) {
    //      //rv += v[i].as<double>();
    //      rv += vals[i];//.as<int>();
    //  }
    return rv;
}

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
//https://preshing.com/20170511/how-to-build-a-cmake-based-project/
//emcc main.cpp ./src/*.cpp ./extern/*.cpp -o dist/engine.js -g  -s DISABLE_EXCEPTION_CATCHING=0 -s TOTAL_MEMORY=33554432  -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 --bind -s WASM=1 -Os -s LEGACY_GL_EMULATION=0  -s GL_UNSAFE_OPTS=0 --pre-js pre-module.js --post-js post-module.js -s ASSERTIONS=2 -s GL_ASSERTIONS=1 -s INVOKE_RUN=0  -std=c++11 -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s OFFSCREENCANVAS_SUPPORT=1 --preload-file textures --preload-file shaders --preload-file extern --use-preload-plugins 
//CMAKE_TOOLCHAIN_FILE=path/to/emscripten/emscripten/version/cmake/Modules/Platform/Emscripten.cmake
//set CMAKE_TOOLCHAIN_FILE=D:/emsdk/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
//Visual Studio 16 2019
//cmake.exe -G "Visual Studio 16 2019" -A Emscripten -DCMAKE_TOOLCHAIN_FILE=%EMSCRIPTEN%\cmake\Modules\Platform\Emscripten.cmake
//cmake -G "Visual Studio 16 2019" -A emscripten -D CMAKE_TOOLCHAIN_FILE=D:/emsdk/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
//emcmake cmake CMakeLists.txt
//https://stackoverflow.com/questions/45260216/emscripten-cmake-pass-emscripten-options-in-cmakelist-file
//cmake -DCMAKE_BUILD_TYPE=Debug -G \"Unix Makefiles\" -DCMAKE_TOOLCHAIN_FILE=D:/emsdk/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake . && make
//cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 16 2019" -DCMAKE_TOOLCHAIN_FILE=D:/emsdk/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake . && make
//cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 16 2019" -DCMAKE_TOOLCHAIN_FILE=D:/emsdk/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake . && ALL_BUILD
EMSCRIPTEN_BINDINGS(pmodule)
{

    //  function("tool$lerp", &tool::lerp);
    //  function("getVersion", &getVersion);
    //  function("getTestBytes", &getTestBytes);
    //  function("getSumBytes", &getSumBytes);
    //  function("callWithMemoryView", &callWithMemoryView);
    function("emval_test_sum", &emval_test_sum);
    function<int,int,int>("emval_test_sum2", &emval_test_sum2);

    function("showVersion", &showVersion);
    function("getTestBytes", &getTestBytes);
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
    //  class_<DemoMain>("DemoMain")
    //  .constructor()
    //  .function("initialize", &DemoMain::initialize)
    //  .function("getTestBytes", &DemoMain::getTestBytes)
    //  ;

    //  class_<CarDemo>("CarDemo")
    //  .constructor<std::string,unsigned int>()
    //  .function("setXY", &CarDemo::setXY)
    //  .function("getTestBytes", &CarDemo::getTestBytes)
    //  .class_function("getStringFromInstance", &CarDemo::getStringFromInstance)
    //  ;
    /*
    //constant("STATIC_CONST_INTEGER_VALUE_1000", StaticConstIntStruct::STATIC_CONST_INTEGER_VALUE_1000);
    class_<TestClass>("TestClass")
    .constructor<int, std::string>()
    .function("incrementX", &TestClass::incrementX)
    .function("initialize", &TestClass::initialize)
    .property("x", &TestClass::getX, &TestClass::setX)
    .property("type", &TestClass::type)
    .class_property("ConstClassType", &TestClass::ConstClassType)//ok
    .class_property("ClassType", &TestClass::ClassType)//ok
    .class_function("getStringFromInstance", &TestClass::getStringFromInstance)
    ;
    //constant("ClassType", &TestClass::ClassType);

    //NodeObj
    class_<NodeObj>("NodeObj")
    .constructor()
    .function("showInfo", &NodeObj::showInfo)
    ;
    class_<AbsObj>("AbsObj")
    .constructor<std::string>()
    .function("showInfo", &AbsObj::showInfo)
    ;
    */
}
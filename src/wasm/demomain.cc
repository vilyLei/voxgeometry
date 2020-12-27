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

*/
#include <iostream>
#include <iomanip>
#include <string>
#include "../voxcgeom/cgeomPre.h"
#include "../voxcgeom/math/Vec3D.h"
#include "../voxcgeom/math/Matrix4.h"
#include "CarDemo.h"
//#include <emscripten/emscripten.h> // note we added the emscripten header
// quick_example.cpp
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

namespace tool
{
    float lerp(float a, float b, float t) {
        std::cout<<"em++ lerp running, use c++11 !\n";
        return ((1 - t) * a + t * b);// * 1.5f;
    }
}
// js中访问希望这样
/*
Module.tool.lerp(0.0,2.0,0.5);
*/
void showVersion() {
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

class DemoMain
{
    public:
        DemoMain()
        {
            std::cout<<"DemoMain construction()!\n";
        }
        ~DemoMain()
        {
            std::cout<<"DemoMain destruction().\n";
        }
        
        void initialize()
        {
            std::cout<<"DemoMain::initialize()!\n";
            voxcgeom::math::Vec3D v3_0(0.5,0.3,0.7);
            voxcgeom::math::Vec3D v3_1;
            v3_1.copyFrom(v3_0);
            v3_1.coutThis();
        }
    private:
    
};


class TestClass
{
    public:
        TestClass(int x, std::string &&info)
          : x(x)
          , m_info(info)
        {
            m_id = s_id++;
            std::cout<<"TestClass::constructor(),m_id: "<<m_id<<std::endl;
        }
        ~TestClass()
        {
            std::cout<<"TestClass::deconstructor().\n";
        }
        void incrementX() {
          ++x;
        }
        int getX() const { return x; }
        void setX(int x_) { x = x_; }
        static std::string getStringFromInstance(const TestClass& instance) {
          return instance.m_info;
        }
        const static int ConstClassType;
        static int ClassType;
        void initialize()
        {
            std::cout<<"TestClass::initialize()!\n";
        }
      int type = 10;
    private:
      int x;
      std::string m_info;
      static int s_id;
      int m_id;
};
int TestClass::s_id = 0;
const int TestClass::ConstClassType = 3001;
int TestClass::ClassType = 2308;

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
    std::cout<<"emval_test_sum v01."<<std::endl;
    unsigned length = v["length"].as<unsigned>();
    //duoble rv = 0;
    int rv = 0;
    for (unsigned i = 0; i < length; ++i) {
        //rv += v[i].as<double>();
        rv += v[i].as<int>();
    }
    return rv;
}
template<typename T, size_t sizeOfArray>
constexpr size_t getElementCount(T (&)[sizeOfArray])
{
    return sizeOfArray;
}

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
EMSCRIPTEN_BINDINGS(pmodule)
{

    function("tool$lerp", &tool::lerp);

    function("showVersion", &showVersion);
    function("getVersion", &getVersion);
    function("getTestBytes", &getTestBytes);
    function("getSumBytes", &getSumBytes);
    function("callWithMemoryView", &callWithMemoryView);
    function("emval_test_sum", &emval_test_sum);

    class_<DemoMain>("DemoMain")
    .constructor()
    .function("initialize", &DemoMain::initialize)
    ;
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

    class_<CarDemo>("CarDemo")
    .constructor<std::string>()
    .function("setXY", &CarDemo::setXY)
    .class_function("getStringFromInstance", &CarDemo::getStringFromInstance)
    ;
    //NodeObj
    class_<NodeObj>("NodeObj")
    .constructor()
    .function("showInfo", &NodeObj::showInfo)
    ;
    class_<AbsObj>("AbsObj")
    .constructor<std::string>()
    .function("showInfo", &AbsObj::showInfo)
    ;
    //EM_ASM(
    //    Module['tool'] = {a:1};
    //    Module['tool']['lerp'] = Module['lerp'];
    //);
}
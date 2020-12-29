
#include <iostream>
#include <string>
#include "CarDemo.h"
using namespace emscripten;

int CarDemo::s_id = 0;
AbsObj::AbsObj(std::string &&info)
{
std::cout<<"AbsObj::constructor().\n";
}
void AbsObj::showInfo()
{
std::cout<<"AbsObj::showInfo().\n";
}
AbsObj::~AbsObj()
{
std::cout<<"AbsObj::deconstructor().\n";
}

CarDemo::CarDemo(std::string info, unsigned int total)
  : m_info(info)
  , m_bytesBuffer(nullptr)
  , m_total(total)
{
    m_id = s_id++;
    m_total = total;
    std::cout<<"CarDemo::constructor(),m_id: "<<m_id<<std::endl;
    m_bytesBuffer = new VCG_Number[total]{10.2f,11,12.2f,13.2f,14.2f};
}
val CarDemo::getTestBytes() {
    return val(typed_memory_view(5, m_bytesBuffer));
}
/*
AbsObj::AbsObj(std::string &&info)
{
  std::cout<<"AbsObj::constructor().\n";
}
AbsObj::AbsObj()
{
  std::cout<<"AbsObj::deconstructor().\n";
}
void AbsObj::showInfo()
{
  std::cout<<"AbsObj::showInfo().\n";
}
//*/
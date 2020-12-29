#pragma once
#include <iostream>
#include <string>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "../voxcgeom/cgeomPre.h"

using namespace emscripten;

class AbsObj
{
  public:
    AbsObj(std::string &&info);
    void showInfo();
    ~AbsObj();
};
class NodeObj
{
  public:
    NodeObj()
    {
      std::cout<<"NodeObj::deconstructor().\n";
    }
    void showInfo()
    {
      std::cout<<"NodeObj::showInfo().\n";
    }
    ~NodeObj()
    {
      std::cout<<"NodeObj::deconstructor().\n";
    }
};
class CarDemo
{
    public:
        CarDemo(std::string info, unsigned int total);
        //    : m_info(info)
        //  {
        //      m_id = s_id++;
        //      std::cout<<"CarDemo::constructor(),m_id: "<<m_id<<std::endl;
        //  }
        ~CarDemo()
        {
            std::cout<<"CarDemo::deconstructor().\n";
        }
        void setXY(int x, int y)
        {
            m_x = x;
            m_y = y;
        }
        int getX() const { return m_x; }
        int getY() const { return m_y; }
        val getTestBytes();
        static std::string getStringFromInstance(const CarDemo& instance) {
          return instance.m_info;
        }
    private:
      VCG_Number *m_bytesBuffer;//new unsigned char[5]{0,1,2,3,4};
      int m_x;
      int m_y;
      std::string m_info;
      static int s_id;
      int m_id;
      unsigned int m_total;
};
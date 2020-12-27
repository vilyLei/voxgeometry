#pragma once
#include <iostream>
#include <string>
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
      std::cout<<"CarDemo::deconstructor().\n";
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
        CarDemo(std::string &&info)
          : m_info(info)
        {
            m_id = s_id++;
            std::cout<<"CarDemo::constructor(),m_id: "<<m_id<<std::endl;
        }
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
        
        static std::string getStringFromInstance(const CarDemo& instance) {
          return instance.m_info;
        }
    private:
      int m_x;
      int m_y;
      std::string m_info;
      static int s_id;
      int m_id;
};
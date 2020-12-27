
#include <iostream>
#include <string>
#include "CarDemo.h"

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
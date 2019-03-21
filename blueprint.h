#ifndef BLUEPRINT_H
#define BLUEPRINT_H
#include <cstdio>

class A
{
  protected:
    unsigned short m_R,m_G,m_B;
  public:
    virtual unsigned short f(unsigned short R) const = 0;
    void setR(unsigned short input){ m_R=input; };
    void setG(unsigned short input){ m_G=input; };
    void setB(unsigned short input){ m_B=input; };
    virtual ~A() {};
};
#endif /* BLUEPRINT_H */

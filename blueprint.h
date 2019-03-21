#ifndef BLUEPRINT_H
#define BLUEPRINT_H
#include <cstdio>
#include <math.h>
class A
{
  protected:
    const long PI = acos(-1);
    const long TWO_PI = PI*2.0;
    mutable unsigned short oR,oG,oB;
  public:
    virtual void f(unsigned short in[],int frameCount,int x,int y) const = 0;
    unsigned short R(){return oR;};
    unsigned short G(){return oG;};
    unsigned short B(){return oB;};
    virtual ~A() {};
};
#endif /* BLUEPRINT_H */

#ifndef BLUEPRINT_H
#define BLUEPRINT_H
#include <cstdio>
#include <math.h>
class A
{
  protected:
    const double PI = acos(-1);
    const double TWO_PI = PI*2.0;
  public:
    virtual void f(unsigned short in[],unsigned short out[]) const = 0;
    virtual ~A() {};
};
#endif /* BLUEPRINT_H */

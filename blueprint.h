#ifndef BLUEPRINT_H
#define BLUEPRINT_H
#include <cstdio>
#include <math.h>
#include <vector>

using namespace std;

class A
{
  protected:
    const long PI = acos(-1);
    const long TWO_PI = PI*2.0;
    const long max = 65535.0;
    mutable unsigned short oR,oG,oB;
    mutable int width=720, height=576;
  public:
    virtual void initFrame(int _width,int _height) const = 0;
    virtual void f(unsigned short in[],vector<unsigned short>& pixels,int frameCount,int x,int y) const = 0;
    unsigned short R(){return oR;};
    unsigned short G(){return oG;};
    unsigned short B(){return oB;};
    virtual ~A() {};
};
#endif /* BLUEPRINT_H */

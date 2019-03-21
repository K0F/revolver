#ifndef BLUEPRINT_H
#define BLUEPRINT_H
#include <cstdio>

class A
{
  protected:
  public:
    unsigned short R,G,B;     // or use a pointer to a larger input object
    virtual void f() const;
    void r(unsigned short _R) { R=_R; }
    void g(unsigned short _G) { G=_G; }
    void b(unsigned short _B) { B=_B; }
    unsigned short getR() { return R; }
    unsigned short getG() { return G; }
    unsigned short getB() { return B; }
    virtual ~A() {};
};
#endif /* BLUEPRINT_H */

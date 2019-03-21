#ifndef BLUEPRINT_H
#define BLUEPRINT_H
#include <cstdio>

class A
{
  protected:
    unsigned short R,G,B;
  public:
    virtual void *f(unsigned short _R, unsigned short _G, unsigned short _B) const = 0;
    void init();
    virtual ~A() {};
};
#endif /* BLUEPRINT_H */

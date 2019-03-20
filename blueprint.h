#ifndef BLUEPRINT_H
#define BLUEPRINT_H
#include <cstdio>

class A
{
  protected:
    double m_input;     // or use a pointer to a larger input object
  public:
    virtual int f(int R, int G, int B) const = 0;
    void init(double input) { m_input=input; }
    virtual ~A() {};
};
#endif /* BLUEPRINT_H */

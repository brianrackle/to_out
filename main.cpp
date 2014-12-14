#include <string>
#include "to_out.hpp"
#include "assert.h"

struct test
{
  void t0(int & i) { i = 5; }
  void t1(double d, float f, int & i) { i = 5; }
};

int main()
{
  using namespace t_o;

  test t;
  
  using f0 = decltype(&test::t0);
  using f1 = decltype(&test::t1);

  auto r0 = to_out(t, &test::t0);
  assert(r0 == 5);

  auto r1 = to_out(t, &test::t1, 1.0, 2.0);
  assert(r1 == 5);

  mft<f0>::class_type ct; //test ct;
  //mft<t0>::return_type rt; //null rt

  //mft<t0>::template arg<0> isn't required here because it doesnt depend on a template parameter
  int i;
  mft<f0>::arg<0>::type at0 = i; //int & ct = i; //reference to i
  rr<mft<f0>::arg<0>::type>::type drat0 = i; //int ct = i; //value of i

}

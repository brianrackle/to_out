#include <string>
#include "to_out.hpp"

struct test
{
  void t0(int & i) { i = 5; }
  void t1(std::string & s) { s = "test"; }
};

int main()
{
  test t;
  
  auto f = &test::t0;

  //int i;
  //(t.*f)(i);
  auto i = t_o(t, &test::t0, int);
  auto s = t_o(t, &test::t1, std::string);
}

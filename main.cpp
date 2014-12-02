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

  //auto i = t_ol(t, &test::t0, int);
  //auto s = t_o(t, &test::t1, std::string);

  member_function_traits<decltype(&test::t0)>::class_type ct;
}

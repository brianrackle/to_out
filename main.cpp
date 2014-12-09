#include <string>
#include "to_out.hpp"

struct test
{
  void t0(int & i) { i = 5; }
  void t1(std::string & s) { s = "test"; }
};

template<class T> using mft = member_function_traits<T>;
template<class T> using rr = std::remove_reference<T>;

int main()
{
  test t;
  
  auto f = &test::t0;

  //auto i = t_ol(t, &test::t0, int);
  auto s = t_o(t, &test::t1);

  using t0 = decltype(&test::t0);

  mft<t0>::class_type ct; //test ct
  //mft<t0>::return_type rt;//null rt
  int i;
  mft<t0>::arg_type at = i; //int & ct = i; //reference to i
  rr<mft<t0>::arg_type>::type drat = i; //int ct = i; //value of i
}

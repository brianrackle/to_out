#include <type_traits>

//TODO: add arguement expansion using parameter pack
template<class T> struct member_function_traits;
template<class T, class R, class A>
struct member_function_traits<R (T::*)(A)>
{
  using class_type = T;
  using return_type = R;
  using arg_type = A;
};

//TODO: use variable templates for multiple parameter single return
//TODO: allow multiple outputs to turn into tuple return type
template<class O, class F, class P>
auto to_out(O & obj, F func) -> typename std::remove_reference<P>::type
{
  typename std::remove_reference<P>::type out;
  (obj.*func)(out);
  return std::move(out);
};

template<class O, class F, class P>
P to_out(O && obj, F func)
{
  P out;
  (obj.*func)(out);
  return std::move(out);
};

//TODO: redefine t_o without a macro
#define t_o(O, F) to_out<decltype(O), decltype(F), member_function_traits<decltype(F)>::arg_type>(O, F)

//TODO: add arguement expansion using parameter pack
template<class T> struct member_function_traits;
template<class T, class R, class A>
struct member_function_traits<R (T::*)(A)>
{
  using class_type = T;
  using return_type = R;
  using arg_type = A;
};

//TODO: use function traits to automatically deduce P
//TODO: use variable templates for multiple parameter single return
//TODO: allow multiple outputs to turn into tuple return type
template<class O, class F, class P>
P to_out(O & obj, F func)
{
  P out;
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
#define t_o(O, F, P) to_out<decltype(O), decltype(F), P>(O, F)

//Failure: P is a type
//auto t_o = [](auto O, auto F, auto P) 
//{ return std::move(to_out<decltype(O), decltype(F), P>(O, F)); };

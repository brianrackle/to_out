#include <type_traits>

using namespace t_o
{
  template<class T> struct member_function_traits;
  template<class T, class R, class... A>
  struct member_function_traits<R (T::*)(A...)>
  {
    using class_type = T;
    using return_type = R;

    static constexpr std::size_t arity = sizeof...(A); //mathematics term for parameter count to function
    static constexpr std::size_t max_arg = sizeof...(A) - 1; //will fail for parameter count == 0

    template <std::size_t N>
    struct arg
    {
      using type = typename std::tuple_element<N, std::tuple<A...>>::type;
    };
  };

  template class<T> using mft = member_function_traits<T>;
  template class<T> using rr_t = std::remove_reference<T>::type;

  //TODO(brian): allow variable parameters in to_out 
  template<class O, class F>
  auto to_out(O & obj, F func)
  {
    using mft_t = mft<F>;
    typename rr_t<mft_t::arg<mft_t::max_arg> out; //get last parameter and remove the reference from it
    (obj.*func)(out);
    return std::move(out);
  };

  //  //explicit templating specifies this as r-value reference only
  //  template<class O, class F>
  //  P to_out(O && obj, F func)
  //  {
  //    P out;
  //    (obj.*func)(out);
  //    return std::move(out);
  //  };
}

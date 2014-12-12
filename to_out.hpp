#include <type_traits>

namespace t_o
{
  template<class T> struct member_function_traits;
  template<class T, class R, class... A>
  struct member_function_traits<R (T::*)(A...)>
  {
    using class_type = T;
    using return_type = R;

    //static constexpr std::size_t arity = sizeof...(A); //mathematics term for parameter count to function
    static constexpr std::size_t max_arg = sizeof...(A) - 1; //will fail for parameter count == 0

    template <std::size_t N>
    struct arg
    {
      using type = typename std::tuple_element<N, std::tuple<A...>>::type;
    };
  };

  template <class T> using mft = member_function_traits<T>;
  template <class T, std::size_t N> using mft_arg_t = typename mft<T>::template arg<N>::type; //ISO C++03 14.2/4 http://stackoverflow.com/questions/3786360/confusing-template-error
  template <class T> using rr = typename std::remove_reference<T>;

  template<class O, class F>
  auto to_out(O && obj, F func)
  {
    //get last parameter and remove the reference from it
    typename rr<mft_arg_t<F, 0>>::type out;
    //auto arg_count = typename mft<F>::max_arg;

    (obj.*func)(out);
    return std::move(out);
  };

  //Removed becuase template is no longer derived by parameters
  //  //explicit templating specifies this as r-value reference only
  //  template<class O, class F>
  //  P to_out(O && obj, F func)
  //  {
  //    P out;
  //    (obj.*func)(out);
  //    return std::move(out);
  //  };
}

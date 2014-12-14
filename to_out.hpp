#include <type_traits>

namespace t_o
{
  template<class T> struct mft;
  template<class T, class R, class... A>
  struct mft<R (T::*)(A...)>
  {
    using class_type = T;
    using return_type = R;

    static constexpr std::size_t arity = sizeof...(A); //mathematics term for parameter count to function

    template <std::size_t N>
    struct arg
    {
      using type = typename std::tuple_element<N, std::tuple<A...>>::type;
    };
  };

  //TODO(brian): can this be put into mft?
  //ISO C++03 14.2/4 http://stackoverflow.com/questions/3786360/confusing-template-error
  template <class T, std::size_t N> using mft_arg_t = 
    typename mft<T>::template arg<N>::type;

  template <class T> using rr = typename std::remove_reference<T>;

  template<class O, class F, class... A>
  auto to_out(O && obj, F func, A... args)
  {
    constexpr auto arity = mft<F>::arity;
    typename rr<mft_arg_t<F, arity - 1>>::type out_param;

    (obj.*func)(args..., out_param);
    return std::move(out_param);
  };

}

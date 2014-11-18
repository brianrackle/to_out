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

#define t_o(O, F, P) to_out<decltype(O), decltype(F), P>(O, F)

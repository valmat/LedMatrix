#ifndef _MOVE
#define _MOVE

namespace std
{
    // std::remove_reference
    template< class T > struct remove_reference      {typedef T type;};
    template< class T > struct remove_reference<T&>  {typedef T type;};
    template< class T > struct remove_reference<T&&> {typedef T type;};

    // std::move
    template<typename _Tp>
    constexpr typename remove_reference<_Tp>::type&&
    move(_Tp&& __t) noexcept
    { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }


    /// integral_constant
    template<typename _Tp, _Tp __v>
    struct integral_constant
    {
        static constexpr _Tp                  value = __v;
        typedef _Tp                           value_type;
        typedef integral_constant<_Tp, __v>   type;
        constexpr operator value_type() { return value; }
    };

    template<typename _Tp, _Tp __v>
    constexpr _Tp integral_constant<_Tp, __v>::value;

    /// The type used as a compile-time boolean with true value.
    typedef integral_constant<bool, true>     true_type;

    /// The type used as a compile-time boolean with false value.
    typedef integral_constant<bool, false>    false_type;

  

    // is_lvalue_reference
    template<typename> struct is_lvalue_reference : public false_type { };
    template<typename _Tp> struct is_lvalue_reference<_Tp&> : public true_type { };

    // std::forward
    template<typename _Tp>
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
    {
      static_assert(!std::is_lvalue_reference<_Tp>::value, "template argument"
            " substituting _Tp is an lvalue reference type");
      return static_cast<_Tp&&>(__t);
    }

}



#endif // _MOVE

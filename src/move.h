#ifndef _MOVE
#define _MOVE

namespace std
{
    // std::remove_reference
    template< class T > struct remove_reference      {typedef T type;};
    template< class T > struct remove_reference<T&>  {typedef T type;};
    template< class T > struct remove_reference<T&&> {typedef T type;};


    // std::move
    template <class T>
    typename remove_reference<T>::type&&
    move(T&& a)
    {
      return a;
    }

    // std::forward
    template<class T>
    T&& forward(typename std::remove_reference<T>::type& t) noexcept {
        return static_cast<T&&>(t);
    }
}



#endif // _MOVE

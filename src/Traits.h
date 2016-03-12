/*
 *
 * Traits to compile time template calculating
 *
 */

// SumTrait is a trait to compile time calculate total cascade size
template <int N0, int ...Ns>
struct SumTrait
{
    constexpr static int sum = SumTrait<N0>::sum + SumTrait<Ns...>::sum;
};

template <int N>
struct SumTrait<N>
{
    constexpr static int sum = N;
};


// SizeTrait is a trait to compile time calculate template integer argument
template <typename T>
struct SizeTrait;

template < template<uint8_t M> class T, uint8_t N>
struct SizeTrait< T<N> >
{
    constexpr static int size = N;
};
template <typename T>
struct SizeTrait
{
    constexpr static int size = SizeTrait< typename std::remove_reference<T>::type >::size;
};
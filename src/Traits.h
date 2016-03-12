/*
 *
 * Traits to compile time template calculating
 *
 *  @author   Valeriy V Dmitriev aka valmat <ufabiz@gmail.com>, http://valmat.ru/
 *  @licenses MIT https://opensource.org/licenses/MIT
 *  @repo     https://github.com/valmat/LedMatrix
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

template < template<int M> class T, int N>
struct SizeTrait< T<N> >
{
    constexpr static int size = N;
};
template <typename T>
struct SizeTrait
{
    constexpr static int size = SizeTrait< typename std::remove_reference<T>::type >::size;
};
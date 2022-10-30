#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H
#include <algorithm>
#include <array>
#include <cmath>

namespace engine
{
namespace math
{
constexpr double pi          = 3.14159265358979323846;
constexpr double degRadScale = 180 / pi;

inline double degToRad(double deg)
{
    return deg / degRadScale;
}

inline double radToDeg(double rad)
{
    return rad * degRadScale;
}

template<typename T, std::size_t N>
using Vector = std::array<T, N>;

template<typename T, std::size_t N, std::size_t M>
using Matrix = std::array<std::array<T, M>, N>;

template<typename T, std::size_t N>
T std_norm(const engine::math::Vector<T, N>& v);

template<typename T, std::size_t N>
T max_norm(const engine::math::Vector<T, N>& v);
} // namespace math
} // namespace engine

template<typename T, std::size_t N>
engine::math::Vector<T, N> operator+(const engine::math::Vector<T, N>& v, const engine::math::Vector<T, N>& w)
{
    engine::math::Vector<T, N> r;
    for (std::size_t i = 0; i < N; ++i)
        r[i] = v[i] + w[i];
    return r;
}

template<typename T, std::size_t N>
engine::math::Vector<T, N>& operator+=(engine::math::Vector<T, N>& v, const engine::math::Vector<T, N>& w)
{
    for (std::size_t i = 0; i < N; ++i)
        v[i] += w[i];
    return v;
}

template<typename T, std::size_t N>
engine::math::Vector<T, N>& operator-=(engine::math::Vector<T, N>& v, const engine::math::Vector<T, N>& w)
{
    for (std::size_t i = 0; i < N; ++i)
        v[i] -= w[i];
    return v;
}

template<typename T, std::size_t N>
engine::math::Vector<T, N> operator-(const engine::math::Vector<T, N>& v, const engine::math::Vector<T, N>& w)
{
    engine::math::Vector<T, N> r;
    for (std::size_t i = 0; i < N; ++i)
        r[i] = v[i] - w[i];
    return r;
}

template<typename T, std::size_t N>
typename engine::math::Vector<T, N>::value_type operator*(const engine::math::Vector<T, N>& v, const engine::math::Vector<T, N>& w)
{
    typename engine::math::Vector<T, N>::value_type r = 0;
    for (std::size_t i = 0; i < N; ++i)
        r += v[i] * w[i];
    return r;
}

template<typename T, std::size_t N>
engine::math::Vector<T, N> operator*(double l, engine::math::Vector<T, N> w)
{
    for (std::size_t i = 0; i < N; ++i)
        w[i] *= l;
    return w;
}

template<typename T, std::size_t N>
engine::math::Vector<T, N> operator*(engine::math::Vector<T, N> w, double l)
{
    for (std::size_t i = 0; i < N; ++i)
        w[i] *= l;
    return w;
}

template<typename T, std::size_t N>
engine::math::Vector<T, N> operator/(engine::math::Vector<T, N> w, double l)
{
    for (std::size_t i = 0; i < N; ++i)
        w[i] /= l;
    return w;
}

template<typename T, std::size_t N, std::size_t M>
engine::math::Vector<T, N> operator*(const engine::math::Matrix<T, N, M>& m, const engine::math::Vector<T, M> v)
{
    engine::math::Vector<T, N> r;
    for (std::size_t i = 0; i < N; ++i)
        r[i] = m[i] * v;
    return r;
}

template<typename T, std::size_t N>
T engine::math::std_norm(const engine::math::Vector<T, N>& v)
{
    return v * v;
}

template<typename T, std::size_t N>
T engine::math::max_norm(const engine::math::Vector<T, N>& v)
{
    return abs(*std::max_element(v.cbegin(), v.cend()));
}
#endif

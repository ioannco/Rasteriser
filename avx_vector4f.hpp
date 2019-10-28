#ifndef AVX_VECTOR4F_HPP
#define AVX_VECTOR4F_HPP

#include <algorithm>
#include <stdexcept>
#include <smmintrin.h>
#include <cmath>

class avx_vector4f
{
public:
                                avx_vector4f(float x, float y, float z, float w)                        ;
                                avx_vector4f(__m128 vector)                                             ;
                                avx_vector4f()                                                          ;
                                avx_vector4f(const avx_vector4f &  other)                               ;
                                avx_vector4f(      avx_vector4f && other)                               ;

                 avx_vector4f & operator =(const avx_vector4f &  other)                        noexcept ;
                 avx_vector4f & operator =(      avx_vector4f && other)                        noexcept ;

                 void           swap (avx_vector4f & other)                                    noexcept ;

                 void           x(const float & val)                                           noexcept ;
                 void           y(const float & val)                                           noexcept ;
                 void           z(const float & val)                                           noexcept ;
                 void           w(const float & val)                                           noexcept ;

                 float          x()                                                      const noexcept ;
                 float          y()                                                      const noexcept ;
                 float          z()                                                      const noexcept ;
                 float          w()                                                      const noexcept ;

                 float          length()                                                 const noexcept ;
                 avx_vector4f   norm()                                                   const          ;
                 avx_vector4f   perspective()                                            const          ;

    friend const avx_vector4f & operator +  (const avx_vector4f & v)                           noexcept ;
    friend const avx_vector4f   operator -  (const avx_vector4f & v)                           noexcept ;

    friend const avx_vector4f   operator +  (const avx_vector4f & v1, const avx_vector4f & v2) noexcept ;
    friend const avx_vector4f   operator -  (const avx_vector4f & v1, const avx_vector4f & v2) noexcept ;
    friend const avx_vector4f   operator *  (const avx_vector4f & v1, const float & num)       noexcept ;
    friend const avx_vector4f   operator *  (const float & num,       const avx_vector4f & v1) noexcept ;
    friend const avx_vector4f   operator /  (const avx_vector4f & v1, const float & num);

    friend const avx_vector4f & operator += (const avx_vector4f & v1, const avx_vector4f & v2) noexcept ;
    friend const avx_vector4f & operator -= (const avx_vector4f & v1, const avx_vector4f & v2) noexcept ;
    friend const avx_vector4f & operator *= (const avx_vector4f & v1, const float & num)       noexcept ;
    friend const avx_vector4f & operator /= (const avx_vector4f & v1, const float & num)       noexcept ;

                                operator __m128()                                        const noexcept ;
                 avx_vector4f & operator =(const __m128 &  vec)                                noexcept ;
                 avx_vector4f & operator =(      __m128 && vec)                                noexcept ;

                 float &        operator[] (size_t i)                                                   ;
           const float &        operator[] (size_t i)                                    const          ;

                 void           dump ()                                                  const noexcept ;

    private:
                 __m128         data                                                                    ;
};

avx_vector4f dot   (const avx_vector4f & v1, const avx_vector4f & v2) noexcept;
avx_vector4f cross (const avx_vector4f & v1, const avx_vector4f & v2) noexcept;

//=======================================================================================================

avx_vector4f::avx_vector4f()
    : data(_mm_set_ps (0.f, 0.f, 0.f, 0.f))
{

}

avx_vector4f::avx_vector4f(float x, float y, float z, float w)
    : data(_mm_set_ps (w, z, y, x))
{

}

avx_vector4f::avx_vector4f(__m128 vector)
    : data(vector)
{

}

avx_vector4f::avx_vector4f(const avx_vector4f & other)
{
    data = other.data;
}

avx_vector4f::avx_vector4f(avx_vector4f && other)
{
    other.swap(*this);
}

inline void avx_vector4f::x (const float & val) noexcept
{
    (*this)[0] = val;
}

inline void avx_vector4f::y (const float & val) noexcept
{
    (*this)[1] = val;
}

inline void avx_vector4f::z (const float & val) noexcept
{
    (*this)[2] = val;
}

inline void avx_vector4f::w (const float & val) noexcept
{
    (*this)[3] = val;
}

inline float avx_vector4f::x () const noexcept
{
    return (*this)[0];
}

inline float avx_vector4f::y () const noexcept
{
    return (*this)[1];
}

inline float avx_vector4f::z () const noexcept
{
    return (*this)[2];
}

inline float avx_vector4f::w () const noexcept
{
    return (*this)[3];
}

inline float avx_vector4f::length() const noexcept
{
    return sqrtf (dot (*this, *this).x ());
}

inline avx_vector4f avx_vector4f::norm() const
{
    return *this / length ();
}

inline avx_vector4f avx_vector4f::perspective() const
{
    return *this / w();
}

inline avx_vector4f & avx_vector4f::operator=(const avx_vector4f & other) noexcept
{
    avx_vector4f (other).swap (*this);
    return *this;
}

inline avx_vector4f & avx_vector4f::operator=(avx_vector4f &&other) noexcept
{
    other.swap (*this);
    return *this;
}

inline void avx_vector4f::swap(avx_vector4f &other) noexcept
{
    __m128 temp = other.data;
    other.data = data;
    data = temp;
}


inline const avx_vector4f & operator + (const avx_vector4f & v) noexcept
{
    return v;
}

inline const avx_vector4f   operator - (const avx_vector4f & v) noexcept
{
    return _mm_mul_ps(v, _mm_set_ps1(-1.f));
}

inline const avx_vector4f   operator + (const avx_vector4f & v1, const avx_vector4f & v2) noexcept
{
    return _mm_add_ps(v1, v2);
}

inline const avx_vector4f   operator - (const avx_vector4f & v1, const avx_vector4f & v2) noexcept
{
    return _mm_sub_ps(v1, v2);
}

inline const avx_vector4f   operator * (const avx_vector4f & v1, const float & num) noexcept
{
    return _mm_mul_ps(v1,_mm_set_ps1(num));
}

inline const avx_vector4f   operator * (const float & num, const avx_vector4f & v1) noexcept
{
    return _mm_mul_ps(v1,_mm_set_ps1(num));
}

inline const avx_vector4f   operator / (const avx_vector4f & v1, const float & num)
{
    return _mm_div_ps(v1,_mm_set_ps1(num));
}

inline avx_vector4f::operator __m128() const noexcept
{
    return data;
}

inline avx_vector4f & avx_vector4f::operator= (const __m128 & vec) noexcept
{
    avx_vector4f(vec).swap (*this);
    return *this;
}

inline avx_vector4f & avx_vector4f::operator= (__m128 && vec) noexcept
{
    data = vec;
    return *this;
}

inline float & avx_vector4f::operator[](size_t i)
{
    if (i > 3)
        throw std::runtime_error ("vector subscript out of range.");

    return reinterpret_cast<float*>(&data)[i];
}

inline const float & avx_vector4f::operator[](size_t i) const
{
    if (i > 3)
        throw std::runtime_error ("vector subscript out of range.");

    return reinterpret_cast<const float*>(&data)[i];
}

inline avx_vector4f dot (const avx_vector4f & v1, const avx_vector4f & v2) noexcept
{
    return _mm_dp_ps (v1, v2, 0xff);
}

inline avx_vector4f cross (const avx_vector4f & v1, const avx_vector4f & v2) noexcept
{
         __m128 lhs = _mm_mul_ps(_mm_shuffle_ps(v1, v1, _MM_SHUFFLE(1, 2, 0, 3)),
            _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(2, 0, 1, 3)));
        __m128 rhs = _mm_mul_ps(_mm_shuffle_ps(v1, v1, _MM_SHUFFLE(2, 0, 1, 3)),
            _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(1, 2, 0, 3)));

        return _mm_sub_ps (lhs, rhs);
}

inline void avx_vector4f::dump () const noexcept
{
    printf ("[%3.f %3.f %3.f %3.f  ]\n", static_cast<double>(x()), static_cast<double>(y()), static_cast<double>(z()), static_cast<double>(w()));
}

#endif // AVX_VECTOR4F_HPP

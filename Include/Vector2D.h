#pragma once
#include <ostream>
#include <array>

template<typename T>
struct Vec2;

template<typename T>
struct Vec2
{
    union
    {
        struct
        {
            T x; ///< X coordinate of the vector
            T y; ///< Y coordinate of the vector

        };
        struct
        {
            T u; ///< X coordinate of the vector
            T v; ///< Y coordinate of the vector

        };
        T coord[2];
    };

    const static Vec2 zero;
    const static Vec2 one;
    const static Vec2 up;
    const static Vec2 down;
    const static Vec2 left;
    const static Vec2 right;


    //Constructors
    constexpr Vec2() noexcept
        : x(0), y(0)
    {
    }

    explicit Vec2(T same) noexcept
        : x(same), y(same)
    {
    }

    constexpr Vec2(T X, T Y) noexcept : x(X), y(Y)
    {
    }

    template<typename U>
    explicit Vec2(const Vec2<U>& vector)  noexcept
        : x(static_cast<T>(vector.x)),
        y(static_cast<T>(vector.y))
    {
    }

    //Operators
    Vec2<T> operator+(const Vec2<T>& rhs) const
    {
        return Vec2<T>(x + rhs.x, y + rhs.y);
    }

    Vec2<T>& operator+=(const Vec2<T>& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    Vec2<T> operator-(const Vec2<T>& rhs) const
    {
        return Vec2<T>(x - rhs.x, y - rhs.y);
    }

    Vec2<T> operator -() const
    {
        return Vec2<T>(-x, -y);
    }

    Vec2<T>& operator-=(const Vec2<T>& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }

    Vec2<T> operator*(const Vec2<T>& rhs) const
    {
        return Vec2<T>(x * rhs.x, y * rhs.y);
    }



    Vec2<T>& operator*=(T rhs)
    {
        this->x *= rhs;
        this->y *= rhs;
        return *this;
    }

    Vec2<T> operator/(const Vec2<T>& rhs) const
    {
        return Vec2<T>(x / rhs.x, y / rhs.y);
    }

    Vec2<T> operator/(T rhs) const
    {
        return (*this) * (1.0f / rhs);
    }

    Vec2<T>& operator/=(T rhs)
    {
        this->x /= rhs;
        this->y /= rhs;
        return *this;
    }

    bool operator==(const Vec2<T>& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2<T>& other) const
    {
        return !(*this == other);
    }

    const T& operator[](size_t p_axis) const
    {

        return coord[p_axis];
    }

    T& operator[](size_t p_axis)
    {

        return coord[p_axis];
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2<T>& dt)
    {
        os << "Vec2(" << dt.x << "," << dt.y << ")";
        return os;
    }


    //Used to specialize in case of other kind of vector
    template<typename U>
    explicit operator U() const;

    //Formulas
    /// \brief Calculates the dot product from two vectors.
    static T Dot(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    /// \brief Calculates the square magnitude.
    [[nodiscard]] T SquareMagnitude() const
    {
        return Dot(*this, *this);
    }

    /// \brief Calculates the magnitude.
    [[nodiscard]] T Magnitude() const
    {
        return std::sqrt(SquareMagnitude());
    }

    /// \brief Calculates the normalized vector.
    [[nodiscard]] Vec2<T> Normalized() const
    {
        return (*this) / (*this).Magnitude();
    }

    /// \brief Interpolate between two vectors.
    /// \param t The interpolation amount.
    static Vec2<T> Lerp(const Vec2<T>& v1, const Vec2<T>& v2, T t)
    {
        return v1 + (v2 - v1) * t;
    }

    /// \brief Reflect the inVec using the normal given (doesn't need to be normalized).
    /// \param inVec The vector to reflect.
    /// \param normal The normal vector of the line to reflect off.
    static Vec2<T> Reflect(const Vec2<T>& inVec, const Vec2<T>& normal)
    {
        return inVec - normal * 2 * Dot(inVec, normal);
    }

    /// \brief Project v1 on v2 (doesn't need to be normalized).
    /// \param v1 The vector to project.
    /// \param v2 The vector to project on.
    static Vec2<T> Project(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        const auto dot = Dot(v1, v2);
        const auto mag = v2.SquareMagnitude();
        return { (dot / mag) * v2.x,
                (dot / mag) * v2.y };
    }

    //Other
    //Used to specialize in case of other kind of vector
    template<typename U>
    explicit Vec2(const U& v);
};

//Implementations
template<typename T, typename U>
Vec2<T> operator*(U lhs, const Vec2<T>& rhs)
{
    return Vec2<T>(rhs.x * lhs, rhs.y * lhs);
}
template<typename T, typename U>
Vec2<T> operator*(const Vec2<T>& lhs, U rhs)
{
    return Vec2<T>(lhs.x * rhs, lhs.y * rhs);
}

//Aliases
using Vec2f = Vec2<float>;
using Vec2df = Vec2<double>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned>;

template<typename T>
inline Vec2<T> const Vec2<T>::zero = Vec2<T>(0, 0);
template<typename T>
inline Vec2<T> const Vec2<T>::one = Vec2<T>(1, 1);
template<typename T>
inline Vec2<T> const Vec2<T>::up = Vec2<T>(0, 1);
template<typename T>
inline Vec2<T> const Vec2<T>::down = Vec2<T>(0, -1);
template<typename T>
inline Vec2<T> const Vec2<T>::left = Vec2<T>(-1, 0);
template<typename T>
inline Vec2<T> const Vec2<T>::right = Vec2<T>(1, 0);
#ifndef EVA_VECTOR
#define EVA_VECTOR

#include <math.h>
#include <iostream>
#include <utility>

template <typename T>
class vec3 {
public:
    vec3();
    vec3(T x, T y, T z);
    vec3(vec3<T>&);
    vec3(const vec3<T>&);
    vec3(vec3<T>&&) noexcept;

    vec3 operator+(vec3<T>);
    void operator+=(vec3<T>);
    vec3 operator-(vec3<T>);
    void operator-=(vec3<T>);
    vec3 operator*(T);
    void operator=(vec3<T>);
    bool operator==(vec3<T>);
    bool operator!=(vec3<T>);
    T dot(vec3<T>);
    vec3 cross(vec3<T>);
    T magnitude();
    void normalize();
    void debugPrint(); 

    T x, y, z;
};

template <typename T>
vec3<T>::vec3() {
    x = 0;
    y = 0;
    z = 0;
}

template <typename T>
vec3<T>::vec3(T nx, T ny, T nz) {
    x = nx;
    y = ny;
    z = nz;
}

template <typename T>
vec3<T>::vec3(vec3<T>& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
}

template <typename T>
vec3<T>::vec3(const vec3<T>& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
}

template <typename T>
vec3<T>::vec3(vec3<T>&& rhs) noexcept {
    x = rhs.x;
    rhs.x = 0;
    y = rhs.y;
    rhs.y = 0;
    z = rhs.z;
    rhs.z = 0;
}

template <typename T>
vec3<T> vec3<T>::operator+(vec3<T> rhs) {
    vec3<T> result;

    result.x = x + rhs.x;
    result.y = y + rhs.y;
    result.z = z + rhs.z;

    return result;
}

template <typename T>
void vec3<T>::operator+=(vec3<T> rhs) {
    x = x + rhs.x;
    y = y + rhs.y;
    z = z + rhs.z;
}

template <typename T>
vec3<T> vec3<T>::operator-(vec3<T> rhs) {
    vec3<T> result;

    result.x = x - rhs.x;
    result.y = y - rhs.y;
    result.z = z - rhs.z;

    return result;
}

template <typename T>
void vec3<T>::operator-=(vec3<T> rhs) {
    x = x - rhs.x;
    y = y - rhs.y;
    z = z - rhs.z;
}

template <typename T>
void vec3<T>::operator=(vec3<T> rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
}

template <typename T>
bool vec3<T>::operator==(vec3<T> rhs) {
    if (x != rhs.x) return false;
    if (y != rhs.y) return false;
    if (z != rhs.z) return false;

    return true;
}

template <typename T>
bool vec3<T>::operator!=(vec3<T> rhs) {
    return !(*this == rhs);
}

template <typename T>
vec3<T> vec3<T>::operator*(T scalar) {
    vec3<T> result;
    
    result.x = x * scalar;
    result.y = y * scalar;
    result.z = z * scalar;

    return result;
}

template <typename T>
T vec3<T>::dot(vec3<T> rhs) {
    T result = 0;

    result += x * rhs.x;
    result += y * rhs.y;
    result += z * rhs.z;

    return result;
}

template <typename T>
vec3<T> vec3<T>::cross(vec3<T> rhs) {
    vec3<T> result;

    result.x = (y * rhs.z) - (z * rhs.y);
    result.y = (z * rhs.x) - (x * rhs.z);
    result.z = (x * rhs.y) - (y * rhs.x);

    return result;
}

template <typename T>
T vec3<T>::magnitude() {
    T result;

    result = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    return result;
}

template <typename T>
void vec3<T>::normalize() {
    T mag = magnitude();

    x = x / mag;
    y = y / mag;
    z = z / mag;
}

template <typename T>
void vec3<T>::debugPrint() {
    std::cout << "(" << x << ", " << y << ", " << z << ")";
}

#endif
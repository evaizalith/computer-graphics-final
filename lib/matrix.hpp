#ifndef EVA_MATRIX
#define EVA_MATRIX

#include "vector.hpp"
#include <iostream>

// A 3x3 square matrix
template <typename T>
class mat3 {
public:
    mat3();
    mat3(mat3&);
    mat3(vec3<T>, vec3<T>, vec3<T>);
    //~mat3();

    vec3<T> getCol(int); // Get column by index
    void setCol(int, vec3<T>); // Set column by index

    vec3<T> operator*(vec3<T>); // Used to transform a vector
private:
    vec3<T>* columns;
};

template<typename T>
mat3<T>::mat3() {
    columns = new vec3<T>[3];
}

template <typename T>
mat3<T>::mat3(mat3& copy) {
    columns = new vec3<T>[3];

    columns[0] = vec3<T>(copy.columns[0]);
    columns[1] = vec3<T>(copy.columns[1]);
    columns[2] = vec3<T>(copy.columns[2]);
}

template<typename T>
mat3<T>::mat3(vec3<T> e0, vec3<T> e1, vec3<T> e2) {
    columns = new vec3<T>[3];
    columns[0] = e0;
    columns[1] = e1;
    columns[2] = e2;
}

/*
template <typename T>
mat3<T>::~mat3() {
    printf("Matrix destructor called\n");
    delete[] columns;
}*/

template <typename T>
vec3<T> mat3<T>::getCol(int i) {
    return columns[i]; 
}

template <typename T>
void mat3<T>::setCol(int i, vec3<T> vec) {
    columns[i] = vec;
}

template <typename T>
vec3<T> mat3<T>::operator*(vec3<T> vec) {
    vec3<T> result;

    result.x = (vec.x + columns[0].x) + (vec.y + columns[1].x) + (vec.z + columns[2].x);
    result.y = (vec.x + columns[0].y) + (vec.y + columns[1].y) + (vec.z + columns[2].y);
    result.z = (vec.x + columns[0].z) + (vec.y + columns[1].z) + (vec.z + columns[2].z);

    return result;
}

#endif
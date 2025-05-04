#ifndef LINA_HPP
#define LINA_HPP

#include <math.h>
#include <type_traits>
#include <stdint.h>

/*

###################
      Vectors
###################


###################
     Matrices
###################
A Mathematical matrix is essentially a grid of numbers and
elements are accessed by their rows and columns, for example
the first element would be at row 0, column 0.

There are 3 matrix structs included in this library, which are the following:
    mat4: a matrix that has 4 rows and 4 columns, all you will need for 3D camera math.
    mat3: a matrix that has 3 rows and 3 columns, you can use this for some 3D camera math 
            but most of it requires 4 dimensional matrices.
    mat2: a matrix that has 2 rows and 2 columns, usually only used for 2D Z axis rotations.

All the matrix structs have a member for each possible position
on the grid, which are all prefixed with an '_' and have two digits
following it, the first digit indicates the row and the second digit
indicates the column. For example, to access row 0, column 0 you'd use
the member '_00'.

There are also members prefix with '_m' that are just aliases for the
members that start at row/column 1 instead of 0. Both access the same
memory, they are here, because starting at 1 just makes more sense to
some people and a lot of mathematical papers on matrices start at row
/column 1 and it can be quite confusing at times to switch between the
two constantly.

================
  Constructors
================
The Default constructor for every matrix struct creates an Identity Matrix (see 'Identity Matrices')
The Non-Default constructor just lets you set every value yourself.
You can get a matrix with every position equal to zero with the 'zeroed' function.

! TODO: Finish writing this shit, and make sure to give a definition /  description of what the fuck an Identity matrix is. 

===============
  Operations
===============
There are operator overloads for addition, subtraction, and multiplication
for all the matrix structs. Matrix division isn't possible, hence why there
is no division operator overload.

>>> Addition/Subtraction <<<
Matrix addition/subtraction is pretty simple, you just add/subtract every value in 
matrix A with the corrosponding value in matrix B and put it in the corrosponding
position in matrix C. 



*/

#define PRINT_VEC2(__vec, __type) printf("<"#__type", "#__type">\n", __vec.x, __vec.y);
#define PRINT_VEC3(__vec, __type) printf("<"#__type", "#__type, #__type">\n", __vec.x, __vec.y, __vec.z);
#define PRINT_VEC4(__vec, __type) printf("<"#__type", "#__type, #__type, #__type">\n", __vec.x, __vec.y, vec.z, vec.w);


namespace lina {
    constexpr double PI = M_PI;
    constexpr double PI_2 = M_PI/2;
    constexpr double TAU = M_PI*2;

    inline float cot(float x) {
        return 1.f/tanf(x);
    }

    inline float dtor(float deg) {
        return deg * PI / 180.f;
    }
    inline float rtod(float rad) {
        return rad * 180.f /  PI;
    }

    /* 
        Vectors 
    */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    struct Vector2 {
        T x, y;
        
        Vector2(T x, T y) {
            this->x=x; this->y=y;
        }
        Vector2() {x=y=(T)0;}
 
        void nullify() {x=y=(T)0;}
 
        Vector2<T> operator-() {
            return Vector2<T>(-x, -y);
        }
 
        Vector2<T> operator+(Vector2<T> v) {
            return Vector2<T>(x+v.x, y+v.y);
        }
        Vector2<T> operator+(T v) {
            return Vector2<T>(x+v, y+v);
        }
        void operator+=(Vector2<T> v) {
            x+=v.x; y+=v.y; 
        }
        void operator+=(T v) {
            x+=v; y+=v;
        }
 
        Vector2<T> operator-(Vector2<T> v) {
            return Vector2<T>(x-v.x, y-v.y);
        }
        Vector2<T> operator-(T v) {
            return Vector2<T>(x-v, y-v);
        }
        void operator-=(Vector2<T> v) {
            x-=v.x; y-=v.y; 
        }
        void operator-=(T v) {
            x-=v; y-=v;
        }
 
        Vector2<T> operator*(Vector2<T> v) {
            return Vector2<T>(x*v.x, y*v.y);
        }
        Vector2<T> operator*(T v) {
            return Vector2<T>(x*v, y*v);
        }
        void operator*=(Vector2<T> v) {
            x*=v.x; y*=v.y; 
        }
        void operator*=(T v) {
            x*=v; y*=v;
        }
 
        Vector2<T> operator/(Vector2<T> v) {
            return Vector2<T>(x/v.x, y/v.y);
        }
        Vector2<T> operator/(T v) {
            return Vector2<T>(x/v, y/v);
        }
        void operator/=(Vector2<T> v) {
            x/=v.x; y/=v.y; 
        }
        void operator/=(T v) {
            x/=v; y/=v;
        }
 
        bool operator==(Vector2<T> o) const {
            return x==o.x && y==o.y;
        }
 
        void operator=(Vector2<T> v) {
            x=v.x; y=v.y;
        }
 
        float length() {
            return sqrt(x * x + y * y);
        }
 
        void normalize() {
            this->operator/=(length());
        }
 
        Vector2<T> normalized() {
            return this->operator/(length());
        }
 
        float dot(Vector2<T> other) {
            return x * other.x + y * other.y;
        }
 
        static float dot(Vector2<T> a, Vector2<T> b) {
            return a.x * b.y + a.y * b.y;
        }
 
        template <typename _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type>
        operator Vector2<_T>() const {
            return Vector2<_T>((_T)x, (_T)y);
        }

    #ifdef SDL_h_
        operator SDL_Point() const {
            return SDL_Point {.x=(int)x, .y=(int)y};
        }
 
        operator SDL_FPoint() const {
            return SDL_FPoint {.x=(float)x, .y=(float)y};
        }
    #endif/* VECTOR_HPP */
    };
 
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    struct Vector3 {
        T x, y, z;
        Vector3(T x, T y, T z) {
            this->x=x; this->y=y; this->z=z;
        }
        Vector3() {x=y=z=(T)0;}
 
        void nullify() {x=y=z=(T)0;}
 
        Vector3<T> operator-() {
            return Vector3<T>(-x, -y, -z);
        }
 
        Vector3<T> operator+(Vector3<T> v) {
            return Vector3<T>(x+v.x, y+v.y, z+v.z);
        }
        Vector3<T> operator+(T v) {
            return Vector3<T>(x+v, y+v, z+v);
        }
        void operator+=(Vector3<T> v) {
            x+=v.x; y+=v.y; z+=v.z; 
        }
        void operator+=(T v) {
            x+=v; y+=v; z+=v;
        }
 
        Vector3<T> operator-(Vector3<T> v) {
            return Vector3<T>(x-v.x, y-v.y, z-v.z);
        }
        Vector3<T> operator-(T v) {
            return Vector3<T>(x-v, y-v, z-v);
        }
        void operator-=(Vector3<T> v) {
            x-=v.x; y-=v.y; z-=v.z;
        }
        void operator-=(T v) {
            x-=v; y-=v; z-=v;
        }
 
        Vector3<T> operator*(Vector3<T> v) {
            return Vector3<T>(x*v.x, y*v.y, z*v.z);
        }
        Vector3<T> operator*(T v) {
            return Vector3<T>(x*v, y*v, z*v);
        }
        void operator*=(Vector3<T> v) {
            x*=v.x; y*=v.y; z*=v.z;
        }
        void operator*=(T v) {
            x*=v; y*=v; z*=v;
        }
 
        Vector3<T> operator/(Vector3<T> v) {
            return Vector3<T>(x/v.x, y/v.y, z/v.z);
        }
        Vector3<T> operator/(T v) {
            return Vector3<T>(x/v, y/v, z/v);
        }
        void operator/=(Vector3<T> v) {
            x/=v.x; y/=v.y; z/=v.z; 
        }
        void operator/=(T v) {
            x/=v; y/=v; z/=v;
        }
 
        bool operator==(Vector3<T> o) const {
            return this->x==o.x && this->y==o.y && this->z==o.z;
        }
 
        void operator=(Vector3<T> v) {
            x=v.x; y=v.y; z=v.z;
        }
 
        float length() {
            return sqrt(x * x + y * y + z * z);
        }
 
        void normalize() {
            this->operator/=(length());
        }
 
        Vector3<T> normalized() {
            return this->operator/(length());
        }
 
        Vector3<T> cross(Vector3<T> other) {
            return Vector3<T>(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
        }
        
        //template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
        static Vector3<T> cross(Vector3<T> a, Vector3<T> b) {
            return Vector3<T>(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
        }
 
        float dot(Vector3<T> other) {
            return x * other.x + y * other.y + z * other.z;
        }
 
        //template <typename _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value, T>::type>
        static float dot(Vector3<T> a, Vector3<T> b) {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }
 
        template <typename _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type>
        operator Vector3<_T>() const {
            return Vector3<_T>((_T)x, (_T)y, (_T)z);
        }

    #ifdef SDL_h_
        operator SDL_Point() const {
            return SDL_Point {.x=(int)x, .y=(int)y};
        }
 
        operator SDL_FPoint() const {
            return SDL_FPoint {.x=(float)x, .y=(float)y};
        }
    #endif /* SDL_h_ */
    };
 
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    struct Vector4 {
        T x, y, z, w;
        Vector4(T x, T y, T z, T w = (T)1) {
            this->x=x; this->y=y; this->z=z; this->w=w;
        }
        Vector4(Vector3<T> v, T w = (T)1) {
            x=v.x; y=v.y; z=v.z; this->w=w;
        }
        Vector4() {x=y=z=(T)0;w=(T)1;}
 
        void nullify() {x=y=z=w=(T)0;}
 
        Vector4<T> operator-() {
            return Vector4<T>(-x, -y, -z, -w);
        }
 
        Vector4<T> operator+(Vector3<T> v) {
            return Vector4<T>(x+v.x, y+v.y, z+v.z, w+v.w);
        }
        Vector4<T> operator+(T v) {
            return Vector4<T>(x+v, y+v, z+v, w+v);
        }
        void operator+=(Vector4<T> v) {
            x+=v.x; y+=v.y; z+=v.z; 
        }
        void operator+=(T v) {
            x+=v; y+=v; z+=v;
        }
 
        Vector4<T> operator-(Vector4<T> v) {
            return Vector4<T>(x-v.x, y-v.y, z-v.z, w-z.w);
        }
        Vector4<T> operator-(T v) {
            return Vector4<T>(x-v, y-v, z-v, w-v);
        }
        void operator-=(Vector4<T> v) {
            x-=v.x; y-=v.y; z-=v.z; w-=v.w;
        }
        void operator-=(T v) {
            x-=v; y-=v; z-=v;
        }
 
        Vector4<T> operator*(Vector4<T> v) {
            return Vector4<T>(x*v.x, y*v.y, z*v.z, w*v.w);
        }
        Vector4<T> operator*(T v) {
            return Vector4<T>(x*v, y*v, z*v, w*v);
        }
        void operator*=(Vector4<T> v) {
            x*=v.x; y*=v.y; z*=v.z; w*=v.z;
        }
        void operator*=(T v) {
            x*=v; y*=v; z*=v; w*=v;
        }
 
        Vector4<T> operator/(Vector4<T> v) {
            return Vector4<T>(x/v.x, y/v.y, z/v.z, w/v.w);
        }
        Vector4<T> operator/(T v) {
            return Vector4<T>(x/v, y/v, z/v, w/v);
        }
        void operator/=(Vector4<T> v) {
            x/=v.x; y/=v.y; z/=v.z; w/=v.w; 
        }
        void operator/=(T v) {
            x/=v; y/=v; z/=v;
        }
 
        bool operator==(Vector4<T> o) const {
            return this->x==o.x && this->y==o.y && this->z==o.z && this->w==o.w;
        }
 
        void operator=(Vector4<T> v) {
            x=v.x; y=v.y; z=v.z; w=v.w;
        }
 
        float length() {
            return sqrt(x * x + y * y + z * z + w * w);
        }
 
        void normalize() {
            this->operator/=(length());
        }
 
        Vector4<T> normalized() {
            return this->operator/(length());
        }
 
        float dot(Vector4<T> other) {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }
 
        //template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
        static float dot(Vector4<T> a, Vector4<T> b) {
            return a.x * b.y + a.y * b.y + a.z * b.z + a.w * b.w;
        }
 
        template <typename _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type>
        operator Vector4<_T>() const {
            return Vector4<_T>((_T)x, (_T)y, (_T)z, (_T)w);
        }
 
        //operator Vector3<T>() const {
        //    return Vector3<T>(x, y, z);
        //}
 
    #ifdef SDL_h_
        operator SDL_Point() const {
            return SDL_Point {.x=(int)x, .y=(int)y};
        }
 
        operator SDL_FPoint() const {
            return SDL_FPoint {.x=(float)x, .y=(float)y};
        }
    #endif /* SDL_h_ */
    };
 
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    struct Rect {
        T x, y, w, h;
        Rect(T x, T y, T w, T h) {
            this->x=x;
            this->y=y;
            this->w=w;
            this->h=h;
        }
        Rect() {x=y=w=h=(T)0;}
 
        bool operator==(Rect<T> o) const {
            return x==o.x && y==o.y && w==o.w && h==o.h;
        }
 
        void operator=(Rect<T> v) {
            x=v.x; y=v.y; w=v.w; h=v.h;
        }
 
        template <typename _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type>
        operator Rect<_T>() const {
            return Rect<_T>((_T)x, (_T)y, (_T)w, (_T)h);
        }
 
    #ifdef SDL_h_
        operator SDL_Rect() const {
            return SDL_Rect {.x=(int)x, .y=(int)y, .w=(int)w, .h=(int)h};
        }
        
        operator SDL_FRect() const {
            return SDL_FRect {.x=(float)x, .y=(float)y, .w=(float)w, .h=(float)h};
        }
    #endif/* VECTOR_HPP */
    };

    // Just Shorter hand versions of Vector class.
    // Also because I just didn't want to rewrite all of this shit.
    typedef Vector4<float> vec4;
    typedef Vector3<float> vec3;
    typedef Vector2<float> vec2;

    typedef Vector4<int> ivec4;
    typedef Vector3<int> ivec3;
    typedef Vector2<int> ivec2;

    typedef Vector4<unsigned> uvec4;
    typedef Vector3<unsigned> uvec3;
    typedef Vector2<unsigned> uvec2;

    /* 
        Matrices
    */
    struct mat4 {
        union {float _00, _m11;}; union {float _01, _m12;}; union {float _02, _m13;}; union {float _03, _m14;};
        union {float _10, _m21;}; union {float _11, _m22;}; union {float _12, _m23;}; union {float _13, _m24;};
        union {float _20, _m31;}; union {float _21, _m32;}; union {float _22, _m33;}; union {float _23, _m34;};
        union {float _30, _m41;}; union {float _31, _m42;}; union {float _32, _m43;}; union {float _33, _m44;};
        
        inline mat4(
            float _1_00, float _2_01, float _3_02, float _4_03,
            float _5_10, float _6_11, float _7_12, float _8_13,
            float _9_20, float _10_21, float _11_22, float _12_23,
            float _13_30, float _14_31, float _15_32, float _16_33
        ) {
            _00=_1_00;  _01=_2_01;  _02=_3_02;  _03=_4_03;
            _10=_5_10;  _11=_6_11;  _12=_7_12;  _13=_8_13;
            _20=_9_20;  _21=_10_21; _22=_11_22; _23=_12_23;
            _30=_13_30; _31=_14_31; _32=_15_32; _33=_16_33;
        }

        // Creates an identitiy matrix.
        inline mat4() {
            _00=_11=_22=_33=1.0f;
            _01=_02=_03=_10=_12=
                _13=_20=_21=_23=_30=
                _31=_32=0;
        }

        // returns an identity matrix
        inline static mat4 identity() {
            // This function is pointless, but some people might like the explicity of using "mat4::identity()"
            // instead of "mat4()" and some people might not realize that the constructor creates an Identity matrix.
            // Even though theres a comment.
            return mat4();
        }

        // returns a matrix with every value initialized to 0.
        inline static mat4 zeroed() {
            return mat4(
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f
            );
        }

        // Operations
        
        // returns a translation matrix 
        inline static mat4 translation(vec3 T) noexcept {
            return mat4(
                1.f, 0.f, 0.f, T.x,
                0.f, 1.f, 0.f, T.y,
                0.f, 0.f, 1.f, T.z,
                0.f, 0.f, 0.f, 1.f
            );
        }

        // translates this matrix by T.
        inline void translate(vec3 T) noexcept {
            *this *= translation(T);
        }

        // returns a scale matrix.
        inline static mat4 scalation(vec4 S) noexcept {
            return mat4(
                S.x, 0.f, 0.f, 0.f,
                0.f, S.y, 0.f, 0.f,
                0.f, 0.f, S.z, 0.f,
                0.f, 0.f, 0.f, S.w
            );
        }

        // scales this matrix by S.
        inline void scale(vec4 S) noexcept {
            *this *= scalation(S);
        }

        // returns a rotation matrix for the X axis that is rotated by `degrees`.
        inline static mat4 rotationX(float degrees) noexcept {
            return mat4(
                1.f, 0.f, 0.f, 0.f, 
                0.f, cosf(degrees), -sinf(degrees), 0.f,
                0.f, sinf(degrees), cosf(degrees), 0.f,
                0.f, 0.f, 0.f, 1.f
            );
        }

        // rotates this matrix on the X axis by `degrees`.
        inline void rotateX(float degrees) noexcept {
            *this *= rotationX(degrees);
        }
        
        inline static mat4 rotationY(float degrees) noexcept {
            return mat4(
                cosf(degrees), 0.f, sinf(degrees), 0.f,
                0.f, 1.f, 0.f, 0.f,
                -sinf(degrees), 0.f, cosf(degrees), 0.f,
                0.f, 0.f, 0.f, 1.f
            );
        }
        
        inline void rotateY(float degrees) noexcept {
            *this *= rotationY(degrees);
        }
        
        inline static mat4 rotationZ(float degrees) noexcept {
            return mat4(
                cosf(degrees), -sinf(degrees), 0.f, 0.f,
                sinf(degrees), cosf(degrees), 0.f, 0.f, 
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f
            );
        }
        
        inline void rotateZ(float degrees) noexcept {
            *this *= rotationZ(degrees);
        }
        
        inline static mat4 rotation(vec3 degrees) noexcept {
            return rotationX(degrees.x) * rotationY(degrees.y) * rotationZ(degrees.z);
        }
        
        inline void rotate(vec3 degrees) noexcept {
            *this *= rotation(degrees);
        }

        inline mat4 transposed() const noexcept {
            return mat4(
                _00, _10, _20, _30,
                _01, _11, _21, _31,
                _02, _12, _22, _32, 
                _03, _13, _23, _33
            );
        }
        inline void transpose() noexcept {
            *this = transposed();
        }

        // Conditions
        inline bool isIdentity() const noexcept {
            return _00 == 1.f && _01 == 0.f && _02 == 0.f && _03 == 0.f &&
                   _10 == 0.f && _11 == 1.f && _12 == 0.f && _13 == 0.f &&
                   _20 == 0.f && _21 == 0.f && _22 == 1.f && _23 == 0.f &&
                   _30 == 0.f && _31 == 0.f && _32 == 0.f && _33 == 1.f ;
        }

        inline bool isZeroed() {
            // I'm aware this function is both pointless and can be done simpler, 
            // I don't care.
            return _00 == 0.f && _01 == 0.f && _02 == 0.f && _03 == 0.f &&
                   _10 == 0.f && _11 == 0.f && _12 == 0.f && _13 == 0.f &&
                   _20 == 0.f && _21 == 0.f && _22 == 0.f && _23 == 0.f &&
                   _30 == 0.f && _31 == 0.f && _32 == 0.f && _33 == 0.f ;
        }

        inline bool isTranslation() const noexcept {
            return _00 == 1.f && _01 == 0 && _02 == 0 &&
                   _00 == 1.f && _01 == 0 && _02 == 0 &&
                   _00 == 1.f && _01 == 0 && _02 == 0 &&
                   _00 == 1.f && _01 == 0 && _02 == 0 &&
                   _03 == 1 ;
        }

        // Operators
        inline bool operator==(mat4 o) const noexcept {
            return _00 == o._00 && _01 == o._01 && _02 == o._02 && _03 == o._03 &&
                   _10 == o._10 && _11 == o._11 && _12 == o._12 && _13 == o._13 &&
                   _20 == o._20 && _21 == o._21 && _22 == o._22 && _23 == o._23 &&
                   _30 == o._30 && _31 == o._31 && _32 == o._32 && _33 == o._33;
        }

        inline mat4 operator+(mat4 m) const noexcept {
            return mat4(
                _00 + m._00, _01 + m._01, _02 + m._02, _03 + m._03, 
                _10 + m._10, _11 + m._11, _12 + m._12, _13 + m._13, 
                _20 + m._20, _21 + m._21, _22 + m._22, _23 + m._23, 
                _30 + m._30, _31 + m._31, _32 + m._32, _33 + m._33
            );
        }
        
        inline void operator+=(mat4 m) noexcept {
            _00 += m._00; _01 += m._01; _02 += m._02; _03 += m._03; 
            _10 += m._10; _11 += m._11; _12 += m._12; _13 += m._13; 
            _20 += m._20; _21 += m._21; _22 += m._22; _23 += m._23; 
            _30 += m._30; _31 += m._31; _32 += m._32; _33 += m._33;
        }
        
        inline mat4 operator+(vec4 v) const noexcept {
            return mat4(
                _00 + v.x, _01, _02, _03,
                _10 + v.y, _11, _12, _13,
                _20 + v.z, _21, _22, _23,
                _30 + v.w, _31, _32, _33
            );
        }
        
        inline void operator+=(vec4 v) noexcept {
            _00 += v.x;
            _10 += v.y;
            _20 += v.z;
            _30 += v.w;
        }

        inline mat4 operator-(mat4 m) const noexcept {
            return mat4(
                _00 - m._00, _01 - m._01, _02 - m._02, _03 - m._03, 
                _10 - m._10, _11 - m._11, _12 - m._12, _13 - m._13, 
                _20 - m._20, _21 - m._21, _22 - m._22, _23 - m._23, 
                _30 - m._30, _31 - m._31, _32 - m._32, _33 - m._33
            );
        }
        
        inline void operator-=(mat4 m) noexcept {
            _00 -= m._00; _01 -= m._01; _02 -= m._02; _03 -= m._03; 
            _10 -= m._10; _11 -= m._11; _12 -= m._12; _13 -= m._13; 
            _20 -= m._20; _21 -= m._21; _22 -= m._22; _23 -= m._23; 
            _30 -= m._30; _31 -= m._31; _32 -= m._32; _33 -= m._33;
        }
        
        inline mat4 operator-(vec4 v) const noexcept {
            return mat4(
                _00 - v.x, _01, _02, _03,
                _10 - v.y, _11, _12, _13,
                _20 - v.z, _21, _22, _23,
                _30 - v.w, _31, _32, _33
            );
        }
        
        inline void operator-=(vec4 v) noexcept {
            _00 -= v.x;
            _10 -= v.y;
            _20 -= v.z;
            _30 -= v.w;
        }

        inline mat4 operator*(mat4 m) const noexcept {
            return mat4(
                _00 * m._00 + _01 * m._10 + _02 * m._20 + _03 * m._30, _00 * m._01 + _01 * m._11 + _02 * m._21 + _03 * m._31, _00 * m._02 + _01 * m._12 + _02 * m._22 + _03 * m._32, _00 * m._03 + _01 * m._13 + _02 * m._23 + _03 * m._33,
                _10 * m._00 + _11 * m._10 + _12 * m._20 + _13 * m._30, _10 * m._01 + _11 * m._11 + _12 * m._21 + _13 * m._31, _10 * m._02 + _11 * m._12 + _12 * m._22 + _13 * m._32, _10 * m._03 + _11 * m._13 + _12 * m._23 + _13 * m._33,
                _20 * m._00 + _21 * m._10 + _22 * m._20 + _23 * m._30, _20 * m._01 + _21 * m._11 + _22 * m._21 + _23 * m._31, _20 * m._02 + _21 * m._12 + _22 * m._22 + _23 * m._32, _20 * m._03 + _21 * m._13 + _22 * m._23 + _23 * m._33,
                _30 * m._00 + _31 * m._10 + _32 * m._20 + _33 * m._30, _30 * m._01 + _31 * m._11 + _32 * m._21 + _33 * m._31, _30 * m._02 + _31 * m._12 + _32 * m._22 + _33 * m._32, _30 * m._03 + _31 * m._13 + _32 * m._23 + _33 * m._33
            );
        }
        
        inline void operator*=(mat4 m) noexcept {
            _00 = _00 * m._00 + _01 * m._10 + _02 * m._20 + _03 * m._30;
            _01 = _00 * m._01 + _01 * m._11 + _02 * m._21 + _03 * m._31;
            _02 = _00 * m._02 + _01 * m._12 + _02 * m._22 + _03 * m._32;
            _03 = _00 * m._03 + _01 * m._13 + _02 * m._23 + _03 * m._33;
                
            _10 = _10 * m._00 + _11 * m._10 + _12 * m._20 + _13 * m._30;
            _11 = _10 * m._01 + _11 * m._11 + _12 * m._21 + _13 * m._31;
            _12 = _10 * m._02 + _11 * m._12 + _12 * m._22 + _13 * m._32;
            _13 = _10 * m._03 + _11 * m._13 + _12 * m._23 + _13 * m._33;
                
            _20 = _20 * m._00 + _21 * m._10 + _22 * m._20 + _23 * m._30;
            _21 = _20 * m._01 + _21 * m._11 + _22 * m._21 + _23 * m._31;
            _22 = _20 * m._02 + _21 * m._12 + _22 * m._22 + _23 * m._32;
            _23 = _20 * m._03 + _21 * m._13 + _22 * m._23 + _23 * m._33;
                
            _30 = _30 * m._00 + _31 * m._10 + _32 * m._20 + _33 * m._30; 
            _31 = _30 * m._01 + _31 * m._11 + _32 * m._21 + _33 * m._31; 
            _32 = _30 * m._02 + _31 * m._12 + _32 * m._22 + _33 * m._32; 
            _33 = _30 * m._03 + _31 * m._13 + _32 * m._23 + _33 * m._33;    
        }
        
        inline vec4 operator*(vec4 v) const noexcept {
            return vec4(
                v.x * _00 + v.x * _10 + v.x * _20 + v.x * _30,
                v.y * _01 + v.y * _11 + v.y * _21 + v.y * _31,
                v.z * _02 + v.z * _12 + v.z * _22 + v.z * _32,
                v.w * _03 + v.w * _13 + v.w * _23 + v.w * _33
            );
        }
    };
    // TODO: Add the functions that mat4 has to mat3 and mat2
    struct mat3 {
        union {float _00, _m11;}; union {float _01, _m12;}; union {float _02, _m13;};
        union {float _10, _m21;}; union {float _11, _m22;}; union {float _12, _m23;};
        union {float _20, _m31;}; union {float _21, _m32;}; union {float _22, _m33;};         

        inline mat3(
            float _1_00, float _2_01, float _3_02,
            float _4_10, float _5_11, float _6_12,
            float _7_20, float _8_21, float _9_22
        ) {
            // I don't know why I decided to name the arguments like this.
            _00 = _1_00; _01 = _2_01; _02 = _3_02;
            _10 = _4_10; _11 = _5_11; _12 = _6_12;
            _00 = _7_20; _01 = _8_21; _02 = _9_22;
        }
        // Creates an identitiy matrix.
        inline mat3() {
            _00 = _11 = _22 = 1.f;
            _01 = _02 = _10 = _12 = _20 = _21 = 0.f;
        }

        // returns a 3x3 identity matrix.
        inline static mat3 identity() {
            return mat3();
        }

        // returns a 3x3 matrix with every value initialized to 0.
        inline static mat3 zeroed() {
            return mat3(
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f
            );
        }

        // Operations

        // returns a 3x3 translation matrix with the given translation.
        inline static mat3 translation(vec2 T) noexcept {
            return mat3(
                1.f, 0.f, T.x,
                0.f, 1.f, T.y,
                0.f, 0.f, 1.f
            );
        }
        // translates the matrix by T.
        inline void translate(vec2 T) noexcept {
            *this *= translation(T);
        }

        // returns a 3x3 scale matrix with the given scale vector.
        // (I don't know what the scale equivelent to "translation" or "rotation" is)
        inline static mat3 scalation(vec3 S) noexcept {
            return mat3(
                S.x, 0.f, 0.f,
                0.f, S.y, 0.f,
                0.f, 0.f, S.z  
            );
        }

        // scales the matrix by S.
        inline void scale(vec3 S) noexcept {
            *this *= scalation(S);
        }

        // returns a 3x3 rotation matrix for the X axis.
        inline static mat3 rotationX(float degrees) noexcept {
            return mat3(
                1.f, 0.f, 0.f, 
                0.f, cosf(degrees), -sinf(degrees),
                0.f, sinf(degrees), cosf(degrees)
            );
        }

        // rotates the matrix on the X axis by `degrees`.
        inline void rotateX(float degrees) noexcept {
            *this *= rotationX(degrees);
        }
        
        // returns a 3x3 rotation matrix for the Y axis.
        inline static mat3 rotationY(float degrees) noexcept {
            return mat3(
                cosf(degrees), 0.f, sinf(degrees),
                0.f, 1.f, 0.f,
                -sinf(degrees), 0.f, cosf(degrees)
            );
        }
        
        // rotates the matrix on the Y axis by `degrees`.
        inline void rotateY(float degrees) noexcept {
            *this *= rotationY(degrees);
        }
        
        // returns a 3x3 rotation matrix for the Z axis.
        inline static mat3 rotationZ(float degrees) noexcept {
            return mat3(
                cosf(degrees), -sinf(degrees), 0.f,
                sinf(degrees), cosf(degrees), 0.f,
                0.f, 0.f, 1.f
            );
        }
        
        // rotates the matrix on the Z axis by `degrees`.
        inline void rotateZ(float degrees) noexcept {
            *this *= rotationZ(degrees);
        }
        
        // returns a 3x3 rotation matrix for all axis, the X,Y,Z components corrospond with the axis it will rotate.
        inline static mat3 rotation(vec3 degrees) noexcept {
            return rotationX(degrees.x) * rotationY(degrees.y) * rotationZ(degrees.z);
        }
        
        inline void rotate(vec3 degrees) noexcept {
            *this *= rotation(degrees);
        }

        inline mat3 transposed() const noexcept {
            return mat3(
                _00, _10, _20,
                _01, _11, _21,
                _02, _12, _22
            );
        }

        inline void transpose() noexcept {
            *this = transposed();
        }

        // Conditions
        inline bool isIdentity() const noexcept {
            return _00 == 1.f && _01 == 0.f && _02 == 0.f &&
                   _10 == 0.f && _11 == 1.f && _12 == 0.f &&
                   _20 == 0.f && _21 == 0.f && _22 == 1.f ;
        }

        inline bool isTranslation() const noexcept {
            return _00 == 1.f && _01 == 0.f &&
                   _10 == 0.f && _11 == 1.f &&
                   _20 == 0.f && _21 == 0.f && 
                   _22 == 1.f ;
        }

        // Operators
        inline bool operator==(mat3 o) const noexcept {
            return _00 == o._00 && _01 == o._01 && _02 == o._02 &&
                   _10 == o._10 && _11 == o._11 && _12 == o._12 &&
                   _20 == o._20 && _21 == o._21 && _22 == o._22 ;
        }

        inline mat3 operator+(mat3 m) const noexcept {
            return mat3(
                _00 + m._00, _01 + m._01, _02 + m._02,
                _10 + m._10, _11 + m._11, _12 + m._12,
                _20 + m._20, _21 + m._21, _22 + m._22
            );
        }

        inline void operator+=(mat3 m) noexcept {
            _00 += m._00; _01 += m._01; _02 += m._02;
            _10 += m._10; _11 += m._11; _12 += m._12;
            _20 += m._20; _21 += m._21; _22 += m._22;
        }

        inline mat3 operator+(vec3 v) const noexcept {
            return mat3(
                v.x + _00, _01, _02,
                v.y + _10, _11, _12,
                v.z + _20, _21, _22
            );
        }

        inline void operator+=(vec3 v) noexcept {
            _00 +=v.x;
            _10 +=v.y;
            _20 +=v.z;
        }

        inline mat3 operator-(mat3 m) const noexcept {
            return mat3(
                _00 - m._00, _01 - m._01, _02 - m._02,
                _10 - m._10, _11 - m._11, _12 - m._12,
                _20 - m._20, _21 - m._21, _22 - m._22
            );
        }

        inline void operator-=(mat3 m) noexcept {
            _00 -= m._00; _01 -= m._01; _02 -= m._02;
            _10 -= m._10; _11 -= m._11; _12 -= m._12;
            _20 -= m._20; _21 -= m._21; _22 -= m._22;
        }

        inline mat3 operator-(vec3 v) const noexcept {
            return mat3(
                v.x - _00, _01, _02,
                v.y - _10, _11, _12,
                v.z - _20, _21, _22
            );
        }

        inline void operator-=(vec3 v) noexcept {
            _00 -=v.x;
            _10 -=v.y;
            _20 -=v.z;
        }

        inline mat3 operator*(mat3 m) const noexcept {
            return mat3(
                _00 * m._00 + _01 * m._10 + _02 * m._20, _00 * m._01 + _01 * m._11 + _02 * m._21, _00 * m._02 + _01 * m._12 + _02 * m._22,
                _10 * m._00 + _11 * m._10 + _12 * m._20, _10 * m._01 + _11 * m._11 + _12 * m._21, _10 * m._02 + _11 * m._12 + _12 * m._22,
                _20 * m._00 + _21 * m._10 + _22 * m._20, _20 * m._01 + _21 * m._11 + _22 * m._21, _20 * m._02 + _21 * m._12 + _22 * m._22
            );
        }

        inline void operator*=(mat3 m) noexcept {
            _00 = _00 * m._00 + _01 * m._10 + _02 * m._20;
            _01 = _00 * m._01 + _01 * m._11 + _02 * m._21;
            _02 = _00 * m._02 + _01 * m._12 + _02 * m._22;
                
            _10 = _10 * m._00 + _11 * m._10 + _12 * m._20;
            _11 = _10 * m._01 + _11 * m._11 + _12 * m._21;
            _12 = _10 * m._02 + _11 * m._12 + _12 * m._22;
                
            _20 = _20 * m._00 + _21 * m._10 + _22 * m._20;
            _21 = _20 * m._01 + _21 * m._11 + _22 * m._21;
            _22 = _20 * m._02 + _21 * m._12 + _22 * m._22;
        }

        inline vec3 operator*(vec3 v) const noexcept {
            return vec3(
                v.x * _00 + v.x * _10 + v.x * _20,
                v.y * _01 + v.y * _11 + v.y * _21,
                v.z * _02 + v.z * _12 + v.z * _22
            );
        }
    };

    struct mat2 {
        union {float _00, _m11;}; union {float _01, _m12;};
        union {float _10, _m21;}; union {float _11, _m22;};

        inline mat2(
            float p00, float p01,
            float p10, float p11
        ) {
            _00 = p00; _01 = p01;
            _10 = p10; _11 = p11;
        }

        // Creates an Identity matrix.
        inline mat2() {
            _00 = 1.f; _01 = 0.f;
            _10 = 0.f; _11 = 1.f;
        }

    };

    inline mat4 CreateRMCameraViewMatrix(vec3 position, vec3 right, vec3 up, vec3 forward) noexcept {
        return lina::mat4({
            right.x,    right.y,    right.z,    -right.dot(position),
            up.x,       up.y,       up.z,       -up.dot(position),
            -forward.x, -forward.y, -forward.z, forward.dot(position),
            0,          0,          0,          1
        });
    }

    inline mat4 CreateCMCameraViewMatrix(vec3 position, vec3 right, vec3 up, vec3 forward) noexcept {
        return lina::mat4({
            right.x, up.x, -forward.x, 0,
            right.y, up.y, -forward.y, 0,
            right.z, up.z, -forward.z, 0,
            -right.dot(position), -up.dot(position), forward.dot(position), 1
        });
    }

    inline mat4 CreateRMCameraPerspectiveMatrix(ivec2 screen_size, float fov, float CloseRenderDistance, float RenderDistance, lina::vec3 cam_offset = {0, 0, 1}) noexcept {
        float cotan_rads_2 = cot(0.5 * dtor(fov));
        
        return lina::mat4 ({
            cotan_rads_2 * screen_size.y/screen_size.x, 0, 0, cam_offset.x,
            0, cotan_rads_2, 0, cam_offset.y,
            0, 0, RenderDistance / (CloseRenderDistance - RenderDistance), -cam_offset.z,
            0, 0, -(RenderDistance * CloseRenderDistance) / (RenderDistance - CloseRenderDistance), 0
        });
    }

    inline mat4 CreateCMCameraPerspectiveMatrix(ivec2 screen_size, float fov, float CloseRenderDistance, float RenderDistance, lina::vec3 cam_offset = {0, 0, 1}) noexcept{
        float cotan_rads_2 = cot(0.5 * dtor(fov));
        
        return lina::mat4 ({
            cotan_rads_2 * screen_size.y/screen_size.x, 0, 0, 0,
            0, cotan_rads_2, 0, 0,
            0, 0, RenderDistance / (CloseRenderDistance - RenderDistance), -(RenderDistance * CloseRenderDistance) / (RenderDistance - CloseRenderDistance),
            cam_offset.x, cam_offset.y, -cam_offset.z, 0
        });
    }

    inline mat4 CreateRMModelMatrix(vec3 position, vec3 rotation, vec4 scale = {1,1,1,1}) noexcept {
        return mat4::translation(position) * mat4::rotationX(rotation.x) * mat4::rotationY(rotation.y) * mat4::rotationZ(rotation.z) * mat4::scalation(scale);
    }
    
    inline mat4 CreateCMModelMatrix(vec3 position, vec3 rotation, vec4 scale = {1,1,1,1}) noexcept {
        return (mat4::translation(position) * mat4::rotationX(rotation.x) * mat4::rotationY(rotation.y) * mat4::rotationZ(rotation.z) * mat4::scalation(scale)).transposed();
    }

    inline vec3 CalculateCameraForwardVector(float pitch, float yaw) {
        return vec3(
            cosf(pitch) * cosf(yaw),
            sinf(pitch),
            cosf(pitch) * sinf(yaw)
        ).normalized();
    }

    inline vec3 CalculateCameraRightVector(vec3 vecForward, vec3 vecGlobalUp = /* Y axis */{0, 1, 0}) {
        return vec3::cross(vecForward, vecGlobalUp).normalized();
    }

    inline vec3 CalculateCameraUpVector(vec3 vecForward, vec3 vecRight) {
        return vec3::cross(vecRight, vecForward).normalized();
    }

}
 
#endif/* LINA_HPP */ 
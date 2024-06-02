// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

struct quat
{
    float r;
    float i;
    float j;
    float k;
};

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
    float rad = glm::radians(degrees);
    float theta = rad / 2.;

    float mag = axis.length();

    vec3 aHat = glm::normalize(axis);

    quat q{ std::cos(theta),
        aHat.x * std::sin(theta),
        aHat.y * std::sin(theta),
        aHat.z * std::sin(theta) };

    // You will change this return call
    return mat3(1 - 2 * (q.j * q.j + q.k * q.k), 2 * (q.i * q.j - q.k * q.r), 2 * (q.i * q.k + q.j * q.r),
        2 * (q.i * q.j + q.k * q.r), 1 - 2 * (q.i * q.i + q.k * q.k), 2 * (q.j * q.k - q.i * q.r),
        2 * (q.i * q.k - q.j * q.r), 2 * (q.j * q.k + q.i * q.r), 1 - 2 * (q.i * q.i + q.j * q.j)
    );
}

inline vec3 Front(const vec3& eye, const vec3& origin = vec3()) {
    return (1.f / (origin - eye).length()) * (origin - eye);
}

inline vec3 Right(const vec3& up, const vec3& eye) {
    vec3 w(Front(eye));
    return glm::cross(up, vec3(w)) * (1.f / glm::cross(up, vec3(w)).length());
}

inline vec3 Up(const vec3& up, const vec3& eye, const vec3& origin = vec3()) {
    return glm::cross(Front(eye, origin), Right(up, eye));
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    eye = rotate(degrees, Up(up, eye)) * eye;
    up = rotate(degrees, Up(up, eye)) * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.  
    eye = rotate(degrees, Right(up, eye)) * eye;
    up = rotate(degrees, Right(up, eye)) * up;
}

mat4 Transform::lookAt(const vec3& eye, const vec3& center, const vec3& up)
{
    vec3 z(glm::normalize(eye - center));
    vec3 y(glm::normalize(up));
    vec3 x(glm::cross(y, z));
    y = glm::cross(z, x);

    // You will change this return call
    return glm::transpose(mat4(vec4(x, -glm::dot(x, eye)),
        vec4(y, -glm::dot(y, eye)),
        vec4(z, -glm::dot(z, eye)),
        vec4(0, 0, 0, 1)));
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    float d = 1. / tanf(glm::radians(fovy) / 2.);
    float A = -zFar / (zFar - zNear);
    float B = (-zFar * zNear) / (zFar - zNear);

    return mat4(d / aspect, 0, 0, 0,
        0, d / aspect, 0, 0,
        0, 0, A, -1,
        0, 0, B, 0);
}

mat4 Transform::scale(const float& sx, const float& sy, const float& sz)
{
    return mat4(sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1);
}

mat4 Transform::translate(const float& tx, const float& ty, const float& tz)
{
    return mat4(1.f, 0.f, 0.f, tx,
        0.f, 1.f, 0.f, ty,
        0.f, 0.f, 1.f, tz,
        0.f, 0.f, 0.f, 1.f);
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3& up, const vec3& zvec)
{
    vec3 x = glm::cross(up, zvec);
    vec3 y = glm::cross(zvec, x);
    vec3 ret = glm::normalize(y);
    return ret;
}

mat4 Transform::cameraToWorld(const vec3& eye, const vec3& center, const vec3& up)
{
    return glm::inverse(lookAt(eye, center, up));
}


Transform::Transform()
{

}

Transform::~Transform()
{

}

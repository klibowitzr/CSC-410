/*
   A class for fooling around with a camera
   David Schulz 2011
*/
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
// #include "desTypes.h"
// #include "desMatrix4.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

class nCamera {
public:
    nCamera(void);
    void roll(float angle);
    void pitch(float angle);
    void yaw(float angle);
    void slide(float du, float dv, float dn);
    vec3 getEye();
    void set(vec3 Eye, vec3 look, vec3 up);

    void set( float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ );

    void setShape(float viewAngle, float aspect, float Near, float Far);
    void setAspect(float asp);
    void getShape(float& viewAngle, float& aspect, float& Near, float& Far);
    void setDefaultCamera();
private:
    void rotAxes(vec3& a, vec3& b, float angle);
    vec3 eye;
    vec3 u, v, n;
    float aspect, nearDist, farDist, viewAngle;
    void setModelViewMatrix();
};
#endif

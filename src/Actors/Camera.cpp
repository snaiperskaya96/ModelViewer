//
// Created by Jury Verrigni on 3/27/17.
//

#include <Tools/OpenGl/OpenGl.h>
#include "Camera.h"

Camera::Camera() {
}

void Camera::Update() {
    Actor::Update();
}

void Camera::Init() {
    Actor::Init();
    OpenGl &Gl = OpenGl::GetInstance();
    AspectRatio = (float) Gl.GetWIndowWidth() / Gl.GetWindowHeight();
    float Range = (float) (tan (FieldOfView * 0.5f) * NearDistance);
    float Sx = (2.0f * NearDistance) / (Range * AspectRatio + Range * AspectRatio);
    float Sy = NearDistance / Range;
    float Sz = -(FarDistance + NearDistance) / (FarDistance - NearDistance);
    float Pz = -(2.0f * FarDistance * NearDistance) / (FarDistance - NearDistance);
    float ProjectionMatrix[] = {
            Sx, 0.0f, 0.0f, 0.0f,
            0.0f, Sy, 0.0f, 0.0f,
            0.0f, 0.0f, Sz, -1.0f,
            0.0f, 0.0f, Pz, 0.0f,
    };
    /* get location numbers of matrices in shader programme
    GLint view_mat_location = glGetUniformLocation (shader_programme, "view");
    GLint proj_mat_location = glGetUniformLocation (shader_programme, "proj");
    /* use program (make current in state machine) and set default matrix values
    glUseProgram (shader_programme);
    glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
    glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat);*/

}

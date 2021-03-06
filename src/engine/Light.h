/*
Copyright (c) 2016, Payet Thibault
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Monwarez Inc nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL PAYET THIBAULT BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// GLEW for all platform
#include <GL/glew.h>
#include <array>
#include <vector>

namespace S3DE
{
struct DirectionalLight
{
    glm::vec3 Color;
    GLfloat AmbientIntensity{0};
    glm::vec3 Direction;
    GLfloat DiffuseIntensity{0};
};
struct BaseLight
{
    glm::vec3 Color;
    GLfloat AmbientIntensity{0};
    GLfloat DiffuseIntensity{0};
};
struct PointLight : public BaseLight
{
    glm::vec3 Position;
    struct
    {
        GLfloat Constant{0};
        GLfloat Linear{0};
        GLfloat Exp{0};
    } Attenuation;
};
struct SpotLight : public PointLight
{
    glm::vec3 Direction;
    float Cutoff{0};
};

class Light : public Shader
{
public:
    static const unsigned int MAX_POINT_LIGHTS = 6;
    static const unsigned int MAX_SPOT_LIGHTS  = 2;

    Light() = default;
    Light( std::string const &vertexSource, std::string const &fragmentSource,
           std::string const &geometrySource );
    Light( Light const & );

    ~Light();
    virtual void SetEyeWorldPos( const glm::vec3 &eyeWorldPos );
    virtual void SetMatSpecularIntensity( GLfloat intensity );
    virtual void SetMatSpecularPower( GLfloat power );
    virtual void SetLights( std::vector<PointLight> const &lights );
    virtual void SetLights( std::vector<SpotLight> const &lights );
    virtual void SetLights( DirectionalLight const &light );
    virtual void Init();

protected:
    glm::vec3 m_eyeWorldPos;
    GLfloat m_specularIntensity{0};
    GLfloat m_specularPower{0};
    // Location
    GLuint m_dirLightColorLocation{0};
    GLuint m_dirLightAmbientIntensityLocation{0};
    GLuint m_dirLightDirectionLocation{0};
    GLuint m_dirLightDiffuseIntensityLocation{0};
    GLuint m_eyeWorldPosLocation{0};
    GLuint m_matSpecularIntensityLocation{0};
    GLuint m_matSpecularPowerLocation{0};
    struct PointLightLocation
    {
        PointLightLocation() = default;

        GLuint Color{0};
        GLuint AmbientIntensity{0};
        GLuint DiffuseIntensity{0};
        GLuint Position;
        struct
        {
            GLuint Constant{0};
            GLuint Linear{0};
            GLuint Exp{0};
        } Atten;
    };
    std::array<PointLightLocation, MAX_POINT_LIGHTS> m_pointLightsLocation;
    struct SpotLightLocation : public PointLightLocation
    {
        SpotLightLocation() = default;
        GLuint Direction{0};
        GLuint Cutoff{0};
    };
    std::array<SpotLightLocation, MAX_SPOT_LIGHTS> m_spotLightsLocation;

    GLuint m_numPointLightsLocation{0};
    GLuint m_numSpotLightsLocation{0};
};
} // end of S3DE namespace

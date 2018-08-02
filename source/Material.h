#ifndef SMATERIAL_H
#define SMATERIAL_H

#include "gl/gl.h"

class Material
{
    public:
        //! Default constructor
        Material() {}
        //! Destructor
        virtual ~Material() {}
        //! Get ambient lighting
        const float* getAmbient() { return ambient; }
        //! Set ambient lighting
        void setAmbient(float r, float g, float b, float a)
        {
            ambient[0] = r;
            ambient[1] = g;
            ambient[2] = b;
            ambient[3] = a;
        }
        //! Get specular lighting
        const float* getSpecular() { return specular; }
        //! Set specular lighting
        void setSpecular(float r, float g, float b, float a)
        {
            specular[0] = r;
            specular[1] = g;
            specular[2] = b;
            specular[3] = a;
        }
        //! Get diffuse lighting
        const float* getDiffuse() { return diffuse; }
        //! Set diffuse lighting
        void setDiffuse(float r, float g, float b, float a)
        {
            diffuse[0] = r;
            diffuse[1] = g;
            diffuse[2] = b;
            diffuse[3] = a;
        }
        //! Get emission lighting
        const float* getEmission() { return emission; }
        //! Set emission lighting
        void setEmission(float r, float g, float b, float a)
        {
            emission[0] = r;
            emission[1] = g;
            emission[2] = b;
            emission[3] = a;
        }
        //! Get shininess
        float getShininess() { return shininess; }
        //! Set shininess
        void setShininess(float shininess) { this->shininess = shininess; }
        //! Get wireframe flag
        bool getWireframeFlag() { return wireframeFlag; }
        //! Set wireframe flag
        void setWireframeFlag(bool wireframeFlag) { this->wireframeFlag = wireframeFlag; }
        //! Get normal flag
        bool getNormalsFlag() { return normalsFlag; }
        //! Set normal flag
        void setNormalsFlag(bool normalsFlag) { this->normalsFlag = normalsFlag; }
        //! Get environmentMapFlag
        bool getEnvironmentMapFlag() { return environmentMapFlag; }
        //! Set environmentMapFlag
        void setEnvironmentMapFlag(bool environmentMapFlag) { this->environmentMapFlag = environmentMapFlag; }
        //! Set texture
        void setTexture( GLuint texture ) { this->texture = texture; }
        //! Get texture
        GLuint getTexture() { return texture; }

    private:
        //! Array for ambient light
        float ambient[4];
        //! Array for specular light
        float specular[4];
        //! Array for diffuse light
        float diffuse[4];
        //! Array for emissive light
        float emission[4];
        //! Shininess coefficent
        float shininess;
        //! flag for wireframe mode
        bool wireframeFlag;
        //! flag for normals
        bool normalsFlag;
        //! flag for environment map
        bool environmentMapFlag;
        //! texture
        GLuint texture;
};

#endif // SMATERIAL_H

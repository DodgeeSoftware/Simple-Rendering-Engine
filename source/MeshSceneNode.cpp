#include "MeshSceneNode.h"

void MeshSceneNode::update()
{

}

void MeshSceneNode::draw()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.getAmbient());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.getSpecular());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.getDiffuse());
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material.getEmission());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.getShininess());


    if(material.getEnvironmentMapFlag() == true)
    {
        glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
    }

    Matrix4 translationMatrix;
    translationMatrix.setTranslation(position);
    Matrix4 rotationMatrix;
    rotationMatrix.setRotationDegrees(rotation);
    Matrix4 scaleMatrix;
    scaleMatrix.setScale(scale);

    Matrix4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;


    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,material.getTexture());

    for(std::vector<SMeshBuffer>::iterator iter = mesh.meshBuffers.begin(); iter != mesh.meshBuffers.end(); iter++)
    {
        if(material.getWireframeFlag() == false)
        {
            glBegin(GL_TRIANGLES);
                for(unsigned int i = 0; i < (*iter).indices.size(); i++)
                {
                    Vertex vertex;
                    vertex.position = (*iter).vertices.at(i).position;
                    vertex.normal = (*iter).vertices.at(i).normal;
                    vertex.textureCoordinate = (*iter).vertices.at(i).textureCoordinate;
                    vertex.position = transformationMatrix * vertex.position;
                    vertex.normal = rotationMatrix * vertex.normal;

                    // set the vertex texture coorindates
                    glTexCoord2d(vertex.textureCoordinate.x, vertex.textureCoordinate.y);
                    // set the vertex normal
                    glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
                    // set the vertex position
                    glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
                }
            glEnd();
        }
        else
        {
            glBegin(GL_LINES);
                for(unsigned int i = 0; i < (*iter).indices.size()-1; i++)
                {
                    Vertex vertex1;
                    vertex1.position = (*iter).vertices.at(i).position;
                    vertex1.normal = (*iter).vertices.at(i).normal;
                    vertex1.textureCoordinate = (*iter).vertices.at(i).textureCoordinate;

                    Vertex vertex2;
                    vertex2.position = (*iter).vertices.at(i+1).position;
                    vertex2.normal = (*iter).vertices.at(i+1).normal;
                    vertex2.textureCoordinate = (*iter).vertices.at(i+1).textureCoordinate;

                    vertex1.position = transformationMatrix * vertex1.position;
                    vertex1.normal = rotationMatrix * vertex1.normal;

                    vertex2.position = transformationMatrix * vertex2.position;
                    vertex2.normal = rotationMatrix * vertex2.normal;

                    // set the vertex texture coorindates
                    glTexCoord2d(vertex1.textureCoordinate.x, vertex1.textureCoordinate.y);
                    // set the vertex normal
                    glNormal3f(vertex1.normal.x, vertex1.normal.y, vertex1.normal.z);
                    // set the vertex position
                    glVertex3f(vertex1.position.x, vertex1.position.y, vertex1.position.z);

                    // set the vertex texture coorindates
                    glTexCoord2d(vertex2.textureCoordinate.x, vertex2.textureCoordinate.y);
                    // set the vertex normal
                    glNormal3f(vertex2.normal.x, vertex2.normal.y, vertex2.normal.z);
                    // set the vertex position
                    glVertex3f(vertex2.position.x, vertex2.position.y, vertex2.position.z);
                }
                if ((*iter).indices.size() >1)
                {
                    Vertex vertex;
                    vertex.position = (*iter).vertices.at(0).position;
                    vertex.normal = (*iter).vertices.at(0).normal;
                    vertex.textureCoordinate = (*iter).vertices.at(0).textureCoordinate;

                    // set the vertex texture coorindates
                    glTexCoord2d(vertex.textureCoordinate.x, vertex.textureCoordinate.y);
                    // set the vertex normal
                    glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
                    // set the vertex position
                    glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
                }
            glEnd();
        }
        if(material.getNormalsFlag() == true)
        {
            glBegin(GL_LINES);
            for(unsigned int i = 0; i < (*iter).indices.size(); i++)
            {
                Vertex vertex;
                vertex.position = (*iter).vertices.at(i).position;
                vertex.normal = (*iter).vertices.at(i).normal;
                vertex.textureCoordinate = (*iter).vertices.at(i).textureCoordinate;
                vertex.position = transformationMatrix * vertex.position;
                vertex.normal = rotationMatrix * vertex.normal;

                // set the vertex normal
                glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
                // set the vertex position
                glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);

                // set the vertex normal
                glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
                // set the vertex position
                glVertex3f(vertex.position.x+vertex.normal.x, vertex.position.y+vertex.normal.y, vertex.position.z+vertex.normal.z);
            }
            glEnd();
        }
    }
    if(material.getEnvironmentMapFlag() == true)
    {
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    }

    glBindTexture(GL_TEXTURE_2D,0);
    glPopMatrix();
}


#include "MeshFactory.h"

Vector3d MeshFactory::findNormal(Vector3d vector1, Vector3d vector2, Vector3d vector3)
{
    Vector3d a = (vector3 - vector2);
    Vector3d b = (vector1 - vector2);
    Vector3d normal = a.crossProduct(b);
    normal.normalise();
    return Vector3d(normal.x, normal.y, normal.z);
}

SMesh MeshFactory::createNull()
{
    // create and return empty mesh
    return SMesh();
}

SMesh MeshFactory::createSphere(Vector3d position, Vector3d rotation, Vector3d size)
{
        // create an empty mesh
        SMesh mesh;
        // setup the translation matrix
        Matrix4 t;
        // setup translation
        t.setTranslation(position);
        // setup the rotation matrix
        Matrix4 r;
        // setup translation
        r.setRotationDegrees(rotation);
        // setup the size matrix
        Matrix4 s;
        // setup translation
        s.setScale(size);
        // create transformation matrix
        Matrix4 transformation = t * r * s;

        for(float phi = 0.0f, deltaPhi = (M_PI) / 8.0f; phi <= (M_PI)-deltaPhi; phi += deltaPhi)
        {
            for(float theta = 0.0f, deltaTheta = (2 * M_PI) / 16.0f; theta <= (2 * M_PI); theta += deltaTheta)
            {
                Vertex v1, v2, v3;

                // Generate triangle 1
                v1.position.x = cos(theta) * sin(phi);
                v1.position.y = -cos(phi);
                v1.position.z = sin(theta) * sin(phi);
                v1.textureCoordinate = Vector2d(theta/(2*M_PI), (phi)/(M_PI));

                v2.position.x = cos(theta+deltaTheta) * sin(phi);
                v2.position.y = -cos(phi);
                v2.position.z = sin(theta+deltaTheta) * sin(phi);
                v2.textureCoordinate = Vector2d((theta+deltaTheta)/(2*M_PI), phi/(M_PI));

                v3.position.x = cos(theta+deltaTheta) * sin(phi+deltaPhi);
                v3.position.y = -cos(phi+deltaPhi);
                v3.position.z = sin(theta+deltaTheta) * sin(phi+deltaPhi);
                v3.textureCoordinate = Vector2d((theta+deltaTheta)/(2*M_PI), (phi+deltaPhi)/(M_PI));

                v1.position = transformation * v1.position;
                v2.position = transformation * v2.position;
                v3.position = transformation * v3.position;

                v1.normal.x = cos(theta) * sin(phi);
                v1.normal.y = -cos(phi);
                v1.normal.z = sin(theta) * sin(phi);

                v2.normal.x = cos(theta) * sin(phi);
                v2.normal.y = -cos(phi);
                v2.normal.z = sin(theta) * sin(phi);

                v3.normal.x = cos(theta) * sin(phi);
                v3.normal.y = -cos(phi);
                v3.normal.z = sin(theta) * sin(phi);

                v1.normal = r* v1.normal;
                v2.normal = r* v2.normal;
                v3.normal = r* v3.normal;

                SMeshBuffer meshBuffer1;
                meshBuffer1.vertices.push_back(v1);
                meshBuffer1.vertices.push_back(v2);
                meshBuffer1.vertices.push_back(v3);
                meshBuffer1.indices.push_back(1);
                meshBuffer1.indices.push_back(2);
                meshBuffer1.indices.push_back(3);
                mesh.meshBuffers.push_back(meshBuffer1);

                // Generate triangle 2
                v1.position.x = cos(theta+deltaTheta) * sin(phi+deltaPhi);
                v1.position.y = -cos(phi+deltaPhi);
                v1.position.z = sin(theta+deltaTheta) * sin(phi+deltaPhi);
                v1.textureCoordinate = Vector2d((theta+deltaTheta)/(2*M_PI), (phi+deltaPhi)/(M_PI));

                v2.position.x = cos(theta) * sin(phi+deltaPhi);
                v2.position.y = -cos(phi+deltaPhi);
                v2.position.z = sin(theta) * sin(phi+deltaPhi);
                v2.textureCoordinate = Vector2d((theta)/(2*M_PI), (phi+deltaPhi)/(M_PI));

                v3.position.x = cos(theta) * sin(phi);
                v3.position.y = -cos(phi);
                v3.position.z = sin(theta) * sin(phi);
                v3.textureCoordinate = Vector2d(theta/(2*M_PI), phi/(M_PI));

                v1.position = transformation * v1.position;
                v2.position = transformation * v2.position;
                v3.position = transformation * v3.position;


                v1.normal.x = cos(theta) * sin(phi);
                v1.normal.y = -cos(phi);
                v1.normal.z = sin(theta) * sin(phi);
                //if (phi < M_PI && v1.normal.magnitude() == 0) v1.normal = Vector3d();

                v2.normal.x = cos(theta) * sin(phi);
                v2.normal.y = -cos(phi);
                v2.normal.z = sin(theta) * sin(phi);

                v3.normal.x = cos(theta) * sin(phi);
                v3.normal.y = -cos(phi);
                v3.normal.z = sin(theta) * sin(phi);

                v1.normal = r* v1.normal;
                v2.normal = r* v2.normal;
                v3.normal = r* v3.normal;

                SMeshBuffer meshBuffer2;
                meshBuffer2.vertices.push_back(v1);
                meshBuffer2.vertices.push_back(v2);
                meshBuffer2.vertices.push_back(v3);
                meshBuffer2.indices.push_back(1);
                meshBuffer2.indices.push_back(2);
                meshBuffer2.indices.push_back(3);
                mesh.meshBuffers.push_back(meshBuffer2);
            }
        }
        return mesh;
}

SMesh MeshFactory::createCube(Vector3d position, Vector3d rotation, Vector3d size)
{
        // setup the translation matrix
        Matrix4 t;
        // setup translation
        t.setTranslation(position);
        // setup the rotation matrix
        Matrix4 r;
        // setup translation
        r.setRotationDegrees(rotation);
        // setup the size matrix
        Matrix4 s;
        // setup translation
        s.setScale(size);
        // create transformation matrix
        Matrix4 transformation = t * r * s;

        SMesh mesh;

        Vector3d vertices[36] = {
            // bottom face
            Vector3d(-1.0f, -1.0f, -1.0f),
            Vector3d(1.0f, -1.0f, -1.0f),
            Vector3d(1.0f, -1.0f,  1.0f),
            Vector3d(1.0f, -1.0f,  1.0f),
            Vector3d(-1.0f, -1.0f,  1.0f),
            Vector3d(-1.0f, -1.0f,  -1.0f),

            // top face
            Vector3d(1.0f, 1.0f,  1.0f),
            Vector3d(1.0f, 1.0f, -1.0f),
            Vector3d(-1.0f, 1.0f, -1.0f),
            Vector3d(-1.0f, 1.0f,  -1.0f),
            Vector3d(-1.0f, 1.0f,  1.0f),
            Vector3d(1.0f, 1.0f,  1.0f),

            // front face
            Vector3d(-1.0f, -1.0f, 1.0f),
            Vector3d(1.0f, -1.0f, 1.0f),
            Vector3d(1.0f, 1.0f,  1.0f),
            Vector3d(1.0f, 1.0f,  1.0f),
            Vector3d(-1.0f, 1.0f,  1.0f),
            Vector3d(-1.0f, -1.0f,  1.0f),

            // back face
            Vector3d(1.0f, 1.0f,  -1.0f),
            Vector3d(1.0f, -1.0f, -1.0f),
            Vector3d(-1.0f, -1.0f, -1.0f),
            Vector3d(-1.0f, -1.0f,  -1.0f),
            Vector3d(-1.0f, 1.0f,  -1.0f),
            Vector3d(1.0f, 1.0f,  -1.0f),

            // left face
            Vector3d(-1.0f, 1.0f,  -1.0f),
            Vector3d(-1.0f, -1.0f, -1.0f),
            Vector3d(-1.0f, -1.0f, 1.0f),
            Vector3d(-1.0f, -1.0f, 1.0f),
            Vector3d(-1.0f, 1.0f, 1.0f),
            Vector3d(-1.0f, 1.0f,  -1.0f),

            // right face
            Vector3d(1.0f, -1.0f, 1.0f),
            Vector3d(1.0f, -1.0f, -1.0f),
            Vector3d(1.0f, 1.0f,  -1.0f),
            Vector3d(1.0f, 1.0f,  -1.0f),
            Vector3d(1.0f, 1.0f, 1.0f),
            Vector3d(1.0f, -1.0f, 1.0f)
        };

        Vector2d textureCoords[36] = {
            // bottom face
            Vector2d(0.0f, 0.0f),
            Vector2d(1.0f, 0.0f),
            Vector2d(1.0f, 1.0f),
            Vector2d(1.0f, 1.0f),
            Vector2d(0.0f, 1.0f),
            Vector2d(0.0f, 0.0f),

            // top face
            Vector2d(1.0f, 1.0f),
            Vector2d(1.0f, 0.0f),
            Vector2d(0.0f, 0.0f),
            Vector2d(0.0f, 0.0f),
            Vector2d(0.0f, 1.0f),
            Vector2d(1.0f, 1.0f),

            // front face
            Vector2d(1.0f, 0.0f),
            Vector2d(0.0f, 0.0f),
            Vector2d(0.0f, 1.0f),
            Vector2d(0.0f, 1.0f),
            Vector2d(1.0f, 1.0f),
            Vector2d(1.0f, 0.0f),

            // back face
            Vector2d(0.0f, 1.0f),
            Vector2d(0.0f, 0.0f),
            Vector2d(1.0f, 0.0f),
            Vector2d(1.0f, 0.0f),
            Vector2d(1.0f, 1.0f),
            Vector2d(0.0f, 1.0f),

            // left face
            Vector2d(0.0f, 1.0f),
            Vector2d(0.0f, 0.0f),
            Vector2d(1.0f, 0.0f),
            Vector2d(1.0f, 0.0f),
            Vector2d(1.0f, 1.0f),
            Vector2d(0.0f, 1.0f),

            // right face
            Vector2d(0.0f, 0.0f),
            Vector2d(1.0f, 0.0f),
            Vector2d(1.0f, 1.0f),
            Vector2d(1.0f, 1.0f),
            Vector2d(0.0f, 1.0f),
            Vector2d(0.0f, 0.0f)
        };

        Vector3d normals[36] = {
            // bottom face
            Vector3d(0.0f, -1.0f, 0.0f),
            Vector3d(0.0f, -1.0f, 0.0f),
            Vector3d(0.0f, -1.0f, 0.0f),
            Vector3d(0.0f, -1.0f, 0.0f),
            Vector3d(0.0f, -1.0f, 0.0f),
            Vector3d(0.0f, -1.0f, 0.0f),

            // top face
            Vector3d(0.0f, 1.0f, 0.0f),
            Vector3d(0.0f, 1.0f, 0.0f),
            Vector3d(0.0f, 1.0f, 0.0f),
            Vector3d(0.0f, 1.0f, 0.0f),
            Vector3d(0.0f, 1.0f, 0.0f),
            Vector3d(0.0f, 1.0f, 0.0f),

            // front face
            Vector3d(0.0f, 0.0f, 1.0f),
            Vector3d(0.0f, 0.0f, 1.0f),
            Vector3d(0.0f, 0.0f, 1.0f),
            Vector3d(0.0f, 0.0f, 1.0f),
            Vector3d(0.0f, 0.0f, 1.0f),
            Vector3d(0.0f, 0.0f, 1.0f),

            // back face
            Vector3d(0.0f, 0.0f, -1.0f),
            Vector3d(0.0f, 0.0f, -1.0f),
            Vector3d(0.0f, 0.0f, -1.0f),
            Vector3d(0.0f, 0.0f, -1.0f),
            Vector3d(0.0f, 0.0f, -1.0f),
            Vector3d(0.0f, 0.0f, -1.0f),

            // left face
            Vector3d(-1.0f, 0.0f, 0.0f),
            Vector3d(-1.0f, 0.0f, 0.0f),
            Vector3d(-1.0f, 0.0f, 0.0f),
            Vector3d(-1.0f, 0.0f, 0.0f),
            Vector3d(-1.0f, 0.0f, 0.0f),
            Vector3d(-1.0f, 0.0f, 0.0f),

            // right face
            Vector3d(1.0f, 0.0f, 0.0f),
            Vector3d(1.0f, 0.0f, 0.0f),
            Vector3d(1.0f, 0.0f, 0.0f),
            Vector3d(1.0f, 0.0f, 0.0f),
            Vector3d(1.0f, 0.0f, 0.0f),
            Vector3d(1.0f, 0.0f, 0.0f)
        };

        for(unsigned int i = 0; i < 36; i++)
        {
            vertices[i] = transformation * vertices[i];
        }

        for(unsigned int i = 0; i < 36; i++)
        {
            normals[i] = r * normals[i];
        }

        for(unsigned int i = 0; i < 36; i+=3)
        {
            Vertex vertex1;
            Vertex vertex2;
            Vertex vertex3;
            vertex1.position = vertices[i + 0];
            vertex1.normal = normals[i + 0];
            vertex1.textureCoordinate = textureCoords[i + 0];

            vertex2.position = vertices[i + 1];
            vertex2.normal = normals[i + 1];
            vertex2.textureCoordinate = textureCoords[i + 1];

            vertex3.position = vertices[i + 2];
            vertex3.normal = normals[i + 2];
            vertex3.textureCoordinate = textureCoords[i + 2];

            SMeshBuffer meshBuffer;
            meshBuffer.vertices.push_back(vertex1);
            meshBuffer.indices.push_back(1);
            meshBuffer.vertices.push_back(vertex2);
            meshBuffer.indices.push_back(2);
            meshBuffer.vertices.push_back(vertex3);
            meshBuffer.indices.push_back(3);
            mesh.meshBuffers.push_back(meshBuffer);
        }
    return mesh;
}

SMesh MeshFactory::createSquareBasedPyramid(Vector3d position, Vector3d rotation, Vector3d size, float baseLength, float baseHeight)
{
    // setup the translation matrix
    Matrix4 t;
    // setup translation
    t.setTranslation(position);
    // setup the rotation matrix
    Matrix4 r;
    // setup translation
    r.setRotationDegrees(rotation);
    // setup the size matrix
    Matrix4 s;
    // setup translation
    s.setScale(size);
    // create transformation matrix
    Matrix4 transformation = t * r * s;

    SMesh mesh;

    Vertex v1, v2, v3;
    int indicies = 0;
    SMeshBuffer meshBuffer;

    v1.textureCoordinate = Vector2d(1,0);
    v2.textureCoordinate = Vector2d(0,0);
    v3.textureCoordinate = Vector2d(0,1);

    v1.position = Vector3d(0.0f, -(baseHeight/2.0f), -(baseLength/2.0f));
    v1.normal = Vector3d(0.0f, -1.0f, 0.0f);
    v1.position = transformation * v1.position;
    v1.normal = r * v1.normal;

    v2.position = Vector3d(-(baseLength/2.0f), -(baseHeight/2.0f), 0.0f);
    v2.normal = Vector3d(0.0f, -1.0f, 0.0f);
    v2.position = transformation * v2.position;
    v2.normal = r * v2.normal;

    v3.position = Vector3d(0.0f, -(baseHeight/2.0f), (baseLength/2.0f));
    v3.normal = Vector3d(0.0f, -1.0f, 0.0f);
    v3.position = transformation * v3.position;
    v3.normal = r * v3.normal;

    meshBuffer.vertices.push_back(v1);
    meshBuffer.vertices.push_back(v2);
    meshBuffer.vertices.push_back(v3);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    mesh.meshBuffers.push_back(meshBuffer);
    meshBuffer.vertices.clear();
    meshBuffer.indices.clear();

    v1.textureCoordinate = Vector2d(0,1);
    v2.textureCoordinate = Vector2d(1,1);
    v3.textureCoordinate = Vector2d(1,0);

    v1.position = Vector3d(0.0f, -(baseHeight/2.0f), (baseLength/2.0f));
    v1.normal = Vector3d(0.0f, -1.0f, 0.0f);
    v1.position = transformation * v1.position;
    v1.normal = r * v1.normal;

    v2.position = Vector3d((baseLength/2.0f), -(baseHeight/2.0f), 0.0f);
    v2.normal = Vector3d(0.0f, -1.0f, 0.0f);
    v2.position = transformation * v2.position;
    v2.normal = r * v2.normal;

    v3.position = Vector3d(0.0f, -(baseHeight/2.0f), -(baseLength/2.0f));
    v3.normal = Vector3d(0.0f, -1.0f, 0.0f);
    v3.position = transformation * v3.position;
    v3.normal = r * v3.normal;

    meshBuffer.vertices.push_back(v1);
    meshBuffer.vertices.push_back(v2);
    meshBuffer.vertices.push_back(v3);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    mesh.meshBuffers.push_back(meshBuffer);
    meshBuffer.vertices.clear();
    meshBuffer.indices.clear();

    v1.textureCoordinate = Vector2d(0,0);
    v2.textureCoordinate = Vector2d(1,0);
    v3.textureCoordinate = Vector2d(0.5,1);

    v1.position = Vector3d(0.0f, -(baseHeight/2.0f), -(baseLength/2.0f));
    v1.position = transformation * v1.position;
    v2.position = Vector3d(-(baseLength/2.0f), -(baseHeight/2.0f), 0.0f);
    v2.position = transformation * v2.position;
    v3.position = Vector3d(0.0f, (baseHeight/2.0f), 0.0f);
    v3.position = transformation * v3.position;
    v1.normal = v2.normal = v3.normal = findNormal(v1.position, v2.position, v3.position);

    meshBuffer.vertices.push_back(v1);
    meshBuffer.vertices.push_back(v2);
    meshBuffer.vertices.push_back(v3);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    mesh.meshBuffers.push_back(meshBuffer);
    meshBuffer.vertices.clear();
    meshBuffer.indices.clear();

    v1.position = Vector3d(-(baseLength/2.0f), -(baseHeight/2.0f), 0.0f);
    v1.position = transformation * v1.position;
    v2.position = Vector3d(0.0f, -(baseHeight/2.0f), (baseLength/2.0f));
    v2.position = transformation * v2.position;
    v3.position = Vector3d(0.0f, (baseHeight/2.0f), 0.0f);
    v3.position = transformation * v3.position;
    v1.normal = v2.normal = v3.normal = findNormal(v1.position, v2.position, v3.position);

    meshBuffer.vertices.push_back(v1);
    meshBuffer.vertices.push_back(v2);
    meshBuffer.vertices.push_back(v3);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    mesh.meshBuffers.push_back(meshBuffer);
    meshBuffer.vertices.clear();
    meshBuffer.indices.clear();

    v1.position = Vector3d(0.0f, -(baseHeight/2.0f), (baseLength/2.0f));
    v1.position = transformation * v1.position;
    v2.position = Vector3d((baseLength/2.0f), -(baseHeight/2.0f), 0.0f);
    v2.position = transformation * v2.position;
    v3.position = Vector3d(0.0f, (baseHeight/2.0f), 0.0f);
    v3.position = transformation * v3.position;
    v1.normal = v2.normal = v3.normal = findNormal(v1.position, v2.position, v3.position);

    meshBuffer.vertices.push_back(v1);
    meshBuffer.vertices.push_back(v2);
    meshBuffer.vertices.push_back(v3);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    mesh.meshBuffers.push_back(meshBuffer);
    meshBuffer.vertices.clear();
    meshBuffer.indices.clear();

    v1.position = Vector3d((baseLength/2.0f), -(baseHeight/2.0f), 0.0f);
    v1.position = transformation * v1.position;
    v2.position = Vector3d(0.0f, -(baseHeight/2.0f), -(baseLength/2.0f));
    v2.position = transformation * v2.position;
    v3.position = Vector3d(0.0f, (baseHeight/2.0f), 0.0f);
    v3.position = transformation * v3.position;
    v1.normal = v2.normal = v3.normal = findNormal(v1.position, v2.position, v3.position);

    meshBuffer.vertices.push_back(v1);
    meshBuffer.vertices.push_back(v2);
    meshBuffer.vertices.push_back(v3);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    meshBuffer.indices.push_back(indicies+=1);
    mesh.meshBuffers.push_back(meshBuffer);
    meshBuffer.vertices.clear();
    meshBuffer.indices.clear();

    return mesh;
}

SMesh MeshFactory::createTorus(Vector3d position, Vector3d rotation, Vector3d size, float centreOffset, Vector2d radius)
{
    // setup the translation matrix
    Matrix4 t;
    // setup translation
    t.setTranslation(position);
    // setup the rotation matrix
    Matrix4 r;
    // setup translation
    r.setRotationDegrees(rotation);
    // setup the size matrix
    Matrix4 s;
    // setup translation
    s.setScale(size);
    // create transformation matrix
    Matrix4 transformation = t * r * s;

    SMesh mesh;

    for(float phi = 0.0f, deltaPhi = (2 * M_PI) / 12.0f; phi < (2 * M_PI)-deltaPhi; phi += deltaPhi)
    {
        for(float theta = 0.0f, deltaTheta = (2 * M_PI) / 16.0f; theta < (2 * M_PI); theta += deltaTheta)
        {
            Matrix4 orbit;
            orbit.makeIdentity();
            orbit.setRotationRadians(Vector3d(0.0f, phi, 0.0f));

            Matrix4 orbitNext;
            orbitNext.makeIdentity();
            orbitNext.setRotationRadians(Vector3d(0.0f, phi + deltaPhi, 0.0f));

            Vertex v1;
            v1.position.x = (cos(theta)*radius.x)+centreOffset;
            v1.position.y = (sin(theta)*radius.y);
            v1.position.z = 0.0f;
            v1.position = transformation * (orbit * v1.position);
            v1.normal.x = cos(theta);
            v1.normal.y = sin(theta);
            v1.normal.z = 0.0f;
            v1.normal = r * (orbit * v1.normal);
            v1.textureCoordinate = Vector2d(theta / (2*M_PI), phi / (2*M_PI));

            Vertex v2;
            v2.position.x = cos(theta)*radius.x+centreOffset;
            v2.position.y = sin(theta)*radius.y;
            v2.position.z = 0.0f;
            v2.position = transformation *(orbitNext * v2.position);
            v2.normal.x = cos(theta);
            v2.normal.y = sin(theta);
            v2.normal.z = 0.0f;
            v2.normal = r * (orbitNext * v2.normal);
            v2.textureCoordinate = Vector2d(theta / (2*M_PI), (phi+deltaPhi) / (2*M_PI));

            Vertex v3;
            v3.position.x = cos(theta+deltaTheta)*radius.x+centreOffset;
            v3.position.y = sin(theta+deltaTheta)*radius.y;
            v3.position.z = 0.0f;
            v3.position = transformation *(orbit * v3.position);
            v3.normal.x = cos(theta+deltaTheta);
            v3.normal.y = sin(theta+deltaTheta);
            v3.normal.z = 0.0f;
            v3.normal = r *(orbit * v3.normal);
            v3.textureCoordinate = Vector2d((theta+deltaTheta) / (2*M_PI), (phi) / (2*M_PI));

            SMeshBuffer meshBuffer1;
            meshBuffer1.vertices.push_back(v1);
            meshBuffer1.vertices.push_back(v2);
            meshBuffer1.vertices.push_back(v3);
            meshBuffer1.indices.push_back(1);
            meshBuffer1.indices.push_back(2);
            meshBuffer1.indices.push_back(3);
            mesh.meshBuffers.push_back(meshBuffer1);

            Vertex v4;
            v4.position.x = cos(theta+deltaTheta)*radius.x+centreOffset;
            v4.position.y = sin(theta+deltaTheta)*radius.y;
            v4.position.z = 0.0f;
            v4.position = transformation *(orbit * v4.position);
            v4.normal.x = cos(theta+deltaTheta);
            v4.normal.y = sin(theta+deltaTheta);
            v4.normal.z = 0.0f;
            v4.normal = r *(orbit * v4.normal);
            v4.textureCoordinate = Vector2d((theta+deltaTheta) / (2*M_PI), (phi) / (2*M_PI));

            Vertex v5;
            v5.position.x = cos(theta)*radius.x+centreOffset;
            v5.position.y = sin(theta)*radius.y;
            v5.position.z = 0.0f;
            v5.position = transformation *(orbitNext * v5.position);
            v5.normal.x = cos(theta);
            v5.normal.y = sin(theta);
            v5.normal.z = 0.0f;
            v5.normal = r * (orbitNext * v5.normal);
            v5.textureCoordinate = Vector2d((theta) / (2*M_PI), (phi+deltaPhi) / (2*M_PI));

            Vertex v6;
            v6.position.x = cos(theta+deltaTheta)*radius.x+centreOffset;
            v6.position.y = sin(theta+deltaTheta)*radius.y;
            v6.position.z = 0.0f;
            v6.position = transformation *(orbitNext * v6.position);
            v6.normal.x = cos(theta+deltaTheta);
            v6.normal.y = sin(theta+deltaTheta);
            v6.normal.z = 0.0f;
            v6.normal = r * (orbitNext * v6.normal);
            v6.textureCoordinate = Vector2d((theta+deltaTheta) / (2*M_PI), (phi+deltaPhi) / (2*M_PI));

            SMeshBuffer meshBuffer2;
            meshBuffer2.vertices.push_back(v4);
            meshBuffer2.vertices.push_back(v5);
            meshBuffer2.vertices.push_back(v6);
            meshBuffer2.indices.push_back(1);
            meshBuffer2.indices.push_back(2);
            meshBuffer2.indices.push_back(3);
            mesh.meshBuffers.push_back(meshBuffer2);

            Vector3d normal;

//                normal = findNormal(p1, p2, p3);
//                glBegin(GL_TRIANGLES);
//                    glNormal3f(normal.x, normal.y, normal.z);
//                    glTexCoord2f(0.0f, 0.0f);
//                    glVertex3f(p1.x, p1.y, p1.z);
//                    glTexCoord2f(1.0f, 0.0f);
//                    glVertex3f(p2.x, p2.y, p2.z);
//                    glTexCoord2f(1.0f, 1.0f);
//                    glVertex3f(p3.x, p3.y, p3.z);
//                glEnd();
//
//                normal = findNormal(p4, p5, p6);
//                glBegin(GL_TRIANGLES);
//                    glNormal3f(normal.x, normal.y, normal.z);
//                    glTexCoord2f(0.0f, 0.0f);
//                    glVertex3f(p4.x, p4.y, p4.z);
//                    glTexCoord2f(1.0f, 0.0f);
//                    glVertex3f(p5.x, p5.y, p5.z);
//                    glTexCoord2f(1.0f, 1.0f);
//                    glVertex3f(p6.x, p6.y, p6.z);
//                glEnd();
        }
    }
    return mesh;
}

SMesh MeshFactory::createCylinder(Vector3d position, Vector3d rotation, Vector3d size, float height, Vector2d radius)
{
    // setup the translation matrix
    Matrix4 t;
    // setup translation
    t.setTranslation(position);
    // setup the rotation matrix
    Matrix4 r;
    // setup translation
    r.setRotationDegrees(rotation);
    // setup the size matrix
    Matrix4 s;
    // setup translation
    s.setScale(size);
    // create transformation matrix
    Matrix4 transformation = t * r * s;

    SMesh mesh;

    for(float theta = 0, thetaDelta=(2*M_PI)/16.0f; theta < (2*M_PI); theta+=thetaDelta)
    {
        Vertex v1;
        v1.position.x = cos(theta)*radius.x;
        v1.position.y = height/2;
        v1.position.z = sin(theta)*radius.y;
        v1.position = transformation * v1.position;
        v1.normal.x = cos(theta);
        v1.normal.y = 0.0f;
        v1.normal.z = sin(theta);
        v1.normal = r * v1.normal;
        v1.textureCoordinate = Vector2d((theta)/(2*M_PI), 1.0f);

        Vertex v2;
        v2.position.x = cos(theta+thetaDelta)*radius.x;
        v2.position.y = height/2;
        v2.position.z = sin(theta+thetaDelta)*radius.y;
        v2.position = transformation * v2.position;
        v2.normal.x = cos(theta+thetaDelta);
        v2.normal.y = 0.0f;
        v2.normal.z = sin(theta+thetaDelta);
        v2.normal = r * v2.normal;
        v2.textureCoordinate = Vector2d((theta+thetaDelta)/(2*M_PI), 1.0f);

        Vertex v3;
        v3.position.x = cos(theta+thetaDelta)*radius.x;
        v3.position.y = -(height/2);
        v3.position.z = sin(theta+thetaDelta)*radius.y;
        v3.position = transformation * v3.position;
        v3.normal.x = cos(theta+thetaDelta);
        v3.normal.y = 0.0f;
        v3.normal.z = sin(theta+thetaDelta);
        v3.normal = r * v3.normal;
        v3.textureCoordinate = Vector2d((theta+thetaDelta)/(2*M_PI), 0.0f);

        Vertex v4;
        v4.position.x = cos(theta+thetaDelta)*radius.x;
        v4.position.y = -(height/2);
        v4.position.z = sin(theta+thetaDelta)*radius.y;
        v4.position = transformation * v4.position;
        v4.normal.x = cos(theta+thetaDelta);
        v4.normal.y = 0.0f;
        v4.normal.z = sin(theta+thetaDelta);
        v4.normal = r * v4.normal;
        v4.textureCoordinate = Vector2d((theta+thetaDelta)/(2*M_PI), 0.0f);

        Vertex v5;
        v5.position.x = cos(theta)*radius.x;
        v5.position.y = -(height/2);
        v5.position.z = sin(theta)*radius.y;
        v5.position = transformation * v5.position;
        v5.normal.x = cos(theta);
        v5.normal.y = 0.0f;
        v5.normal.z = sin(theta);
        v5.normal = r * v5.normal;
        v5.textureCoordinate = Vector2d((theta)/(2*M_PI), 0.0f);

        Vertex v6;
        v6.position.x = cos(theta)*radius.x;
        v6.position.y = height/2;
        v6.position.z = sin(theta)*radius.y;
        v6.position = transformation * v6.position;
        v6.normal.x = cos(theta);
        v6.normal.y = 0.0f;
        v6.normal.z = sin(theta);
        v6.normal = r * v6.normal;
        v6.textureCoordinate = Vector2d((theta)/(2*M_PI), 1.0f);

        Vertex v7;
        v7.position.x = cos(theta)*radius.x;
        v7.position.y = height/2;
        v7.position.z = sin(theta)*radius.y;
        v7.position = transformation * v7.position;
        v7.normal.x = 0.0f;
        v7.normal.y = 1.0f;
        v7.normal.z = 0.0f;
        v7.normal = r * v7.normal;
        v7.textureCoordinate = Vector2d(0.5f*cos(theta)+0.5f, 0.5f*sin(theta)+0.5f);

        Vertex v8;
        v8.position.x = cos(theta+thetaDelta)*radius.x;
        v8.position.y = height/2;
        v8.position.z = sin(theta+thetaDelta)*radius.y;
        v8.position = transformation * v8.position;
        v8.normal.x = 0.0f;
        v8.normal.y = 1.0f;
        v8.normal.z = 0.0f;
        v8.normal = r * v8.normal;
        v8.textureCoordinate = Vector2d(0.5f*cos(theta + thetaDelta)+0.5f, 0.5f*sin(theta + thetaDelta)+0.5f);

        Vertex v9;
        v9.position.x = 0.0f;
        v9.position.y = height/2;
        v9.position.z = 0.0f;
        v9.position = transformation * v9.position;
        v9.normal.x = 0.0f;
        v9.normal.y = 1.0f;
        v9.normal.z = 0.0f;
        v9.normal = r * v9.normal;
        v9.textureCoordinate = Vector2d(0.5,0.5);

        Vertex v10;
        v10.position.x = 0.0f;
        v10.position.y = -(height/2);
        v10.position.z = 0.0f;
        v10.position = transformation * v10.position;
        v10.normal.x = 0.0f;
        v10.normal.y = -1.0f;
        v10.normal.z = 0.0f;
        v10.normal = r * v10.normal;
        v10.textureCoordinate = Vector2d(0.5f,0.5f);

        Vertex v11;
        v11.position.x = cos(theta+thetaDelta)*radius.x;
        v11.position.y = -(height/2);
        v11.position.z = sin(theta+thetaDelta)*radius.y;
        v11.position = transformation * v11.position;
        v11.normal.x = 0.0f;
        v11.normal.y = -1.0f;
        v11.normal.z = 0.0f;
        v11.normal = r * v11.normal;
        v11.textureCoordinate = Vector2d(0.5f*cos(theta + thetaDelta)+0.5f, 0.5f*sin(theta + thetaDelta)+0.5f);

        Vertex v12;
        v12.position.x = cos(theta)*radius.x;
        v12.position.y = -(height/2);
        v12.position.z = sin(theta)*radius.y;
        v12.position = transformation * v12.position;
        v12.normal.x = 0.0f;
        v12.normal.y = -1.0f;
        v12.normal.z = 0.0f;
        v12.normal = r * v12.normal;
        v12.textureCoordinate = Vector2d(0.5f*cos(theta)+0.5f, 0.5f*sin(theta)+0.5f);

        SMeshBuffer meshBuffer;
        meshBuffer.vertices.push_back(v1);
        meshBuffer.vertices.push_back(v2);
        meshBuffer.vertices.push_back(v3);
        meshBuffer.vertices.push_back(v4);
        meshBuffer.vertices.push_back(v5);
        meshBuffer.vertices.push_back(v6);
        meshBuffer.vertices.push_back(v7);
        meshBuffer.vertices.push_back(v8);
        meshBuffer.vertices.push_back(v9);

        meshBuffer.vertices.push_back(v10);
        meshBuffer.vertices.push_back(v11);
        meshBuffer.vertices.push_back(v12);
        meshBuffer.indices.push_back(1);
        meshBuffer.indices.push_back(2);
        meshBuffer.indices.push_back(3);
        meshBuffer.indices.push_back(4);
        meshBuffer.indices.push_back(5);
        meshBuffer.indices.push_back(6);
        meshBuffer.indices.push_back(7);
        meshBuffer.indices.push_back(8);
        meshBuffer.indices.push_back(9);

        meshBuffer.indices.push_back(10);
        meshBuffer.indices.push_back(11);
        meshBuffer.indices.push_back(12);

        mesh.meshBuffers.push_back(meshBuffer);

    }

    return mesh;
}

SMesh MeshFactory::createHollowCylinder(Vector3d position, Vector3d rotation, Vector3d size, float height, Vector2d outerRadius, Vector2d innerRadius)
{
    // setup the translation matrix
    Matrix4 t;
    // setup translation
    t.setTranslation(position);
    // setup the rotation matrix
    Matrix4 r;
    // setup translation
    r.setRotationDegrees(rotation);
    // setup the size matrix
    Matrix4 s;
    // setup translation
    s.setScale(size);
    // create transformation matrix
    Matrix4 transformation = t * r * s;

    SMesh mesh;

    float r1 = 1.0f;
    float r2 = 0.8f;

    for(float theta = 0, thetaDelta=(2*M_PI)/16.0f; theta < (2*M_PI); theta+=thetaDelta)
    {
        Vertex v1;
        v1.position.x = cos(theta)*outerRadius.x;
        v1.position.y = height/2;
        v1.position.z = sin(theta)*outerRadius.y;
        v1.position = transformation * v1.position;
        v1.normal.x = cos(theta);
        v1.normal.y = 0.0f;
        v1.normal.z = sin(theta);
        v1.normal = r * v1.normal;
        v1.textureCoordinate = Vector2d((theta)/(2*M_PI), 1.0f);

        Vertex v2;
        v2.position.x = cos(theta+thetaDelta)*outerRadius.x;
        v2.position.y = height/2;
        v2.position.z = sin(theta+thetaDelta)*outerRadius.y;
        v2.position = transformation * v2.position;
        v2.normal.x = cos(theta+thetaDelta);
        v2.normal.y = 0.0f;
        v2.normal.z = sin(theta+thetaDelta);
        v2.normal = r * v2.normal;
        v2.textureCoordinate = Vector2d((theta+thetaDelta)/(2*M_PI), 1.0f);

        Vertex v3;
        v3.position.x = cos(theta+thetaDelta)*outerRadius.x;
        v3.position.y = -(height/2);
        v3.position.z = sin(theta+thetaDelta)*outerRadius.y;
        v3.position = transformation * v3.position;
        v3.normal.x = cos(theta+thetaDelta);
        v3.normal.y = 0.0f;
        v3.normal.z = sin(theta+thetaDelta);
        v3.normal = r * v3.normal;
        v3.textureCoordinate = Vector2d((theta+thetaDelta)/(2*M_PI), 0.0f);

        Vertex v4;
        v4.position.x = cos(theta+thetaDelta)*outerRadius.x;
        v4.position.y = -(height/2);
        v4.position.z = sin(theta+thetaDelta)*outerRadius.y;
        v4.position = transformation * v4.position;
        v4.normal.x = cos(theta+thetaDelta);
        v4.normal.y = 0.0f;
        v4.normal.z = sin(theta+thetaDelta);
        v4.normal = r * v4.normal;
        v4.textureCoordinate = Vector2d((theta+thetaDelta)/(2*M_PI), 0.0f);

        Vertex v5;
        v5.position.x = cos(theta)*outerRadius.x;
        v5.position.y = -(height/2);
        v5.position.z = sin(theta)*outerRadius.y;
        v5.position = transformation * v5.position;
        v5.normal.x = cos(theta);
        v5.normal.y = 0.0f;
        v5.normal.z = sin(theta);
        v5.normal = r * v5.normal;
        v5.textureCoordinate = Vector2d((theta)/(2*M_PI), 0.0f);

        Vertex v6;
        v6.position.x = cos(theta)*outerRadius.x;
        v6.position.y = height/2;
        v6.position.z = sin(theta)*outerRadius.y;
        v6.position = transformation * v6.position;
        v6.normal.x = cos(theta);
        v6.normal.y = 0.0f;
        v6.normal.z = sin(theta);
        v6.normal = r * v6.normal;
        v6.textureCoordinate = Vector2d((theta)/(2*M_PI), 1.0f);

        SMeshBuffer meshBuffer;
        meshBuffer.vertices.push_back(v1);
        meshBuffer.vertices.push_back(v2);
        meshBuffer.vertices.push_back(v3);
        meshBuffer.vertices.push_back(v4);
        meshBuffer.vertices.push_back(v5);
        meshBuffer.vertices.push_back(v6);
        meshBuffer.indices.push_back(1);
        meshBuffer.indices.push_back(2);
        meshBuffer.indices.push_back(3);
        meshBuffer.indices.push_back(4);
        meshBuffer.indices.push_back(5);
        meshBuffer.indices.push_back(6);

        mesh.meshBuffers.push_back(meshBuffer);
    }

    for(float theta = 0, thetaDelta=(2*M_PI)/16.0f; theta < (2*M_PI); theta+=thetaDelta)
    {
        Vertex v1;
        v1.position.x = cos(theta)*innerRadius.x;
        v1.position.y = height/2;
        v1.position.z = sin(theta)*innerRadius.y;
        v1.position = transformation * v1.position;
        v1.normal.x = -cos(theta);
        v1.normal.y = 0.0f;
        v1.normal.z = -sin(theta);
        v1.normal = r * v1.normal;
        v1.textureCoordinate = Vector2d((theta)/(2*M_PI), 1.0f);

        Vertex v2;
        v2.position.x = cos(theta+thetaDelta)*innerRadius.x;
        v2.position.y = height/2;
        v2.position.z = sin(theta+thetaDelta)*innerRadius.y;
        v2.position = transformation * v2.position;
        v2.normal.x = -cos(theta+thetaDelta);
        v2.normal.y = 0.0f;
        v2.normal.z = -sin(theta+thetaDelta);
        v2.normal = r * v2.normal;
        v2.textureCoordinate = Vector2d((theta+thetaDelta)/(2*M_PI), 1.0f);

        Vertex v3;
        v3.position.x = cos(theta+thetaDelta)*innerRadius.x;
        v3.position.y = -(height/2);
        v3.position.z = sin(theta+thetaDelta)*innerRadius.y;
        v3.position = transformation * v3.position;
        v3.normal.x = -cos(theta+thetaDelta);
        v3.normal.y = 0.0f;
        v3.normal.z = -sin(theta+thetaDelta);
        v3.normal = r * v3.normal;
        v3.textureCoordinate = Vector2d((theta+thetaDelta)/(2*M_PI), 0.0f);

        Vertex v4;
        v4.position.x = cos(theta+thetaDelta)*innerRadius.x;
        v4.position.y = -(height/2);
        v4.position.z = sin(theta+thetaDelta)*innerRadius.y;
        v4.position = transformation * v4.position;
        v4.normal.x = -cos(theta+thetaDelta);
        v4.normal.y = 0.0f;
        v4.normal.z = -sin(theta+thetaDelta);
        v4.normal = r * v4.normal;
        v4.textureCoordinate = Vector2d((theta+thetaDelta)/(2*M_PI), 0.0f);

        Vertex v5;
        v5.position.x = cos(theta)*innerRadius.x;
        v5.position.y = -(height/2);
        v5.position.z = sin(theta)*innerRadius.y;
        v5.position = transformation * v5.position;
        v5.normal.x = -cos(theta);
        v5.normal.y = 0.0f;
        v5.normal.z = -sin(theta);
        v5.normal = r * v5.normal;
        v5.textureCoordinate = Vector2d((theta)/(2*M_PI), 0.0f);

        Vertex v6;
        v6.position.x = cos(theta)*innerRadius.x;
        v6.position.y = height/2;
        v6.position.z = sin(theta)*innerRadius.y;
        v6.position = transformation * v6.position;
        v6.normal.x = -cos(theta);
        v6.normal.y = 0.0f;
        v6.normal.z = -sin(theta);
        v6.normal = r * v6.normal;
        v6.textureCoordinate = Vector2d((theta)/(2*M_PI), 1.0f);

        SMeshBuffer meshBuffer;
        meshBuffer.vertices.push_back(v1);
        meshBuffer.vertices.push_back(v2);
        meshBuffer.vertices.push_back(v3);
        meshBuffer.vertices.push_back(v4);
        meshBuffer.vertices.push_back(v5);
        meshBuffer.vertices.push_back(v6);
        meshBuffer.indices.push_back(1);
        meshBuffer.indices.push_back(2);
        meshBuffer.indices.push_back(3);
        meshBuffer.indices.push_back(4);
        meshBuffer.indices.push_back(5);
        meshBuffer.indices.push_back(6);

        mesh.meshBuffers.push_back(meshBuffer);
    }

    // the difference between the outer and the inner radius, divided by the outer radius
    float k = (r1 - r2) / r1;

    for(float theta = 0, thetaDelta=(2*M_PI)/16.0f; theta < (2*M_PI); theta+=thetaDelta)
    {

        Vertex v1;
        v1.position.x = cos(theta)*outerRadius.x;
        v1.position.y = height/2;
        v1.position.z = sin(theta)*outerRadius.y;
        v1.position = transformation * v1.position;
        v1.normal.x = 0.0f;
        v1.normal.y = 1.0f;
        v1.normal.z = 0.0f;
        v1.normal = r * v1.normal;
        v1.textureCoordinate = Vector2d(cos(theta)*0.5+0.5f, sin(theta)*0.5+0.5f);

        Vertex v2;
        v2.position.x = cos(theta)*innerRadius.x;
        v2.position.y = height/2;
        v2.position.z = sin(theta)*innerRadius.y;
        v2.position = transformation * v2.position;
        v2.normal.x = 0.0f;
        v2.normal.y = 1.0f;
        v2.normal.z = 0.0f;
        v2.normal = r * v2.normal;
        v2.textureCoordinate = Vector2d((k*cos(theta)*0.5+0.5f), (k*sin(theta)*0.5+0.5f));

        Vertex v3;
        v3.position.x = cos(theta+thetaDelta)*outerRadius.x;
        v3.position.y = height/2;
        v3.position.z = sin(theta+thetaDelta)*outerRadius.y;
        v3.position = transformation * v3.position;
        v3.normal.x = 0.0f;
        v3.normal.y = 1.0f;
        v3.normal.z = 0.0f;
        v3.normal = r * v3.normal;
        v3.textureCoordinate = Vector2d((cos(theta+thetaDelta)*0.5+0.5f), (sin(theta+thetaDelta)*0.5+0.5f));

        Vertex v4;
        v4.position.x = cos(theta+thetaDelta)*outerRadius.x;
        v4.position.y = height/2;
        v4.position.z = sin(theta+thetaDelta)*outerRadius.y;
        v4.position = transformation * v4.position;
        v4.normal.x = 0.0f;
        v4.normal.y = 1.0f;
        v4.normal.z = 0.0f;
        v4.normal = r * v4.normal;
        v4.textureCoordinate = Vector2d((cos(theta+thetaDelta)*0.5+0.5f), (sin(theta+thetaDelta)*0.5+0.5f));

        Vertex v5;
        v5.position.x = cos(theta)*innerRadius.x;
        v5.position.y = height/2;
        v5.position.z = sin(theta)*innerRadius.y;
        v5.position = transformation * v5.position;
        v5.normal.x = 0.0f;
        v5.normal.y = 1.0f;
        v5.normal.z = 0.0f;
        v5.normal = r * v5.normal;
        v5.textureCoordinate = Vector2d((k*cos(theta)*0.5+0.5f), (k*sin(theta)*0.5+0.5f));

        Vertex v6;
        v6.position.x = cos(theta+thetaDelta)*innerRadius.x;
        v6.position.y = height/2;
        v6.position.z = sin(theta+thetaDelta)*innerRadius.y;
        v6.position = transformation * v6.position;
        v6.normal.x = 0.0f;
        v6.normal.y = 1.0f;
        v6.normal.z = 0.0f;
        v6.normal = r * v6.normal;
        v6.textureCoordinate = Vector2d((k*cos(theta+thetaDelta)*0.5+0.5f), (k*sin(theta+thetaDelta)*0.5+0.5f));

        SMeshBuffer meshBuffer;
        meshBuffer.vertices.push_back(v1);
        meshBuffer.vertices.push_back(v2);
        meshBuffer.vertices.push_back(v3);
        meshBuffer.vertices.push_back(v4);
        meshBuffer.vertices.push_back(v5);
        meshBuffer.vertices.push_back(v6);
        meshBuffer.indices.push_back(1);
        meshBuffer.indices.push_back(2);
        meshBuffer.indices.push_back(3);
        meshBuffer.indices.push_back(4);
        meshBuffer.indices.push_back(5);
        meshBuffer.indices.push_back(6);

        mesh.meshBuffers.push_back(meshBuffer);
    }

    for(float theta = 0, thetaDelta=(2*M_PI)/16.0f; theta < (2*M_PI); theta+=thetaDelta)
    {

        Vertex v1;
        v1.position.x = cos(theta)*outerRadius.x;
        v1.position.y = -(height/2);
        v1.position.z = sin(theta)*outerRadius.y;
        v1.position = transformation * v1.position;
        v1.normal.x = 0.0f;
        v1.normal.y = -1.0f;
        v1.normal.z = 0.0f;
        v1.normal = r * v1.normal;
        v1.textureCoordinate = Vector2d(0.5f*cos(theta)+0.5f, 0.5f*sin(theta)+0.5f);

        Vertex v2;
        v2.position.x = cos(theta)*innerRadius.x;
        v2.position.y = -(height/2);
        v2.position.z = sin(theta)*innerRadius.y;
        v2.position = transformation * v2.position;
        v2.normal.x = 0.0f;
        v2.normal.y = -1.0f;
        v2.normal.z = 0.0f;
        v2.normal = r * v2.normal;
        v2.textureCoordinate = Vector2d((0.5f*k*cos(theta)+0.5f), (0.5f*k*sin(theta)+0.5f));

        Vertex v3;
        v3.position.x = cos(theta+thetaDelta)*outerRadius.x;
        v3.position.y = -(height/2);
        v3.position.z = sin(theta+thetaDelta)*outerRadius.y;
        v3.position = transformation * v3.position;
        v3.normal.x = 0.0f;
        v3.normal.y = -1.0f;
        v3.normal.z = 0.0f;
        v3.normal = r * v3.normal;
        v3.textureCoordinate = Vector2d((0.5f*cos(theta+thetaDelta)+0.5f), (0.5f*sin(theta+thetaDelta)+0.5f));

        Vertex v4;
        v4.position.x = cos(theta+thetaDelta)*outerRadius.x;
        v4.position.y = -(height/2);
        v4.position.z = sin(theta+thetaDelta)*outerRadius.y;
        v4.position = transformation * v4.position;
        v4.normal.x = 0.0f;
        v4.normal.y = -1.0f;
        v4.normal.z = 0.0f;
        v4.normal = r * v4.normal;
        v4.textureCoordinate = Vector2d((0.5f*cos(theta+thetaDelta)+0.5f), (0.5f*sin(theta+thetaDelta)+0.5f));

        Vertex v5;
        v5.position.x = cos(theta)*innerRadius.x;
        v5.position.y = -(height/2);
        v5.position.z = sin(theta)*innerRadius.y;
        v5.position = transformation * v5.position;
        v5.normal.x = 0.0f;
        v5.normal.y = -1.0f;
        v5.normal.z = 0.0f;
        v5.normal = r * v5.normal;
        v5.textureCoordinate = Vector2d((0.5f*k*cos(theta)+0.5f), (0.5f*k*sin(theta)+0.5f));

        Vertex v6;
        v6.position.x = cos(theta+thetaDelta)*innerRadius.x;
        v6.position.y = -(height/2);
        v6.position.z = sin(theta+thetaDelta)*innerRadius.y;
        v6.position = transformation * v6.position;
        v6.normal.x = 0.0f;
        v6.normal.y = -1.0f;
        v6.normal.z = 0.0f;
        v6.normal = r * v6.normal;
        v6.textureCoordinate = Vector2d((0.5f*k*cos(theta+thetaDelta)+0.5f), (0.5f*k*sin(theta+thetaDelta)+0.5f));

        SMeshBuffer meshBuffer;
        meshBuffer.vertices.push_back(v1);
        meshBuffer.vertices.push_back(v2);
        meshBuffer.vertices.push_back(v3);
        meshBuffer.vertices.push_back(v4);
        meshBuffer.vertices.push_back(v5);
        meshBuffer.vertices.push_back(v6);
        meshBuffer.indices.push_back(1);
        meshBuffer.indices.push_back(2);
        meshBuffer.indices.push_back(3);
        meshBuffer.indices.push_back(4);
        meshBuffer.indices.push_back(5);
        meshBuffer.indices.push_back(6);

        mesh.meshBuffers.push_back(meshBuffer);
    }

    return mesh;
}

SMesh MeshFactory::loadModel(const char* filename, Vector3d position, Vector3d rotation, Vector3d size)
{
    // setup the translation matrix
    Matrix4 t;
    // setup translation
    t.setTranslation(position);
    // setup the rotation matrix
    Matrix4 r;
    // setup translation
    r.setRotationDegrees(rotation);
    // setup the size matrix
    Matrix4 s;
    // setup translation
    s.setScale(size);
    // create transformation matrix
    Matrix4 transformation = t * r * s;

    SMesh mesh;

    PlyFile* pPlyFile;
    FILE* pFile;
    pFile = fopen(filename,"r");
    if (pFile == NULL) return mesh;

    pPlyFile = read_ply(pFile);
    if(pPlyFile == NULL) return mesh;

    std::cout << "Load File: [" << filename << "] success." << std::endl;
    std::cout << std::endl;
    std::cout << "File type: " << pPlyFile->file_type << std::endl;
    std::cout << std::endl;
    std::cout << "Version: " << pPlyFile->version << std::endl;
    std::cout << std::endl;
    std::cout << "Number of comments: " << pPlyFile->num_comments << std::endl;
    for(int i = 0; i < pPlyFile->num_comments; i++)
    {
        char* comment = pPlyFile->comments[i];
        std::cout << "\t" << comment << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Number of element types: " << pPlyFile->num_elem_types << std::endl;
    for(int i = 0; i < pPlyFile->num_elem_types; i++)
    {
        PlyElement* plyElement = pPlyFile->elems[i];
            char* name = plyElement->name;
            std::cout << std::endl;
            std::cout << "\tElement Name: " << name << " Number of elements in file: " << plyElement->num << std::endl;

            std::cout << "\t\tNumber of Properties: " << plyElement->nprops << std::endl;
            for(int j = 0; j < plyElement->nprops; j++)
            {
                PlyProperty* property = plyElement->props[j];
                std::cout << "\t\t\tElement Name: " << property->name << std::endl;
                //std::cout << "\t\t\t" << property-> << std::endl;
            }
            std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Number of object info: " << pPlyFile->num_obj_info << std::endl;
    for(int i = 0; i < pPlyFile->num_obj_info; i++)
    {
        std::cout << "\t" << pPlyFile->obj_info[i] << std::endl;
    }
    close_ply(pPlyFile);
    fclose(pFile);
    return mesh;
}

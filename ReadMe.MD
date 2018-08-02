# A Simple OpenGL Rendering Engine

I made a small rendering engine using OpenGL. All transformations here are done with a custom matrix class. There is a scene manager with scene-nodes. There are materials which are applied to mesh buffers. Mesh buffers contain vertex information i.e. vertex colours, normals, texture co-ordinates. Materials support wire-frame/solid, environment mapping and support for textures. I created a sky-box to which involved drawing a mesh at the camera location then clearing the Z-Buffer before rendering all the normal objects.

Controls are WASD and the mouse.


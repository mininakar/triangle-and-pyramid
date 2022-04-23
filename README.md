# triangle-and-pyramid
<h1 align="center"> CAMERA SPACE </h1>

>Description of shaders. We use shaders to create a pyramid (3d shape).

For shader use: **#version 330** that means we're use GLSL ver. 3.3.

<h3>Vertex Shader:</h3>

For every call to the shader on the GPU, the values of the new vertex will be supplied from the buffer.

**layout (location = 0) in vec3 Position;** 

Set the transformation code for the coordinates of the incoming vertex.

**gl_Position = vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0);** 

<h3>Pixel shader:</h3> 

Set colors
**FragColor = vec4(1.0, 0.0, 0.0, 1.0);**

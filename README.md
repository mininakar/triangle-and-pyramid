# triangle-and-pyramid
<h2>The Pipeline class</h2> is a pipeline class that abstracts the details of getting all the transformations needed for a single object.

Here are 3 private vectors that store the result after each operation of finding the matrix by transformation: 
  **glm::vec3 m_scale;
	glm::vec3 m_worldPos;
	glm::vec3 m_rotateInfo;**

<h1 align="center"> CAMERA SPACE </h1>

>Description of shaders. We use shaders to create a pyramid (3d shape).

For shader use: **#version 330** that means we're use GLSL ver. 3.3.

<h3>Vertex Shader:</h3>

1)For every call to the shader on the GPU, the values of the new vertex will be supplied from the buffer:

**layout (location = 0) in vec3 Position;** 

2)Set the transformation code for the coordinates of the incoming vertex:

**gl_Position = vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0);** 

<h3>Pixel shader:</h3> 

1)Set colors:

**FragColor = vec4(1.0, 0.0, 0.0, 1.0);**

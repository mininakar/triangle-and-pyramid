# triangle-and-pyramid
<h1 align="center"> CAMERA SPACE

Use shaders to create a pyramid (3d shape).

For shader use:  #version 330
that means we're use GLSL ver. 3.3.

Vertex Shader:
means that for every call to the shader on the GPU, the values of the new vertex will be supplied from the buffer.
layout (location = 0) in vec3 Position; - Вершина содержит' означает, что для каждого вызова шейдера в GPU значения новой вершины будут поставляться из буфера.

set the transformation code for the coordinates of the incoming vertex.
gl_Position = vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0); -задаем кодом трансформации для координат входящей вершины.

pixel shader: used to determine the color of a pixel.

Set colors
FragColor = vec4(1.0, 0.0, 0.0, 1.0);

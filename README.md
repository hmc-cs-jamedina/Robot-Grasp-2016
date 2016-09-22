# Robot-Grasp-2016

This repository is a personal backup of some of the code used in an exploration of robotic grasping conducted at Oregon State University during the Summer of 2016. Please look at the repository Grasp-Rendering-Modification to see a more complete version of this code.

The "WarmCool-shaders" folder contains shaders that implement warm/cool shading in GLSL. The folder includes a bmp file that can be used as a texture map if desired. To switch between implementing the warm/cool shading through RGB modulation and texture mapping, use the second "color" variable in the fragment shader instead of the first "color" variable.

"QtTest" contains a full implementation of warm-cool rendering in a 3D application using Qt version 5.2.1.

#shader vertex
#version 120
attribute vec3 position;
attribute vec3 normals;
uniform mat4 MVP;
varying vec3 _normals;
void main(void) {
    _normals = normals;
    vec4 v = vec4(position, 1.0);
    gl_Position = MVP * v;
}

#shader fragment
#version 120
uniform vec4 color;
uniform vec3 light;
varying vec3 _normals;
void main(void) {
    //float d = clamp(dot(light,vec3(1,1,1)),0.0,1.0) + 1.0;
    float d = clamp(dot(light,_normals),0,1) + 0.2;
    gl_FragColor = d* color;
}
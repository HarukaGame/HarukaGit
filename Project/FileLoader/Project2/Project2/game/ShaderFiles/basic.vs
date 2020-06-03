attribute vec3 position;
attribute vec3 normals;
uniform mat4 MVP;
varying vec3 _normals;
void main(void) {
_normals = normals;
vec4 v = vec4(position, 1.0);
gl_Position = MVP * v;
}
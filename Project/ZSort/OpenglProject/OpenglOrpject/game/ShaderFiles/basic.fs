uniform vec4 color;
uniform vec3 light;
varying vec3 _normals;
void main(void) {
    //float d = clamp(dot(light,vec3(1,1,1)),0.0,1.0) + 1.0;
    float d = clamp(dot(light,_normals),0.3,1);
    gl_FragColor = d* color;
}
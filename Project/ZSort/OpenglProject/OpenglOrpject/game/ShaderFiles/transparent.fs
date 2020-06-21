uniform vec4 color;
void main(void) {
    //float d = clamp(dot(light,vec3(1,1,1)),0.0,1.0) + 1.0;
    gl_FragColor = color;
}
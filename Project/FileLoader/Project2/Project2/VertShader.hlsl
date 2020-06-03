#define INLINE_TEXT(str) #str

INLINE_TEXT(
    attribute vec3 position;
    uniform mat4 MVP;
    void main(void) {
        vec4 v = vec4(position, 1.0);
        gl_Position = MVP * v;
    }
);
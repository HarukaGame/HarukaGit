#include "shader_loader.h"
#include "GL/glew.h"
#include "debug_print.h"

int CShaderLoader::CreateShaderProgram(const char* _vertSource, int _vertLength, const char* _fragSource, int _fragLength)
{
    //バーテックスシェーダーコンパイル
    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertShaderID, 1, &_vertSource, &_vertLength);
    glCompileShader(vertShaderID);

    GLint success = 0;
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        PRINT("バーテックスシェーダーのコンパイルに失敗しました");
    }

    //フラグメントシェーダーのコンパイル
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderID, 1, &_fragSource, &_fragLength);
    glCompileShader(fragShaderID);

    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &_fragLength);
    if (success == GL_FALSE) {
        PRINT("フラグメントシェーダーのコンパイルに失敗しました");

    }

    //プログラムオブジェクトの作成
    GLuint programID = glCreateProgram();
    if (programID == 0) {
        PRINT("プログラムオブジェクトの生成に失敗しました");
    }
    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);
    GLint attached;
    glGetProgramiv(programID, GL_ATTACHED_SHADERS, &attached);
    if (attached == GL_FALSE) {
        PRINT("シェーダーのアタッチに失敗しました");

    }
    //リンク
    GLint linked;
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        PRINT("シェーダーのリンクに失敗しました");

    }

    return programID;
}

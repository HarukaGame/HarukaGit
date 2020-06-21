#include "shader.h"
#include "GL/glew.h"
#include "debug_print.h"

bool CShader::SetUpUniform(int _programID)
{
    m_programID = _programID;
    glUseProgram(m_programID);

    //----------------------------------------------------------
    //uniform設定
    //----------------------------------------------------------

    m_uniformList[SHADER_UNIFORM_COLOR] = -1;
    m_uniformList[SHADER_UNIFORM_COLOR] = glGetUniformLocation(m_programID, "color");
    if (m_uniformList[SHADER_UNIFORM_COLOR] == -1) {
        PRINT("color uniformの取得に失敗しました");

    }

    m_uniformList[SHADER_UNIFORM_LIGHT] = -1;

    m_uniformList[SHADER_UNIFORM_LIGHT] = glGetUniformLocation(m_programID, "light");
    if (m_uniformList[SHADER_UNIFORM_LIGHT] == -1) {
        printf("light uniformの取得に失敗しました");

    }

    m_uniformList[SHADER_UNIFORM_MVP] = -1;

    m_uniformList[SHADER_UNIFORM_MVP] = glGetUniformLocation(m_programID, "MVP");
    if (m_uniformList[SHADER_UNIFORM_MVP] == -1) {
        printf("MVP uniformの取得に失敗しました");

    }

    //----------------------------------------------------------
    //attribute設定
    //----------------------------------------------------------

    m_attributeList[SHADER_ATTRIBUTE_POSITION] = glGetAttribLocation(m_programID, "position");
    if (m_attributeList[SHADER_ATTRIBUTE_POSITION] == -1) {
        PRINT("position attributeの取得に失敗しました\n");
    }
    m_attributeList[SHADER_ATTRIBUTE_NORMAL] = glGetAttribLocation(m_programID, "normals");
    if (m_attributeList[SHADER_ATTRIBUTE_NORMAL] == -1) {
        PRINT("normal attributeの取得に失敗しました\n");
    }


    return true;
}

bool CShader::SetUpUniform()
{
    glUseProgram(m_programID);

    //----------------------------------------------------------
    //uniform設定
    //----------------------------------------------------------

    m_uniformList[SHADER_UNIFORM_COLOR] = -1;
    m_uniformList[SHADER_UNIFORM_COLOR] = glGetUniformLocation(m_programID, "color");
    if (m_uniformList[SHADER_UNIFORM_COLOR] == -1) {
        PRINT("color uniformの取得に失敗しました");

    }

    m_uniformList[SHADER_UNIFORM_LIGHT] = -1;

    m_uniformList[SHADER_UNIFORM_LIGHT] = glGetUniformLocation(m_programID, "light");
    if (m_uniformList[SHADER_UNIFORM_LIGHT] == -1) {
        printf("light uniformの取得に失敗しました");

    }

    m_uniformList[SHADER_UNIFORM_MVP] = -1;

    m_uniformList[SHADER_UNIFORM_MVP] = glGetUniformLocation(m_programID, "MVP");
    if (m_uniformList[SHADER_UNIFORM_MVP] == -1) {
        printf("MVP uniformの取得に失敗しました");

    }

    //----------------------------------------------------------
    //attribute設定
    //----------------------------------------------------------

    m_attributeList[SHADER_ATTRIBUTE_POSITION] = glGetAttribLocation(m_programID, "position");
    if (m_attributeList[SHADER_ATTRIBUTE_POSITION] == -1) {
        PRINT("position attributeの取得に失敗しました\n");
    }
    m_attributeList[SHADER_ATTRIBUTE_NORMAL] = glGetAttribLocation(m_programID, "normals");
    if (m_attributeList[SHADER_ATTRIBUTE_NORMAL] == -1) {
        PRINT("normal attributeの取得に失敗しました\n");
    }


    return true;
}

int CShader::GetProgramID()const
{
	return m_programID;
}

int CShader::GetUniform(SHADER_UNIFORM _uniform) const
{
    return m_uniformList[_uniform];
}

int CShader::GetAttribute(SHADER_ATTRIBUTE _attribute) const
{
    return m_attributeList[_attribute];
}

void CShader::CreateShaderProgram(const char* _vertSource, int _vertLength, const char* _fragSource,int _fragLength)
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
    m_programID = glCreateProgram();
    if (m_programID == 0) {
        PRINT("プログラムオブジェクトの生成に失敗しました");
    }
    glAttachShader(m_programID, vertShaderID);
    glAttachShader(m_programID, fragShaderID);
    GLint attached;
    glGetProgramiv(m_programID, GL_ATTACHED_SHADERS, &attached);
    if (attached == GL_FALSE) {
        PRINT("シェーダーのアタッチに失敗しました");

    }
    //リンク
    GLint linked;
    glLinkProgram(m_programID);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        PRINT("シェーダーのリンクに失敗しました");

    }

    if (SetUpUniform() == false) {
        PRINT("ユニフォームセットアップに失敗しました");
    }
}

void CShader::SetTransparent(const bool _value)
{
    m_transparent = _value;
}

bool CShader::GetTransparent() const
{
    return m_transparent;
}

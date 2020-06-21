#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__
#include <Windows.h>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600




//#include "glm/matrix.hpp"

typedef unsigned int GLuint;
class CMesh;
class CShader;
class CBuffer;

class CRenderer {
public:
	bool Initialize(HWND _hwnd);
	void StartDisplay();
	void MeshDraw(CBuffer* _buffer,const CShader* _shader, glm::mat4& modelMat);
	void Release();


	void SetLight(const CShader* _shader, const float _x, const float _y, const float _z);
	void SetColor(const CShader* _shader, const float _r, const float _g, const float _b, const float _a);

	//const char* ReadShaderCode(const char* filename, const char* code);
	
private:
	glm::mat4 GetModelMatirix(glm::vec3 trans, glm::vec3 rotate, glm::vec3 scale);
	glm::mat4 GetViewMatirix(glm::vec3 camera, glm::vec3 target, glm::vec3 up, bool inverseZ = false);
	glm::mat4 GetViewMatirix(glm::vec3 trans, glm::vec3 rotate);
	glm::mat4 GetTransMatrix(glm::vec3 trans);
	glm::mat4 GetRotateMatrix(glm::vec3 rotate);
	glm::mat4 GetScaleMatrix(glm::vec3 scale);
	glm::mat4 GetProjectionMatrix(float _angle, float _aspect, float _far, float _near);
	//正規化デバイス座標からスクリーン座標への変換
	glm::mat4 GetViewPortMatrix(float _width, float hwight);
	void GLRelease();

	



	HWND m_hwnd;
	HDC m_hdc;
	HGLRC m_glrc;
};


#endif // !__RENDERER_H__
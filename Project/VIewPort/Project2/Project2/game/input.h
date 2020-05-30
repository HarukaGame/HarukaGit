#pragma once
#include <windows.h>

typedef unsigned char BYTE;
typedef struct tagPOINT POINT;

/**
	@class Input
	@brief ���͂��Ǘ�����N���X
*/
class Input {

	/*! �R���X�g���N�^*/
	private:Input();

	/*! @brief Input�N���X�𐶐�����֐�
		@return ���� Input�N���X�̃C���X�^���X,���s NULL
		@note �A�v���P�[�V�����J�n���Ɉ�x�������s����
	*/
	public:static Input* CreateInstance();

	public:static void SetWnd(HWND _hwnd);


	/*! @brief �C���X�^���X���폜����֐�
		@note �A�v���P�[�V�����I�����Ɏ��s����
	*/
	public:void static DestroyInstance();


	/*! @brief ���͂�~�ς���֐�
		@note ���͂��ꂽ�L�[���d���Ȃ��œo�^���Ă���
	*/
	public:void static StackInput();

	/*! @brief ���͂̒~�ς��J������֐�
	*/
	public:void static ReleaseInput();

	/*! @brief �L�[��������Ă��邩�ǂ���
		@param int key ���ׂ�L�[
	*/
	public:bool static GetKey(const int key);


	/*! @brief �L�[��������n�߂����ǂ���
		@param int key ���ׂ�L�[
	*/
	public:bool static GetKeyDown(const int key);


	/*! @brief �L�[�������ꂽ���ǂ���
		@param int key ���ׂ�L�[
		@param int key ���ׂ�L�[
	*/
	public:bool static GetKeyUp(const int key);

	public:POINT static GetMousePosition();

	public:float static GetMouseWheel();

	#if DEBUG_MODE
	/*! @brief �Ώۂ̃L�[�̏�Ԃ�\��
		@param int key ���ׂ�L�[
	*/
	public:void static ShowInputState(BYTE);
	#endif
};


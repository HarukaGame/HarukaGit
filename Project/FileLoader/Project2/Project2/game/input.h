#pragma once
#include <windows.h>

typedef unsigned char BYTE;
typedef struct tagPOINT POINT;

/**
	@class Input
	@brief 入力を管理するクラス
*/
class Input {

	/*! コンストラクタ*/
	private:Input();

	/*! @brief Inputクラスを生成する関数
		@return 成功 Inputクラスのインスタンス,失敗 NULL
		@note アプリケーション開始時に一度だけ実行する
	*/
	public:static Input* CreateInstance();

	public:static void SetWnd(HWND _hwnd);


	/*! @brief インスタンスを削除する関数
		@note アプリケーション終了時に実行する
	*/
	public:void static DestroyInstance();


	/*! @brief 入力を蓄積する関数
		@note 入力されたキーを重複なしで登録していく
	*/
	public:void static StackInput();

	/*! @brief 入力の蓄積を開放する関数
	*/
	public:void static ReleaseInput();

	/*! @brief キーが押されているかどうか
		@param int key 調べるキー
	*/
	public:bool static GetKey(const int key);


	/*! @brief キーが押され始めたかどうか
		@param int key 調べるキー
	*/
	public:bool static GetKeyDown(const int key);


	/*! @brief キーが離されたかどうか
		@param int key 調べるキー
		@param int key 調べるキー
	*/
	public:bool static GetKeyUp(const int key);

	public:POINT static GetMousePosition();

	public:float static GetMouseWheel();

	#if DEBUG_MODE
	/*! @brief 対象のキーの状態を表示
		@param int key 調べるキー
	*/
	public:void static ShowInputState(BYTE);
	#endif
};


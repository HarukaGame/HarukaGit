// CreateVector.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "my_vector.h"

class MyClass {
private:
    const char* m_text = "";
public:
    MyClass(){}
    MyClass(const char* text) {
        m_text = text;
    }
    void SetText(const char* text) {
        m_text = text;
    }
    void Print() {
        printf("%s\n",m_text);
    }
};

void FooA() {
    CVector<MyClass> a;
    a.PushBack(MyClass("a"));
    a.PushBack(MyClass("b"));
    a.PushBack(MyClass("c"));
    a.PushBack(MyClass("d"));
    a.PushBack(MyClass("e"));
    a.PushBack(MyClass("f"));
    a.Insert(MyClass("Z"), 1);
    a.Erace(0);

    for (CVector<MyClass>::iterator it = a.begin(); it != a.end(); it++) {
        it->Print();
    }

    while (a.begin() != a.end()) {
        a.PopBack();
    }
}

void FooB() {
    CVector<MyClass*> b;
    b.PushBack(new MyClass("a"));
    b.PushBack(new MyClass("b"));
    b.PushBack(new MyClass("c"));
    b.PushBack(new MyClass("d"));
    b.PushBack(new MyClass("e"));
    b.PushBack(new MyClass("f"));
    b.Insert(new MyClass("Z"), 1);
    delete b.Erace(0);

    for (CVector<MyClass*>::iterator it = b.begin(); it != b.end(); it++) {
        (*it)->Print();
    }

    while (b.begin() != b.end()) {
        delete b.PopBack();
    }
}

void FooC() {
    CVector<int> c;
    c.PushBack(1);
    c.PushBack(2);
    c.PushBack(3);
    c.PushBack(4);
    c.PushBack(5);

    for (CVector<int>::iterator it = c.begin(); it != c.end(); it++){
        printf("%d\n",*it);
    }
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    FooA();
    FooB();
    FooC();
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します

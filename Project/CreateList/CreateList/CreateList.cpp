// CreateList.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "my_list.h"

class Test {
private:
    int value = 0;
public:
    Test(int n) { value = n; }
    void Show() { std::cout << value; }
};

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    CList<Test*> a;
    a.PushBack(new Test(1));
    a.PushBack(new Test(2));
    a.PushBack(new Test(3));
    a.PushBack(new Test(4));

    for (CList<Test*>::iterator iter = a.Begin(); iter != a.End(); iter=iter+1) {
        (*iter)->Show();
    }
    std::cout << std::endl;

    CList<Test> b;
    b.PushBack(Test(5));
    b.PushBack(Test(6));
    b.PushBack(Test(7));
    b.PushBack(Test(8));

    for (CList<Test>::iterator iter = b.Begin(); iter != b.End();iter++) {
        iter->Show();
    }
    while (a.Empty() == false) {
        delete a.PopBack();
    }
}


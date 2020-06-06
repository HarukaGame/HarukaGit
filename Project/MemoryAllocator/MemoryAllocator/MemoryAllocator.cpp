// MemoryAllocator.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include <iostream>
#include <chrono>
#include <set>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

// 実験的なメモリアロケータ、スレッドセーフではありません
// @param <T> 要素のタイプ
// @param <MinElements> 一度に確保する最小の要素の数 
template <class T, size_t MinElements = 100>
class my_allocator {
    // メモリブロック
    struct mem_block {
        size_t allocated; // 確保した要素の数
        size_t used; // 確保された要素の数
        size_t deleted; // 開放された要素の数
        char elements[]; // 要素の配列、長さは不定
    };
    // メモリブロックのポインタ集合、ソード済み
    std::set<mem_block*> mem_blocks;
    // 最後に確保されたメモリブロックのポインタ
    mem_block* last_block;

public:
    // 型定義
    using value_type = T;

    // リバインド定義
    template <class U>
    struct rebind { typedef my_allocator<U, MinElements> other; };

    // コンストラクタ
    my_allocator() : mem_blocks(), last_block(nullptr) {}

    // コピーコンストラクタ、メンバーはすべてコピーしません
    my_allocator(const my_allocator&) : my_allocator() {};
    void operator =(const my_allocator&) = delete;

    // デストラクタ
    ~my_allocator() {
        for (mem_block* ptr : this->mem_blocks) {
            ::operator delete(ptr);
        }
        this->mem_blocks.clear();
        this->last_block = nullptr;
    }

    // メモリを割り当てます
    T* allocate(size_t num, const void* hint = nullptr) {
        // 最後に確保されたメモリブロックから確保できる要素の数を取得します
        // std::cout << "allocate: " << num << std::endl;
        size_t unused = 0;
        if (this->last_block)
            unused = this->last_block->allocated - this->last_block->used;
        // 確保できる要素の数が十分な場合はメモリブロックから確保します
        if (unused >= num) {
            size_t index = this->last_block->used * sizeof(T);
            this->last_block->used += num;
            return reinterpret_cast<T*>(&this->last_block->elements[index]);
        }
        // 確保できる要素の数が足りない場合は新たなメモリブロックを確保します
        size_t allocated_new = std::max(num, MinElements);
        mem_block* block_new = reinterpret_cast<mem_block*>(
            ::operator new(sizeof(mem_block) + allocated_new * sizeof(T)));
        if (!block_new)
            return nullptr;
        block_new->allocated = allocated_new;
        block_new->used = num;
        block_new->deleted = 0;
        this->mem_blocks.insert(block_new); // 集合に加わります
        // 要素がすべて使われた場合はメモリブロックをlast_blockに設定しません
        if (block_new->used < block_new->allocated)
            this->last_block = block_new;
        return reinterpret_cast<T*>(block_new->elements);
    }

    // メモリを開放します
    void deallocate(T* p, size_t num) {
        // ポインタが対応するメモリブロックを探します
        // std::cout << "deallocate: " << num << std::endl;
        intptr_t p_min = reinterpret_cast<intptr_t>(p);
        intptr_t p_sub = sizeof(mem_block) + MinElements * sizeof(T) - 1;
        p_min = (p_min > p_sub) ? (p_min - p_sub) : 0;
        auto block_it = this->mem_blocks.lower_bound(
            reinterpret_cast<mem_block*>(p_min));
        if (block_it == this->mem_blocks.end()) {
            std::cerr << "get mem block failed" << std::endl;
            return;
        }
        // 確保した要素がすべて開放された場合はメモリブロックを開放します
        mem_block* block_ptr = (*block_it);
        block_ptr->deleted += num;
        if (block_ptr == this->last_block) {
            // メモリブロックがlast_blockだった場合はallocatedと比較します
            if (block_ptr->deleted >= block_ptr->allocated) {
                this->last_block = nullptr;
                ::operator delete(block_ptr);
                this->mem_blocks.erase(block_it);
            }
        }
        else if (block_ptr->deleted >= block_ptr->used) {
            // メモリブロックがlast_blockでない場合はusedと比較します
            ::operator delete(block_ptr);
            this->mem_blocks.erase(block_it);
        }
    }

    // デバッグ用の情報をコンソールに出力します
    void debug_print() {
        std::cout << "mem blocks total: " << this->mem_blocks.size() << std::endl;
        for (mem_block* ptr : this->mem_blocks) {
            std::cout << "mem blocks " << reinterpret_cast<intptr_t>(ptr);
            std::cout << " a " << ptr->allocated;
            std::cout << " u " << ptr->used;
            std::cout << " d " << ptr->deleted << " [ ";
            std::cout << std::hex;
            for (size_t i = 0, j = ptr->used * sizeof(T); i < j; ++i) {
                std::cout << +ptr->elements[i] << " ";
            }
            std::cout << std::oct << "]" << std::endl;
        }
    }
};

// ベンチマーク用の関数
template <class T>
std::chrono::milliseconds benchmark(const T& function) {
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    function();
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now() - start);
}

// テスト用のクラス
class my_class {
    int value;
public:
    my_class(int value) : value(value) {
        std::cout << "call my_class constructor: " << this->value << std::endl;
    }
    my_class(const my_class& obj) {
        std::cout << "call my_class copy constructor: " << obj.value << std::endl;
        this->value = obj.value;
    }
    ~my_class() {
        std::cout << "call my_class destructor: " << this->value << std::endl;
    }
    int get_value() const { return value; }
};
int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // デバッグサンプル
    my_allocator<int, 4> allocator;
    int* a = allocator.allocate(1);
    a[0] = 1;
    int* b = allocator.allocate(2);
    b[0] = 2;
    b[1] = 2;
    int* c = allocator.allocate(3);
    c[0] = 3;
    c[1] = 3;
    c[2] = 3;
    int *d = allocator.allocate(1);
    d[0] = 1;
    allocator.debug_print();
    std::cout << "dealloc a, b" << std::endl;
    allocator.deallocate(a, 1);
    allocator.deallocate(b, 2);
    allocator.debug_print();
    std::cout << "dealloc c" << std::endl;
    allocator.deallocate(c, 3);
    allocator.debug_print();
    std::cout << "dealloc d" << std::endl;
    allocator.deallocate(d, 1);
    allocator.debug_print();
    //std::vector<my_class, my_allocator<my_class>> test_array;
    //test_array.push_back(1);
    //test_array.push_back(2);
    //test_array.emplace_back(3);
    //for (const my_class& obj : test_array) {
    //    std::cout << obj.get_value() << std::endl;
    //}

    // ベンチマーク
    //std::cout << "benchmark default allocator" << std::endl;
    //std::cout << benchmark([] {
    //    std::set<int> int_set;
    //    for (size_t i = 0; i < 10000000; ++i) {
    //        int_set.insert(i);
    //    }
    //    // std::this_thread::sleep_for(std::chrono::seconds(15));
    //    int_set.clear();
    //    }).count() << std::endl;
    //    std::cout << "benchmark my allocator" << std::endl;
    //    std::cout << benchmark([] {
    //        std::set<int, std::less<int>, my_allocator<int, 1000>> int_set;
    //        for (size_t i = 0; i < 10000000; ++i) {
    //            int_set.insert(i);
    //        }
    //        // std::this_thread::sleep_for(std::chrono::seconds(15));
    //        int_set.clear();
    //        }).count() << std::endl;


            return 0;
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

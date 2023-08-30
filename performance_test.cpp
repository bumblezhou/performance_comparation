
#include <iostream>
#include <cstring>
#include <limits>
#include <chrono>
#include <string>
#include <regex>

using namespace std;

struct test_struct {
    int size;
    char data[1024];
};

void test_send_pointer_addr(const uint32_t max_test_count, const void* p_test_struct) {
    for (int i = 0; i < max_test_count; i++) {
        test_struct * p_t{static_cast<test_struct *>(const_cast<void*>(p_test_struct))};
        // cout << "Static cast -> size:" << p_t->size << ", data:" << p_t->data << endl;
        // cout << p_t->size << "," << p_t->data[128] << " ";
    }
    // cout << endl;
}

void test_send_memory_copy(const uint32_t max_test_count, const void* p_test_struct) {
    for (int i = 0; i < max_test_count; i++) {
        test_struct t{0};
        (void)memcpy(&t, p_test_struct, sizeof(test_struct));
        // cout << "Memory copy -> size:" << t.size << ", data:" << t.data << endl;
        // cout << t.size << "," << t.data[128] << " ";
    }
    // cout << endl;
}

void test_send_struct_ref(const uint32_t max_test_count, test_struct * p_test_struct) {
    for (int i = 0; i < max_test_count; i++) {
        test_struct * p_t{p_test_struct};
        // cout << "Struct ref -> size:" << p_t->size << ", data:" << p_t->data << endl;
        // cout << p_t->size << "," << p_t->data[128] << " ";
    }
    // cout << endl;
}

int main(int argc, char** argv) {

    if(argc != 2) {
        printf("invalid arguments!\n");
        printf("Usage:\n");
        printf("./performance_test --max_test_count=100\n");
        return 1;
    }

    std::string argv1 {argv[1]};

    std::regex argv_pattern("^--max_test_count=\\d+$");
    if(!std::regex_search(argv1, argv_pattern)) {
        printf("invalid arguments!\n");
        printf("Usage:\n");
        printf("./performance_test --max_test_count=100\n");
        return 1;
    }

    // cout << "argv[1]:" << argv1 << endl;
    std::string argv_value {argv1.replace(argv1.begin(), argv1.begin() + 17, "")};
    int i_argv_value{stoi(argv_value)};
    // cout << "argv[1]->value:" << argv_value << endl;

    test_struct t {12, "Hello world Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World"};
    
    char p_t[sizeof(test_struct)];
    (void)memcpy((&p_t)[0], &t, sizeof(test_struct));
    
    const uint32_t max_test_count{i_argv_value > 0 ? i_argv_value : 100U};
    
    printf("test_send_pointer_addr testing ...\n");
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    test_send_pointer_addr(max_test_count, (&p_t)[0]);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    printf("test_send_pointer_addr testing ...\n");
    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
    test_send_memory_copy(max_test_count, (&p_t)[0]);
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    
    printf("test_send_struct_ref testing ...\n");
    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    test_send_struct_ref(max_test_count, &t);
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    
    std::cout << "Static cast Time elapsed = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Memory copy Time elapsed = " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << "[µs]" << std::endl;
    std::cout << "Struct ref Time elapsed = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << "[µs]" << std::endl;

    return 0;
}


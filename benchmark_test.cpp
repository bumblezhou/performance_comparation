#include <benchmark/benchmark.h>
#include <cstring>
#include <iostream>
using namespace std;

struct test_struct {
    int size;
    char data[1024];
    // char data[128];
};

// static void test_send_pointer_addr(void* p_test_struct) {
static void test_send_pointer_addr(benchmark::State& state, const void* p_test_struct) {
    for (auto _ : state) {
        test_struct * p_t{static_cast<test_struct *>(const_cast<void *>(p_test_struct))};
        // cout << "Static cast -> size:" << p_t->size << ", data:" << p_t->data << endl;
        // cout << p_t->size << "," << p_t->data[128] << " ";
    }
    // cout << endl;
}

// static void test_send_memory_copy(void* p_test_struct) {
static void test_send_memory_copy(benchmark::State& state, const void* p_test_struct) {
    for (auto _ : state) {
        test_struct t{0};
        (void)memcpy(&t, p_test_struct, sizeof(test_struct));
        // cout << "Memory copy -> size:" << t.size << ", data:" << t.data << endl;
        // cout << t.size << "," << t.data[128] << " ";
    }
    // cout << endl;
}

// static void test_send_struct_ref(test_struct * p_test_struct) {
static void test_send_struct_ref(benchmark::State& state, const test_struct* p_test_struct) {
    for (auto _ : state) {
        const test_struct * p_t{p_test_struct};
        // cout << "Struct ref -> size:" << p_t->size << ", data:" << p_t->data << endl;
        // cout << p_t->size << "," << p_t->data[128] << " ";
    }
    // cout << endl;
}

test_struct t {12, "Hello world Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World"};
// test_struct t {12, "Hello world Hello World Hello World Hello"};
char p_t[sizeof(test_struct)];

// Register the function as a benchmark

// Define another benchmark

// BENCHMARK_MAIN();

int main(int argc, char** argv)
{
   (void)memcpy((&p_t)[0], &t, sizeof(test_struct));

   benchmark::RegisterBenchmark("test_send_pointer_addr", test_send_pointer_addr, (&p_t)[0]);
   benchmark::RegisterBenchmark("test_send_memory_copy", test_send_memory_copy, (&p_t)[0]);
   benchmark::RegisterBenchmark("test_send_struct_ref", test_send_struct_ref, &t);

   ::benchmark::Initialize(&argc, argv);
   ::benchmark::RunSpecifiedBenchmarks();
}
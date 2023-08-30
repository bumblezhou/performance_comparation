# A simple project for c/c++ performance comparation

## Handwritten code
```bash
g++ performance_test.cpp -std=c++11 -o performance_test

./performance_test --max_test_count=10000
```

## Use google benchmark
```bash
g++ benchmark_test.cpp -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o benchmark_test

./benchmark_test --benchmark_min_time=10000x
```
Reference: 

https://google.github.io/benchmark/

https://github.com/google/benchmark

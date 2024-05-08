# A simple project for c/c++ performance comparation

## Handwritten code
```bash
g++ performance_test.cpp -std=c++11 -o performance_test

./performance_test --max_test_count=10000
```

## Prepare(installation) for google benchmark
```bash
git clone https://github.com/google/benchmark.git
cd benchmark
cmake -E make_directory "build"
cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../
cmake --build "build" --config Release
sudo cmake --build "build" --config Release --target install
```

## Use google benchmark
```bash
g++ benchmark_test.cpp -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o benchmark_test

./benchmark_test --benchmark_min_time=10000x

./benchmark_test
```
Reference: 

https://google.github.io/benchmark/

https://github.com/google/benchmark

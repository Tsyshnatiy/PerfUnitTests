#include <benchmark/benchmark.h>

#include <algorithm>
#include <numeric>
#include <memory>
#include <list>

int fibonacci(int n)
{
    int n1 = 0;
    int n2 = 1;
    int result = n1;
    result = n == 2 ? n2 : result;

    for (int i = 2 ; i < n ; ++i)
    {
        result = n1 + n2;
        n1 = n2;
        n2 = result;
    }

    return result;
}

auto doubleToStringConversionTest(int count)
{
	std::vector<double> inputNumbers(count);
	std::vector<std::string> outNumbers;

	std::iota(std::begin(inputNumbers), std::end(inputNumbers), 0.12345);
	for (auto &num : inputNumbers) {
		outNumbers.push_back(std::to_string(num));
  }
	return outNumbers;
}

static void BM_vector_push_back(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<int> v;
    v.reserve(1);
    auto data = v.data();           // Allow v.data() to be clobbered. Pass as non-const
    benchmark::DoNotOptimize(data); // lvalue to avoid undesired compiler optimizations
    v.push_back(42);
    benchmark::ClobberMemory(); // Force 42 to be written to memory.
  }
}

static void BM_string_accumulate(benchmark::State& state) {
  for (auto _ : state) {
    std::string s;        // Allow v.data() to be clobbered. Pass as non-const
    benchmark::DoNotOptimize(s); // lvalue to avoid undesired compiler optimizations
    for (int i = 0 ; i < 100 ; ++i) {
        s += s;
        benchmark::ClobberMemory(); // Force 42 to be written to memory.
    }
  }
}

static void BM_fibonacci(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(fibonacci(10000));
  }
}

static void BM_doubleToString(benchmark::State& state) {
	while (state.KeepRunning()) {
		benchmark::DoNotOptimize(doubleToStringConversionTest(state.range(0)));
	}
}

struct A
{
    float f = 0;
    double l = 0;
};

static void BM_uptr(benchmark::State& state) {
  for (auto _ : state) {
    auto number = std::make_unique<A>();
    benchmark::DoNotOptimize(number); // lvalue to avoid undesired compiler optimizations
    benchmark::ClobberMemory(); // Force 42 to be written to memory.
  }
}

static void BM_shared_ptr(benchmark::State& state) {
  for (auto _ : state) {
    auto number = std::make_shared<A>();
    benchmark::DoNotOptimize(number); // lvalue to avoid undesired compiler optimizations
    benchmark::ClobberMemory(); // Force 42 to be written to memory.
  }
}

static void BM_list_reverse(benchmark::State& state) {
    std::list<int> l;
    for (int i = 0 ; i < state.range(0) ; ++i) {
        l.push_front(i);
    }
    for (auto _ : state) {
        l.reverse();
        benchmark::DoNotOptimize(l); // lvalue to avoid undesired compiler optimizations
        benchmark::ClobberMemory(); // Force 42 to be written to memory.
    }
}

BENCHMARK(BM_vector_push_back);
BENCHMARK(BM_string_accumulate);
BENCHMARK(BM_fibonacci);
BENCHMARK(BM_doubleToString) -> Arg(10) -> Arg(100) -> Arg(1000) -> Arg(10000) -> Arg(100000);
BENCHMARK(BM_uptr);
BENCHMARK(BM_shared_ptr);
BENCHMARK(BM_list_reverse) -> Arg(10000) -> Arg(100000) -> Arg(1000000);

// Run the benchmark
BENCHMARK_MAIN();
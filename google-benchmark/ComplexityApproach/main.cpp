#include <benchmark/benchmark.h>

#include <list>

static void BM_StringCompare(benchmark::State& state) {
  std::string s1(state.range(0), '-');
  std::string s2(state.range(0), '-');

  for (auto _ : state) {
    auto comparison_result = s1.compare(s2);
    benchmark::DoNotOptimize(comparison_result);
  }
  state.SetComplexityN(state.range(0));
}

static void BM_BinarySearch(benchmark::State& state) {
  std::vector<int> v;
  v.reserve(state.range(0));
  for (int i = 0 ; i < state.range(0) ; ++i) {
    v.push_back(i);
  }

  for (auto _ : state) {
    auto f = std::binary_search(std::begin(v), std::end(v), state.range(0) / 3);
    benchmark::DoNotOptimize(v);
    benchmark::DoNotOptimize(f);
    benchmark::ClobberMemory();
  }

  state.SetComplexityN(state.range(0));
}

static void BM_ListReverse(benchmark::State& state) {
  std::list<int> l;
  for (int i = 0 ; i < state.range(0) ; ++i) {
    l.push_front(i);
  }

  for (auto _ : state) {
    l.reverse();
    benchmark::DoNotOptimize(l);
    benchmark::ClobberMemory();
  }

  state.SetComplexityN(state.range(0));
}

static void BM_Search(benchmark::State& state) {
  std::vector<int> v;
  v.reserve(state.range(0));
  for (int i = 0 ; i < state.range(0) ; ++i) {
    v.push_back(i);
  }

  for (auto _ : state) {
    auto it = std::find(std::begin(v), std::end(v), state.range(0) / 3);
    benchmark::DoNotOptimize(v);
    benchmark::DoNotOptimize(it);
    benchmark::ClobberMemory();
  }

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_StringCompare)
    ->RangeMultiplier(2)->Range(1<<10, 1<<18)->Complexity(benchmark::oN);
BENCHMARK(BM_BinarySearch)
    ->RangeMultiplier(2)->Range(1<<18, 1<<24)->Complexity(benchmark::oLogN);
BENCHMARK(BM_ListReverse)
    ->RangeMultiplier(2)->Range(1<<10, 1<<18)->Complexity(benchmark::oN);
BENCHMARK(BM_Search)
    ->RangeMultiplier(2)->Range(1<<18, 1<<24)->Complexity(benchmark::oLogN);


BENCHMARK_MAIN();
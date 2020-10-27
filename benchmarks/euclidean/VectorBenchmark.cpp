#include <benchmark/benchmark.h>
#include <euclidean/Vector.hpp>

#define BENCHMARK_VECTORS(benchmark) \
BENCHMARK_TEMPLATE(benchmark, 1); \
BENCHMARK_TEMPLATE(benchmark, 2); \
BENCHMARK_TEMPLATE(benchmark, 3); \
BENCHMARK_TEMPLATE(benchmark, 4)

#define BENCHMARK_VECTOR_BINARY(name, operation) \
template<std::size_t N> \
void BM_Vector##name(benchmark::State & state) { \
    auto v1 = Vector<N>::random(); \
    auto v2 = Vector<N>::random(); \
    for (auto _ : state) { \
        benchmark::DoNotOptimize(v1 operation v2); \
    } \
} \
BENCHMARK_VECTORS(BM_Vector##name)

BENCHMARK_VECTOR_BINARY(Addition, +);
BENCHMARK_VECTOR_BINARY(Subtraction, -);
BENCHMARK_VECTOR_BINARY(Multiplication, *);
BENCHMARK_VECTOR_BINARY(Division, /);

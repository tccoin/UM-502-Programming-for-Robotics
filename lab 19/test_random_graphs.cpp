#include <iomanip>
#include <chrono>

#include "lab19_fix_code.cpp"
// #include "lab19_fix_code_fixed.cpp"

void print_stats(unsigned long long n_cyclic, unsigned long long i)
{
    std::cout << std::setprecision(3) << static_cast<double>(n_cyclic) / i * 100 << "\% graphs had cycles\n";
}

int main()
{
    srand(0);

    bool print{false};
    unsigned long long n_cyclic = 0;
    unsigned long long n = 50'000;
    //   unsigned long long n = 1;
    unsigned int n_vertices = 10'000;
    unsigned int n_edges = 2'000;

    auto const start = std::chrono::steady_clock::now();

    for (unsigned long long i = 0; i < n; ++i)
    {
        if (i % 1000 == 0 && i > 0)
        {
            print_stats(n_cyclic, i);
        }

        // This graph should have a cycle
        Graph g(n_vertices);
        for (auto edge_idx{0u}; edge_idx < n_edges; ++edge_idx)
        {
            auto const parent = rand() % n_vertices;
            auto const child = rand() % n_vertices;
            g.addEdge(parent, child);
        }

        if (g.isCyclic())
        {
            ++n_cyclic;
        }
    }

    auto const end = std::chrono::steady_clock::now();
    auto const dt = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    print_stats(n_cyclic, n);

    std::cout << "took " << dt.count() << " seconds\n";

    return 0;
}
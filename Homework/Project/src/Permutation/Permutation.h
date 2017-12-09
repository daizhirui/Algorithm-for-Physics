#include <vector>
class Permutation
{
    int n;
    int m;
    std::vector<int> box;
    std::vector<int> per;
    bool final;
public:
    int count;
    Permutation(const int n, const int m);
    std::vector<int> pop();
    void restart();
};
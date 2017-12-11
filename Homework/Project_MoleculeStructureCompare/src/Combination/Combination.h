#include <vector>

class Combination
{
    int n;
    int m;

    std::vector<int> box;
    std::vector<int> com;
    void tidy(int);
public:
    int count;
    Combination(const int, const int);
    std::vector<int> pop();
    void restart();
};
#include <functional>
#include <iostream>
template <typename F>
struct DeferHelper
{
    DeferHelper(F &&f) : f_(std::move(f)) {}
    ~DeferHelper()
    {
        if (valid)
            f_();
    }
    DeferHelper(DeferHelper &&dh) : f_(std::move(dh.f_))
    {
        dh.valid = false;
    }
    DeferHelper(const DeferHelper &dh) = delete;
    DeferHelper &operator=(const DeferHelper &dh) = delete;
    F f_;
    bool valid = true;
};
template <typename F>
DeferHelper<F> Defer(F &&f)
{
    return std::move(f);
}
#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_0(x) DEFER_2(x, __COUNTER__)
#define Defer(expr) auto DEFER_0(temp) = Defer([&]() { expr })

int main()
{
    Defer(std::cout << "1111" << std::endl;);
    Defer(std::cout << "2222" << std::endl;);
    Defer(std::cout << "3333" << std::endl;);

    std::cout << "end main" << std::endl;

    return 0;
}

#include <string>
#include <ostream>
class LombokBaryCentricLombokTest {
 public:
    LombokBaryCentricLombokTest() = default;
    LombokBaryCentricLombokTest(
        float alpha,
        float beta,
        float gamma,
        std::string name
    );
 private:
    float alpha;
    float beta;
    float gamma;
    std::string name;
};
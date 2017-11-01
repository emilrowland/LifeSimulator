#include "catch.hpp"
#include "RandomGenerator.h"

TEST_CASE("RandomGenerator", "[RandomGenerator]"){
    SECTION("randomIntegers Length"){
        RandomGenerator random = RandomGenerator(1);
        std::vector<int> r = random.randomIntegers(0, 10, 25);
        CHECK(r.size() == 25);
    }
}

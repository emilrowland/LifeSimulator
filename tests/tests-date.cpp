#include "catch.hpp"
#include "Date.h"
#include <stdexcept>

TEST_CASE("Date", "[Date]"){
    Date refDate = Date(2017,10,27,12,10,10);

    SECTION("Dates"){
        CHECK_NOTHROW(Date(2017,1,31,23,59,59));
        CHECK_NOTHROW(Date(2017,2,28,23,59,59));
        CHECK_NOTHROW(Date(2017,3,31,23,59,59));
        CHECK_NOTHROW(Date(2017,4,30,23,59,59));
        CHECK_NOTHROW(Date(2017,5,31,23,59,59));
        CHECK_NOTHROW(Date(2017,6,30,23,59,59));
        CHECK_NOTHROW(Date(2017,7,31,23,59,59));
        CHECK_NOTHROW(Date(2017,8,31,23,59,59));
        CHECK_NOTHROW(Date(2017,9,30,23,59,59));
        CHECK_NOTHROW(Date(2017,10,31,23,59,59));
        CHECK_NOTHROW(Date(2017,11,30,23,59,59));
        CHECK_NOTHROW(Date(2017,12,31,23,59,59));

        CHECK_THROWS_AS(Date(2017,1,32,23,59,60), std::invalid_argument);
        CHECK_THROWS_AS(Date(2017,1,32,23,60,59), std::invalid_argument);
        CHECK_THROWS_AS(Date(2017,1,32,24,59,59), std::invalid_argument);
        CHECK_THROWS_AS(Date(2017,13,32,23,59,59), std::invalid_argument);
        CHECK_THROWS_WITH(Date(2017,1,32,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,2,29,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,3,32,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,4,31,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,5,32,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,6,31,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,7,32,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,8,32,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,9,31,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,10,32,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,11,31,23,59,59), "Not an valid Date!");
        CHECK_THROWS_WITH(Date(2017,12,32,23,59,59), "Not an valid Date!");
    }
    SECTION("Less than"){
        REQUIRE(Date(2017,10,27,12,10,9) < refDate);
        REQUIRE(Date(2017,10,27,12,9,10) < refDate);
        REQUIRE(Date(2017,10,27,11,10,10) < refDate);
        REQUIRE(Date(2017,10,26,12,10,10) < refDate);
        REQUIRE(Date(2017,9,27,12,10,10) < refDate);
        REQUIRE(Date(2016,10,27,12,10,10) < refDate);

        REQUIRE_FALSE(refDate < refDate);
        REQUIRE_FALSE(Date(2017,10,27,12,10,11) < refDate);
        REQUIRE_FALSE(Date(2017,10,27,12,11,10) < refDate);
        REQUIRE_FALSE(Date(2017,10,27,13,10,10) < refDate);
        REQUIRE_FALSE(Date(2017,10,28,12,10,10) < refDate);
        REQUIRE_FALSE(Date(2017,11,27,12,10,10) < refDate);
        REQUIRE_FALSE(Date(2018,10,27,12,10,10) < refDate);
    }
    SECTION("Less than or equal"){
        REQUIRE(refDate <= refDate);
        REQUIRE(Date(2017,10,27,12,10,9) <= refDate);
        REQUIRE(Date(2017,10,27,12,9,10) <= refDate);
        REQUIRE(Date(2017,10,27,11,10,10) <= refDate);
        REQUIRE(Date(2017,10,26,12,10,10) <= refDate);
        REQUIRE(Date(2017,9,27,12,10,10) <= refDate);
        REQUIRE(Date(2016,10,27,12,10,10) <= refDate);

        REQUIRE_FALSE(Date(2017,10,27,12,10,11) < refDate);
        REQUIRE_FALSE(Date(2017,10,27,12,11,10) < refDate);
        REQUIRE_FALSE(Date(2017,10,27,13,10,10) < refDate);
        REQUIRE_FALSE(Date(2017,10,28,12,10,10) < refDate);
        REQUIRE_FALSE(Date(2017,11,27,12,10,10) < refDate);
        REQUIRE_FALSE(Date(2018,10,27,12,10,10) < refDate);
    }
    SECTION("Equal"){
        REQUIRE(refDate == refDate);
        REQUIRE(Date(2017,10,27,12,10,9) == Date(2017,10,27,12,10,9));
        REQUIRE(Date(2017,10,27,12,9,10) == Date(2017,10,27,12,9,10));
        REQUIRE(Date(2017,10,27,11,10,10) == Date(2017,10,27,11,10,10));
        REQUIRE(Date(2017,10,26,12,10,10) == Date(2017,10,26,12,10,10));
        REQUIRE(Date(2017,9,27,12,10,10) == Date(2017,9,27,12,10,10));
        REQUIRE(Date(2016,10,27,12,10,10) == Date(2016,10,27,12,10,10));

        REQUIRE_FALSE(Date(2017,10,27,12,10,11) == refDate);
        REQUIRE_FALSE(Date(2017,10,27,12,11,10) == refDate);
        REQUIRE_FALSE(Date(2017,10,27,13,10,10) == refDate);
        REQUIRE_FALSE(Date(2017,10,28,12,10,10) == refDate);
        REQUIRE_FALSE(Date(2017,11,27,12,10,10) == refDate);
        REQUIRE_FALSE(Date(2018,10,27,12,10,10) == refDate);
    }
    SECTION("Tick"){
        Date date = Date(2017,12,31,23,59,58);
        SECTION("Default"){
            date.tick();
            REQUIRE(date == Date(2017,12,31,23,59,59));
            date.tick();
            REQUIRE(date == Date(2018,1,1,0,0,0));
        }
        SECTION("Custom tick duration"){
            date.tick(2);
            REQUIRE(date == Date(2018,1,1,0,0,0));
            date.tick();
            REQUIRE(date == Date(2018,1,1,0,0,1));
            date.tick(59);
            REQUIRE(date == Date(2018,1,1,0,1,0));
            date.tick(10);
            REQUIRE(date == Date(2018,1,1,0,1,10));
            date.tick(59);
            REQUIRE(date == Date(2018,1,1,0,2,9));
        }
    }
    SECTION("Add"){
        Date date = Date(2017,1,30,23,59,59);
        SECTION("Check days in month"){
            DeltaTime addDate = DeltaTime(0,0,5,0,0,1);
            date.add(addDate);
            CHECK(date == Date(2017,2,5,0,0,0));
            date = Date(2017,2,27,23,59,59);
            date.add(addDate);
            CHECK(date == Date(2017,3,5,0,0,0));
            date = Date(2017,3,30,23,59,59);
            date.add(addDate);
            CHECK(date == Date(2017,4,5,0,0,0));
            date = Date(2017,4,29,23,59,59);
            date.add(addDate);
            CHECK(date == Date(2017,5,5,0,0,0));
            date = Date(2017,5,30,23,59,59);
            date.add(addDate);
            CHECK(date == Date(2017,6,5,0,0,0));
            date = Date(2017,6,29,23,59,59);
            date.add(addDate);
            CHECK(date == Date(2017,7,5,0,0,0));
            date = Date(2017,7,30,23,59,59);
            date.add(addDate);
            CHECK(date == Date(2017,8,5,0,0,0));
            date = Date(2017,8,30,23,59,59);
            date.add(addDate);
            CHECK(date == Date(2017,9,5,0,0,0));
            date = Date(2017,9,29,23,59,59);
            date.add(addDate);
            CHECK(date == Date(2017,10,5,0,0,0));
            date = Date(2017,10,30,23,59,59);
            date.add(addDate);
            CHECK(date == Date(2017,11,5,0,0,0));
            date = Date(2017,12,30,23,59,59);
            date.add(addDate);
            CHECK(date == Date(2018,1,5,0,0,0));
        }
        SECTION("Basic addition"){
            date = Date(2017,12,31,23,59,59);
            date.add(DeltaTime(0,0,0,0,0,1));
            CHECK(date == Date(2018,1,1,0,0,0));
            date = Date(2017,12,31,23,59,59);
            date.add(DeltaTime(0,0,0,0,1,0));
            CHECK(date == Date(2018,1,1,0,0,59));
            date = Date(2017,12,31,23,59,59);
            date.add(DeltaTime(0,0,0,1,0,0));
            CHECK(date == Date(2018,1,1,0,59,59));
            date = Date(2017,12,31,23,59,59);
            date.add(DeltaTime(0,0,1,0,0,0));
            CHECK(date == Date(2018,1,1,23,59,59));
            date = Date(2017,12,31,23,59,59);
            date.add(DeltaTime(0,1,0,0,0,0));
            CHECK(date == Date(2018,1,31,23,59,59));
            date = Date(2017,12,31,23,59,59);
            date.add(DeltaTime(1,0,0,0,0,0));
            CHECK(date == Date(2018,12,31,23,59,59));
            date = Date(2017,1,31,23,59,59);
            date.add(DeltaTime(0,1,0,0,0,0));
            CHECK(date == Date(2018,3,3,23,59,59)); //Can't pass should probably use DeltaTime objects for addition.
        }
    }
    SECTION("toString"){
        REQUIRE(refDate.toString() == "2017-10-27 12:10:10");
        REQUIRE(Date(2020,9,9,9,9,9).toString() == "2020-9-9 9:9:9");
    }
}

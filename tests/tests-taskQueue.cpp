#include "catch.hpp"
#include "TaskQueue.h"

TEST_CASE( "TaskQueue", "[TaskQueue]" ) {
    TaskQueue<std::string> todoQueue = TaskQueue<std::string>(10);
    REQUIRE(todoQueue.empty());

    SECTION("Add task"){
        todoQueue.push("Task 1", 5);
        REQUIRE(todoQueue.top() == "Task 1");
        REQUIRE(!todoQueue.empty());
        REQUIRE(todoQueue.pop() == "Task 2");
        REQUIRE(todoQueue.empty());
    }
}

#include "catch.hpp"
#include "TaskQueue.h"

TEST_CASE("TaskQueue", "[TaskQueue]"){
    TaskQueue<std::string> todoQueue = TaskQueue<std::string>(10);

    SECTION("Empty"){
        REQUIRE(todoQueue.empty());
        todoQueue.push("Task 1", 5);
        REQUIRE(!todoQueue.empty());
    }
    SECTION("Pop empty"){
        REQUIRE(todoQueue.empty());
        CHECK_THROWS_AS(todoQueue.pop().empty(), std::domain_error);
    }
    SECTION("Add task"){
        todoQueue.push("Task 1", 5);
        todoQueue.push("Task 2", 1);
        REQUIRE(todoQueue.top() == "Task 2");
        REQUIRE(!todoQueue.empty());
        REQUIRE(todoQueue.pop() == "Task 2");
        REQUIRE(todoQueue.top() == "Task 1");
        REQUIRE(todoQueue.pop() == "Task 1");
        REQUIRE(todoQueue.empty());
    }
    SECTION("Task order"){
        todoQueue.push("Task 1", 1);
        todoQueue.push("Task 2", 1);
        todoQueue.push("Task 3", 2);
        todoQueue.push("Task 4", 1);
        todoQueue.push("Task 5", 1);
        REQUIRE(todoQueue.pop() == "Task 1");
        REQUIRE(todoQueue.pop() == "Task 2");
        REQUIRE(todoQueue.pop() == "Task 4");
        REQUIRE(todoQueue.pop() == "Task 5");
        REQUIRE(todoQueue.pop() == "Task 3");
        REQUIRE(todoQueue.empty());
    }
    SECTION("Change priority"){
        todoQueue.push("Task 1", 5);
        todoQueue.push("Task 2", 1);
        SECTION("Simple"){
            todoQueue.changePriority("Task 1", 1);
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.pop() == "Task 2");
            REQUIRE(todoQueue.empty());
        }
        SECTION("Negative priority no dependence"){
            todoQueue.changePriority("Task 1", -1);
            REQUIRE(todoQueue.pop() == "Task 2");
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.empty());
        }
        SECTION("Negative priority on dependence"){
            todoQueue.addDependence("Task 1", "Task 3", 1);
            todoQueue.changePriority("Task 1", -1);
            REQUIRE(todoQueue.pop() == "Task 3");
            REQUIRE(todoQueue.pop() == "Task 2");
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.empty());
        }

    }
    SECTION("Add dependence on top"){
        todoQueue.push("Task 1", 5);
        todoQueue.push("Task 2", 1);
        todoQueue.addDependenceTop("Task 3", 10);
        REQUIRE(todoQueue.pop() == "Task 3");
        REQUIRE(todoQueue.pop() == "Task 2");
        REQUIRE(todoQueue.pop() == "Task 1");
        REQUIRE(todoQueue.empty());
    }
    SECTION("Add dependence"){
        todoQueue.push("Task 1", 5);
        todoQueue.push("Task 2", 1);
        todoQueue.addDependence("Task 1", "Task 3", 1);
        REQUIRE(todoQueue.pop() == "Task 3");
        REQUIRE(todoQueue.pop() == "Task 2");
        REQUIRE(todoQueue.pop() == "Task 1");
        REQUIRE(todoQueue.empty());
    }
    SECTION("Check uniqueness"){
        todoQueue.push("Task 1", 5);
        SECTION("Simple"){
            todoQueue.push("Task 1", 5);
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.empty());
        }
        SECTION("New priority"){
            todoQueue.push("Task 2", 1);
            todoQueue.push("Task 1", 1);
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.pop() == "Task 2");
            REQUIRE(todoQueue.empty());
        }
        SECTION("Dependence uniqueness Simple"){
            todoQueue.addDependenceTop("Task 1");
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.empty());
        }
        SECTION("Dependence uniqueness"){
            todoQueue.addDependenceTop("Task 2");
            todoQueue.addDependenceTop("Task 2");
            REQUIRE(todoQueue.pop() == "Task 2");
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.empty());
        }
        SECTION("Task to dependence 1"){
            todoQueue.push("Task 2", 1);
            todoQueue.addDependence("Task 1", "Task 2");
            REQUIRE(todoQueue.pop() == "Task 2");
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.empty());
        }
        SECTION("Task to dependence 2"){
            todoQueue.push("Task 2", 10);
            todoQueue.addDependence("Task 1", "Task 2");
            REQUIRE(todoQueue.pop() == "Task 2");
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.empty());
        }
        SECTION("Task to dependence 3"){
            todoQueue.push("Task 2", 10);
            todoQueue.addDependence("Task 2", "Task 3");
            todoQueue.addDependence("Task 1", "Task 3");
            REQUIRE(todoQueue.pop() == "Task 3");
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.pop() == "Task 2");
            REQUIRE(todoQueue.empty());
        }
        SECTION("Task to dependence 4"){
            todoQueue.push("Task 2", 10);
            todoQueue.addDependence("Task 2", "Task 3");
            todoQueue.addDependence("Task 1", "Task 2");
            REQUIRE(todoQueue.pop() == "Task 2");
            REQUIRE(todoQueue.pop() == "Task 1");
            REQUIRE(todoQueue.pop() == "Task 3");
            REQUIRE(todoQueue.empty());
        }
    }
}

#include <fstream>
#include "JSON/json.hpp"
#include "Utility.h"
#include <iostream>

#include "SimConfigurations.h"

using json = nlohmann::json;

SimConfigurations::SimConfigurations(std::string confFilePath){
    std::ifstream i(Utility::getExecuteblePath() + confFilePath);
    json simConfigJSON;
    i >> simConfigJSON;
    SimConfigurations::startDate = new Date(simConfigJSON["StartDate"].get<std::string>());
    SimConfigurations::simDuration = DeltaTime(simConfigJSON["SimDuration"]["years"],0,0,0,0,0);
    SimConfigurations::humanStartNum = simConfigJSON["Humans"]["StartNum"];
}

Date* SimConfigurations::getStartDate(){
    return SimConfigurations::startDate;
}

DeltaTime SimConfigurations::getSimDuration(){
    return SimConfigurations::simDuration;
}

int SimConfigurations::getHumanStartNum(){
    return SimConfigurations::humanStartNum;
}

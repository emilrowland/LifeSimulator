#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(int seed = 50062){
    RandomGenerator::seed = seed;
}

std::vector<int> RandomGenerator::randomIntegers(int min, int max, unsigned int N){
    std::vector<int> res;
    std::mt19937 rng(RandomGenerator::seed + RandomGenerator::seq);
    std::uniform_int_distribution<int> gen(min, max);
    for(unsigned int i = 0; i < N; i++){
        res.push_back(gen(rng));
    }
    RandomGenerator::seq++;
    return res;
}

int RandomGenerator::randomInteger(int min, int max){
    std::mt19937 rng(RandomGenerator::seed + RandomGenerator::seq);
    std::uniform_int_distribution<int> gen(min, max);
    RandomGenerator::seq++;
    return gen(rng);
}

std::string RandomGenerator::randomName(unsigned int min, unsigned int max){
    std::string res = "";
    int n = RandomGenerator::randomInteger(min, max);
    std::vector<int> ri = RandomGenerator::randomIntegers(0, RandomGenerator::length_validCharacters - 1, n);
    for(int i = 0; i < n; i++){
        res += RandomGenerator::validCharacters[ri[i]];
    }
    res[0] = toupper(res[0]);
    return res;
}

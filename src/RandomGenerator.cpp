#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(int seed){
    RandomGenerator::seed = seed;
}

std::vector<int> RandomGenerator::randomIntegers(int min, int max, unsigned int N){
    std::vector<int> res;
    res.reserve(N);
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
    std::string res;
    int n = RandomGenerator::randomInteger(min, max);
    res.reserve(n);
    std::vector<int> ri = RandomGenerator::randomIntegers(0, RandomGenerator::validNameCharacters.length() - 1, n);
    for(int i = 0; i < n; i++){
        res += RandomGenerator::validNameCharacters[ri[i]];
    }
    //Check if name contains vowel
    bool c = false;
    for(int i = 0; i < RandomGenerator::vowels.length(); i++){
        if(res.find(RandomGenerator::vowels[i]) == std::string::npos){
            c = true;
            break;
        }
    }
    //If there is no vowels then add one at an random place.
    if(!c){
        int r = RandomGenerator::randomInteger(min, n - 1);
        int p = RandomGenerator::randomInteger(0, RandomGenerator::vowels.length() - 1);
        res[r] = RandomGenerator::vowels[p];
    }
    res[0] = toupper(res[0]);
    return res;
}

char* RandomGenerator::randomId(unsigned int length){
    char *id = new char[length];
    std::vector<int> ri = RandomGenerator::randomIntegers(0, RandomGenerator::validCharacters.length() - 1, length);
    for(int i = 0; i < length; i++){
        id[i] = RandomGenerator::validCharacters[ri[i]];
    }
    return id;
}

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>
#include <string>
#include <vector>


class RandomGenerator
{
    public:
        RandomGenerator(int seed = 50062);
        int seed;
        unsigned int seq = 0;
        std::vector<int> randomIntegers(int min, int max, unsigned int N);
        int randomInteger(int min, int max);
        std::string randomName(unsigned int min, unsigned int max);
        char* randomId(unsigned int length);
    protected:
    private:
        const std::string validNameCharacters = "abcdefghijklmnopqrstuvwxyz";
        const std::string validCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";
        const std::string vowels = "aeiou";
        const unsigned int length_validCharacters = RandomGenerator::validCharacters.length();
};

#endif // RANDOMGENERATOR_H

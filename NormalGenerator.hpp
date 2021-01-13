#ifndef NORMALGENERATOR_HPP_INCLUDED
#define NORMALGENERATOR_HPP_INCLUDED

#include <cmath>
#include <random>

// Class generates normally distributed random numbers
class NormalGenerator
{
    public:
        // Constructor
        NormalGenerator(const int seed = 1, const double mean = 0, const double var = 1);

        // Destructor
        ~NormalGenerator();

        // Generator
        double rng();

        // Change seed
        void SetSeed(const int seed);

        // Restores initial seed
        void ResetSeed();

    protected:

        int mSeed; // Seed for rng

        double mMean; // Mean for normal distribution

        double mVar; // Variance for normal distribution

        int mInitSeed; // Initial seed
};
// To generate random normal, instantiate a NormalGenerator object then do object.rng()

#endif

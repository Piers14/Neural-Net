#include "NormalGenerator.hpp"

const double pi = atan(1) * 4;

// Constructor
NormalGenerator::NormalGenerator(const int seed, const double mean, const double var)
{
    mSeed = seed;
    mMean = mean;
    mVar = var;
    mInitSeed = seed;
}

// Destructor
NormalGenerator::~NormalGenerator() {

}

// Generates a normal random number
double NormalGenerator::rng()
{
    // Uses inbuilt cpp random number generator
    std::minstd_rand generator(mSeed);

    // Uniform RVs between 1 and (2^31)-1
    int uniformRV1 = generator();
    mSeed = uniformRV1;
    int uniformRV2 = generator();
    mSeed = uniformRV2;

    // Scaling onto (0,1)
    double u1 = (double)uniformRV1 / (pow(2,31) - 1);
    double u2 = (double)uniformRV2 / (pow(2,31) - 1);

    // Box-Muller transform
    double x;
    x = sqrt(-2 * log((double)u1)) * cos(2*pi * u2);

    // Scaling the normal RV
    x = sqrt(mVar) * x + mMean;

    return x;
}

// Change the seed
void NormalGenerator::SetSeed(const int seed)
{
    mSeed = seed;
}

// Reset the seed back to the initial seed
void NormalGenerator::ResetSeed()
{
    mSeed = mInitSeed;
}

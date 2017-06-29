/* CHANGELOG
 * Written by Josh Grooms on 20170629
 */

#pragma once
#include "Enumerator.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Math
        {
            struct ProbabilityDistributions: public Enumerator
            {

                typedef enum
                {
                    Bernoulli,
                    Binomial,
                    Cauchy,
                    ChiSquared,
                    Exponential,
                    Fisher,
                    Gamma,
                    Geometric,
                    LogNormal,
                    Normal,
                    Poisson,
                    StudentT,
                    Uniform,
                    Weibull,
                } Distributions;

                constexpr ProbabilityDistributions(Distributions value = Uniform): 
                    Enumerator(value)
                {

                }

            };
        }
    }
}

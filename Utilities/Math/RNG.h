/* CHANGELOG
 * Written by Josh Grooms on 20170629
 */

#pragma once
#include "Enumerator.h"
#include "UtilitiesAPI.h"
#include "Math/Math.h"
#include "Math/PDFs.h"



namespace Cyclone
{
    namespace Utilities
    {




        struct RNG
        {
            using PDF = Math::ProbabilityDistributions;

            private:

                struct rng;
                rng*        Internals;

                PDF         _distribution;
                uint        _seed;

            public:
                
                /** PROPERTIES **/
                virtual PDF Distribution()      const { return _distribution; }
                virtual uint Seed()             const { return _seed; }

                

                /** CONSTRUCTORS **/
                UtilitiesAPI RNG();
                UtilitiesAPI RNG(uint seed, PDF distribution);
                UtilitiesAPI virtual ~RNG();



                /** UTILITIES **/



        };
    }
}
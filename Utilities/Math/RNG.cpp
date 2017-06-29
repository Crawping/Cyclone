#include "Math/RNG.h"
#include <random>
#include <time.h>



namespace Cyclone
{
    namespace Utilities
    {



        /** INTERNAL UTILITIES **/
        struct RNG::rng
        {
            std::default_random_engine              Generator;
            std::uniform_real_distribution<double>  Distribution;

            RNG::rng():
                Distribution(0.0, 1.0)
            {

            }

        };


        /** PROPERTIES **/



        /** CONSTRUCTORS **/
        RNG::RNG():
            Internals(new rng()),
            _seed(time(0))
        {

        }
        RNG::RNG(uint seed, PDF distribution):
            Internals(new rng()),
            _distribution(distribution),
            _seed(seed)
        {

        }
        RNG::~RNG()
        {
            if (Internals) { delete Internals; }
        }

    }
}
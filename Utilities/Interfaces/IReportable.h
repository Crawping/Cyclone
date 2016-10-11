/* CHANGELOG 
 * Written by Josh Grooms on 20161009
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> An interface that represents any object capable of providing detailed diagnostic information. </summary>
        class IReportable
        {
            public:

                /// <summary> Destroys any specially allocated resources held by the reportable object. </summary>
                virtual ~IReportable() { }

                /// <summary> Generates a human-readable string detailing the internal state of the reportable object. </summary>
                virtual string Report() const = 0;

        };
    }
}

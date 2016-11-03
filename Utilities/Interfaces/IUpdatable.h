/* CHANGELOG
 * Written by Josh Grooms on 20160821
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {
        class IUpdatable
        {

            public:
                
                virtual bool NeedsUpdate()  const = 0;
                
                virtual ~IUpdatable() { }

                virtual void Update() = 0;
                
        };
    }
}

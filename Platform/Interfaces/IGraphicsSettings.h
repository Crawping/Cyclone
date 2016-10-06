/* CHANGELOG
 * Written by Josh Grooms on 20161006
 */

#pragma once



namespace Cyclone
{
    namespace Platform
    {
        class GPU;

        struct IGraphicsSettings
        {
            
            virtual ~IGraphicsSettings() { }

            virtual void Apply(GPU* gpu) const = 0;
                
        };
    }
}

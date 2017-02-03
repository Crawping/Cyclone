/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once



namespace Cyclone
{
    namespace Scenes
    {
        class ISceneComponent
        {
            public:


                virtual bool IsEnabled() const = 0;
                
        };
    }
}

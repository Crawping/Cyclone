/* CHANGELOG
 * Written by Josh Grooms on 20161023
 */

#pragma once



namespace Cyclone
{
    namespace UI
    {

        class IInterfaceControl
        {
            public:

                virtual bool IsEnabled() const = 0;

                virtual ~IInterfaceControl() { }
        };
    }
}

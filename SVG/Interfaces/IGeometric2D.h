/* CHANGELOG
 * Written by Josh Grooms on 20170101
 */

#pragma once
#include "EnumerationsSVG.h"
#include "Interfaces/IGeometric.h"



namespace Cyclone
{
    namespace { using namespace OpenGL; }
    namespace SVG
    {
        class IGeometric2D : public virtual IGeometric
        {
            public:

                virtual Vector<PathCommands> Commands() const = 0;
                virtual bool IsClosed()                 const = 0;
                virtual Vector<float> Parameters()      const = 0;

                virtual ~IGeometric2D() { }
        };
    }
}

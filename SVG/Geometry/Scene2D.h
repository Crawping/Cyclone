/* CHANGELOG 
 * Written by Josh Grooms on 20160918
 */

#pragma once
#include "SVGAPI.h"
#include "Geometry/Path2D.h"
#include <set>



namespace Cyclone
{
    namespace SVG
    {
        class Scene2D
        {
            public:

                SVGAPI Scene2D();

                SVGAPI void Add(const Path2D& path);
                SVGAPI void Remove(const Path2D& path);
                SVGAPI void Render() const;
                SVGAPI void Update();
                SVGAPI void Update(const Path2D& path);


            
            private:

                std::set<const Path2D*> Paths;
                
        };
    }
}

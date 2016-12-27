/* CHANGELOG
 * Written by Josh Grooms on 20161002
 */


#include "AdvancedRenderer.h"

using namespace Renderers



class Program : public AdvancedRenderer
{
    public:
        
        Program() : 
            AdvancedRenderer(Area(0, 0, 1024, 960), "3D SVG Rendering")
        {

        }

    protected:


        
        
};
/* CHANGELOG
 * Written by Josh Grooms on 20161030
 */

#pragma once
#include "UIAPI.h"
#include "Controls/InterfaceControl.h"
#include "Geometry/Rectangle2D.h"



namespace Cyclone
{
    namespace UI
    {
        class Panel : public InterfaceControl
        {
            public:
            
                const Path2D& Shape()       const override { return _shape; }
                


                UIAPI Panel();


            
                
            protected:



            private:
                Rectangle2D _shape;

        };
    }
}

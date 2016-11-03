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
            
                const Rectangle2D& Shape()       const override { return _shape; }
                


                UIAPI Panel();


            
                
            protected:

                Rectangle2D& Shape() override { return _shape; }

            private:
                Rectangle2D _shape;

        };
    }
}

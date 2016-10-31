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
            
                Path2D* Shape() const { return (Path2D*)&_shape; }

                UIAPI Panel();

                UIAPI void Configure(const ControlStyle& style) override;

            
                
            protected:



            private:
                Rectangle2D _shape;

        };
    }
}

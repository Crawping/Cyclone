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
            
                /** PROPERTIES **/
                List<IRenderable&> Components() override { return List<IRenderable&>(); }
                const Rectangle2D& Shape()      const override { return _shape; }
                Rectangle2D& Shape()            override { return _shape; }

                UIAPI Panel& BorderRadius(const Border& value);



                /** CONSTRUCTOR **/
                UIAPI Panel();

            private:
                Rectangle2D _shape;

        };
    }
}

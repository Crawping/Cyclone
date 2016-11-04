/* CHANGELOG
 * Written by Josh Grooms on 20161022
 */

#pragma once
#include "Event.h"
#include "UIAPI.h"
#include "Controls/InterfaceControl.h"
#include "Geometry/Rectangle2D.h"
#include "Text/Text2D.h"



namespace Cyclone
{
    namespace 
    { 
        using namespace SVG;
        using namespace Utilities;
    }

    namespace UI
    {
        
        class Button : public InterfaceControl
        {
            public:

                /** PROPERTIES **/
                Rectangle2D& Shape()            override { return _shape; }
                const Rectangle2D& Shape()      const override { return _shape; }
                const string& Text()            const { return _text.Text(); }

                UIAPI Button& BorderRadius(const Border& value) override;
                UIAPI Button& Offset(const Vector2& value);
                UIAPI Button& Size(const Vector2& value);
                UIAPI Button& Text(const string& value);

                
                UIAPI Button();


            protected:

                

            private:

                Rectangle2D _shape;
                Text2D      _text;



                void UpdateTextPosition();


        };
    }
}

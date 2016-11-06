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
                /// <summary> Gets a reference to the button's shape data. </summary>
                Rectangle2D& Shape()            override { return _shape; }
                /// <summary> Gets a constant reference to the button's shape data. </summary>
                const Rectangle2D& Shape()      const override { return _shape; }
                /// <summary> Gets the string of text displayed within the button. </summary>
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

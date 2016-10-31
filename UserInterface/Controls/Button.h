/* CHANGELOG
 * Written by Josh Grooms on 20161022
 */

#pragma once
#include "Event.h"
#include "UIAPI.h"
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
        
        class Button : public Rectangle2D
        {
            public:

                /** PROPERTIES **/
                bool IsEnabled()                const { return _isEnabled; }
                const string& Text()            const { return _text.Text(); }


                UIAPI Button& IsEnabled(bool value);
                UIAPI Button& Offset(const Vector2& value);
                UIAPI Button& Size(const Vector2& value);
                UIAPI Button& Text(const string& value);



                /** EVENTS **/
                //Event<const Button&> OnHover;
                //Event<const Button&> OnPress;
                //Event<const Button&> OnRelease;


                
                UIAPI Button();




            private:

                bool    _isEnabled;
                Text2D  _text;


                void UpdateTextPosition();


        };
    }
}

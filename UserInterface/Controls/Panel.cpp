#include "Controls/Panel.h"



namespace Cyclone
{
    namespace UI
    {

        /** PROPERTIES **/
        Panel& Panel::BorderRadius(const Border& value)
        {
            InterfaceControl::BorderRadius(value);
            _shape.CornerRadius(value.Left);
            return *this;
        }



        /** CONSTRUCTOR **/
        Panel::Panel()
        {

        }

    }
}
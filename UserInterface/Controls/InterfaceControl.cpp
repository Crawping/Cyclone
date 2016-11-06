#include "Controls/InterfaceControl.h"



namespace Cyclone
{
    namespace UI
    {

        /** PROPERTIES **/
        InterfaceControl& InterfaceControl::BackgroundColor(const Color4& value)
        {
            _style.BackgroundColor = value;
            Shape().PrimaryColor(value);
            return *this;
        }
        InterfaceControl& InterfaceControl::BorderColor(const Color4& value)
        {
            _style.BorderColor = value;
            Shape().SecondaryColor(value);
            return *this;
        }
        InterfaceControl& InterfaceControl::BorderRadius(const Border& value) 
        { 
            _style.BorderRadius = value; 
            return *this;
        }
        InterfaceControl& InterfaceControl::BorderWidth(const Border& value)
        { 
            _style.BorderWidth = value; 
            Shape().StrokeWidth(value.Left);
            return *this; 
        }
        InterfaceControl& InterfaceControl::IsClippingEnabled(bool value)
        {
            _isClippingEnabled = value;
            return *this;
        }
        InterfaceControl& InterfaceControl::IsEnabled(bool value)
        { 
            _isEnabled = value;
            return *this; 
        }
        InterfaceControl& InterfaceControl::Offset(const Vector3& value)
        {
            Shape().Offset(value);
            return *this;
        }
        InterfaceControl& InterfaceControl::Orientation(const Vector3& value)
        {
            Shape().Orientation(value);
            return *this;
        }
        InterfaceControl& InterfaceControl::Position(const Vector3& value)
        {
            Shape().Position(value);
            return *this;
        }
        InterfaceControl& InterfaceControl::Size(const Vector3& value)
        {
            Shape().Size(value);
            return *this;
        }
        InterfaceControl& InterfaceControl::Style(const ControlStyle& value)
        {
            _style = value;
            return this->
                 BackgroundColor(_style.BackgroundColor)
                .BorderColor(_style.BorderColor)
                .BorderRadius(_style.BorderRadius)
                .BorderWidth(_style.BorderWidth);
        }



        /** CONSTRUCTOR **/
        InterfaceControl::InterfaceControl() : 
            _isClippingEnabled(true),
            _isEnabled(true),
            _isHighlighted(false),
            _isSelected(false),
            _parent(nullptr)
        {

        }



        /** UTILITIES **/



        /** RENDERING UTILITIES**/
        void InterfaceControl::Update()   const 
        {
            //UpdateStyle();
            Shape().Update();
        }

    }
}
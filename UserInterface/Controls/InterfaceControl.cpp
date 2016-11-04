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
        InterfaceControl& InterfaceControl::Style(const ControlStyle& value)
        {
            _style = value;
            Shape()
                .StrokeWidth(value.BorderWidth.Left)
                .PrimaryColor(value.BackgroundColor)
                .SecondaryColor(value.BorderColor);
            return *this;
        }



        /** CONSTRUCTOR **/
        InterfaceControl::InterfaceControl() : 
            _isClippingEnabled(true),
            _isEnabled(true),
            _parent(nullptr)
        {

        }



        /** UTILITIES **/
        void InterfaceControl::UpdateStyle()
        {

        }



        /** RENDERING UTILITIES**/
        void InterfaceControl::Update()   const 
        {
            //UpdateStyle();
            Shape().Update();
        }




        //void InterfaceControl::UpdateStyle()
        //{
        //    Shape()
        //        .PrimaryColor(BackgroundColor())
        //        .SecondaryColor(BorderColor())
        //}
    }
}
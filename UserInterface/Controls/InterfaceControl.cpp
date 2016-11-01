#include "Controls/InterfaceControl.h"



namespace Cyclone
{
    namespace UI
    {

        /** PROPERTIES **/
        InterfaceControl& InterfaceControl::BackgroundColor(const Color4& value)
        {
            _style.BackgroundColor = value; 
            return *this;
        }
        InterfaceControl& InterfaceControl::BorderColor(const Color4& value)
        {
            _style.BorderColor = value; 
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
            if (!Shape()) { return *this; }

            Shape()->
                 StrokeWidth(value.BorderWidth.Left)
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




        /** RENDERING UTILITIES**/
        void InterfaceControl::Fill()     const 
        {
            if (Shape())
                Shape()->Fill();
        }
        void InterfaceControl::Stroke()   const 
        {
            if (Shape())
                Shape()->Stroke();
        }
        void InterfaceControl::Update()   const 
        {
            if (Shape())
                Shape()->Update();
        }

    }
}
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
            Shape()
                .StrokeWidth(BorderWidth().Left)
                .PrimaryColor(BackgroundColor())
                .SecondaryColor(BorderColor());
        }



        /** RENDERING UTILITIES**/
        void InterfaceControl::Fill()     const 
        {
            Shape().Fill();
        }
        void InterfaceControl::Stroke()   const 
        {
            Shape().Stroke();
        }
        void InterfaceControl::Update()   const 
        {
            Shape().Update();
        }

    }
}
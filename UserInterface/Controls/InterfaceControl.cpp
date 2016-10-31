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



        /** CONSTRUCTOR **/
        InterfaceControl::InterfaceControl() : 
            _isClippingEnabled(true),
            _isEnabled(true),
            _parent(nullptr)
        {

        }



        /** UTILITIES **/
        void InterfaceControl::Configure(const ControlStyle& style)
        {
            _style = style;
            if (!Shape()) { return; }

            Shape()->
                StrokeWidth(style.BorderWidth.Left)
                .PrimaryColor(style.BackgroundColor)
                .SecondaryColor(style.BorderColor);
        }



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
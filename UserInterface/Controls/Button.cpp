#include "Controls/Button.h"



namespace Cyclone
{
    namespace UI
    {

        /** PROPERTIES **/
        Button& Button::IsEnabled(bool value)
        {
            _isEnabled = false; 
            return *this;
        }
        Button& Button::Offset(const Vector2& value)
        {
            Rectangle2D::Offset(value);
            UpdateTextPosition();
            return *this;
        }
        Button& Button::Size(const Vector2& value)
        {
            Rectangle2D::Size(value);
            UpdateTextPosition();
            return *this;
        }
        Button& Button::Text(const string& value)
        {
            _text.Text(value);
            UpdateTextPosition();
            return *this;
        }



        /** CONSTRUCTOR **/
        Button::Button() :
            _isEnabled(true)
        {
            _text.PrimaryColor(Color4::Black);
            _components.Append(&_text);
        }




        void Button::UpdateTextPosition()
        {
            _text
                .X(Bounds().X + (0.5f * (Bounds().Width - _text.Bounds().Width)))
                .Y(Bounds().Y + (0.5f * (Bounds().Height - _text.Bounds().Height)))
                .Z(Z() + 0.02f);
        }
    }
}
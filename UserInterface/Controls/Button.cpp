#include "Controls/Button.h"



namespace Cyclone
{
    namespace UI
    {

        /** PROPERTIES **/
        Button& Button::BorderRadius(const Border& value)
        {
            InterfaceControl::BorderRadius(value);
            _shape.CornerRadius(value.Left);
            return *this;
        }
        Button& Button::Offset(const Vector2& value)
        {
            _shape.Offset(value);
            UpdateTextPosition();
            return *this;
        }
        Button& Button::Size(const Vector2& value)
        {
            _shape.Size(value);
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
        Button::Button()
        {
            _text.PrimaryColor(Color4::Black);

            _components.Append(&_text);
        }




        void Button::UpdateTextPosition()
        {
            _text
                .X(Shape().Bounds().X + (0.5f * (Shape().Bounds().Width - _text.Bounds().Width)))
                .Y(Shape().Bounds().Y + (0.5f * (Shape().Bounds().Height - _text.Bounds().Height)))
                .Z(Shape().Z() + 0.02f);
        }
    }
}
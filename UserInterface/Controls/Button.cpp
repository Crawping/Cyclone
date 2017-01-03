#include "Controls/Button.h"
#include "Text/Text2D.h"



namespace Cyclone
{
    namespace UI
    {

        /** PROPERTIES **/
        List<IRenderable&> Button::Components()
        {
            List<IRenderable&> components;
            components.Append(_text);
            return components;
        }
        Button& Button::BorderRadius(const Border& value)
        {
            InterfaceControl::BorderRadius(value);
            _shape.CornerRadius(value.Left);
            return *this;
        }
        Button& Button::Offset(const Vector2& value)
        {
            InterfaceControl::Offset(value);
            UpdateTextPosition();
            return *this;
        }
        Button& Button::Size(const Vector2& value)
        {
            InterfaceControl::Size(value);
            UpdateTextPosition();
            return *this;
        }
        Button& Button::Text(const string& value)
        {
            _text.Text(value);
            UpdateTextPosition();
            return *this;
        }
        Button& Button::TextColor(const Color4& value)
        {
            _text.PrimaryColor(value);
            return *this;
        }



        /** CONSTRUCTOR **/
        Button::Button()
        {
            _text.PrimaryColor(Color4::Black);
        }



        void Button::Update()
        {
            _shape.Update();
            _text.Update();
        }

        void Button::UpdateTextPosition()
        {
            const Volume& bounds = Shape().Bounds();
            Vector3 offShape(Shape().Offset());

            _text.Position( offShape - (_text.Bounds().Size()) * 0.5f );
            _text.Z( Shape().Z() + 0.01f );
        }
    }
}

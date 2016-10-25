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
        Button& Button::Text(const string& value)
        {
            _text.Text(value);
            return *this;
        }



        /** CONSTRUCTOR **/
        Button::Button() :
            _isEnabled(true)
        {
            _components.Append(&_text);
        }





    }
}
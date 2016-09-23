/* CHANGELOG
 * Written by Josh Grooms on 20150910
 */

#include "Utilities.h"
#include "Vector2.h"



namespace Cyclone
{
    namespace Utilities
    {
        /** STATIC DATA **/
        const Vector2 Vector2::One      = Vector2(1.0f, 1.0f);
        const Vector2 Vector2::UnitX    = Vector2(1.0f, 0.0f);
        const Vector2 Vector2::UnitY    = Vector2(0.0f, 1.0f);
        const Vector2 Vector2::Zero     = Vector2(0.0f, 0.0f);


        string Vector2::ToString() const
        {
            return "(" + num2str(X) + ", " + num2str(Y) + ")";
        }
    }
}
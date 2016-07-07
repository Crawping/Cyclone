/* CHANGELOG
 * Written by Josh Grooms on 20150907
 */

#include "Color4.h"
#include "Utilities.h"

#include <random>
#include <sstream>
#include <time.h>



/** CONSTANT DATA **/
const Color4 Color4::Black          = Color4(0.0f, 0.0f, 0.0f, 1.0f);
const Color4 Color4::Blue           = Color4(0.0f, 0.0f, 1.0f, 1.0f);
const Color4 Color4::Cyan           = Color4(0.0f, 1.0f, 1.0f, 1.0f);
const Color4 Color4::Green          = Color4(0.0f, 1.0f, 0.0f, 1.0f);
const Color4 Color4::Magenta        = Color4(1.0f, 0.0f, 1.0f, 1.0f);
const Color4 Color4::Red            = Color4(1.0f, 0.0f, 0.0f, 1.0f);
const Color4 Color4::Transparent    = Color4(0.0f, 0.0f, 0.0f, 0.0f);
const Color4 Color4::White          = Color4(1.0f, 1.0f, 1.0f, 1.0f);
const Color4 Color4::Yellow         = Color4(1.0f, 1.0f, 0.0f, 1.0f);



/** UTILITIES **/
static uint RandomSeed = time(NULL);
Color4 Color4::Random()
{
    srand(RandomSeed++);

    float r, g, b;
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;

    return Color4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}
constexpr int Color4::ToInt() const
{
    return
        (int(R * 255) << 24) |
        (int(G * 255) << 16) |
        (int(B * 255) << 8)  |
        (int(A * 255) << 0);
}
string Color4::ToString() const
{
    return "(" + num2str(R) + ", " + num2str(G) + ", " + num2str(B) + ", " + num2str(A) + ")";
}

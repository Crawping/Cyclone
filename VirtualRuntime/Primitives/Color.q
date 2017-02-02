/* CHANGELOG
 * Written by Josh Grooms on 20170201
 */



namespace Core.Primitives
{

    class Color.RGBA : 
        alias = rgba;
    {

        /** DATA **/
        float R = 0.0f;
        float G = 0.0f;
        float B = 0.0f;
        float A = 1.0f;



        /** CONSTRUCTORS **/
        Color()         : Color(0.0f, 0.0f, 0.0f, 1.0f) { }
        Color(float g)  : Color(g, g, g, 1.0f) { }
        Color(float r, float g, float b, float a = 1.0f)
        {
            (R, G, B, A) = (r, g, b, a);
        }
        Color(List<float> channels)
        {
            (R, G, B, A) = channels;
        }


        

    }


    enum Colors : Color
    {
        Black   = { 0.0f, 0.0f, 0.0f, 1.0f };
        Blue    = { 0.0f, 0.0f, 1.0f, 1.0f };
        Green   = { 0.0f, 1.0f, 0.0f, 1.0f };
        Red     = { 1.0f, 0.0f, 0.0f, 1.0f };
        White   = { 1.0f, 1.0f, 1.0f, 1.0f };
    }

}
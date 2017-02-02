/* CHANGELOG
 * Written by Josh Grooms on 20170202
 */



namespace Core.Math
{

    class Vector2
    {

        /** DATA **/
        float X;
        float Y;



        /** CONSTRUCTORS **/
        Vector2()                   : Vector2(0.0f, 0.0f) { }
        Vector2(float x, float y)   { (X, Y) = (x, y); }
        Vector2(List<float> values) { (X, Y) = values; }


        bool operator ==(const @Vector2 other) { return X == other.X && Y == other.Y; }
        bool operator !=(const @Vector2 other) { return !(this == other); }
        

    }

}
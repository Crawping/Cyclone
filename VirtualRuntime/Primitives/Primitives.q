/* CHANGELOG
 * Written by Josh Grooms on 20170202
 */




namespace Core.Primitives
{
    
    interface INumeric
    {

        INumeric operator +(const @INumeric other);
        INumeric operator /(const @INumeric other);
        INumeric operator *(const @INumeric other);
        INumeric operator -(const @INumeric other);

        operator +=(const @INumeric other);
        operator /=(const @INumeric other);
        operator *=(const @INumeric other);
        operator -=(const @INumeric other);
    }


    class Character:
        alias   = char;
        base    = internal char;
    {

    }
    class Float32:
        alias       = float;
        base        = internal float;
        interface   = INumeric;
    {

    }
    class Float64:
        alias       = double;
        base        = internal double;
        interface   = INumeric;
    {

    }
    class Integer8:
        alias       = byte;
        base        = internal byte;
        interface   = INumeric;
    {

    }
    class Integer16:
        alias       = short;
        base        = internal short;
        interface   = INumeric;
    {

    }
    class Integer32:
        alias       = int;
        base        = internal int;
        interface   = INumeric;
    {

    }
    class Integer64:
        alias       = long;
        base        = internal long;
    {

    }
    class UnsignedInteger8:
        alias       = ubyte;
        base        = internal ubyte;
    {

    }
    class UnsignedInteger16:
        alias       = ushort;
        base        = internal ushort;
    {

    }
    class UnsignedInteger32:
        alias       = uint;
        base        = internal uint;
    {

    }
    class UnsignedInteger64:
        alias       = ulong;
        base        = internal ulong;
    {

    }

}
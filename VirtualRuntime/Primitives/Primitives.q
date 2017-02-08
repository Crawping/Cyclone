/* CHANGELOG
 * Written by Josh Grooms on 20170202
 */




namespace Core.Primitives
{
    
    interface IComparable
    {

    }

    interface INumeric:
        interface = IComparable;
    {

        INumeric operator +(const @INumeric other);
        INumeric operator /(const @INumeric other);
        INumeric operator *(const @INumeric other);
        INumeric operator -(const @INumeric other);

        @INumeric operator +=(const @INumeric other);
        @INumeric operator /=(const @INumeric other);
        @INumeric operator *=(const @INumeric other);
        @INumeric operator -=(const @INumeric other);
    }



    class Float32:
        alias       = float;
        base        = internal float;
        interface   = INumeric;
    {
        float MaxValue:         (const, static) = 3.40282347E+38F;
        float MinValue:         (const, static) = -3.40282347E+38F;
    }
    class Float64:
        alias       = double;
        base        = internal double;
        interface   = INumeric;
    {
        double MaxValue:        (const, static) = 1.7976931348623157E+308;
        double MinValue:        (const, static) = -1.7976931348623157E+308;
    }
    class Integer8:
        alias       = byte;
        base        = internal byte;
        interface   = INumeric;
    {
        byte MaxValue:          (const, static) = 127;
        byte MinValue:          (const, static) = -128;
    }
    class Integer16:
        alias       = short;
        base        = internal short;
        interface   = INumeric;
    {
        short MaxValue:         (const, static) = 32767;
        short MinValue:         (const, static) = -32768;
    }
    class Integer32:
        alias       = int;
        base        = internal int;
        interface   = INumeric;
    {
        int MaxValue:           (const, static) = 2147483647;
        int MinValue:           (const, static) = -2147483648;
    }
    class Integer64:
        alias       = long;
        base        = internal long;
        interface   = INumeric;
    {
        long MaxValue:          (const, static) = 9223372036854775807;    
        long MinValue:          (const, static) = -9223372036854775808;
    }
    class UnsignedInteger8:
        alias       = ubyte;
        base        = internal ubyte;
        interface   = INumeric;
    {
        ubyte MaxValue:         (const, static) = 255;
        ubyte MinValue:         (const, static) = 0;
    }
    class UnsignedInteger16:
        alias       = ushort;
        base        = internal ushort;
        interface   = INumeric;
    {
        ushort MaxValue:        (const, static) = 65535;
        ushort MinValue:        (const, static) = 0;
    }
    class UnsignedInteger32:
        alias       = uint;
        base        = internal uint;
        interface   = INumeric;
    {
        uint MaxValue:          (const, static) = 4294967295;
        uint MinValue:          (const, static) = 0;
    }
    class UnsignedInteger64:
        alias       = ulong;
        base        = internal ulong;
        interface   = INumeric;
    {
        ulong MaxValue:         (const, static) = 18446744073709551615;
        ulong MinValue:         (const, static) = 0;
    }

}
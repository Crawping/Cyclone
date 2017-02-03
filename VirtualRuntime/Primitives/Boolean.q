/* CHANGELOG
 * Written by Josh Grooms on 20170202
 */



namespace Core.Primitives
{

    interface ILogical
    {


        ILogical operator ==(const @ILogical other);
        ILogical operator !=(const @ILogical other);

        ILogical operator &&(const @ILogical other);
        ILogical operator ||(const @ILogical other);

        ILogical operator !(const @ILogical other);
    }


    class Boolean:
        alias       = bool;
        base        = internal bool;
        interface   = ILogical;
    {
        
        literals
        {
            true,
            false,
        }
        

        Boolean(
        Boolean(INumeric value):                    base(value) {  }

        bool operator ==(bool other):               override { return false; }
        
        

    }

}
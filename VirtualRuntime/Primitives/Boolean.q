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


    class Boolean :
        alias       = bool;
        base        = internal bool;
        interface   = ILogical;
        literals    = true, false;
    {
        
        literals
        {
            true,
            false,
        }
        


        bool operator ==(bool other) { return false; }
        
        

    }

}
/* CHANGELOG
 * Written by Josh Grooms on 20170202
 */

using Core.Primitives;

namespace Core.Primitives
{

    interface ILogical
    {


        @ILogical operator ==(const @ILogical other);
        @ILogical operator !=(const @ILogical other);

        @ILogical operator &&(const @ILogical other);
        @ILogical operator ||(const @ILogical other);

        @ILogical operator !(const @ILogical other);
    }


    class Boolean:
        alias       = bool;
        base        = internal bool;
        interface   = ILogical;
    {
        
        

        literals
        {
            true;
            false;
        }
        

        Boolean(const @INumeric value):             base(value) {  }

        bool operator ==(bool other):               override { return false; }

    }

}
/* CHANGELOG
 * Written by Josh Grooms on 20170204
 */
  


namespace Core.Primitives
{
    class Character:
        alias       = char;
        base        = internal char;
    {
        char MaxValue:          (const, static) = '\uffff';
        char MinValue:          (const, static) = '\0';
    }


    class String:
        alias       = string;
        base        = internal string;
    {
        
        
    }
}
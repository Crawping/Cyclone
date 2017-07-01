#include "IO/Console.h"
#include "Collections/Array.h"
#include "Virtual/Class.h"
#include "Virtual/Function.h"
#include "Virtual/Machine.h"



namespace Cyclone
{
    namespace Virtual
    {

        /** CONSTRUCTOR & DESTRUCTOR **/
        Machine::Machine()
        {

        }
        Machine::~Machine()
        {
            
        }



        /** PUBLIC UTILITIES **/
        void Machine::Abort()   { _interrupt = Instructions::Abort; }
        void Machine::Pause()   { _interrupt = Instructions::Pause; }
        void Machine::Resume()  { _interrupt = Instructions::None; }

        void Machine::Execute(const ICollection<Instruction>& instructions)
        {
            for (uint a = 0; a < instructions.Count(); a++)
            {
                switch (_interrupt)
                {
                    case Instructions::Abort:       
                    case Instructions::Return:      return;
                    case Instructions::Pause:       a--; continue;
                    default:                        break;
                }

                const auto& cmd = instructions(a).Command;
                const auto& ops = instructions(a).Operands;

                if (cmd >= Instructions::Add && cmd <= Instructions::Xor)
                {
                    Compute(cmd, ops(0), ops(1), ops(2));
                    continue;
                }

                switch (cmd)
                {
                    case Instructions::Abort:       _interrupt = cmd;                       return;
                    case Instructions::Allocate:    Allocate(ops(0), ops(1));               break;
                    case Instructions::Call:        Call(ops(0), ops(1), ops(2));           break;
                    case Instructions::Copy:        Copy(ops(0), ops(1));                   break;
                    case Instructions::Delete:      Delete(ops(0));                         break;
                    case Instructions::Index:       break;
                    case Instructions::Jump:        a = ops(0).Offset();                    break;
                    case Instructions::JumpIf:
                        a = Access<Number>(ops(0)) ? ops(1).Offset() : ops(2).Offset();
                        break;

                    case Instructions::Load:        Load(ops(0), ops(1));                   break;
                    case Instructions::Print:
                        Console::WriteLine(Access<String>(ops(0)));
                        break;
                    case Instructions::Return:      return;
                    default:                        break;
                }
            }
        }



        /** PRIVATE UTILITIES **/
        void Machine::Allocate(Reference x, Reference y)
        {
            if (x.Type() != ReferenceTypes::Array) { return; }
            Insert(x, Array(y.Type(), y.Offset()));
            //switch (x.Type())
            //{
            //    case ReferenceTypes::Array:         Insert(x, Array());     break;
            //    case ReferenceTypes::Function:      Insert(x, Function());  break;
            //    case ReferenceTypes::Number:        Insert(x, Number());    break;
            //    case ReferenceTypes::Object:        Insert(x, Class());     break;
            //    case ReferenceTypes::Reference:     Insert(x, Reference()); break;
            //    case ReferenceTypes::String:        Insert(x, String());    break;
            //    default:                            break;
            //}
        }
        void Machine::Call(Reference x, Reference y, Reference z)
        {
            auto& ws = Workspace();
            _scopes.Push(StackFrame());
                auto& nws = Workspace().Inputs(ws.Inputs());
                Execute( Access<Function>(x).Logic() );
            _scopes.Pop();
        }
        void Machine::Compute(Instructions cmd, Reference xr, Reference yr, Reference zr)
        {
            Number& x(Access<Number>(xr));
            Number& y(Access<Number>(yr));
            Number& z(Access<Number>(zr));

            switch (cmd)
            {
                case Instructions::Add:             x = y + z;              break;
                case Instructions::Cast:            x = x.Cast(y.Type());   break;
                case Instructions::Compare:         x = y.Compare(z);       break;
                case Instructions::Decrement:       x--;                    break;
                case Instructions::Divide:          x = y / z;              break;
                case Instructions::Increment:       x++;                    break;
                case Instructions::Multiply:        x = y * z;              break;
                case Instructions::Negate:          x = ~y;                 break;
                case Instructions::Not:             x = !y;                 break;
                case Instructions::Or:              x = y | z;              break;
                case Instructions::Subtract:        x = y - z;              break;
                case Instructions::Xor:             x = y ^ z;              break;
                default:                            break;
            }
        }
        void Machine::Copy(Reference x, Reference y)
        {
            switch (x.Type())
            {
                case ReferenceTypes::Array:         Access<Array>(x) = Access<Array>(y);            break;
                case ReferenceTypes::Number:        Access<Number>(x) = Access<Number>(y);          break;
                case ReferenceTypes::Reference:     Access<Reference>(y) = Access<Reference>(y);    break;
                default:                            break;
            }
        }
        void Machine::Delete(Reference x)
        {
            if (x.Base())   Workspace().Delete(x);
            else            _memory.Delete(x);
        }
        void Machine::Index(Reference x, Reference y, Reference z)
        {
            Number& n( Access<Array>(y).Access(z) );
            Reference r( (ulong)n.Value() );

            switch (x.Type())
            {
                //case ReferenceTypes::Array:         Access<Array>(x) = Access<Array>(y).Access(z);      break;
                case ReferenceTypes::Object:        Access<Class>(x) = Access<Class>(r);            break;
                case ReferenceTypes::Function:      Access<Function>(x) = Access<Function>(r);      break;
                case ReferenceTypes::Number:        Access<Number>(x) = n;                          break;
                case ReferenceTypes::Reference:     Access<Reference>(x) = r;                       break;
                case ReferenceTypes::String:        Access<String>(x) = Access<String>(r);          break;
                default:                            break;
            }
        }
        void Machine::Load(Reference x, Reference y)
        {
            switch (x.Type())
            {
                case ReferenceTypes::Array:         Workspace().Insert(x, Access<Array>(y));        break;
                case ReferenceTypes::Object:        Workspace().Insert(x, Access<Class>(y));        break;
                case ReferenceTypes::Function:      Workspace().Insert(x, Access<Function>(y));     break;
                case ReferenceTypes::Number:        Workspace().Insert(x, Access<Number>(y));       break;
                case ReferenceTypes::Reference:     Workspace().Insert(x, Access<Reference>(y));    break;
                case ReferenceTypes::String:        Workspace().Insert(x, Access<String>(y));       break;
                default:                            break;
            }
        }
            
    }
}
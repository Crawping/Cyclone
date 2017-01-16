/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once
#include "Enumerator.h"
#include "SceneAPI.h"
#include "Interfaces/ISceneMessage.h"



namespace Cyclone
{
    namespace Scenes
    {


        struct LiteralTypes : public Enumerator
        {
            enum Types
            {
                Nothing,
                Float,
                Integer,
                String,
            };

            constexpr LiteralTypes(enum Types t = Float) : Enumerator((int)t) { }
        };

        struct Literal
        {
            LiteralTypes Type;
            union
            {
                float   FloatValue;
                int     IntegerValue;
                char*   StringValue;
            };




            Literal operator +(Literal other) const
            {
                switch (Type)
                {

                }
            }


        };
     







        template<typename T>
        struct Lit
        {
            public:
                using Type = T;

                constexpr Lit(T value) : Value(value) { }

                constexpr operator Type() const { return Value; }

            private:
                Type Value;

        };


        struct Instruction
        {
            Instructions            Command;
            Vector<LiteralTypes>    Parameters;

                SceneAPI void Execute();

        };


        struct Add : public Instruction
        {
            //Vector<int>
                
        };
    }
}

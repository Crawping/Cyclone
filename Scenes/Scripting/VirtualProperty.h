/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "SceneAPI.h"
#include "Collections/Registry.h"
#include "Messaging/Literal.h"



namespace Cyclone
{
    namespace Scenes
    {

        class VirtualProperty
        {
            public:

                /** PROPERTIES **/
                uint ID()                           const { return _id; }
                const string& Name()                const { return _name; }



                /** CONSTRUCTOR **/
                SceneAPI VirtualProperty();

            private:

                uint        _id;
                string      _name;

                Registry<Literal> Data;
        };


        class VirtualFunction
        {
            public:

                uint ID()                           const { return _id; }
                const string& Name()                const { return _name; }
                const Vector<Instructions>& Logic() const { return _logic; }

            private:

                uint    _id;
                string  _name;

                Vector<Instructions> _logic;
        };



        class VirtualClass
        {
            public:
                
                /** PROPERTIES **/
                uint ID()                           const { return _id; }
                const string& Name()                const { return _name; }



                /** UTILITIES **/
                SceneAPI Literal Get(const Literal& target);
                SceneAPI void Set(const Literal& target, const Literal& value);

            private:

                uint    _id;
                string  _name;

                BST<uint, VirtualFunction>  _methods;
                BST<uint, VirtualProperty>  _properties;

        };

    }
}

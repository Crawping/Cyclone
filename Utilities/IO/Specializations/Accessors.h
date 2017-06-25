/* CHANGELOG
 * Written by Josh Grooms on 20170608
 */

#pragma once
#include "Meta/Function.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A structure that stores a generic invokable code routine. </summary>
        /// <typeparam name="T"> The type of the stored routine. </typeparam>
        template<typename T> struct Functor
        {
            protected:
                T _value;

            public:
                /// <summary> Constructs a new functor object using a given routine pointer. </summary>
                /// <param name="value"> Any kind of function, method, or member pointer to be stored. </param>
                Functor(T value):                               _value(value) { }
        };

        /// <summary> A structure that represents a routine used to get or set data values. </summary>
        /// <typeparam name="T"> The type of the stored routine. </typeparam>
        template<typename T> struct Accessor { };

        /// <summary> A structure that represents an ordinary function used to get or set data values. </summary>
        /// <typeparam name="T"> The type of the function's output argument. </typeparam>
        /// <typeparam name="U"> The types of the function's input arguments. </typeparam>
        template<typename T, typename ... U>
        struct Accessor<FunctionPointer<T, U...>>:              public Functor<FunctionPointer<T>>
        {
            using Functor::Functor;

            /// <summary> Invokes the stored accessor function with the given input arguments. </summary>
            /// <returns> The forwarded output argument of the accessor function. </returns>
            /// <param name="object"> An unused pointer to some object instance. </param>
            /// <param name="arguments"> A list of input arguments to be forwarded to the accessor function. </param>
            T operator ()(const void* object, U ... arguments)  const { return (_value)(arguments...); }
            /// <summary> Invokes the stored accessor function with the given input arguments. </summary>
            /// <returns> The forwarded output argument of the accessor function. </returns>
            /// <param name="object"> An unused reference to some object instance. </param>
            /// <param name="arguments"> A list of input arguments to be forwarded to the accessor function. </param>
            template<typename V>
            T operator ()(const V& object, U ... arguments)     const { return (_value)(arguments...); }
        };

        /// <summary> A structure that represents an accessor to a data member of a class. </summary>
        /// <typeparam name="T"> The type of the data stored by the member. </typeparam>
        /// <typeparam name="U"> The class to which the data member belongs. </typeparam>
        template<typename T, typename U>
        struct Accessor<MemberPointer<T, U>>:                   public Functor<MemberPointer<T, U>>
        {
            using Functor::Functor;

            /// <summary> Gets the value of the stored data member from a given object. </summary>
            /// <returns> The value of the object's data member. </returns>
            /// <param name="object"> A pointer to an instance of the class to which the data member belongs. </param>
            T operator ()(U* object)                            const { return (object->*_value); }
            /// <summary> Gets the value of the stored data member from a given object. </summary>
            /// <returns> The value of the object's data member. </returns>
            /// <param name="object"> A reference to an instance of the class to which the data member belongs. </param>
            T operator ()(U& object)                            const { return (object.*_value); }
            /// <summary> Gets the value of the stored data member from a given object. </summary>
            /// <returns> The value of the object's data member. </returns>
            /// <param name="object"> A pointer to an instance of the class to which the data member belongs. </param>
            T operator ()(const U* object)                      const { return (object->*_value); }
            /// <summary> Gets the value of the stored data member from a given object. </summary>
            /// <returns> The value of the object's data member. </returns>
            /// <param name="object"> A reference to an instance of the class to which the data member belongs. </param>
            T operator ()(const U& object)                      const { return (object.*_value); }

            /// <summary> Sets the value of the stored data member from a given object. </summary>
            /// <returns> The value of the object's data member. </returns>
            /// <param name="object"> A pointer to an instance of the class to which the data member belongs. </param>
            T operator ()(U* object, T value)                   const { return (object->*_value) = value; }
            /// <summary> Gets the value of the stored data member from a given object. </summary>
            /// <returns> The value of the object's data member. </returns>
            /// <param name="object"> A reference to an instance of the class to which the data member belongs. </param>
            T operator ()(U& object, T value)                   const { return (object.*_value) = value; }
        };

        /// <summary> A structure that represents a constant-qualified class method used to get or set data values. </summary>
        /// <typeparam name="T"> The type of the method's output argument. </typeparam>
        /// <typeparam name="U"> The class to which the method belongs. </typeparam>
        /// <typeparam name="V"> The types of the method's input arguments. </typeparam>
        template<typename T, typename U, typename ... V>
        struct Accessor<ConstMethodPointer<T, U, V...>>:        public Functor<ConstMethodPointer<T, U, V...>>
        {
            using Functor::Functor;

            /// <summary> Invokes the stored accessor method with the given input arguments. </summary>
            /// <returns> The forwarded output argument of the accessor method. </returns>
            /// <param name="object"> A pointer to an instance of the class to which the accessor method belongs. </param>
            /// <param name="arguments"> A list of input arguments to be forwarded to the accessor function. </param>
            T operator ()(const U* object, V ... arguments)     const { return (object->*_value)(arguments...); }
            /// <summary> Invokes the stored accessor method with the given input arguments. </summary>
            /// <returns> The forwarded output argument of the accessor method. </returns>
            /// <param name="object"> A reference to an instance of the class to which the accessor method belongs. </param>
            /// <param name="arguments"> A list of input arguments to be forwarded to the accessor function. </param>
            T operator ()(const U& object, V ... arguments)     const { return (object.*_value)(arguments...); }
        };

        /// <summary> A structure that represents a class method used to get or set data values. </summary>
        /// <typeparam name="T"> The type of the method's output argument. </typeparam>
        /// <typeparam name="U"> The class to which the method belongs. </typeparam>
        /// <typeparam name="V"> The types of the method's input arguments. </typeparam>
        template<typename T, typename U, typename ... V>
        struct Accessor<MethodPointer<T, U, V...>>:             public Functor<MethodPointer<T, U, V...>>
        {
            using Functor::Functor;

            /// <summary> Invokes the stored accessor method with the given input arguments. </summary>
            /// <returns> The forwarded output argument of the accessor method. </returns>
            /// <param name="object"> A pointer to an instance of the class to which the accessor method belongs. </param>
            /// <param name="arguments"> A list of input arguments to be forwarded to the accessor function. </param>
            T operator ()(U* object, V ... arguments)           const { return (object->*_value)(arguments...); }
            /// <summary> Invokes the stored accessor method with the given input arguments. </summary>
            /// <returns> The forwarded output argument of the accessor method. </returns>
            /// <param name="object"> A reference to an instance of the class to which the accessor method belongs. </param>
            /// <param name="arguments"> A list of input arguments to be forwarded to the accessor function. </param>
            T operator ()(U& object, V ... arguments)           const { return (object.*_value)(arguments...); }
        };

        /// <summary> A structure that represents a data member of a class. </summary>
        /// <typeparam name="T"> The type of the stored data. </typeparam>
        /// <typeparam name="U"> The class to which the data member belongs. </typeparam>
        template<typename T, typename U>
        struct Field:                                           public Accessor< MemberPointer<T, U> > 
        {
            using Accessor::Accessor;
        };


        /// <summary> A structure that represents a get-accessor method of a class. </summary>
        /// <typeparam name="T"> The type of the data retrieved by the method. </typeparam>
        /// <typeparam name="U"> The class to which the method belongs. </typeparam>
        template<typename T, typename U>
        struct Getter:                                          public Accessor< MethodPointer<T, U> >
        {
            using Accessor::Accessor;
        };
        /// <summary> A structure that represents a constant-qualified get-accessor method of a class. </summary>
        /// <typeparam name="T"> The type of the data retrieved by the method. </typeparam>
        /// <typeparam name="U"> The class to which the method belongs. </typeparam>
        template<typename T, typename U>
        struct Getter<T, const U>:                              public Accessor< ConstMethodPointer<T, U> >
        {
            using Accessor::Accessor;
        };

    }
}

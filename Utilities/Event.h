/* CHANGELOG
 * Written by Josh Grooms on 20151029
 */

#pragma once
#include "TypeDefinitions.h"
#include <algorithm>
#include <vector>



 /// <summary> An abstract interface meant for use in event callback functions. </summary>
template<typename ... T>
struct Callback
{   
    virtual void Invoke(T ... arguments) = 0;
};

/// <summary> A structure representing an ordinary function pointer that takes a single argument. </summary>
template<typename ... T>
struct PlainFunctionPointer : public Callback<T...>
{
    private:
        using FunctionPointer = void (*)(T ... arguments);

        /// <summary> A pointer to the function that can be invoked through this class. </summary>
        FunctionPointer Function;
        
    public:
        
        PlainFunctionPointer(FunctionPointer fun) : Function(fun) { }
        
        void Invoke(T ... arguments) override { Function(arguments...); }
};

/// <summary> A structure representing a pointer to an object method. </summary>
template<typename T, typename ... U>
struct ObjectMethodPointer : public Callback<U...>
{
    private:
        using MethodPointer = void (T::*)(U ... arguments);
        
        /// <summary> A pointer to the object instance needed to succesfully call a class method. </summary>
        T* Object;
        /// <summary> A pointer to the method function that will eventually be called. </summary>
        MethodPointer Method;
               
    public:
        
        ObjectMethodPointer(T* object, MethodPointer method) : 
           Object(object),
           Method(method)
        {
           
        }
        
        void Invoke(U ... arguments) override { (Object->*Method)(arguments...); }
};


///* ACTION - A class that enables simple events in C++ with callback functions that have no input or output arguments. 
// * 
// *      This class is designed to behave nearly identically to C# 'Action' type events. 
// */
//class Action
//{
//    private:
//        std::vector<Callback<>*> Subscriptions;
//
//
//    public:
//        /** PROPERTIES **/
//        /* COUNT - Gets the number of callback functions that are currently registered for this event. */
//        uint Count()    const { return Subscriptions.size(); }
//        /* ISEMPTY - Determines whether or not this event has any registered callback functions. */
//        bool IsEmpty()  const { return Subscriptions.empty(); }
//
//
//
//        /** CONSTRUCTOR **/
//        /* ACTION - Constructs a new 'Action' instance with an empty event queue. */
//        Action() : Subscriptions() { }
//        
//
//
//        /** UTILITIES **/
//        /* CLEAR - Removes all callback functions that are currently registered for this event. */
//        void Clear() { Subscriptions.clear(); }
//        /* REGISTER - Subscribes a new callback function to be executed when this event is triggered.
//         *
//         *      OUTPUT:
//         *          evt:        Event&
//         *
//         *      INPUT:
//         *          callback:   FunctionPointer
//         */
//        void Register(Callback<>* callback) { Subscriptions.push_back(callback); }
//        /* UNREGISTER - Unsubscribes a callback function, preventing its future execution when this event is triggered. */
//        void Unregister(Callback<>* callback)
//        {
//            Subscriptions.erase( std::remove(Subscriptions.begin(), Subscriptions.end(), callback), Subscriptions.end() );
//        }
//
//
//
//        /** OPERATORS **/
//        /* += - A shortcut operator that registers new callback functions for the event. */
//        void operator +=(Callback<>* callback) { Register(callback); }
//        /* -= - A shortcut operator that unregisters callback functions from the event. */
//        void operator -=(Callback<>* callback) { Unregister(callback); }
//        /* () - Serially executes each of the callback functions within the event queue. */
//        void operator ()()
//        {
//            for (auto callback : Subscriptions)
//                callback->Invoke();
//        }
//};
//
//
//
//
//
//
//template<typename T>
//class Event
//{
//    private:
//        typedef void (*FunctionPointer)(T x);
////        std::vector<FunctionPointer> Subscriptions;
//        std::vector<Callback<T>*> Subscriptions;
//    
//        
//
//    public:
//        /** PROPERTIES **/
//        /* COUNT - Gets the number of callback functions that are currently registered for this event. */
//        uint Count()        const { return Subscriptions.size(); }
//        /* ISEMPTY - Determines whether or not this event has any registered callback functions. */
//        bool IsEmpty()      const { return Subscriptions.empty(); }
//
//
//
//        /** CONSTRUCTOR **/
//        Event() : Subscriptions() { }
//
//
//
//        /** UTILITIEIS **/
//        /* CLEAR - Removes all callback functions that are currently registered for this event. */
//        void Clear()              { Subscriptions.clear(); }
//        /* REGISTER - Subscribes a new callback function to be executed when this event is triggered.
//         *
//         *      OUTPUT:
//         *          evt:        Event&
//         *
//         *      INPUT:
//         *          callback:   Callback<T>*
//         */
//        Event& Register(Callback<T>* callback)
//        {
//            Subscriptions.push_back(callback);
//            return *this;
//        }        
//        /* UNREGISTER - Unsubscribes a callback function, preventing its future execution when this event is triggered. */
//        Event& Unregister(Callback<T>* callback)
//        {
//            Subscriptions.erase( std::remove(Subscriptions.begin(), Subscriptions.end(), callback), Subscriptions.end() );
//            return *this;
//        }
//
//
//
//        /** OPERATORS **/
//        /* += - A shortcut operator that registers new function callbacks for an event. */
//        void operator +=(Callback<T>* callback) { Register(callback); }
//
//        void operator -=(Callback<T>* callback) { Unregister(callback); }
//        /* () - Serially executes each of the function callbacks within the event queue. */
//        void operator ()(T x)
//        {
//            for (auto callback : Subscriptions)
//                callback->Invoke(x);
//        }
//
//};

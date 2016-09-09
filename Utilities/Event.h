/* CHANGELOG
 * Written by Josh Grooms on 20151029
 */

#pragma once
#include "TypeDefinitions.h"
#include <algorithm>
#include <vector>



namespace Cyclone
{
	namespace Utilities
	{

		 /// <summary> An abstract interface meant for use in event callback functions. </summary>
		template<typename ... T>
		struct ICallback
		{   
			virtual void Invoke(T ... arguments) const = 0;
		};

		/// <summary> A structure representing an ordinary function pointer that takes a single argument. </summary>
		template<typename ... T>
		struct FunctionPointer : public ICallback<T...>
		{
			private:
				using Function = void (*)(T ... arguments);

				/// <summary> A pointer to the function that can be invoked through this class. </summary>
				Function _function;
        
			public:
        
                /// <summary> Constructs a new function object referring to a specific function pointer. </summary>
                /// <param name="fun"></param>
				FunctionPointer(Function fun) : _function(fun) { }
        
				void Invoke(T ... arguments) const override { _function(arguments...); }
		};

		/// <summary> A structure representing a pointer to an object method. </summary>
		template<typename T, typename ... U>
		struct MethodPointer : public ICallback<U...>
		{
			private:
				using Method = void (T::*)(U ... arguments);
        
				/// <summary> A pointer to the object instance needed to succesfully call a class method. </summary>
				T*      _object;
				/// <summary> A pointer to the method function that will eventually be called. </summary>
				Method  _method;
               
			public:
        
				MethodPointer(T* object, Method method) : 
				   _object(object),
				   _method(method)
				{
           
				}
				        
				void Invoke(U ... arguments) const override { (_object->*_method)(arguments...); }
		};



		template<typename ... T>
		class Event
		{
			private:
                using Function = void(*)(T ... arguments);

                template<typename S>
                using Method = void (S::*)(T ... arguments);

				std::vector<ICallback<T...>*> Subscriptions;
    
			public:
				/** PROPERTIES **/
                /// <summary> Gets the number of callback functions that are currently registered for this event. </summary>
				uint Count()        const { return Subscriptions.size(); }
                /// <summary> Determines whether this event has any registered callback functions. </summary>
				bool IsEmpty()      const { return Subscriptions.empty(); }



				/** CONSTRUCTOR **/
				Event() : Subscriptions() { }
                ~Event()
                {
                    for (auto callback : Subscriptions)
                        delete callback;
                }


				/** UTILITIES **/
                /// <summary> Removes all callback functions that are currently registered for this event. </summary>
				void Clear()              
                { 
                    for (auto callback : Subscriptions)
                        delete callback;
                    Subscriptions.clear(); 
                }
                /// <summary> Subscribes a new callback function to be executed when this event is triggered. </summary>
                /// <param name="callback"></param>
                void Register(Function callback)
                {
                    Subscriptions.push_back(new FunctionPointer<T...>(callback));
                }
                
                template<typename S>
                void Register(S* object, Method<S> callback)
                {
                    Subscriptions.push_back(new MethodPointer<S, T...>(object, callback));
                }

                /// <summary> Unsubscribes a callback function, preventing its future execution when this event is triggered. </summary>
				/*Event& Unregister(ICallback<T>* callback)
				{
					Subscriptions.erase( std::remove(Subscriptions.begin(), Subscriptions.end(), callback), Subscriptions.end() );
					return *this;
				}*/



				/** OPERATORS **/
                /// <summary> Serially executes each of the callback functions within the event queue. </summary>
				void operator ()(T ... arguments)
				{
					for (auto callback : Subscriptions)
						callback->Invoke(arguments...);
				}

		};

        /// <summary> A class that enables simple events in C++ with callback functions that have no input or output arguments. </summary>
        /// <remarks> This class is designed to behave similarly to C# 'Action' type events. </remarks>
        using Action = Event<>;

	}
}
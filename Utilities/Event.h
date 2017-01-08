/* CHANGELOG
 * Written by Josh Grooms on 20151029
 */

#pragma once
#include "Functions.h"
#include "Collections/List.h"
//#include <algorithm>
//#include <vector>



namespace Cyclone
{
	namespace Utilities
	{

		template<typename ... T>
		class Event
		{
			private:

                List<ICallback<T...>*> Subscriptions;
    
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
                    Subscriptions.Clear(); 
                }
                /// <summary> Subscribes a new callback function to be executed when this event is triggered. </summary>
                /// <param name="callback"></param>                
                void Register(Function<T...> callback)
                {
                    Subscriptions.Append(new Function<T...>(callback));
                }
                
                template<typename S>
                void Register(Method<S, T...> callback)
                {
                    Subscriptions.Append(new Method<S, T...>(callback));
                }

                template<typename S>
                void Register(S* object, MethodPointer<S, T...> callback)
                {
                    Subscriptions.Append(new Method<S, T...>(object, callback));
                }

                /// <summary> Unsubscribes a callback function, preventing its future execution when this event is triggered. </summary>
                void Remove(const ICallback<T...>& callback)
                {
                    uint idx = 0;
                    for (auto s : Subscriptions)
                        if (callback == *s) 
                        { 
                            delete s; 
                            Subscriptions.Remove(idx);
                            break;
                        }
                        else                { idx++; }
                }

                template<typename S>
                void Remove(S* object, MethodPointer<S, T...> callback) { Remove(Method<S, T...>(object, callback)); }



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
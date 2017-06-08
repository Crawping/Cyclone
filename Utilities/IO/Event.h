/* CHANGELOG
 * Written by Josh Grooms on 20151029
 */

#pragma once
#include "Collections/ArrayList.h"
#include "IO/Members.h"



namespace Cyclone
{
	namespace Utilities
	{

		template<typename ... T>
		class Event
		{
			private:

                ArrayList<ICallback<void, T...>*> Subscriptions;

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
                void Register(const ICallback<void, T...>* callback)
                {
                    Subscriptions.Append(callback->Copy());
                }
                /// <summary> Subscribes a new callback function to be executed when this event is triggered. </summary>
                /// <param name="callback"></param>
                void Register(Procedure<T...> callback)
                {
                    Subscriptions.Append(new Procedure<T...>(callback));
                }

                template<typename S>
                void Register(Method<void, S, T...> callback)
                {
                    Subscriptions.Append(new Method<void, S, T...>(callback));
                }

                template<typename S>
                void Register(S* object, MethodPointer<void, S, T...> callback)
                {
                    Subscriptions.Append(new Method<void, S, T...>(object, callback));
                }

                /// <summary> Unsubscribes a callback function, preventing its future execution when this event is triggered. </summary>
                void Remove(const ICallback<void, T...>& callback)
                {
                    uint idx = 0;
                    for (auto s : Subscriptions)
                        if (callback == *s)
                        {
                            delete s;
                            Subscriptions.Remove(idx);
                            return;
                        }
                        else
                            idx++;
                }

                template<typename S>
                void Remove(S* object, MethodPointer<void, S, T...> callback) { Remove(Method<void, S, T...>(object, callback)); }



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

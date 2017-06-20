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

        template<typename ... T> class Event;


        template<typename ... T> struct SubscriptionData
        {
            ICallback<void, T...>*  Callback;
            bool                    IsSuspended;
            Event<T...>*            Parent;
        };

        /// <summary> A structure that represents a callback subscription to an event. </summary>
        /// <typeparam name="T"> A list of input argument types matching those of some governing event structure. </typeparam>
        template<typename ... T> struct Subscription
        {
            friend class Event<T...>;
            private:
                
                SubscriptionData<T...>*     _data;

                /// <summary> Constructs a new live event subscription. </summary>
                /// <param name="data"> The event subscription data. </param>
                Subscription(SubscriptionData<T...>* data):         _data(data) { }
                
            public:

                /// <summary> Gets whether the subscription has been temporarily suspended. </summary>
                bool IsSuspended()                                  const { return _data ? _data->IsSuspended : true; }

                /// <summary> Constructs an empty event subscription. </summary>
                Subscription():                                     _data(nullptr) { }

                /// <summary> Removes the subscription data from the event's callback queue. </summary>
                /// <remarks> 
                ///     Calls to this method permanently disable an event subscription by deleting all of the backing data, 
                ///     making the subscription structure useless afterward. 
                /// </remarks>
                void Cancel()                                       { if (_data) { _data->Parent->Unsubscribe(*this); } }
                /// <summary> Enables a suspended event subscription. </summary>
                /// <remarks>
                ///     Calls to this method re-enable a suspended event subscription, which allows the governing event to 
                ///     once again execute the associated callback routine. Invoking this method on subscriptions that are 
                ///     not suspended has no effect.
                /// </remarks>
                void Resume()                                       { if (_data) { _data->IsSuspended = false; } }
                /// <summary> Temporarily disables the event subscription. </summary>
                /// <remarks> 
                ///     Calls to this method temporarily disable an event subscription, preventing further executions of 
                ///     the callback routine when the governing event is triggered. However, unlike the <see cref="Cancel"/> 
                ///     method, the backing data is persisted, and the subscription can subsequently be re-enabled by calling 
                ///     the <see cref="Resume"/> method.
                /// </remarks>
                void Suspend()                                      { if (_data) { _data->IsSuspended = true; } }

                /// <summary> Determines whether two event subscriptions are equivalent. </summary>
                /// <returns> A Boolean <c>true</c> if the subscriptions are equivalent, or <c>false</c> otherwise. </returns>
                /// <param name="other"> Another event subscription to be tested. </param>
                template<typename ... U> 
                bool operator ==(const Subscription<U...>& other)   const { return false; }
                bool operator ==(const Subscription& other)         const { return (_data == other._data); }
        };


        /// <summary> A structure that represents a collection of callback routines that can be executed on demand. </summary>
        /// <typeparam name="T"> A list of input argument types used to invoke the stored callback routines. </typeparam>
		template<typename ... T> class Event
		{
			private:

                ArrayList<SubscriptionData<T...>*> Subscriptions;

			public:

				/** PROPERTIES **/
                /// <summary> Gets the number of callback functions that are currently registered for this event. </summary>
				uint Count()        const { return Subscriptions.Count(); }
                /// <summary> Determines whether this event has any registered callback functions. </summary>
				bool IsEmpty()      const { return Subscriptions.IsEmpty(); }



				/** CONSTRUCTOR **/
				Event() { }
                Event(Event&& other)        = delete;
                Event(const Event& other)   = delete;
                ~Event()
                {
                    for (auto* s : Subscriptions)
                    {
                        delete s->Callback;
                        delete s;
                    }
                }


				/** UTILITIES **/
                /// <summary> Registers a new callback routine to be executed when the event is triggered. </summary>
                /// <returns> A structure that represents a live subscription to the event. </returns>
                /// <param name="callback"> The callback routine to be invoked. </param>
                Subscription<T...> Subscribe(const ICallback<void, T...>& callback)
                {
                    auto* data = new SubscriptionData<T...>{ callback.Copy(), false, this };
                    Subscriptions.Append(data);
                    return Subscription<T...>(data);
                }
                /// <summary> Registers a new callback function to be executed when this event is triggered.  </summary>
                /// <returns> A structure that represents a live subscription to the event. </returns>
                /// <param name="callback"> A pointer to the function that will be called when the event is triggered. </param>
                Subscription<T...> Subscribe(FunctionPointer<void, T...> callback)
                {
                    return Subscribe(Function<void, T...>(callback));
                }
                /// <summary> Registers a new callback method to be executed when the event is triggered.  </summary>
                template<typename S>
                Subscription<T...> Subscribe(S* object, MethodPointer<void, S, T...> callback)
                {
                    return Subscribe(Method<void, S, T...>(object, callback));
                }
                /// <summary> Cancels a particular subscription to the event. </summary>
                /// <param name="subscription"> The subscription to be cancelled. </param>
                void Unsubscribe(Subscription<T...>& subscription)
                {
                    int idx = Subscriptions.Find(subscription._data);
                    if (idx < 0)    { return; }
                    else            { Subscriptions.Remove(idx); }

                    delete subscription._data->Callback;
                    delete subscription._data;
                }



				/** OPERATORS **/
                /// <summary> Serially executes each of the callback functions within the event queue. </summary>
				void operator ()(T ... arguments)
				{
					for (auto* s : Subscriptions)
                        if (!s->IsSuspended)
                            s->Callback->Invoke(arguments...);
				}

		};

        /// <summary> A class that enables simple events in C++ with callback functions that have no input or output arguments. </summary>
        /// <remarks> This class is designed to behave similarly to C# 'Action' type events. </remarks>
        using Action = Event<>;

	}
}

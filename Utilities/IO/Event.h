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

        template<typename ... T> struct Subscription
        {
            friend class Event<T...>;

            private:
                
                SubscriptionData<T...>*     _data;

                Subscription(SubscriptionData<T...>* data):         _data(data) { }
                
            public:

                bool IsSuspended()                                  const { return _data ? _data->IsSuspended : true; }

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
                /// <summary> Removes all callback functions that are currently registered for this event. </summary>
				void Clear()
                {
                    for (auto& s : Subscriptions)
                    {
                        delete s.Callback;
                        delete s;
                    }
                    Subscriptions.Clear();
                }
                /// <summary> Registers a new callback routine to be executed when this event is triggered. </summary>
                /// <returns> A structure that represents a live subscription to the event. </returns>
                /// <param name="callback"> The callback function to be invoked. </param>
                
                Subscription<T...> Subscribe(const ICallback<void, T...>& callback)
                {
                    auto* data = new SubscriptionData<T...>{ callback.Copy(), false, this };
                    Subscriptions.Append(data);
                    return Subscription<T...>(data);
                }
                Subscription<T...> Subscribe(FunctionPointer<void, T...> callback)
                {
                    return Subscribe(Function<void, T...>(callback));
                }
                template<typename S>
                Subscription<T...> Subscribe(S* object, MethodPointer<void, S, T...> callback)
                {
                    return Subscribe(Method<void, S, T...>(object, callback));
                }
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

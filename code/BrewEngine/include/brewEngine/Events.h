#pragma once
#include <functional>
#include <list>
#include <utility>

namespace gl3::brewEngine::events {
    /// Represents an event that listeners can subscribe to.
    /// Events have an owner and an arbitrary number of arguments that are passed to the listeners when invoked.
    /// Only the owner is allowed to invoke the event.
    template<typename Owner, typename... Args>
    class Events {
      friend Owner; // the friend class owner can access non-public memebers

    public:
        //we don't know how many parameters will be needed wich is why a parameter pack is being used
        using listener_t = typename std::function<void(Args...)>;
        using container_t = typename std::list<listener_t>; //Any number of listeners might be interested in our event
        using handle_t = typename container_t::iterator; //We might need that so we can remove a listener from our list.

        /// Adds an event listener. All registered event listeners are called when the event is invoked.
        /// Its function signature is defined by the @a listener_t.
        /// @return Returns a handle you can pass to the @a removeListener function.
        handle_t addListener(listener_t listener) {
            listeners.push_back(listener);
            return --listeners.end();
        }
        /// Removes an event listener. Removed event listeners are no longer called when the event is invoked.
        /// @param handle The handle returned by the @a addListener function.
        void removeListener(handle_t handle) {
            listeners.erase(handle);
        }
    private:
        //invoke goes through the list and calls all callbacks. It also forwards all arguments to the functions
        void invoke(Args... args) {
            container_t unmodifiedCallbacks(listeners);
            for(auto &callback : unmodifiedCallbacks) {
                callback(std::forward<Args>(args)...);
            }
        }
        container_t listeners;
    };
}
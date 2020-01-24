//
// Created by Oshikuru on 12.9.2019..
//

#ifndef GX_BASE_FACTORY_H
#define GX_BASE_FACTORY_H

#include <functional>
#include <unordered_map>

namespace gx
{
    // Delegate for creating instance.
    template<typename BasePtr, typename ...Args>
    using creator_function = std::function<BasePtr(Args...)>;

    // Factory with base creation pattern for faster specific factory implementation.
    template<typename Derived, typename Key, typename BasePtr, typename ...Args>
    struct base_factory
    {
        // Get factory singleton instance.
        static Derived& instance() noexcept;

        // Register creation delegate with given key.
        bool register_creator(Key const& key, creator_function<BasePtr, Args...>&& creator);
        // Creates instance from registered delegate with given key.
        BasePtr create(Key const& key, Args... args) const;

    private:
        std::unordered_map<Key, creator_function<BasePtr, Args...>> creators_;
    };

    template <typename Derived, typename Key, typename BasePtr, typename ... Args>
    Derived& base_factory<Derived, Key, BasePtr, Args...>::instance() noexcept
    {
        static Derived factory;
        return factory;
    }

    template <typename Derived, typename Key, typename BasePtr, typename ... Args>
    bool base_factory<Derived, Key, BasePtr, Args...>::register_creator(Key const& key,
                                                                        creator_function<BasePtr, Args...>&& creator)
    {
        creators_[key] = std::move(creator);
        return true;
    }

    template <typename Derived, typename Key, typename BasePtr, typename ... Args>
    BasePtr base_factory<Derived, Key, BasePtr, Args...>::create(Key const& key, Args... args) const
    {
        return creators_.at(key)(args...);
    }
}

#endif //GX_BASE_FACTORY_H

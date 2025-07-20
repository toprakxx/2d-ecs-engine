#pragma once
#include <functional>
#include <memory>
#include <typeindex>
#include "./Event.h"
#include "../Logger/Logger.h"

class IEventCallback {
public:
	virtual ~IEventCallback() = default;
	virtual void Call(Event& e) = 0;
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
public:
	using CallbackFunction = void (TOwner::*) (TEvent&);

	EventCallback(TOwner* _ownerInstance, CallbackFunction _function)
	:
	ownerInstance(_ownerInstance), function(_function) {};
	
	
	virtual void Call(Event& e) {
		std::invoke(function, ownerInstance, static_cast<TEvent&>(e));
	}

private:
	TOwner* ownerInstance;
	CallbackFunction function;
};

class EventBus {
	using HandlerList = std::vector<std::unique_ptr<IEventCallback>>;

public:
	template <typename TOwner, typename TEvent>
	void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::* callbackFunction) (TEvent& event)) {
		auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
		subscribers[typeid(TEvent)].push_back(std::move(subscriber));
	}

	template <typename TEvent, typename ...TArgs>
	void EmitEvent(TArgs&& ...args) {
		auto callbacks = subscribers.find(typeid(TEvent));
		if (callbacks == subscribers.end()) {
			Logger::Log("Event with no listeners.");
			return;
		}

		TEvent event(std::forward<TArgs>(args)...);

		for (auto& uptr : callbacks->second) {
			uptr->Call(event);
		}
	}

private:
	std::unordered_map<std::type_index, HandlerList> subscribers;
};

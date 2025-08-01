#pragma once
#include <functional>
#include <typeindex>
#include <string>
#include "./Event.h"
#include "../Logger/Logger.h"

class EventBus {
public:
	template <typename TOwner, typename TEvent>
	void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction) (TEvent&)) {
		auto wrapper = [ownerInstance, callbackFunction](Event& event)	{
			std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(event));
		};
		subscribers[typeid(TEvent)].push_back(std::move(wrapper));
	}

	template <typename TEvent, typename ...TArgs>
	void EmitEvent(TArgs&&... args) {
		auto callbacks = subscribers.find(typeid(TEvent));
		if (callbacks == subscribers.end()) {
			// Logger::Err(std::string("Event with no listeners: ") + typeid(TEvent).name());
			return;
		}

		TEvent event(std::forward<TArgs>(args)...);

		for (auto callback : callbacks->second) callback(event);
	}

private:
	//A data structure holding the subscribed functions to each event type
	//those functions get called with the instance of the event type they are subscribed to
	std::unordered_map<std::type_index, std::vector<std::function<void(Event&)>>> subscribers;
};

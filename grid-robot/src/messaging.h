#pragma once

/**
 * @brief Typed singleton Topic. Every message type can
 * only be sent across a single Topic. Topics are
 * assigned as static variables; references to them
 * are guaranteed to last across the lifetime of the program.
 */
template <typename T> class Topic {
public:
	/// Get an reference to the topic singleton
	static Topic<T> &getInstance() {
		static Topic<T> instance;
		return instance;
	}

	/**
	 * @brief Publish a message to the topic. Published
	 * messages are copied into all of the subscriber queues.
	 */
	void publishTo(T message) {
		for (auto &queue : this->msg_queues) {
			(*queue).push(message);
		}
	}

	/**
	 * Subscribe to messages on this topic.
	 * @return Shared pointer to queue containing the subscribed message. To
	 * access the message, use the standard queue.front() and queue.pop()
	 * semantics.
	 */
	std::shared_ptr<std::queue<T>> subscribeTo() {
		std::shared_ptr<std::queue<T>> queue = std::make_shared<std::queue<T>>();
		this->msg_queues.push_back(queue);
		return queue;
	}

private:
	Topic(){};
	~Topic(){};
	Topic(const Topic<T> &) = delete;
	Topic<T> &operator=(const Topic<T> &) = delete;

protected:
	std::vector<std::shared_ptr<std::queue<T>>> msg_queues;
};

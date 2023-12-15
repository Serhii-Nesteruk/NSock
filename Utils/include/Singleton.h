#pragma once

#include <memory>
#include <mutex>

namespace Utils
{
	template<class T>
	class Singleton
	{
	public:
		static T& instance();

	protected:
		Singleton() = default;
		virtual ~Singleton() = default;
	};

	template<class T>
	T& Singleton<T>::instance()
	{
		static std::unique_ptr<T> object;
		static std::mutex mutex;
		if (!object)
		{
			std::lock_guard<decltype(mutex)> lockGuard(mutex);
			if (!object)
			{
				object = std::unique_ptr<T>(new T);
			}
		}

		return *object.get();
	}
}
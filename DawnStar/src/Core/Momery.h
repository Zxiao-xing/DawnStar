#pragma once

#include <memory>

namespace DawnStar {

	// ��װ C++ �� uniqueptr �� sharedptr ָ��
	template<typename T>
	using UniquePtr = std::unique_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr UniquePtr<T> CreateUnique(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	constexpr UniquePtr<T> CreateUniqueByPtr(T* typePtr) {
		return UniquePtr<T>(typePtr);
	}

	template<typename T>
	using SharedPtr = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr SharedPtr<T> CreateShared(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
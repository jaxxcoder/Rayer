#pragma once

#include <memory>

#define BIT(x) (1 << x)

//////////////////////////////////////
///////////PLATFORMS/////////////////
////Windows => GLFWwindow(Using glfw)
////////////////////////////////////

#ifdef RAYER_PLATFORM_WINDOWS

	#define RAYER_WINDOW GLFWwindow

#endif



namespace Rayer {

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T , typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {

		return std::make_shared<T>(std::forward<Args>(args)...);

	}


	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args ... args) {

		return std::make_unique<T>(std::forward<Args>(args)...);
	}


}
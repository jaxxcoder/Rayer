#include "rpch.h"

namespace Rayer {


	class IWindow {

	public:

		virtual void* getNativeWindow() = 0;
		virtual void init(int width, int height, const char* title) = 0;
		virtual bool shouldClose() const  = 0;
		virtual void swapBuffers() const = 0;
		virtual int getWindowWidth() const = 0;
		virtual int getWindowHeight() const = 0;
		virtual void poolEvents() const = 0;
		virtual void renderWindow()  = 0;
		virtual void maximizeWindow() const = 0;
		virtual void setIcon(const char* iconPath) = 0;
		virtual void clearFrame() = 0;
		virtual void cleanup() = 0;
		virtual void storeBufferSize() = 0;
	};

}
#pragma once

namespace Rayer {

	class IGui {

	public:

		
		virtual void renderGUI() = 0;
		virtual void setFont(const char*,float) = 0;
		virtual void setupContext(void*) = 0;
		virtual void cleanup() = 0;
	};

}
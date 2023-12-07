#pragma once

#include<filesystem>
namespace fs = std::filesystem;

#include "rpch.h"
#include "vertexArrayObject.h"
#include "vertexBufferObject.h"
#include "render/Shader.h"
#include "frameBuffer.h"

//#include <utility>


namespace Rayer {

	enum class RenderType {

		DrawArrays,
		DrawElements
	};

	class OpenGL_Renderer {

	public:

		struct Data {
			float vertices[9] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
			};
		};

		OpenGL_Renderer();

		void initialize();
		void render(Shader* rShader , RenderType _renderType);
		void bindFrameBuffer();
		void unbindFrameBuffer();
		GLuint getRenderTextureID();

	private:

		//***************Graphics data and configuaration*****************
		std::unique_ptr<vertexArrayObject> VAO = nullptr;
		std::unique_ptr<vertexBufferObject> VBO = nullptr;

		//**************Frame Buffer *********************
		std::unique_ptr<frameBuffer> _frameBuffer = nullptr;
		GLuint textureColorBuffer;
		


	};

}
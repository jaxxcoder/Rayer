#pragma once
#include "rpch.h"
#include "Texture.h"

namespace Rayer {


	class frameBuffer {

	public:

		GLuint ID = NULL;

		frameBuffer();
		void init();
		void createFrameBuffer();
		void setTexture(TextureType _textureType , GLuint _texID);
		void checkStatus();
		GLuint getRenderTextureID();
		void Bind();
		void Unbind();
	
	private:

		std::unique_ptr<Texture> _texture;

	};

}
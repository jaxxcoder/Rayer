#pragma once
#include "rpch.h"

namespace Rayer {

	enum class TextureType {

		Texture2D,
		Texture3D

	};

	class Texture {

	public :
	
		GLuint ID = NULL;

		Texture(TextureType _textureType);
		void createTexture(TextureType _textureType);
		GLuint getTextureID();

	};

}
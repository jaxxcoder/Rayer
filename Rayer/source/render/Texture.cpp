#include "Texture.h"

namespace Rayer {

	Texture::Texture(TextureType _textureType) {

		createTexture(_textureType);

		if (ID == NULL) {

			std::cout << "Texture creation failed" << std::endl;

		}

	}

	void Texture::createTexture(TextureType _textureType) {

		if (_textureType == TextureType::Texture2D) {

			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		}

		else if (_textureType == TextureType::Texture3D) {

			std::cout << "Sorry , not implemented yet" << std::endl;

		}

		else {

			std::cout << "Invalid texture type." << std::endl;

		}
	}

	GLuint Texture::getTextureID() {

		return ID;

	}

}
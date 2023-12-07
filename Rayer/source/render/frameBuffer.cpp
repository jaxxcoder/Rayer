#include "frameBuffer.h"

namespace Rayer {

	frameBuffer::frameBuffer() {

		_texture = std::make_unique<Texture>(TextureType::Texture2D);
		init();
	}

	void frameBuffer::createFrameBuffer() {

		glGenFramebuffers(1, &ID);
		glBindFramebuffer(GL_FRAMEBUFFER, ID);

	}

	void frameBuffer::setTexture(TextureType _textureType , GLuint _texID) {

		if (_textureType == TextureType::Texture2D) {

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texID, 0);

		}

		else {

			std::cout << "Sorry , Not implemented yet." << std::endl;

		}

	}

	void frameBuffer::checkStatus() {

		

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {

			std::cout << "Framebuffer creation failed" << std::endl;

		}

		else {

			std::cout << "Framebuffer creation successfull." << std::endl;

		}

		

	}

	void frameBuffer::Bind() {

		glBindFramebuffer(GL_FRAMEBUFFER, ID);

	}

	void frameBuffer::Unbind() {

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void frameBuffer::init() {

		createFrameBuffer();
		setTexture(TextureType::Texture2D, _texture->getTextureID());
		checkStatus();
		Unbind();
	}

	GLuint frameBuffer::getRenderTextureID() {

		return _texture->getTextureID();
	}

}
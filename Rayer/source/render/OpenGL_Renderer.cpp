#include "OpenGL_Renderer.h"


namespace Rayer {

	OpenGL_Renderer::OpenGL_Renderer() {
		
		Data vertData;

		VAO = std::make_unique<vertexArrayObject>();
		VBO = std::make_unique<vertexBufferObject>(vertData.vertices, sizeof(vertData.vertices));
		_frameBuffer = std::make_unique<frameBuffer>();
		initialize();
	}

	void OpenGL_Renderer::initialize() {

		VAO->Bind();

		VBO->Bind();

		VAO->LinkAttribute(*VBO, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		VAO->Unbind();

	}

	void OpenGL_Renderer::render(Shader* rShader , RenderType _renderType) {
		
		if (_renderType == RenderType::DrawArrays) {
			rShader->Activate();
			VAO->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
			VAO->Unbind();
			rShader->Deactivate();
		}

		else if (_renderType == RenderType::DrawElements) {

			std::cout << "Sorry , Not implemented yet." << std::endl;

		}

		else {

			std::cout << "Undefined render type!" << std::endl;

		}
	}

	

	void OpenGL_Renderer::bindFrameBuffer() {

		_frameBuffer->Bind();

	}

	void OpenGL_Renderer::unbindFrameBuffer() {

		_frameBuffer->Unbind();

	}


	GLuint OpenGL_Renderer::getRenderTextureID() {

		return _frameBuffer->getRenderTextureID();
	}

}
#pragma once
#include "rpch.h"
#include "vertexBufferObject.h"

namespace Rayer{

	class vertexArrayObject {
	
	public:

		GLuint ID = NULL;

		vertexArrayObject();
		
		void LinkAttribute(vertexBufferObject& vbo, GLint layout, GLint numCom, GLenum type, GLboolean noormalize , GLint stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();

	};
}
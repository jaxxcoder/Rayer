#pragma once
#include "rpch.h"

namespace Rayer {

	class vertexBufferObject {

	public:

		GLuint ID = NULL;
		
		vertexBufferObject(GLfloat* vertices , int size);

		void Bind();
		void Unbind();
		void Delete();
	};
}
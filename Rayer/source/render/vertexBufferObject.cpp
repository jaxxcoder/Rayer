#include "vertexBufferObject.h"

namespace Rayer {

	vertexBufferObject::vertexBufferObject(GLfloat* vertices , int size) {

		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER , size , vertices , GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void vertexBufferObject::Bind() {

		glBindBuffer(GL_ARRAY_BUFFER, ID);

	}

	void vertexBufferObject::Unbind() {

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void vertexBufferObject::Delete() {

		glDeleteBuffers(1, &ID);

	}

}
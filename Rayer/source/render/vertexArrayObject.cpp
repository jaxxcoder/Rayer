#include "vertexArrayObject.h"


namespace Rayer{

	vertexArrayObject::vertexArrayObject() {

		glGenVertexArrays(1, &ID);


	}

	void vertexArrayObject::LinkAttribute(vertexBufferObject& vbo, GLint layout, GLint numCom, GLenum type, GLboolean normalize ,  GLint stride, void* offset) {

		vbo.Bind();
		glVertexAttribPointer(layout, numCom, type, normalize, stride, offset);
		glEnableVertexAttribArray(layout);
		vbo.Unbind();
	}

	void vertexArrayObject::Bind() {

		glBindVertexArray(ID);

	 }

	void vertexArrayObject::Unbind() {

		glBindVertexArray(0);

	}

	void vertexArrayObject::Delete() {

		glDeleteVertexArrays(1, &ID);

	}

}
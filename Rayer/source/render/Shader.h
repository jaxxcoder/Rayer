#pragma once
#include "rpch.h"

namespace Rayer {

	class Shader {

	public:

		GLuint vertexShaderID = NULL;
		GLuint fragmentShaderID = NULL;
		GLuint programID = NULL;
		
		struct ShaderCode {

			const char* vertexShaderCode = "#version 330 core\n"
                                "layout (location = 0) in vec3 aPos;\n"
                                "void main() {\n"
                                "   gl_Position = vec4(0.4f * aPos.x,0.4f * aPos.y, aPos.z, 1.0);\n"
				"}\0";
			
			const char* fragmentShaderCode = "#version 330 core\n"
                                "out vec4 fragColor;\n"
                                "void main() {\n"
                                "   fragColor = vec4(0.0f , 1.0f , 0.0f , 1.0f);\n"
				"}\0";

		};

		Shader();

		void createShader(GLenum shaderType);
		void createProgram();
		void compileErrors(GLuint shaderID, const char* type);
		void attachShader(GLenum shaderType);
		void Activate();
		void validateProgram();
		void shaderCleanup();
		void linkProgram();
		void Deactivate();
		Shader* getInstance();

	private:

		Shader* shaderInstance;
	};

}
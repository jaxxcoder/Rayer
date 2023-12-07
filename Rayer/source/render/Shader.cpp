#include "Shader.h"

namespace Rayer {


	Shader::Shader() {

		shaderInstance = this;

		createShader(GL_VERTEX_SHADER);
		createShader(GL_FRAGMENT_SHADER);

		createProgram();

		//Activate();
		attachShader(GL_VERTEX_SHADER);
		attachShader(GL_FRAGMENT_SHADER);

		linkProgram();

		shaderCleanup();

		validateProgram();
	}

	void Shader::createShader(GLenum shaderType) {

		ShaderCode shader_source;

		if (shaderType == GL_VERTEX_SHADER) {

			vertexShaderID = glCreateShader(shaderType);
			glShaderSource(vertexShaderID, 1, &shader_source.vertexShaderCode, nullptr);
			glCompileShader(vertexShaderID);
			compileErrors(vertexShaderID, "VERTEX");

		}

		else if (shaderType == GL_FRAGMENT_SHADER) {

			fragmentShaderID = glCreateShader(shaderType);
			glShaderSource(fragmentShaderID, 1, &shader_source.fragmentShaderCode, nullptr);
			glCompileShader(fragmentShaderID);
			compileErrors(fragmentShaderID, "FRAGMENT");

		}

	}

	void Shader::createProgram() {

		programID = glCreateProgram();

		if (programID != NULL) {

			std::cout << "Shader program is successfully created with id " << programID << std::endl;

		}

	}

	void Shader::compileErrors(GLuint shaderID, const char* type) {

		GLint shaderStatus;
		char infoLog[1024];

		if (type == "VERTEX" || type == "FRAGMENT") {

			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderStatus);

			if (shaderStatus == GL_FALSE) {

				glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);

				std::cout << "Error compiling shader(" << type << ")" << "\n" << infoLog << std:: endl;

			}

			std::cout << "The shader(" << type << ") " << "is successfully compiled with id " << shaderID << "." << std::endl;
			 
			
		}

		else if(type == "PROGRAM") {

			glGetProgramiv(shaderID, GL_LINK_STATUS, &shaderStatus);

			if (shaderStatus == GL_FALSE) {

				glGetProgramInfoLog(shaderID, 1024, nullptr, infoLog);
				std::cout << "Error linking program :" << "\n" << infoLog << std::endl;

			}

			std::cout << "The shader program "<< "is successfully linked with id " << shaderID << "." << std::endl;

		}

		else if (type == "VALIDATE_PROGRAM") {

			glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &shaderStatus);

			if (shaderStatus == GL_FALSE) {

				glGetProgramInfoLog(shaderID, 1024, nullptr, infoLog);
				std::cout << "Error validating program :" << "\n" << infoLog << std::endl;

			}

			std::cout << "The shader program " << "is successfully validated with id " << shaderID << "." << std::endl;

		}

	}

	void Shader::attachShader(GLenum shaderType) {

		if (shaderType == GL_VERTEX_SHADER) {

			glAttachShader(programID, vertexShaderID);

		}

		else if (shaderType == GL_FRAGMENT_SHADER) {

			glAttachShader(programID, fragmentShaderID);

		}

	}

	void Shader::Activate() {
		
		glUseProgram(programID);
		std::cout << "Shader program with id: " << programID << " is activated" << std::endl;

	}

	void Shader::Deactivate() {

		glUseProgram(0);
		std::cout << "Shader program with id: " << programID << " is deactivated" << std::endl;
	}

	void Shader::shaderCleanup() {

		if (vertexShaderID == NULL && fragmentShaderID == NULL) {

			std::cout << "No shader found for cleanup" << std::endl;

		}

		else if (vertexShaderID != NULL && fragmentShaderID == NULL) {

			glDeleteShader(vertexShaderID);
			std::cout << "Shader cleanup process is completed." << std::endl;
		}

		else if (vertexShaderID == NULL && fragmentShaderID != NULL) {

			glDeleteShader(fragmentShaderID);
			std::cout << "Shader cleanup process is completed." << std::endl;

		}

		else {
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
			std::cout << "Shader cleanup process is completed." << std::endl;
		}
	}

	void Shader::linkProgram() {

		glLinkProgram(programID);
		compileErrors(programID, "PROGRAM");

	}

	void Shader::validateProgram() {

		glValidateProgram(programID);
		compileErrors(programID, "VALIDATE_PROGRAM");
	}

	Shader* Shader::getInstance() {

		return shaderInstance;

	}

}
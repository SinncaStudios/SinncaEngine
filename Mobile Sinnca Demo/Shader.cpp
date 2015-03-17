//
//  Shader.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Shader.h"
#include "OpenFile.h"
#include "Heap.h"
#include "Graphics.h"
#include "Platform.h"

#include "Computer.h"

namespace sinnca
{
	
	
	void shader::loadShaders(std::string vs, std::string fs, std::string gs)
	{
		
		vsText = openTextFile(vs);
		fsText = openTextFile(fs);
		
	}
	
	void shader::setShaders(std::string v, std::string f, std::string g)
	{
		
	}
	
	void shader::initShaders()
	{
		//GLint compiled;
		GLchar const *vSource = vsText.c_str();
		GLchar const *fSource = fsText.c_str();
		GLint vSize = (GLint)vsText.size();
		GLint fSize = (GLint)fsText.size();
		
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		
		glShaderSource(vertexShader, 1, &vSource, &vSize);
		glShaderSource(fragmentShader, 1, &fSource, &fSize);
		
		GLint success;
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLchar shaderLog1[200];
			glGetShaderInfoLog(vertexShader, sizeof(shaderLog1), 0, &shaderLog1[0]);
			fprintf(stderr, "Vertex Shader Log: %s\n", shaderLog1);
		}
		
		
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLchar shaderLog2[200];
			glGetShaderInfoLog(fragmentShader, sizeof(shaderLog2), 0, &shaderLog2[0]);
			fprintf(stderr, "Fragment Shader Log: %s\n", shaderLog2);
		}
		
		
		shaderProgram = glCreateProgram();
		if (shaderProgram == 0)
		{
			printf("Failed to create shader program...\n");
		}
		
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		
		attributePosition = glGetAttribLocation(shaderProgram, "position");
		attributeColor = glGetAttribLocation(shaderProgram, "vertColor");
		attributeTexCo = glGetAttribLocation(shaderProgram, "texCoord");
		
		uniformMVMatrix = glGetUniformLocation(shaderProgram, "MVMatrix");
		uniformNormalMatrix = glGetUniformLocation(shaderProgram, "NORMatrix");
		uniformTex = glGetUniformLocation(shaderProgram, "tex");
		
		//glEnableVertexAttribArray(attributeColor);
		glEnableVertexAttribArray(attributePosition);
		glEnableVertexAttribArray(attributeTexCo);
		
		
		//check program
		GLint logLen;
		GLchar log[200];
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			glGetProgramInfoLog(shaderProgram, logLen, &logLen, log);
			fprintf(stderr, "GLSL log: %s\n", log);
		}
	}
	
	// functions for setting uniform values with floats
	bool shader::uniformVar(std::string var, float value1)
	{
		GLint loc = glGetUniformLocation(shaderProgram, var.c_str());
		if (loc == -1)
		{
			return false;
		}
		glUniform1f(loc, value1);
		return true;
	}
	bool shader::uniformVar(std::string var, float value1, float value2)
	{
		GLint loc = glGetUniformLocation(shaderProgram, var.c_str());
		if (loc == -1)
		{
			return false;
		}
		glUniform2f(loc, value1, value2);
		return true;
	}
	bool shader::uniformVar(std::string var, float value1, float value2, float value3)
	{
		GLint loc = glGetUniformLocation(shaderProgram, var.c_str());
		if (loc == -1)
		{
			return false;
		}
		glUniform3f(loc, value1, value2, value3);
		return true;
	}
	bool shader::uniformVar(std::string var, float value1, float value2, float value3, float value4)
	{
		GLint loc = glGetUniformLocation(shaderProgram, var.c_str());
		if (loc == -1)
		{
			return false;
		}
		glUniform4f(loc, value1, value2, value3, value4);
		return true;
	}
	
	// functions for setting uniform values with integers
	bool shader::uniformVar(std::string var, int value1)
	{
		GLint loc = glGetUniformLocation(shaderProgram, var.c_str());
		if (loc == -1)
		{
			return false;
		}
		glUniform1i(loc, value1);
		return true;
	}
	bool shader::uniformVar(std::string var, int value1, int value2)
	{
		GLint loc = glGetUniformLocation(shaderProgram, var.c_str());
		if (loc == -1)
		{
			return false;
		}
		glUniform2i(loc, value1, value2);
		return true;
	}
	bool shader::uniformVar(std::string var, int value1, int value2, int value3)
	{
		GLint loc = glGetUniformLocation(shaderProgram, var.c_str());
		if (loc == -1)
		{
			return false;
		}
		glUniform3i(loc, value1, value2, value3);
		return true;
	}
	bool shader::uniformVar(std::string var, int value1, int value2, int value3, int value4)
	{
		GLint loc = glGetUniformLocation(shaderProgram, var.c_str());
		if (loc == -1)
		{
			return false;
		}
		glUniform4i(loc, value1, value2, value3, value4);
		return true;
	}
	
	bool shader::uniformVar(std::string var, bool value1)
	{
		GLint loc = glGetUniformLocation(shaderProgram, var.c_str());
		if (loc == -1)
		{
			return false;
		}
		glUniform1i(loc, (int)value1);
		return true;
	}
	
	void shader::bindShader()
	{
		glUseProgram(shaderProgram);
		
		//glUniformMatrix4fv(uniformMVMatrix, 1, false, (float*)Graphics->getModelMatrix());
		//glUniformMatrix3fv(uniformNormalMatrix, 1, false, (float*)Graphics->getNormalMatrix());
	}
	
	void shader::unBindShader()
	{
		glUseProgram(0);
	}
	
	
	void* shader::operator new(size_t s, std::string n)
	{
		shader* sh = Script::createObject<shader>();
		
		Script::setGlobal(n);
		return (void*)sh;
	}
	
	void shader::operator delete(void *p)
	{
		Heap->deallocate(p);
	}
	/*
	defaultShader* defaultShader::_instance = NULL;
	defaultShader* defaultShader::Instance()
	{
		if (_instance == NULL)
		{
			_instance = Heap->allocateNew<defaultShader>();
			
			_instance->vsText =
			"attribute vec4 position;"
			"attribute vec4 VertColor;"
			"attribute vec2 TexCoord;"
			"uniform vec4 FaceColor;"
			"uniform mat4 MVMatrix;"
			"uniform mat3 NORMatrix;"
			"varying vec4 SNColor = FaceColor;"
			"varying vec2 TexCoordv = TexCoord;"
			//"varying mat4 testThing = MVMatrix;"
			
			"void main()"
			"{"
			"mat4 idty;"
			"idty[0] = vec4(1.0, 0.0, 0.0, 0.0);"
			"idty[1] = vec4(0.0, 1.0, 0.0, 0.0);"
			"idty[2] = vec4(0.0, 0.0, 1.0, 0.0);"
			"idty[3] = vec4(0.0, 0.0, 0.0, 1.0);"
			//"gl_FrontColor = SNColor;"
			//"gl_TexCoord[0] = gl_MultiTexCoord0;"
			"gl_Position = MVMatrix * position;"
			//"TexCoordv = TexCoord;"
			"}";
			
			_instance->fsText = "uniform sampler2D tex;"
#ifdef snMobile
			"varying lowp vec4 SNColor;"
			"varying lowp vec2 TexCoordv;"
#else
			"varying vec4 SNColor;"
			
#endif
			"uniform bool textured;"
			//"varying mat4 testThing;"
			//"vec4 convert(mat4 m){return vec4(m[0][0] / 2.0, m[1][1], m[2][2], m[3][3] / 2.0);}"
			"void main(){"
			
			//"mat4 testM;"
			//"testM[0] = vec4(1.0, 0.0, 0.0, 0.0);"
			//"testM[1] = vec4(0.0, 1.0, 0.0, 0.0);"
			//"testM[2] = vec4(0.0, 0.0, 1.0, 0.0);"
			//"testM[3] = vec4(0.0, 0.0, 0.0, 1.0);"
			
			"if(textured)"
			"{"
			"gl_FragColor = SNColor * texture2D(tex, TexCoordv);"
			"} else {"
			"gl_FragColor = SNColor;"
			//"gl_FragColor = vec4(1.0, 0.4, 0.8, 1.0);"
			//"gl_FragColor = convert(testThing);"
			"}"
			"}";
			
			_instance->fsText = openTextFile(Computer->getResourcePath() + "/BasicFrag.fs");
			_instance->vsText = openTextFile(Computer->getResourcePath() + "/BasicVert.vs");
			
			_instance->initShaders();
			Graphics::currentShader = _instance;
			
		}
		
		return _instance;
	}
	*/
	
	
	
	static int l_newShader(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this shader...");
		}
		
		Script::checkTable(1);
		createShader(lua_tostring(L, 2));
		return 0;
	}
	
	
	
	static const luaL_Reg shaderFuncs[] = {
		{"new", l_newShader},
		{NULL, NULL}
	};
	
	
	void registerShader()
	{
		Script::registerType<shader>(shaderFuncs);
	}
}
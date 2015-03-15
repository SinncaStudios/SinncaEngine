//
//  Shader.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Shader__
#define __SinncaEngine__Shader__

#include <iostream>
#include "i_graphics.h"
#include "Script.h"

namespace sinnca
{
	class shader
	{
		//const GLchar* vsText;
		//const GLchar* fsText;
		std::string vsText;
		std::string fsText;
		
		std::string vsFile;
		std::string fsFile;
		
		unsigned int shaderProgram;
		unsigned int vertexShader;
		unsigned int fragmentShader;
		
		// a VERY basic glsl precompiler
		void preCompile();
		
	public:
		
		static constexpr auto metatable = "shader";
		
		//shader();
		
		GLint uniformMVMatrix, uniformNormalMatrix, attributeColor, attributePosition, attributeTexCo, uniformTex;
		void loadShaders(std::string vs, std::string fs, std::string gs = "");
		void setShaders(std::string v, std::string f, std::string g = "");
		
		void initShaders();
		
		// functions for setting uniform values with floats
		bool uniformVar(std::string var, float value1);
		bool uniformVar(std::string var, float value1, float value2);
		bool uniformVar(std::string var, float value1, float value2, float value3);
		bool uniformVar(std::string var, float value1, float value2, float value3, float value4);
		
		// functions for setting uniform values with integers
		bool uniformVar(std::string var, int value1);
		bool uniformVar(std::string var, int value1, int value2);
		bool uniformVar(std::string var, int value1, int value2, int value3);
		bool uniformVar(std::string var, int value1, int value2, int value3, int value4);
		
		bool uniformVar(std::string var, bool value1);
		
		void bindShader();
		void unBindShader();
		
		unsigned int getProgram()
		{
			return shaderProgram;
		}
		
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
		
	};
	
	#define createShader(a) new(a)shader()
	void registerShader();
	/*
#define DefaultShader (defaultShader::Instance())
	class defaultShader : public shader
	{
		
	public:
		
		static defaultShader* Instance();
		
	protected:
		
		static defaultShader* _instance;
	};
	 */
}

#endif /* defined(__SinncaEngine__Shader__) */

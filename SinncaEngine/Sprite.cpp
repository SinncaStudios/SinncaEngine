//
//  Sprite.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/2/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Sprite.h"
#include "Graphics.h"
#include "Heap.h"

namespace sinnca
{
	sprite::sprite()
	{
		
		newind[0] = 0;
		newind[1] = 1;
		newind[2] = 3;
		newind[3] = 2;
		
		glGenBuffers(1, &vBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glGenBuffers(1, &iBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(newind), newind, GL_STATIC_DRAW);
		
	}
	
	sprite::~sprite()
	{
		glDeleteBuffers(1, &vBuffer);
		glDeleteBuffers(1, &iBuffer);
	}
	
	
	
	void sprite::render()
	{
		
		
		glUseProgram(Graphics::currentShader->getProgram());
		
		
		glUniformMatrix4fv(Graphics::currentShader->uniformMVMatrix, 1, GL_FALSE, (float*)Graphics::getCombinedMatrix());
		
		
		glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
		
		glVertexAttribPointer(Graphics::currentShader->attributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
		glVertexAttribPointer(Graphics::currentShader->attributeTexCo, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(float) * 3));
		
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);
	}
	
	
	vertex* sprite::getVertices()
	{
		return vertices;
	}
	
}



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
		/*
		 // Start with vertex data
		 vertices[0].position.x = 0.0f;
		 vertices[0].position.y = 0.0f;
		 vertices[0].position.z = 0.0f;
		 
		 vertices[1].position.x = 1.0f;
		 vertices[1].position.y = 0.0f;
		 vertices[1].position.z = 0.0f;
		 
		 vertices[2].position.x = 1.0f;
		 vertices[2].position.y = 1.0f;
		 vertices[2].position.z = 0.0f;
		 
		 vertices[3].position.x = 0.0f;
		 vertices[3].position.y = 1.0f;
		 vertices[3].position.z = 0.0f;
		 
		 // Normals
		 vertices[0].normal.x = 0.0f;
		 vertices[0].normal.y = 0.0f;
		 vertices[0].normal.z = 0.0f;
		 
		 vertices[1].normal.x = 0.0f;
		 vertices[1].normal.y = 0.0f;
		 vertices[1].normal.z = 0.0f;
		 
		 vertices[2].normal.x = 0.0f;
		 vertices[2].normal.y = 0.0f;
		 vertices[2].normal.z = 0.0f;
		 
		 vertices[3].normal.x = 0.0f;
		 vertices[3].normal.y = 0.0f;
		 vertices[3].normal.z = 0.0f;
		 
		 // Then texture coordinates
		 vertices[0].texco.u = 0.0f;
		 vertices[0].texco.v = 0.0f;
		 
		 vertices[1].texco.u = 1.0f;
		 vertices[1].texco.v = 0.0f;
		 
		 vertices[2].texco.u = 1.0f;
		 vertices[2].texco.v = 1.0f;
		 
		 vertices[3].texco.u = 0.0f;
		 vertices[3].texco.v = 1.0f;
		 */
		
		
		
		//ind = new GLuint[4]; //sprites only need 4 vertices
		//ind = (GLuint*)Heap->allocate(sizeof(GLuint) * 4, __alignof(GLuint));
		/*
		 // this will be more complex in the mesh class
		 ind[0] = 0;
		 ind[1] = 1;
		 ind[2] = 3;
		 ind[3] = 2;*/
		
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
		
		
		//Graphics->setMatrixMode(SINNCA_MODELVIEW_MATRIX);
		//Graphics->move(0.0f, -left, 0.0f);
		//Graphics->scale(100.0f, 100.0f, 0.0f);
		
		
		glUseProgram(Graphics->currentShader->getProgram());
		
		
		glUniformMatrix4fv(Graphics->currentShader->uniformMVMatrix, 1, GL_FALSE, (float*)Graphics->getCombinedMatrix());
		
		/*
		 GLint att = glGetAttribLocation(Graphics->currentShader->getProgram(), "position");
		 
		 glEnableVertexAttribArray(att);
		 glVertexAttribPointer(att, 2, GL_FLOAT, GL_FALSE, 0, POSITION);
		 
		 //att = glGetAttribLocation(Graphics->currentShader->getProgram(), "VertColor");
		 
		 //glEnableVertexAttribArray(att);
		 //glVertexAttribPointer(att, 4, GL_FLOAT, GL_FALSE, 0, COLOR);
		 
		 glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		 //left += 0.1f;
		 */
		/*
		 //Desktop Renderer
		 //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		 glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
		 
		 glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(vertex), vertices);
		 glTexCoordPointer(2, GL_FLOAT, sizeof(vertex), (GLvoid*)offsetof(vertex, texco));
		 glVertexPointer(2, GL_FLOAT, sizeof(vertex), (GLvoid*)offsetof(vertex, position));
		 
		 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
		 
		 glUniformMatrix4fv(Graphics->currentShader->uniformMVMatrix, 1, GL_FALSE, (float*)Graphics->getModelMatrix());
		 glEnableVertexAttribArray(Graphics->currentShader->attributePosition);
		 glVertexAttribPointer(Graphics->currentShader->attributePosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
		 
		 glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, NULL);
		 //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		 */
		
		/*
		 glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
		 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
		 glVertexAttribPointer(Graphics->currentShader->attributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), vertices);
		 
		 glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		 */
		/*
		 glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
		 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
		 
		 
		 glVertexAttribPointer(Graphics->currentShader->attributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
		 
		 
		 glDrawElements(GL_TRIANGLE_STRIP, sizeof(newind) / sizeof(newind[0]), GL_UNSIGNED_BYTE, 0);
		 */
		
		glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
		
		glVertexAttribPointer(Graphics->currentShader->attributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
		glVertexAttribPointer(Graphics->currentShader->attributeTexCo, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(float) * 3));
		
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);
	}
}
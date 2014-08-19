//
//  Tree.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/10/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Tree.h"
#include "Heap.h"

#include "Computer.h"
#include "Script.h"
#include "Global.h"

namespace sinnca
{
	tree* tree::_instance = NULL;
	
	tree* tree::Instance()
	{
		if (_instance == NULL)
		{
			_instance = Heap->allocateNew<tree>();
		}
		
		return _instance;
	}
	
	tree::tree()
	{
		root = NULL;
		currentScene = this;
		
		entityStorage = NULL;
		name = "root";
		
	}
	
	tree::~tree()
	{
		
	}
	
	void tree::setup(const char* path)
	{
		Script->newBlankTable();
		
		Script->pushValue(1);
		Script->setMetaTable(-2);
		
		Script->pushValue(1);
		Script->setField(1, "__index");
		
		root = (scene**)Script->newUserdata<scene>();
		*root = Heap->allocateNew<scene>();
		
		Script->getGlobal("scene");
		Script->setMetaTable(-2);
		Script->getMetaTable("scene");
		Script->setMetaTable(-2);
		
		Script->setField(-2, "__self");
		Script->setGlobal("root");
		
#ifdef snMobile
		Script->doFile(path);
#else
		Script->doFile(Computer->getResourcePath() + "/" + "main.lua");
#endif
		
	}
	
	/*
	void tree::render()
	{
		children.resetItr();
		for (int i = 0; i < noOfChildren; i++, children++)
		{
			if (children.getData())
			{
				children.getData()->render();
			}
		}
	}
	 */
	
}
//
//  Node.cpp
//  Sinnca Engine v2
//
//  Created by Ryan Oldis on 7/27/11.
//  Copyright 2011 Sinnca Studios. All rights reserved.
//

#include "Node.h"
#include "script.h"

node::node()
{
	parent = NULL;
	
	noOfChildren = 0;
	draw = true;
}

node::~node()
{
	children.clear();
}


node* node::getParent()
{
	return parent;
}
void node::setParent(node* np)
{
	if (parent != NULL)
	{
		parent->removeChild(this);
	}
	
	parent = np;
}
void node::addChild(node* ch)
{
	if (ch != NULL)
	{
		
		ch->setParent(this);
		children.push_back(ch);
		
		noOfChildren++;
	}
}
void node::removeChild(node* ch)
{
	if (ch != NULL && noOfChildren > 0)
	{
		for (int i = 0; i < noOfChildren; i++)
		{
			if (children[i] == ch)
			{
				children.erase(children.begin() + i);
				break;
			}
		}
	}
}

void node::callBehavior()
{
	for (int i = 0; i < noOfChildren; i++)
	{
		children[i]->callBehavior();
	}
	
	Script->getGlobal(name);
	
	Script->getLocal(-1, "update");
	//Script->checkType(2, LUA_TFUNCTION);
	
	Script->call(0, 0);
}




static const luaL_Reg nodeFuncs[] = {
	
	{"addChild", addChild},
	{"removeChild", removeChild},
	{NULL, NULL}
};

void registerNode(lua_State* L)
{
	luaL_register(L, "node", nodeFuncs);
	lua_pushvalue(L,-1);
	lua_setfield(L, -2, "__index"); 
}
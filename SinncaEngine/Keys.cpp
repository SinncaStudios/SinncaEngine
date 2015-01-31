//
//  Keys.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/13/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include <stdio.h>
#include "Input.h"
#include "Script.h"

namespace sinnca
{
	void Input::setupKeys()
	{
		Script->newBlankTable();
		
		
		Script->setTableField("UNKNOWN", 0);
		Script->setTableField("first", 0);
		Script->setTableField("backspace", 8);
		Script->setTableField("tab", 9);
		Script->setTableField("clear", 12);
		Script->setTableField("return", 13);
		Script->setTableField("pause", 19);
		Script->setTableField("escape", 27);
		Script->setTableField("space", 32);
		Script->setTableField("exclaim", 33);
		Script->setTableField("dbl_quote", 34);
		Script->setTableField("hash", 35);
		Script->setTableField("dollar", 36);
		Script->setTableField("ampersand", 38);
		Script->setTableField("quote", 39);
		Script->setTableField("paren_l", 40);
		Script->setTableField("paren_r", 41);
		Script->setTableField("asterisk", 42);
		Script->setTableField("plus", 43);
		Script->setTableField("comma", 44);
		Script->setTableField("minus", 45);
		Script->setTableField("period", 46);
		Script->setTableField("slash", 47);
		Script->setTableField("_0", 48);
		Script->setTableField("_1", 49);
		Script->setTableField("_2", 50);
		Script->setTableField("_3", 51);
		Script->setTableField("_4", 52);
		Script->setTableField("_5", 53);
		Script->setTableField("_6", 54);
		Script->setTableField("_7", 55);
		Script->setTableField("_8", 56);
		Script->setTableField("_9", 57);
		Script->setTableField("colon", 58);
		Script->setTableField("semicolon", 59);
		Script->setTableField("less", 60);
		Script->setTableField("equals", 61);
		Script->setTableField("greater", 62);
		Script->setTableField("question", 63);
		Script->setTableField("at", 64);
		
		Script->setTableField("bracket_l", 91);
		Script->setTableField("backslash", 92);
		Script->setTableField("bracket_r", 93);
		Script->setTableField("caret", 94);
		Script->setTableField("underscore", 95);
		Script->setTableField("backquote", 96);
		Script->setTableField("a", 97);
		Script->setTableField("b", 98);
		Script->setTableField("c", 99);
		Script->setTableField("d", 100);
		Script->setTableField("e", 101);
		Script->setTableField("f", 102);
		Script->setTableField("g", 103);
		Script->setTableField("h", 104);
		Script->setTableField("i", 105);
		Script->setTableField("j", 106);
		Script->setTableField("k", 107);
		Script->setTableField("l", 108);
		Script->setTableField("m", 109);
		Script->setTableField("n", 110);
		Script->setTableField("o", 111);
		Script->setTableField("p", 112);
		Script->setTableField("q", 113);
		Script->setTableField("r", 114);
		Script->setTableField("s", 115);
		Script->setTableField("t", 116);
		Script->setTableField("u", 117);
		Script->setTableField("v", 118);
		Script->setTableField("w", 119);
		Script->setTableField("x", 120);
		Script->setTableField("y", 121);
		Script->setTableField("z", 122);
		Script->setTableField("delete", 127);
		
		/*
		 // don't do this yet
		for (int i = 0; i < 95; i++)
		{
			Script->setTableField("WORLD_" + (160 + i), 160 + i);
		}
		 */
		
		Script->setTableField("kp0", 256);
		Script->setTableField("kp1", 257);
		Script->setTableField("kp2", 258);
		Script->setTableField("kp3", 259);
		Script->setTableField("kp4", 260);
		Script->setTableField("kp5", 261);
		Script->setTableField("kp6", 262);
		Script->setTableField("kp7", 263);
		Script->setTableField("kp8", 264);
		Script->setTableField("kp9", 265);
		Script->setTableField("kp_period", 266);
		Script->setTableField("kp_divide", 267);
		Script->setTableField("kp_multiply", 268);
		Script->setTableField("kp_minus", 269);
		Script->setTableField("kp_plus", 270);
		Script->setTableField("kp_enter", 271);
		Script->setTableField("kp_equals", 272);
		
		Script->setTableField("up", 273);
		Script->setTableField("down", 274);
		Script->setTableField("right", 275);
		Script->setTableField("left", 276);
		Script->setTableField("insert", 277);
		Script->setTableField("home", 278);
		Script->setTableField("end", 279);
		Script->setTableField("pageUp", 280);
		Script->setTableField("pageDown", 281);
		
		Script->setTableField("f1", 282);
		Script->setTableField("f2", 283);
		Script->setTableField("f3", 284);
		Script->setTableField("f4", 285);
		Script->setTableField("f5", 286);
		Script->setTableField("f6", 287);
		Script->setTableField("f7", 288);
		Script->setTableField("f8", 289);
		Script->setTableField("f9", 290);
		Script->setTableField("f10", 291);
		Script->setTableField("f11", 292);
		Script->setTableField("f12", 293);
		Script->setTableField("f13", 294);
		Script->setTableField("f14", 295);
		Script->setTableField("f15", 296);
		
		Script->setTableField("numLock", 300);
		Script->setTableField("capsLock", 301);
		Script->setTableField("scrollLock", 302);
		Script->setTableField("rShift", 303);
		Script->setTableField("lShift", 304);
		Script->setTableField("rCtrl", 305);
		Script->setTableField("lCtrl", 306);
		Script->setTableField("rAlt", 307);
		Script->setTableField("lAlt", 308);
		Script->setTableField("rMeta", 309);
		Script->setTableField("lMeta", 310);
		Script->setTableField("rSuper", 311);
		Script->setTableField("lSuper", 312);
		Script->setTableField("mode", 313);
		Script->setTableField("compose", 314);
		
		Script->setTableField("help", 315);
		Script->setTableField("printScn", 316);
		Script->setTableField("sysReq", 317);
		Script->setTableField("break", 318);
		Script->setTableField("menu", 319);
		Script->setTableField("power", 320);
		Script->setTableField("euro", 321);
		Script->setTableField("undo", 322);
		
		Script->setGlobal("Key");
	}
}
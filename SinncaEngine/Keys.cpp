//
//  Keys.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/13/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include <stdio.h>
#include <sstream>
#include "Input.h"
#include "Script.h"

namespace sinnca
{
	void Input::keySetupHelper(int currentKey)
	{
		// possible alternatives:
		//
		// array of strings
		// strings in inputTypes
		
		switch (currentKey)
		{
		
					case 8:
			Script->push("backspace");
			break;
					case 9:
			Script->push("tab");
			break;
					case 12:
			Script->push("clear");
			break;
					case 13:
			Script->push("return");
			break;
					case 19:
			Script->push("pause");
			break;
					case 27:
			Script->push("escape");
			break;
					case 32:
			Script->push("space");
			break;
					case 33:
			Script->push("exclaim");
			break;
					case 34:
			Script->push("dbl_quote");
			break;
					case 35:
			Script->push("hash");
			break;
					case 36:
			Script->push("dollar");
			break;
					case 38:
			Script->push("ampersand");
			break;
					case 39:
			Script->push("quote");
			break;
					case 40:
			Script->push("paren_l");
			break;
					case 41:
			Script->push("paren_r");
			break;
					case 42:
			Script->push("asterisk");
			break;
					case 43:
			Script->push("plus");
			break;
					case 44:
			Script->push("comma");
			break;
					case 45:
			Script->push("minus");
			break;
					case 46:
			Script->push("period");
			break;
					case 47:
			Script->push("slash");
			break;
					case 48:
			Script->push("_0");
			break;
					case 49:
			Script->push("_1");
			break;
					case 50:
			Script->push("_2");
			break;
					case 51:
			Script->push("_3");
			break;
					case 52:
			Script->push("_4");
			break;
					case 53:
			Script->push("_5");
			break;
					case 54:
			Script->push("_6");
			break;
					case 55:
			Script->push("_7");
			break;
					case 56:
			Script->push("_8");
			break;
					case 57:
			Script->push("_9");
			break;
					case 58:
			Script->push("colon");
			break;
					case 59:
			Script->push("semicolon");
			break;
					case 60:
			Script->push("less");
			break;
					case 61:
			Script->push("equals");
			break;
					case 62:
			Script->push("greater");
			break;
					case 63:
			Script->push("question");
			break;
					case 64:
			Script->push("at");
			break;
					
					case 91:
			Script->push("bracket_l");
			break;
					case 92:
			Script->push("backslash");
			break;
					case 93:
			Script->push("bracket_r");
			break;
					case 94:
			Script->push("caret");
			break;
					case 95:
			Script->push("underscore");
			break;
					case 96:
			Script->push("backquote");
			break;
					case 97:
			Script->push("a");
			break;
					case 98:
			Script->push("b");
			break;
					case 99:
			Script->push("c");
			break;
					case 100:
			Script->push("d");
			break;
					case 101:
			Script->push("e");
			break;
					case 102:
			Script->push("f");
			break;
					case 103:
			Script->push("g");
			break;
					case 104:
			Script->push("h");
			break;
					case 105:
			Script->push("i");
			break;
					case 106:
			Script->push("j");
			break;
					case 107:
			Script->push("k");
			break;
					case 108:
			Script->push("l");
			break;
					case 109:
			Script->push("m");
			break;
					case 110:
			Script->push("n");
			break;
					case 111:
			Script->push("o");
			break;
					case 112:
			Script->push("p");
			break;
					case 113:
			Script->push("q");
			break;
					case 114:
			Script->push("r");
			break;
					case 115:
			Script->push("s");
			break;
					case 116:
			Script->push("t");
			break;
					case 117:
			Script->push("u");
			break;
					case 118:
			Script->push("v");
			break;
					case 119:
			Script->push("w");
			break;
					case 120:
			Script->push("x");
			break;
					case 121:
			Script->push("y");
			break;
					case 122:
			Script->push("z");
			break;
					case 127:
			Script->push("delete");
			break;
					
					/*
					 // don't do this yet
					for (int i = 0; i < 95; i++)
					{
						Script->setTableField("WORLD_" + (160 + i), 160 + i);
					}
					 */
					
					case 256:
			Script->push("kp0");
			break;
					case 257:
			Script->push("kp1");
			break;
					case 258:
			Script->push("kp2");
			break;
					case 259:
			Script->push("kp3");
			break;
					case 260:
			Script->push("kp4");
			break;
					case 261:
			Script->push("kp5");
			break;
					case 262:
			Script->push("kp6");
			break;
					case 263:
			Script->push("kp7");
			break;
					case 264:
			Script->push("kp8");
			break;
					case 265:
			Script->push("kp9");
			break;
					case 266:
			Script->push("kp_period");
			break;
					case 267:
			Script->push("kp_divide");
			break;
					case 268:
			Script->push("kp_multiply");
			break;
					case 269:
			Script->push("kp_minus");
			break;
					case 270:
			Script->push("kp_plus");
			break;
					case 271:
			Script->push("kp_enter");
			break;
					case 272:
			Script->push("kp_equals");
			break;
					
					case 273:
			Script->push("up");
			break;
					case 274:
			Script->push("down");
			break;
					case 275:
			Script->push("right");
			break;
					case 276:
			Script->push("left");
			break;
					case 277:
			Script->push("insert");
			break;
					case 278:
			Script->push("home");
			break;
					case 279:
			Script->push("end");
			break;
					case 280:
			Script->push("pageUp");
			break;
					case 281:
			Script->push("pageDown");
			break;
					
					case 282:
			Script->push("f1");
			break;
					case 283:
			Script->push("f2");
			break;
					case 284:
			Script->push("f3");
			break;
					case 285:
			Script->push("f4");
			break;
					case 286:
			Script->push("f5");
			break;
					case 287:
			Script->push("f6");
			break;
					case 288:
			Script->push("f7");
			break;
					case 289:
			Script->push("f8");
			break;
					case 290:
			Script->push("f9");
			break;
					case 291:
			Script->push("f10");
			break;
					case 292:
			Script->push("f11");
			break;
					case 293:
			Script->push("f12");
			break;
					case 294:
			Script->push("f13");
			break;
					case 295:
			Script->push("f14");
			break;
					case 296:
			Script->push("f15");
			break;
					
					case 300:
			Script->push("numLock");
			break;
					case 301:
			Script->push("capsLock");
			break;
					case 302:
			Script->push("scrollLock");
			break;
					case 303:
			Script->push("rShift");
			break;
					case 304:
			Script->push("lShift");
			break;
					case 305:
			Script->push("rCtrl");
			break;
					case 306:
			Script->push("lCtrl");
			break;
					case 307:
			Script->push("rAlt");
			break;
					case 308:
			Script->push("lAlt");
			break;
					case 309:
			Script->push("rMeta");
			break;
					case 310:
			Script->push("lMeta");
			break;
					case 311:
			Script->push("rSuper");
			break;
					case 312:
			Script->push("lSuper");
			break;
					case 313:
			Script->push("mode");
			break;
					case 314:
			Script->push("compose");
			break;
					
					case 315:
			Script->push("help");
			break;
					case 316:
			Script->push("printScn");
			break;
					case 317:
			Script->push("sysReq");
			break;
					case 318:
			Script->push("break");
			break;
					case 319:
			Script->push("menu");
			break;
					case 320:
			Script->push("power");
			break;
					case 321:
			Script->push("euro");
			break;
					case 322:
			Script->push("undo");
			break;
				
			default:
				
				std::stringstream str;
				str << "Unknown_" << currentKey;
				Script->push(str.str());
				break;
		}
		
		
	}
}

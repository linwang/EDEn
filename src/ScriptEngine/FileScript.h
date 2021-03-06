/*
 *  This file is covered by the Ruby license. See LICENSE.txt for more details.
 *
 *  Copyright (C) 2007-2012 Noam Chitayat. All rights reserved.
 */

#ifndef FILE_SCRIPT_H
#define FILE_SCRIPT_H

#include "Script.h"

/**
 * A FileScript is a type of Script that runs Lua code supplied in a Lua script
 * file.
 *
 * @author Noam Chitayat
 */
class FileScript : public Script
{
   public:
      /**
       * Constructor.
       * Creates a new Lua thread by forking the main VM, and then
       * loads the specified script file onto the new thread's stack.
       *
       * @param luaVM The main Lua stack to fork a thread from.
       * @param scriptPath The path to a script that should be run on this thread.
       */
      FileScript(lua_State* luaVM, const std::string& scriptPath);

      /**
       * Destructor.
       */
      ~FileScript();
};

#endif

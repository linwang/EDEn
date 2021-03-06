/*
 *  This file is covered by the Ruby license. See LICENSE.txt for more details.
 *
 *  Copyright (C) 2007-2012 Noam Chitayat. All rights reserved.
 */

#ifndef EXECUTION_STACK_H
#define EXECUTION_STACK_H

#include "Singleton.h"
#include <stack>

class GameState;

/**
 * The heart of the game's execution.
 * Holds different states of the game (Title Screen, Tile Engine, etc.) 
 * and allows for easy change of state.
 * Main functionality is calling advanceFrame and drawFrame, and destroying finished states in the execute() function.
 *
 * @author Noam Chitayat
 */
class ExecutionStack
{
   /**
    * The stack that holds the various states that the player
    * has transitioned through.
    */
   std::stack<GameState*> stateStack;

   /**
    * Remove and delete the most recent state pushed on the stack.
    */
   void popState();

   public:

      /**
       * Destructor.
       */
      ~ExecutionStack();
       
      /**
       * Pushes (and activates) a new game state.
       * After this method call, newState is responsible
       * for all drawing and logic steps until it is finished
       * or another state is pushed
       *
       * @param newState the new state of the game
       */
      void pushState(GameState* newState);

      /**
       * Execute the game loop.
       * Step through the state logic. If the logic returns true
       * then the state is not ready to terminate, so run its draw step.
       * Otherwise, pop the stack and activate the next most recent state.
       * Keep going until there are no more states, and then quit.
       */
      void execute();
};

#endif

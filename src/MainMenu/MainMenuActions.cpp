/*
 *  This file is covered by the Ruby license. See LICENSE.txt for more details.
 *
 *  Copyright (C) 2007-2012 Noam Chitayat. All rights reserved.
 */

#include "MainMenu.h"
#include "ExecutionStack.h"
#include "GraphicsUtil.h"
#include "Music.h"
#include "Sound.h"

#include "TileEngine.h"
#include "MenuShell.h"
#include "HomeMenu.h"
#include "PlayerData.h"

#define CHAP1 "chapter1"
#define SAVE_GAME "data/savegames/savegamejson.edd"
//Actions for each of the list ops in the title screen

/**
 * 'New Game' was selected. Push a TileEngine state and fade to black.
 * [this will eventually change to a chapter selection list, with the fade
 * and pushed state (field or battle) changing based on the chapter].
 */
void MainMenu::NewGameAction()
{
   TileEngine* tileEngine = new TileEngine(executionStack, CHAP1);
   executionStack.pushState(tileEngine);
   chooseSound->play();
   Music::fadeOutMusic(1000);
   GraphicsUtil::getInstance()->FadeToColor(0.0f, 0.0f, 0.0f, 1000);
}

/**
 * 'Menu Prototype' was selected. Push a Menu state.
 * \todo This will eventually be removed entirely, as it is only a programmer convenience right now.
 */
void MainMenu::MenuPrototypeAction()
{
   PlayerData* playerData = new PlayerData();
   playerData->load(SAVE_GAME);

   /** \todo This is never deleted, causing a memory leak. */
   MenuShell* menuShell = new MenuShell(*playerData);

   HomeMenu* menu = new HomeMenu(executionStack, *menuShell, *playerData);
   executionStack.pushState(menu);
}

/**
 * 'Load Game' was selected. (TODO)
 */
void MainMenu::LoadGameAction()
{
}

/**
 * 'Options' was selected.
 * Perform any transitions necessary and load up the options menu interface. (TODO)
 */
void MainMenu::OptionsAction()
{
}

/**
 * 'About' was selected. (TODO)
 */
void MainMenu::AboutAction()
{
}

/**
 * 'Quit Game' was selected. Signal state logic termination, fade to black.
 */
void MainMenu::QuitAction()
{
   finished = true;
   chooseSound->play();
   Music::fadeOutMusic(1000);
   GraphicsUtil::getInstance()->FadeToColor(0.0f, 0.0f, 0.0f, 1000);
}

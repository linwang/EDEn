#ifndef HOME_PANE_H_
#define HOME_PANE_H_

#include "MenuPane.h"

class PlayerData;
class CharacterModule;
class CharacterSelectListener;

/**
 * The GUI elements of the home pane, which is the first menu pane that is shown.
 *
 * @author Noam Chitayat
 */
class HomePane : public MenuPane
{
   /** The player data to summarize in this pane. */
   PlayerData& playerData;

   /** The modules used to summarize attributes for all the characters in the party. */
   CharacterModule* characterModules;

   public:
      /**
       * Constructor.
       *
       * @param playerData The player data to display in the pane.
       * @param rect The preferred dimensions of this pane.
       */
      HomePane(PlayerData& playerData, const gcn::Rectangle& rect);

      /**
       * Sets the listener for character selection events
       * (when a character in the home pane is clicked).
       * If a listener is already set, it will be disconnected when the new one is set.
       *
       * @param listener The new listener to set.
       */
      void setCharacterSelectListener(CharacterSelectListener* listener);

      /**
       * Refreshes the character information displayed in the pane.
       */
      void refresh();

      /**
       * Destructor.
       */
      ~HomePane();
};

#endif
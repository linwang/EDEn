/*
 *  This file is covered by the Ruby license. See LICENSE.txt for more details.
 *
 *  Copyright (C) 2007-2012 Noam Chitayat. All rights reserved.
 */

#ifndef ENTITY_GRID_H
#define ENTITY_GRID_H

#include <list>
#include <vector>
#include "MovementDirection.h"
#include "Pathfinder.h"

class Obstacle;
class Map;
class Actor;
struct shapes::Point2D;
struct shapes::Rectangle;
struct TileState;

/**
 * The EntityGrid class binds to a Map and stores the locations of entities on top of it.
 * EntityGrid instances also provide an interface to entities like the actor and PlayerCharacter to detect collisions
 * and route around them.
 *
 * @author Noam Chitayat
 */
class EntityGrid
{
   friend class Pathfinder;
   
   /** The size of a movement tile (used to control pathfinding granularity) */
   static const int MOVEMENT_TILE_SIZE;

   /** The square root of 2. */
   static const float ROOT_2;

   /** Floating-point notation for infinity. */
   static const float INFINITY;

   /** The map on which the grid is overlaid. */
   const Map* map;

   /** The pathfinding component used to navigate in this map. */
   Pathfinder pathfinder;
   
   /** The width of the pathfinder map. */
   int collisionMapWidth;

   /** The height of the pathfinder map. */
   int collisionMapHeight;

   /** The map of entities and states for each of the tiles. */
   TileState** collisionMap;

   /**
    * Clean up the map of tile states.
    */
   void deleteCollisionMap();

   /**
    * @param area The pixel-coordinate rectangle to determine boundaries for.
    *
    * @return Get the tile boundaries of the specified rectangle.
    */
   shapes::Rectangle getCollisionMapEdges(const shapes::Rectangle& area) const;

   /**
    * Checks if an area is available.
    *
    * @param area The coordinates of the top-left corner of the area to occupy (in pixels)
    * @param width The width of the area to occupy (in pixels)
    * @param height The height of the area to occupy (in pixels)
    * @param state The new state of the area (entity and type)
    *
    * @return true if the area can be successfully occupied, false if there was something else in the area.
    */
   bool canOccupyArea(const shapes::Point2D& area, int width, int height, TileState state) const;
   
   /**
    * If an area is available, occupy it and set the tiles within it to the new state. 
    * NOTE: This is an all-or-nothing operation, which means that if there is anything blocking the area from being occupied, the entire area will be unmodified. If the area can be occupied, it will be occupied completely.
    *
    * @param area The coordinates of the top-left corner of the area to occupy (in pixels)
    * @param width The width of the area to occupy (in pixels)
    * @param height The height of the area to occupy (in pixels)
    * @param state The new state of the area (entity and type)
    *
    * @return true if the area has been successfully occupied, false if there was something else in the area.
    */
   bool occupyArea(const shapes::Point2D& area, int width, int height, TileState state);

   /**
    * Free the tiles belonging to a given entity within a specified area. 
    *
    * @param locationToFree The coordinates of the top-left corner of the area to free (in pixels)
    * @param width The width of the area to free (in pixels)
    * @param height The height of the area to free (in pixels)
    */
   void freeArea(const shapes::Point2D& locationToFree, int width, int height);
   
   /**
    * Free the tiles belonging to a given entity within a specified area. 
    *
    * @param previousLocation The coordinates of the top-left corner of the area to free (in pixels)
    * @param currentLocation The coordinates of the top-left corner of the area to keep in the current state (in pixels)
    * @param width The width of the area to free (in pixels)
    * @param height The height of the area to free (in pixels)
    * @param state The state to remove from the tiles
    */
   void freeArea(const shapes::Point2D& previousLocation, const shapes::Point2D& currentLocation, int width, int height, TileState state);

   /**
    * Helper function to unconditionally set the tiles in an area to a given state. 
    *
    * @param area The rectangular area to set (with edge coordinates in tiles)
    * @param state The new state of the area (entity and type)
    */
   void setArea(const shapes::Rectangle& area, TileState state);

   public:
      /** A set of waypoints to move through in order to go from one point to another. */
      typedef std::list<shapes::Point2D> Path;

      /**
       * Constructor.
       */
      EntityGrid();
      
      /**
       * @return The map data that the EntityGrid is operating on.
       */
      const Map* getMapData() const;
      
      /**
       * Sets a new map to operate on. Initializes the collision map and
       * runs computations on it to inform heuristics for best path calculations.
       *
       * @param newMapData The new map to operate on.
       */
      void setMapData(const Map* newMapData);
   
      /**
       * @return The name of the map.
       */
      std::string getName() const;
      
      /**
       * @return The width of the map.
       */
      int getWidth() const;
      
      /**
       * @return The height of the map.
       */
      int getHeight() const;

      /**
       * @param point The coordinates to check (in pixels)
       *
       * @return true iff the point is within the map
       */
      bool withinMap(const shapes::Point2D& point) const;
      
      /**
       * @param x The x-coordinate to check (in pixels)
       * @param y The y-coordinate to check (in pixels)
       *
       * @return true iff the x-y coordinate is within the map
       */
      bool withinMap(const int x, const int y) const;

      /**
       * Process logic for the map and its obstacles.
       */
      void step(long timePassed);
   
      /**
       * Finds an ideal path from the source coordinates to the destination.
       *
       * @param src The coordinates of the source (in pixels).
       * @param dst The coordinates of the destination (in pixels).
       *
       * @return The ideal best path from the source point to the destination point.
       */
      Path findBestPath(const shapes::Point2D& src, const shapes::Point2D& dst);
      
      /**
       * Finds the shortest path from the source coordinates to the destination
       * around all obstacles and entities.
       *
       * @param src The coordinates of the source (in pixels).
       * @param dst The coordinates of the destination (in pixels).
       * @param width The width of the moving entity.
       * @param height The width of the moving entity.
       *
       * @return The shortest unobstructed path from the source point to the destination point.
       */
      Path findReroutedPath(const shapes::Point2D& src, const shapes::Point2D& dst, int width, int height);
      
      /**
       * Checks an area for obstacles or entities.
       *
       * @param area The coordinates of the top-left corner of the area (in pixels)
       * @param width The width of the area (in pixels)
       * @param height The height of the area (in pixels)
       *
       * @return true iff a given area is entirely free of obstacles and entities.
       */
      bool isAreaFree(const shapes::Point2D& area, int width, int height) const;
   
      /**
       * Add an obstacle and occupy the tiles under it.
       * NOTE: This is an all-or-nothing operation, which means that if there is anything blocking the area from being occupied, the entire area will be unmodified. If the area can be occupied, it will be occupied completely.
       *
       * @param area The coordinates of the top-left corner of the obstacle (in pixels)
       * @param width The width of the obstacle (in pixels)
       * @param height The height of the obstacle (in pixels)
       *
       * @return true if the obstacle has been successfully placed in the area, false if there was something else in the area.
       */
      bool addObstacle(const shapes::Point2D& area, int width, int height);

      /**
       * Add an Actor and occupy the tiles under it.
       * NOTE: This is an all-or-nothing operation, which means that if there is anything blocking the area from being occupied, the entire area will be unmodified. If the area can be occupied, it will be occupied completely.
       *
       * @param actor The actor to add.
       * @param area The area to add the actor to.
       *
       * @return true if the actor has been successfully placed in the area, false if there was something else in the area.
       */
      bool addActor(Actor* actor, const shapes::Point2D& area);

      /**
       * Change the actor location, if the destination tiles are available to occupy.
       * NOTE: This is an all-or-nothing operation, which means that if there is anything blocking the destination from being occupied, the entire area will be unmodified. If the area can be occupied, it will be occupied completely.
       *
       * @param actor The actor to relocate.
       * @param dst The coordinates to relocate the actor to (in pixels)
       *
       * @return true if the player character has been successfully moved to the destination, false if there was something else in the destination.
       */
      bool changeActorLocation(Actor* actor, const shapes::Point2D& dst);

      /**
       * Remove the player and free the tiles under it.
       *
       * @param actor The actor that is being removed.
       * @param area The prior coordinates of the top-left corner of the player character (in pixels)
       * @param width The width of the actor (in pixels)
       * @param height The height of the actor (in pixels)
       */
      void removeActor(Actor* actor);

      /**
       * Gets the actor occupying the area in front of the specified actor, if one exists.
       *
       * @param actor The actor to search in front of.
       */
      Actor* getAdjacentActor(Actor* actor) const;

      /**
       * Given the distance the entity can move and the direction, moves as far as possible until an obstacle is encountered.
       *
       * @param actor The actor to move.
       * @param xDirection The direction moved on the x-axis.
       * @param yDirection The direction moved on the y-axis.
       * @param distance The total distance that the player character can be moved in this call.
       */
      void moveToClosestPoint(Actor* actor, int xDirection, int yDirection, int distance);
   
      /**
       * Request permission from the EntityGrid to move an Actor from the source to the given destination.
       * NOTE: After the actor has completed this movement, endMovement MUST be called in order to notify the EntityGrid to perform the appropriate clean-up.
       *
       * @param actor The actor that is moving.
       * @param dst The coordinates of the destination (in pixels).
       *
       * @return true iff the actor can move from the source to the destination.
       */
      bool beginMovement(Actor* actor, const shapes::Point2D& dst);
      
      /**
       * Notifies the EntityGrid that the actor failed to complete movement from the source to the given destination and occupies some area between the source and destination.
       *
       * @param actor The actor that was moving.
       * @param src The coordinates of the source (in pixels).
       * @param dst The coordinates of the original destination (in pixels).
       */
      void abortMovement(Actor* actor, const shapes::Point2D& src, const shapes::Point2D& dst);
      
      /**
       * Notifies the EntityGrid that the actor moved successfully from the source to the given destination and no longer occupies the source coordinates.
       *
       * @param actor The actor that was moving.
       * @param src The coordinates of the source (in pixels).
       * @param dst The coordinates of the destination (in pixels).
       */
      void endMovement(Actor* actor, const shapes::Point2D& src, const shapes::Point2D& dst);
   
      /**
       * Draw the collision map for diagnostic purposes.
       */
      void draw();

      /**
       * Destructor.
       */
      ~EntityGrid();
};

#endif

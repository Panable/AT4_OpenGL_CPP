#pragma once


#include <vector>
#include "GameObject.h"


/**
 * Holds all Tiles as part of the level
 * Loads/Renders level from disk
 */
class GameLevel
{
public:

    //Current Level GameObjects
    std::vector<GameObject> m_Bricks;

    /**
     * Loads Level From File
     * @param file level file
     * @param levelWidth width of level
     * @param levelHeight height of level
     */
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);

    /**
     * Draws the level
     * @param renderer renderer obj
     */
    void Draw(SpriteRenderer& renderer);

    //is the level completed?
    bool IsCompleted;

public:
    GameLevel() {}
private:
    void Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

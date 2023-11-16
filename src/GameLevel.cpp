#include "GameLevel.h"

#include <fstream>
#include <sstream>

void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    //clear previous data.
    m_Bricks.clear();

    unsigned int tileCode; //value of the tile
    //GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData; //tile information

    if (fstream)
    {
        //read each line from the file
        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;

            // Parse each (tileCode) from the line and store it in the row vector.
            while (sstream >> tileCode)
            {
                row.push_back(tileCode);
            }
            //push the row into the tile data
            tileData.push_back(row);
        }

        //initialize the level
        if (!tileData.empty())
            Init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (GameObject& tile : m_Bricks)
    {
        if(!tile.m_Destroyed)
            tile.Draw(renderer);
    }
}

void GameLevel::Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    //dimensions of vector
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();

    float unitWidth;
    unitWidth = levelWidth / static_cast<float>(width);
    float unitHeight = levelHeight / height;

    //initialize the level tiles

    for (unsigned int y = 0; y < height; ++y) //scan by y
    {
        for (unsigned int x = 0; x < width; ++x) //scan by x
        {
            if (tileData[y][x] == 1) // solid
            {
                glm::vec2 pos(unitWidth * x, unitHeight * y);
                glm::vec2 size(unitWidth, unitHeight);
                GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
                obj.m_IsSolid = true;
                this->m_Bricks.push_back(obj);
            } else if (tileData[y][x] > 1)
            {
                glm::vec3 color;
                switch (tileData[y][x])
                {
                    case 2:
                        color = glm::vec3(0.2f, 0.6f, 1.0f);
                        break;
                    case 3:
                        color = glm::vec3(0.2f, 0.6f, 1.0f);
                        break;
                    case 4:
                        color = glm::vec3(0.0f, 0.7f, 0.0f);
                        break;
                    case 5:
                        color = glm::vec3(1.0f, 0.5f, 0.0f);
                        break;
                    default:
                        color = glm::vec3(1.0f);
                        break;
                }
                glm::vec2 pos(unitWidth * x, unitHeight * y);
                glm::vec2 size(unitWidth, unitHeight);
                m_Bricks.emplace_back(pos, size, ResourceManager::GetTexture("block"), color);
            }
        }
    }
}

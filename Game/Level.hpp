#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>

class Level
{
public:
    void LevelSelect(int lvl);
    int* getLevelArray();
private:
    int levelArray[20 * 20]; 
};

#endif // LEVEL_HPP
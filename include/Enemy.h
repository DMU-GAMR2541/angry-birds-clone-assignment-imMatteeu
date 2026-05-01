#include "DynamicObject.h"
#pragma once

enum class EnemySize { Small, Medium, Large };

struct EnemyData {
	EnemySize size;
	int health;
};

class Enemy : DynamicObject {
/// <summary>
/// Varaibles that define an enemy.
/// </summary>
private:
    int i_health;
    bool b_isDestroyed;
    EnemySize e_size;

    static EnemyData getEnemyData(EnemyData enemyData) {}

public:
    //Default constructor for an enemy. 
    Enemy() = default;
    Enemy(int i_initialHealth) : i_health(i_initialHealth), b_isDestroyed(false) {} 

    //Class functions to be tested.
    void takeDamage(int damage) {
        if (damage < 0) return;
            i_health -= damage;
        if (i_health <= 0) {
            i_health = 0;
            b_isDestroyed = true;
        }
    }

    int getHealth() const { return i_health; }
    bool checkIfPopped() const { return b_isDestroyed; }
};
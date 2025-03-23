#include "weapon.h"
/**
 * @file weapon.cpp
 * @author Joe Davitt (jjdavitt@nic.edu)
 * @brief
 * @version 0.1
 * @date 2025-03-23
 *
 * @copyright Copyright (c) 2025
 *
 */
Weapon::Weapon(std::string name, float d, float r)
{
    mName = name;
    mWepDmg = d;
    mRate = r;
}
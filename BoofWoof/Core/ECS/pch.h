#pragma once
#ifndef PCH_H
#define PCH_H

#include <memory>
#include <unordered_map>
#include <cassert>
#include <bitset>
#include <queue>
#include <cstdint>
#include <set>
#include <array>

//#include "ComponentManager.h"
//#include "EntityManager.h"
//#include "SystemManager.h"

// A simple type alias
using Entity = std::uint32_t;

// Used to define the size of arrays later on
const Entity MAX_ENTITIES = 5000;

// A simple type alias
using ComponentType = std::uint8_t;

// Used to define the size of arrays later on
const ComponentType MAX_COMPONENTS = 32;

// A simple type alias
using Signature = std::bitset<MAX_COMPONENTS>;

#endif
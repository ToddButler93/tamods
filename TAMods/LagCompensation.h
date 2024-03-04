#pragma once

#include <list>
#include <unordered_set>
#include <unordered_map>

struct ZeroPingNonChainProjectile
{
    FVector fire_location;
    UClass* projectile_class;
    FVector physical_location;
    FVector client_location;
    ATrProjectile* spawned_projectile;
};

extern std::list<ZeroPingNonChainProjectile> zero_ping_non_chain_projectiles;
extern std::unordered_set<ATrProjectile*> spawned_projectiles_set;
extern std::unordered_map<ATrProjectile*, ATrProjectile*> real_projectile_to_spawned_projectile;
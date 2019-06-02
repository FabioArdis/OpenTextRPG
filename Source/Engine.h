#pragma once

#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Location.h"

class Engine final {
public:
    Engine() = default;
    virtual compl Engine() = default;
    
    void CreateItems(void);
    void Battle(Enemy enemy);
    void Battle(Dummy dummy);
    void Start(void);
    void Play(void);
    void Save(void);
    void Load(void);
    void Pause(void);
    void PlayerUp(void);
    void Stats(void);
    void Magic(Enemy& enemy);
    void Magic(Dummy& dummy);
    void Items(void);
    void Randomize(void);
    void ChooseClass(void);
    void Summary(void);
    void TrainingZone1(void);
    void TrainingZone2(void);
    void TrainingZoneBattle(void) = delete;
    template <size_t rows, size_t columns>
    void UpdateDungeon(string (&iDungeon)[rows][columns]);
};

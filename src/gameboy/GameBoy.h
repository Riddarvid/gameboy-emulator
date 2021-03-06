//
// Created by algot on 2021-02-23.
//

#pragma once

#include <memory>

#include "CPU.h"
#include "MMU.h"
#include "PPU.h"

#define FRIEND_TEST(test_case_name, test_name)\
friend class test_case_name##_##test_name##_Test

#define JOYPAD_RELEASE 0
#define JOYPAD_PRESS   1

class GameBoy {
public:
    GameBoy();
    void step();
    std::unique_ptr<uint8_t[]> getScreenTexture();
    void joypad_input(uint8_t key, uint8_t action);
    void load_rom(std::string bootFilepath, std::string romFilepath);
    void load_game_rom(std::string filepath);
    void load_boot_rom(std::string filepath);
    bool isReadyToDraw() const;
    void confirmDraw();
    void cpu_dump();

private:
    bool on;

    std::shared_ptr<MMU> mmu;
    std::unique_ptr<CPU> cpu;
    std::unique_ptr<PPU> ppu;

    FRIEND_TEST(PPU, g_tile_rom);
};

//
// Created by algot on 2021-02-23.
//

#include "GameBoy.h"

GameBoy::GameBoy() {
    this->mmu = std::make_shared<MMU>();
    this->cpu = std::make_unique<CPU>(0x0000, 0xFFFE, mmu);
    this->ppu = std::make_unique<PPU>(mmu);
}

void GameBoy::step() {
    if (!this->cpu->getStop()) {
        // TODO: Check for interrupts
        int cycles = 0;
        if (!this->cpu->getHalt()) {
            cycles = this->cpu->execute_instruction();

        }else if(mmu->read(0xffff) & mmu->read(0xFF0F) & 0x1f){

        }
        this->ppu->update(cycles);
        this->mmu->timer_update(cycles);
    } else if (mmu->read(0xFFFF)) {
        cpu->return_from_stop();
    }


}

uint8_t *GameBoy::getScreen() {
    return this->ppu->getFrameBuffer()->data();
}

void GameBoy::joypad_input(uint8_t key, uint8_t action) {
    switch (action) {
        case JOYPAD_PRESS:
            this->mmu->joypad_press(key);
            break;
        case JOYPAD_RELEASE:
            this->mmu->joypad_release(key);
            break;
        default:
            std::cout << "Invalid parameter `action` to GameBoy::joypad_input: " << action << std::endl;
            break;
    }
}

void GameBoy::load_game_rom(std::string filepath) {
    this->mmu->load_game_rom(filepath);
}

void GameBoy::load_boot_rom(std::string filepath) {
    this->mmu->load_boot_rom(filepath);
}

void GameBoy::cpu_dump() {
    this->cpu->cpu_dump();
}

bool GameBoy::readyToDraw() const {
    return this->ppu->getReadyToDraw();
}

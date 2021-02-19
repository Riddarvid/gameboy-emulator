//
// Created by algot on 2021-02-15.
//

#include <memory>

#include "gtest/gtest.h"
#include "../src/gameboy/mmu.h"

TEST(MMU, read_write){
    std::shared_ptr<MMU> mmu = std::make_shared<MMU>();

    // Disable boot ROM
    mmu->write(0xff50, 0x01);

    mmu->write_GAME_ROM_ONLY_IN_TESTS(0x30, 0xa1);
    ASSERT_EQ(mmu->read(0x30), 0xa1);

    mmu->write(0xc030, 0xd5);
    ASSERT_EQ(mmu->read(0xc030), 0xd5);
}

TEST(MMU, read_write_interrupt_enable){
    std::shared_ptr<MMU> mmu = std::make_shared<MMU>();

    // Disable boot ROM
    mmu->write(0xff50, 0x01);

    // Test default value
    ASSERT_EQ(mmu->read(0xffff), 0x1f);

    mmu->write(0xffff, 0x0a);
    ASSERT_EQ(mmu->read(0xffff), 0x0a);
}

TEST(MMU, disable_boot_rom){
    std::shared_ptr<MMU> mmu = std::make_shared<MMU>();

    mmu->write_BOOT_ROM_ONLY_IN_TESTS(0x00, 0x55);
    ASSERT_EQ(mmu->read(0x00), 0x55);

    // Disable boot ROM
    mmu->write(0xff50, 0x01);

    ASSERT_EQ(mmu->read(0x00), 0x00);
}

TEST(MMU, joypad){
    std::shared_ptr<MMU> mmu = std::make_shared<MMU>();

    mmu->write(IO_JOYPAD, JOYPAD_SEL_BUTTONS);
    ASSERT_EQ(mmu->read(IO_JOYPAD), 0b1111);
    mmu->write(IO_JOYPAD, JOYPAD_SEL_DIRECTIONS);
    ASSERT_EQ(mmu->read(IO_JOYPAD), 0b1111);

    // Press Left button
    mmu->joypad_press(JOYPAD_LEFT);
    mmu->write(IO_JOYPAD, JOYPAD_SEL_DIRECTIONS);
    ASSERT_EQ(mmu->read(IO_JOYPAD), 0b1101);

    // Press Down button
    mmu->joypad_press(JOYPAD_DOWN);
    mmu->write(IO_JOYPAD, JOYPAD_SEL_DIRECTIONS);
    ASSERT_EQ(mmu->read(IO_JOYPAD), 0b0101);

    // Press Select button
    mmu->joypad_press(JOYPAD_SELECT);
    mmu->write(IO_JOYPAD, JOYPAD_SEL_DIRECTIONS);
    ASSERT_EQ(mmu->read(IO_JOYPAD), 0b0101);

    mmu->write(IO_JOYPAD, JOYPAD_SEL_BUTTONS);
    ASSERT_EQ(mmu->read(IO_JOYPAD), 0b1011);

    // Release Down button
    mmu->joypad_release(JOYPAD_DOWN);

    mmu->write(IO_JOYPAD, JOYPAD_SEL_BUTTONS);
    ASSERT_EQ(mmu->read(IO_JOYPAD), 0b1011);

    mmu->write(IO_JOYPAD, JOYPAD_SEL_DIRECTIONS);
    ASSERT_EQ(mmu->read(IO_JOYPAD), 0b1101);
}

//TEST(MMU, load_rom){
//    std::shared_ptr<MMU> mmu = std::make_shared<MMU>();
//    mmu->disable_boot_rom();
//    mmu->load_rom("rom.gb");
//
//    ASSERT_EQ(mmu->read(0x104), 0xce);
//    ASSERT_EQ(mmu->read(0x105), 0xed);
//}
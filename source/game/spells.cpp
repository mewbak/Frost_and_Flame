/**
 * Copyright (C) 2011-2013 Paul Wortmann, PhysHex Games, www.physhexgames.co.nr
 * This file is part of "Frost And Flame"
 *
 * "Frost And Flame" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * "Frost And Flame" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with "Frost And Flame" If not, see <http://www.gnu.org/licenses/>.
 *
 * @author  Paul Wortmann
 * @email   physhex@gmail.com
 * @website www.physhexgames.co.nr
 * @license GPL V3
 * @date 2011-11-11
 */

#include "spells.hpp"
#include "game.hpp"

extern game_class game;

//----------------------------------------------------------------------------------------------------------------

void  spell_class::init_spells(void)
{
    spell_type*      temp_spell_pointer;
    //------------------------- Fire arrow --------------------------------------------------------------------------
    temp_spell_pointer = game.spell_manager.add_spell(ITEM_SPELL_ARROW_FIRE);
    temp_spell_pointer->data.UID                    = ITEM_SPELL_ARROW_FIRE;
    temp_spell_pointer->data.name                   = "Fire Arrow";
    temp_spell_pointer->data.active                 = true;
    temp_spell_pointer->data.cooldown.current       = 10;
    temp_spell_pointer->data.cooldown.maximum       = 10;
    temp_spell_pointer->data.cooldown.rate          = 0.1f;
    temp_spell_pointer->data.duration.current       = 0;
    temp_spell_pointer->data.duration.maximum       = 10;
    temp_spell_pointer->data.duration.rate          = 0.2f;
    temp_spell_pointer->data.image.level_0          = game.texture_manager.add_texture("data/textures/UI/icons/spells/fire-arrows-1.png");
    temp_spell_pointer->data.image.level_1          = game.texture_manager.add_texture("data/textures/UI/icons/spells/fire-arrows-2.png");
    temp_spell_pointer->data.image.level_2          = game.texture_manager.add_texture("data/textures/UI/icons/spells/fire-arrows-3.png");
    temp_spell_pointer->data.level.current          = 1;
    temp_spell_pointer->data.level.maximum          = MAX_SPELL_LEVEL;
    temp_spell_pointer->data.level.experience       = 0.0f;
    temp_spell_pointer->data.level.next             = 2;
    temp_spell_pointer->data.mana_cost              = 2;
    temp_spell_pointer->data.passive                = false;
    temp_spell_pointer->data.projectile_number      = 1;
    temp_spell_pointer->data.sound.on_move          = game.sound_manager.add_sound("data/sound/inventory/bottle_01.wav");
    temp_spell_pointer->data.sound.on_use           = game.sound_manager.add_sound("data/sound/inventory/bubble_01.wav");
    //------------------------- Ice arrow --------------------------------------------------------------------------
    temp_spell_pointer = game.spell_manager.add_spell(ITEM_SPELL_ARROW_ICE);
    temp_spell_pointer->data.UID                    = ITEM_SPELL_ARROW_ICE;
    temp_spell_pointer->data.name                   = "ICE Arrow";
    temp_spell_pointer->data.active                 = true;
    temp_spell_pointer->data.cooldown.current       = 10;
    temp_spell_pointer->data.cooldown.maximum       = 10;
    temp_spell_pointer->data.cooldown.rate          = 0.1f;
    temp_spell_pointer->data.duration.current       = 0;
    temp_spell_pointer->data.duration.maximum       = 10;
    temp_spell_pointer->data.duration.rate          = 0.2f;
    temp_spell_pointer->data.image.level_0          = game.texture_manager.add_texture("data/textures/UI/icons/spells/ice-blue-1.png");
    temp_spell_pointer->data.image.level_1          = game.texture_manager.add_texture("data/textures/UI/icons/spells/ice-blue-2.png");
    temp_spell_pointer->data.image.level_2          = game.texture_manager.add_texture("data/textures/UI/icons/spells/ice-blue-3.png");
    temp_spell_pointer->data.level.current          = 1;
    temp_spell_pointer->data.level.maximum          = MAX_SPELL_LEVEL;
    temp_spell_pointer->data.level.experience       = 0.0f;
    temp_spell_pointer->data.level.next             = 2;
    temp_spell_pointer->data.mana_cost              = 2;
    temp_spell_pointer->data.passive                = false;
    temp_spell_pointer->data.projectile_number      = 1;
    temp_spell_pointer->data.sound.on_move          = game.sound_manager.add_sound("data/sound/inventory/bottle_01.wav");
    temp_spell_pointer->data.sound.on_use           = game.sound_manager.add_sound("data/sound/inventory/bubble_01.wav");
    //------------------------- Lightning arrow --------------------------------------------------------------------------
    temp_spell_pointer = game.spell_manager.add_spell(ITEM_SPELL_ARROW_LIGHTNING);
    temp_spell_pointer->data.UID                    = ITEM_SPELL_ARROW_LIGHTNING;
    temp_spell_pointer->data.name                   = "Lightning Arrow";
    temp_spell_pointer->data.active                 = true;
    temp_spell_pointer->data.cooldown.current       = 10;
    temp_spell_pointer->data.cooldown.maximum       = 10;
    temp_spell_pointer->data.cooldown.rate          = 0.1f;
    temp_spell_pointer->data.duration.current       = 0;
    temp_spell_pointer->data.duration.maximum       = 10;
    temp_spell_pointer->data.duration.rate          = 0.2f;
    temp_spell_pointer->data.image.level_0          = game.texture_manager.add_texture("data/textures/UI/icons/spells/lightning-blue-1.png");
    temp_spell_pointer->data.image.level_1          = game.texture_manager.add_texture("data/textures/UI/icons/spells/lightning-blue-2.png");
    temp_spell_pointer->data.image.level_2          = game.texture_manager.add_texture("data/textures/UI/icons/spells/lightning-blue-3.png");
    temp_spell_pointer->data.level.current          = 1;
    temp_spell_pointer->data.level.maximum          = MAX_SPELL_LEVEL;
    temp_spell_pointer->data.level.experience       = 0.0f;
    temp_spell_pointer->data.level.next             = 2;
    temp_spell_pointer->data.mana_cost              = 2;
    temp_spell_pointer->data.passive                = false;
    temp_spell_pointer->data.projectile_number      = 1;
    temp_spell_pointer->data.sound.on_move          = game.sound_manager.add_sound("data/sound/inventory/bottle_01.wav");
    temp_spell_pointer->data.sound.on_use           = game.sound_manager.add_sound("data/sound/inventory/bubble_01.wav");
    //------------------------- Elemental arrow --------------------------------------------------------------------------
    temp_spell_pointer = game.spell_manager.add_spell(ITEM_SPELL_ARROW_ELEMENTAL);
    temp_spell_pointer->data.UID                    = ITEM_SPELL_ARROW_ELEMENTAL;
    temp_spell_pointer->data.name                   = "Elemental Arrow";
    temp_spell_pointer->data.active                 = true;
    temp_spell_pointer->data.cooldown.current       = 10;
    temp_spell_pointer->data.cooldown.maximum       = 10;
    temp_spell_pointer->data.cooldown.rate          = 0.1f;
    temp_spell_pointer->data.duration.current       = 0;
    temp_spell_pointer->data.duration.maximum       = 10;
    temp_spell_pointer->data.duration.rate          = 0.2f;
    temp_spell_pointer->data.image.level_0          = game.texture_manager.add_texture("data/textures/UI/icons/spells/beam-royal-1.png");
    temp_spell_pointer->data.image.level_1          = game.texture_manager.add_texture("data/textures/UI/icons/spells/beam-royal-2.png");
    temp_spell_pointer->data.image.level_2          = game.texture_manager.add_texture("data/textures/UI/icons/spells/beam-royal-3.png");
    temp_spell_pointer->data.level.current          = 1;
    temp_spell_pointer->data.level.maximum          = MAX_SPELL_LEVEL;
    temp_spell_pointer->data.level.experience       = 0.0f;
    temp_spell_pointer->data.level.next             = 2;
    temp_spell_pointer->data.mana_cost              = 2;
    temp_spell_pointer->data.passive                = false;
    temp_spell_pointer->data.projectile_number      = 1;
    temp_spell_pointer->data.sound.on_move          = game.sound_manager.add_sound("data/sound/inventory/bottle_01.wav");
    temp_spell_pointer->data.sound.on_use           = game.sound_manager.add_sound("data/sound/inventory/bubble_01.wav");
    //------------------------------------------------------------------------------------------------------------
};



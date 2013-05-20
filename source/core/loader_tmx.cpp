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

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "loader_tmx.hpp"
#include "../game.hpp"

extern game_class         game;

void tmx_load(tmx_map_type *tmx_map_pointer, std::string file_name)
{
    game.core.log.file_write("Loading TMX map file -> ",file_name);
    int          position_count  = 0;
    int          position_start  = 0;
    bool         map_data        = true;
    bool         tileset_data    = false;
    bool         layer_data      = false;
    int          tileset_count   = 0;
    int          layer_count     = 0;
    int          tile_count      = 0;
    char         temp_char       = ' ';
    float        temp_float_data;
    int          temp_int_data;
    std::string  temp_string_data;
    std::string  temp_string_key;
    std::string  temp_string_value;
    std::string  data_line;
    tmx_map_pointer->data.number_of_tiles    = 0;
    tmx_map_pointer->data.number_of_tilesets = 0;
    tmx_map_pointer->data.number_of_layers   = 0;
    std::fstream script_file(file_name.c_str(),std::ios::in|std::ios::binary);
    if (script_file.is_open())
    {
        // find size of data and set new array size
        while (script_file.good())
        {
            getline(script_file,data_line);
            {
                position_count = 0;
                if ((data_line[position_count] == ' ') && (data_line.length() > 2))
                {
                    temp_char = ' ';
                    while (temp_char == ' ')
                    {
                        temp_char = data_line[position_count];
                        position_count++;
                    }
                    position_count--;
                }
                position_start = position_count;
                if((data_line[position_count] == '<') && (data_line[position_count+1] == '/') && (data_line.length() > 2))
                {
                    temp_char         = ' ';
                    temp_string_key   = "";
                    temp_string_value = "";
                    while(temp_char != '>')
                    {
                        temp_char = data_line[position_count];
                        if((temp_char != '<') && (temp_char != '/') && (temp_char != '>'))
                        {
                            temp_string_key += temp_char;
                        }
                        position_count++;
                        if(position_count > (int)data_line.length()) temp_char = '>';
                    }
                    if (temp_string_key == "tileset")
                    {
                        tileset_count++;
                    }
                }
                position_count = position_start;
                if((data_line[position_count] == '<') && (data_line[position_count+1] != '/') && (data_line.length() > 2))
                {
                    position_count++;
                    while(position_count < (int)data_line.length())
                    {
                        temp_char         = ' ';
                        temp_string_key   = "";
                        temp_string_value = "";
                        while(temp_char != '"')
                        {
                            temp_char = data_line[position_count];
                            if((temp_char != '"') && (temp_char != '='))
                            {
                                if((data_line[position_count-1] != '"') && (temp_char == ' ')) temp_string_key += temp_char;
                                else if (temp_char != ' ') temp_string_key += temp_char;
                            }
                            position_count++;
                            if(position_count > (int)data_line.length()) temp_char = '"';
                        }
                        temp_char        = ' ';
                        while(temp_char != '"')
                        {
                            temp_char = data_line[position_count];
                            if(temp_char != '"') temp_string_value += temp_char;
                            position_count++;
                            if(position_count > (int)data_line.length()) (temp_char = '"');
                        }
                        temp_string_data    = temp_string_value.c_str();
                        temp_float_data     = atof(temp_string_value.c_str());
                        temp_int_data       = atoi(temp_string_value.c_str());
                        if (temp_string_key == "map version")      map_data     = true;
                        if (map_data)
                        {
                            if (temp_string_key == "width")       tmx_map_pointer->data.map_width  = temp_int_data;
                            if (temp_string_key == "height")      tmx_map_pointer->data.map_height = temp_int_data;
                            if (temp_string_key == "tileheight")  map_data                         = false;
                        }
                        if (temp_string_key == "layer name")      tmx_map_pointer->data.number_of_layers++;
                    }
                }
            }
        }
        tmx_map_pointer->data.number_of_tiles    = tmx_map_pointer->data.map_width * tmx_map_pointer->data.map_height;
        tmx_map_pointer->data.number_of_tilesets = tileset_count;
        script_file.clear();
        script_file.seekg(0, std::ios::beg);
        tmx_map_pointer->tileset      = new tmx_tileset_type[tmx_map_pointer->data.number_of_tilesets+1];
        tmx_map_pointer->layer        = new tmx_layer_type  [tmx_map_pointer->data.number_of_layers+1];
        for(layer_count = 0; layer_count <= tmx_map_pointer->data.number_of_layers; layer_count++)
        {
            tmx_map_pointer->layer[layer_count].tile = new tmx_tile_type   [tmx_map_pointer->data.number_of_tiles+1];
        }
        position_count                           = 0;
        position_start                           = 0;
        map_data                                 = true;
        tileset_data                             = false;
        layer_data                               = false;
        tileset_count                            = 0;
        layer_count                              = 0;
        tile_count                               = 0;
        temp_char                                = ' ';
        tmx_map_pointer->data.number_of_tiles    = 0;
        tmx_map_pointer->data.number_of_tilesets = 0;
        // load data
        while (script_file.good())
        {
            getline(script_file,data_line);
            {
                position_count = 0;
                if ((data_line[position_count] == ' ') && (data_line.length() > 2))
                {
                    temp_char = ' ';
                    while (temp_char == ' ')
                    {
                        temp_char = data_line[position_count];
                        position_count++;
                    }
                    position_count--;
                }
                position_start = position_count;
                if((data_line[position_count] == '<') && (data_line[position_count+1] == '/') && (data_line.length() > 2))
                {
                    temp_char         = ' ';
                    temp_string_key   = "";
                    temp_string_value = "";
                    while(temp_char != '>')
                    {
                        temp_char = data_line[position_count];
                        if((temp_char != '<') && (temp_char != '/') && (temp_char != '>'))
                        {
                            temp_string_key += temp_char;
                        }
                        position_count++;
                        if(position_count > (int)data_line.length()) temp_char = '>';
                    }
                    if (temp_string_key == "tileset")
                    {
                        tmx_map_pointer->tileset[tileset_count].number_of_tiles = ((tmx_map_pointer->tileset[tileset_count].image_width / tmx_map_pointer->tileset[tileset_count].tile_width) * (tmx_map_pointer->tileset[tileset_count].image_height / tmx_map_pointer->tileset[tileset_count].tile_height));
                        tileset_data = false;
                        tileset_count++;
                    }
                    if (temp_string_key == "layer")
                    {
                        tile_count      = 0;
                        layer_data      = false;
                        layer_count++;
                    }
                }
                position_count = position_start;
                if((data_line[position_count] == '<') && (data_line[position_count+1] != '/') && (data_line.length() > 2))
                {
                    position_count++;
                    while(position_count < (int)data_line.length())
                    {
                        temp_char         = ' ';
                        temp_string_key   = "";
                        temp_string_value = "";
                        while(temp_char != '"')
                        {
                            temp_char = data_line[position_count];
                            if((temp_char != '"') && (temp_char != '='))
                            {
                                if((data_line[position_count-1] != '"') && (temp_char == ' ')) temp_string_key += temp_char;
                                else if (temp_char != ' ') temp_string_key += temp_char;
                            }
                            position_count++;
                            if(position_count > (int)data_line.length()) temp_char = '"';
                        }
                        temp_char        = ' ';
                        while(temp_char != '"')
                        {
                            temp_char = data_line[position_count];
                            if(temp_char != '"') temp_string_value += temp_char;
                            position_count++;
                            if(position_count > (int)data_line.length()) (temp_char = '"');
                        }
                        temp_string_data    = temp_string_value.c_str();
                        temp_float_data     = atof(temp_string_value.c_str());
                        temp_int_data       = atoi(temp_string_value.c_str());
                        if (temp_string_key == "map version")      map_data     = true;
                        if (temp_string_key == "tileset firstgid") tileset_data = true;
                        if (temp_string_key == "layer name")       layer_data   = true;
                        if (map_data)
                        {
                            if (temp_string_key == "?xml version") tmx_map_pointer->data.xml_version     = temp_float_data;
                            if (temp_string_key == "map version")  tmx_map_pointer->data.map_version     = temp_float_data;
                            if (temp_string_key == "encoding")     tmx_map_pointer->data.xml_encoding    = temp_string_data;
                            if (temp_string_key == "orientation")  tmx_map_pointer->data.map_orientation = temp_string_data;
                            if (temp_string_key == "width")        tmx_map_pointer->data.map_width       = temp_int_data;
                            if (temp_string_key == "height")       tmx_map_pointer->data.map_height      = temp_int_data;
                            if (temp_string_key == "tilewidth")    tmx_map_pointer->data.map_tile_width  = temp_int_data;
                            if (temp_string_key == "tileheight")   tmx_map_pointer->data.map_tile_height = temp_int_data;
                            if (temp_string_key == "tileheight")   map_data                              = false;
                        }
                        if (tileset_data)
                        {
                            if (temp_string_key == "tileset firstgid") tmx_map_pointer->tileset[tileset_count].first_gid    = temp_int_data;
                            if (temp_string_key == "name")             tmx_map_pointer->tileset[tileset_count].image_name   = temp_string_data;
                            if (temp_string_key == "tilewidth")        tmx_map_pointer->tileset[tileset_count].tile_width   = temp_int_data;
                            if (temp_string_key == "tileheight")       tmx_map_pointer->tileset[tileset_count].tile_height  = temp_int_data;
                            if (temp_string_key == "image source")     tmx_map_pointer->tileset[tileset_count].image_source = temp_string_data;
                            if (temp_string_key == "width")            tmx_map_pointer->tileset[tileset_count].image_width  = temp_int_data;
                            if (temp_string_key == "height")           tmx_map_pointer->tileset[tileset_count].image_height = temp_int_data;
                        }
                        if (layer_data)
                        {
                            if (temp_string_key == "layer name") tile_count      = 0;
                            if (temp_string_key == "width")      tmx_map_pointer->layer[layer_count].width  = temp_int_data;
                            if (temp_string_key == "height")     tmx_map_pointer->layer[layer_count].height = temp_int_data;
                            if (temp_string_key == "tile gid")
                            {
                                tmx_map_pointer->layer[layer_count].tile[tile_count].tile_tileset = 0;
                                for (int temp_tileset_count = 0; temp_tileset_count < tileset_count; temp_tileset_count++)
                                {
                                    if (temp_int_data >= tmx_map_pointer->tileset[temp_tileset_count].first_gid)
                                    {
                                        tmx_map_pointer->layer[layer_count].tile[tile_count].tile_tileset = temp_tileset_count;
                                    }
                                }
                                temp_int_data -= tmx_map_pointer->tileset[tmx_map_pointer->layer[layer_count].tile[tile_count].tile_tileset].first_gid;
                                temp_int_data += 1;
                                tmx_map_pointer->layer[layer_count].tile[tile_count].tile         = temp_int_data;
                                tmx_map_pointer->layer[layer_count].tile[tile_count].collision    = false;
                                tile_count++;
                            }
                        }
                    }
                }
            }
        }
        script_file.close();
        tmx_map_pointer->data.number_of_tiles    = tmx_map_pointer->data.map_width * tmx_map_pointer->data.map_height;
        tmx_map_pointer->data.number_of_tilesets = tileset_count;
        tmx_map_pointer->data.number_of_layers   = layer_count;
        for (int tileset_number = 0; tileset_number < tmx_map_pointer->data.number_of_tilesets; tileset_number++)
        {
            tmx_map_pointer->tileset[tileset_number].image_source    = game.core.file.path_remove(tmx_map_pointer->tileset[tileset_number].image_source);
            tmx_map_pointer->tileset[tileset_number].image_source    = game.core.file.path_add(tmx_map_pointer->tileset[tileset_number].image_source,"data/tilesets/");
            tmx_map_pointer->tileset[tileset_number].tile            = game.texture_manager.add_texture(tmx_map_pointer->tileset[tileset_number].image_source.c_str(),true,tmx_map_pointer->tileset[tileset_number].tile_width,tmx_map_pointer->tileset[tileset_number].tile_height);
            tmx_map_pointer->tileset[tileset_number].number_of_tiles = tmx_map_pointer->tileset[tileset_number].tile->frame_max;
        }
    }
    else game.core.log.file_write("Unable to load TMX map file -> ",file_name);
};

void tmx_save(tmx_map_type *tmx_map_pointer, std::string file_name)
{
    std::fstream script_file(file_name.c_str(),std::ios::out|std::ios::binary|std::ios::trunc);
    if (script_file.is_open())
    {
        script_file << "<?xml version=";
        script_file << '"';
        script_file << (float)tmx_map_pointer->data.xml_version;
        if ((float)tmx_map_pointer->data.xml_version == (int)tmx_map_pointer->data.xml_version) script_file << ".0";
        script_file << '"';
        script_file << " encoding=";
        script_file << '"';
        script_file << tmx_map_pointer->data.xml_encoding.c_str();
        script_file << '"';
        script_file << "?>";
        script_file << "\n";

        script_file << "<map version=";
        script_file << '"';
        script_file << (float)tmx_map_pointer->data.map_version;
        if ((float)tmx_map_pointer->data.map_version == (int)tmx_map_pointer->data.map_version) script_file << ".0";
        script_file << '"';
        script_file << " orientation=";
        script_file << '"';
        script_file << tmx_map_pointer->data.map_orientation.c_str();
        script_file << '"';
        script_file << " width=";
        script_file << '"';
        script_file << tmx_map_pointer->data.map_width;
        script_file << '"';
        script_file << " height=";
        script_file << '"';
        script_file << tmx_map_pointer->data.map_height;
        script_file << '"';
        script_file << " tilewidth=";
        script_file << '"';
        script_file << tmx_map_pointer->data.map_tile_width;
        script_file << '"';
        script_file << " tileheight=";
        script_file << '"';
        script_file << tmx_map_pointer->data.map_tile_height;
        script_file << '"';
        script_file << ">";
        script_file << "\n";

        script_file << " <properties>";
        script_file << "\n";
        script_file << "  <property name=";
        script_file << '"';
        script_file << "MAP_ID";
        script_file << '"';
        script_file << " value=";
        script_file << '"';
        script_file << "0";
        script_file << '"';
        script_file << "/>";
        script_file << "\n";
        script_file << " </properties>";
        script_file << "\n";

        for (int tileset_count = 0; tileset_count < tmx_map_pointer->data.number_of_tilesets; tileset_count++)
        {
            script_file << " <tileset firstgid=";
            script_file << '"';
            script_file << tmx_map_pointer->tileset[tileset_count].first_gid;
            script_file << '"';
            script_file << " name=";
            script_file << '"';
            script_file << tmx_map_pointer->tileset[tileset_count].image_name;
            script_file << '"';
            script_file << " tilewidth=";
            script_file << '"';
            script_file << tmx_map_pointer->tileset[tileset_count].tile_width;
            script_file << '"';
            script_file << " tileheight=";
            script_file << '"';
            script_file << tmx_map_pointer->tileset[tileset_count].tile_height;
            script_file << '"';
            script_file << ">";
            script_file << "\n";
            script_file << "  <image source=";
            script_file << '"';
            script_file << tmx_map_pointer->tileset[tileset_count].image_source;
            script_file << '"';
            script_file << " width=";
            script_file << '"';
            script_file << tmx_map_pointer->tileset[tileset_count].image_width;
            script_file << '"';
            script_file << " height=";
            script_file << '"';
            script_file << tmx_map_pointer->tileset[tileset_count].image_height;
            script_file << '"';
            script_file << "/>";
            script_file << "\n";
            script_file << " </tileset>";
            script_file << "\n";
        }
        for (int layer_count = 0; layer_count < tmx_map_pointer->data.number_of_layers; layer_count++)
        {
            script_file << " <layer name=";
            script_file << '"';
            script_file << "tile";
            script_file << '"';
            script_file << " width=";
            script_file << '"';
            script_file << tmx_map_pointer->layer[layer_count].width;
            script_file << '"';
            script_file << " height=";
            script_file << '"';
            script_file << tmx_map_pointer->layer[layer_count].height;
            script_file << '"';
            script_file << ">";
            script_file << "\n";
            script_file << "  <data>";
            script_file << "\n";
            for (int tile_count = 0; tile_count < tmx_map_pointer->data.number_of_tiles; tile_count++)
            {
                script_file << "   <tile gid=";
                script_file << '"';
                script_file << ((tmx_map_pointer->layer[layer_count].tile[tile_count].tile + tmx_map_pointer->tileset[tmx_map_pointer->layer[layer_count].tile[tile_count].tile_tileset].first_gid) - 1);
                script_file << '"';
                script_file << "/>";
                script_file << "\n";
            }
            script_file << "  </data>";
            script_file << "\n";
            script_file << " </layer>";
            script_file << "\n";
        }
        script_file << "</map>";
        script_file << "\n";
        script_file.close();
    }
};


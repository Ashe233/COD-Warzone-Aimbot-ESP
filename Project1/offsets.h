#pragma once
#include <windows.h>
//UPDATED 30/03/2022
#define refdef_ptr  0x11DB9CF8
#define game_mode  0x0F0191B0
#define OFF_local_index 0xFC500
#define OFF_local_index_pos 0x02F0


#define OFF_name_array 0x11DD9F88
#define OFF_name_array_padding 0x5E80
#define OFF_name_array_size 0xD8 //IDK


#define player_team_id 0x5E04
#define player_pos 0x5AB8
#define OFF_player_size 0x64A8
#define OFF_player_valid 0x0084
#define OFF_player_dead_1 0x609A
#define OFF_player_dead_2  0x4EEB

#define bone_base  0x76398
#define bone_size 0x0188
#define bone_offset 0x00D8

#define camera_ptr 0x125617B0
#define camera_pos  0x0208

/*
enum BONE_INDEX : unsigned long
{
    BONE_POS_HELMET = 8,        //  DOME

    BONE_POS_HEAD = 7,
    BONE_POS_NECK = 6,
    BONE_POS_CHEST = 5,
    BONE_POS_MID = 4,
    BONE_POS_TUMMY = 3,
    BONE_POS_PELVIS = 2,        // DICK

    BONE_POS_RIGHT_FOOT_1 = 21,
    BONE_POS_RIGHT_FOOT_2 = 22,
    BONE_POS_RIGHT_FOOT_3 = 23,
    BONE_POS_RIGHT_FOOT_4 = 24, //  TOE

    BONE_POS_LEFT_FOOT_1 = 17,
    BONE_POS_LEFT_FOOT_2 = 18,
    BONE_POS_LEFT_FOOT_3 = 19,
    BONE_POS_LEFT_FOOT_4 = 20,  //  TOE

    BONE_POS_LEFT_HAND_1 = 13,
    BONE_POS_LEFT_HAND_2 = 14,
    BONE_POS_LEFT_HAND_3 = 15,
    BONE_POS_LEFT_HAND_4 = 16,  //  HAND

    BONE_POS_RIGHT_HAND_1 = 9,
    BONE_POS_RIGHT_HAND_2 = 10,
    BONE_POS_RIGHT_HAND_3 = 11,
    BONE_POS_RIGHT_HAND_4 = 12, //  HAND

    BONE_RAND = 7 & 6 & 5 & 1
};

// Bone Array Order
static std::vector<std::vector<int>> BoneVector
{
    { BONE_INDEX::BONE_POS_LEFT_HAND_4, BONE_INDEX::BONE_POS_LEFT_HAND_3, BONE_INDEX::BONE_POS_LEFT_HAND_2, BONE_INDEX::BONE_POS_NECK },               // Left hand -> neck
    { BONE_INDEX::BONE_POS_RIGHT_HAND_4, BONE_INDEX::BONE_POS_RIGHT_HAND_3, BONE_INDEX::BONE_POS_RIGHT_HAND_2, BONE_INDEX::BONE_POS_NECK },                      // Right hand -> neck
    { BONE_INDEX::BONE_POS_LEFT_FOOT_4, BONE_INDEX::BONE_POS_LEFT_FOOT_3, BONE_INDEX::BONE_POS_LEFT_FOOT_2, BONE_INDEX::BONE_POS_LEFT_FOOT_1, BONE_INDEX::BONE_POS_TUMMY },       // Left foot -> bottom spine
    { BONE_INDEX::BONE_POS_RIGHT_FOOT_4, BONE_INDEX::BONE_POS_RIGHT_FOOT_3, BONE_INDEX::BONE_POS_RIGHT_FOOT_2, BONE_INDEX::BONE_POS_RIGHT_FOOT_1, BONE_INDEX::BONE_POS_TUMMY },       // Right foot -> bottom spine
    { BONE_INDEX::BONE_POS_TUMMY, BONE_INDEX::BONE_POS_CHEST, BONE_INDEX::BONE_POS_NECK, BONE_INDEX::BONE_POS_HEAD }                           // Bottom spine -> head
};
*/
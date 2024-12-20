/*
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MANGOS_DBCSTRUCTURE_H
#define MANGOS_DBCSTRUCTURE_H

#include <map>
#include <set>
#include "Define.h"
#include "DBCEnums.h"

// Structures using to access raw DBC data and required packing to portability

// GCC have alternative #pragma pack(N) syntax and old gcc version not support pack(push,N), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

struct AchievementEntry
{
    uint32    ID;                                           // 0
    uint32    factionFlag;                                  // 1 -1=all, 0=horde, 1=alliance
    uint32    mapID;                                        // 2 -1=none
    //uint32 parentAchievement;                             // 3 its Achievement parent (can`t start while parent uncomplete, use its Criteria if don`t have own, use its progress on begin)
    char* name[16];                                         // 4-19
    //uint32 name_flags;                                    // 20
    char* description[16];                                  // 21-36
    //uint32 desc_flags;                                    // 37
    uint32    categoryId;                                   // 38
    uint32    points;                                       // 39 reward points
    //uint32 OrderInCategory;                               // 40
    uint32    flags;                                        // 41
    //uint32    icon;                                       // 42 icon (from SpellIcon.dbc)
    char* titleReward[16];                                  // 43-58
    //uint32 titleReward_flags;                             // 59
    uint32 count;                                           // 60 - need this count of completed criterias (own or referenced achievement criterias)
    uint32 refAchievement;                                  // 61 - referenced achievement (counting of all completed criterias)
};

struct AchievementCategoryEntry
{
    uint32    ID;                                           // 0
    uint32    parentCategory;                               // 1 -1 for main category
    //char *name[16];                                       // 2-17
    //uint32 name_flags;                                    // 18
    //uint32    sortOrder;                                  // 19
};

struct AchievementCriteriaEntry
{
    uint32  ID;                                             // 0
    uint32  referredAchievement;                            // 1
    uint32  requiredType;                                   // 2
    uint32  field3;                                         // 3 main requirement
    uint32  count;                                          // 4 main requirement count
    uint32  additionalRequirement1_type;                    // 5 additional requirement 1 type
    uint32  additionalRequirement1_value;                   // 6 additional requirement 1 value
    uint32  additionalRequirement2_type;                    // 7 additional requirement 2 type
    uint32  additionalRequirement2_value;                   // 8 additional requirement 1 value
    char*  name[16];                                        // 9-24
    //uint32 name_flags;                                    // 25
    uint32  completionFlag;                                 // 26
    uint32  groupFlag;                                      // 27
    //uint32 unk1;                                          // 28 Alway appears with timed events
                                                            // for timed spells it is spell id for
                                                            // timed kills it is creature id
    uint32  timeLimit;                                      // 29 time limit in seconds
    //uint32 showOrder;                                     // 30 show order
};

struct AreaTableEntry
{
    uint32  ID;                                             // 0
    uint32  mapid;                                          // 1
    uint32  zone;                                           // 2 if 0 then it's zone, else it's zone id of this area
    uint32  exploreFlag;                                    // 3, main index
    uint32  flags;                                          // 4, unknown value but 312 for all cities
                                                            // 5-9 unused
    int32   area_level;                                     // 10
    char*   area_name[16];                                  // 11-26
                                                            // 27, string flags, unused
    uint32  team;                                           // 28
};

struct AreaGroupEntry
{
    uint32  AreaGroupId;                                    // 0
    uint32  AreaId[6];                                      // 1-6
    uint32  nextGroup;                                      // 7 index of next group
};

struct AreaTriggerEntry
{
    uint32  id;                                             // 0        m_ID
    uint32  mapid;                                          // 1        m_ContinentID
    float   x;                                              // 2        m_x
    float   y;                                              // 3        m_y
    float   z;                                              // 4        m_z
    float   radius;                                         // 5        m_radius
    float   box_x;                                          // 6        m_box_length
    float   box_y;                                          // 7        m_box_width
    float   box_z;                                          // 8        m_box_heigh
    float   box_orientation;                                // 9        m_box_yaw
};

struct AuctionHouseEntry
{
    uint32    houseId;                                      // 0 index
    uint32    faction;                                      // 1 id of faction.dbc for player factions associated with city
    uint32    depositPercent;                               // 2 1/3 from real
    uint32    cutPercent;                                   // 3
    //char*     name[16];                                   // 4-19
                                                            // 20 string flag, unused
};

struct BankBagSlotPricesEntry
{
    uint32  ID;
    uint32  price;
};

struct BarberShopStyleEntry
{
    uint32  Id;                                             // 0
    uint32  type;                                           // 1 value 0 -> hair, value 2 -> facialhair
    //char*   name[16];                                     // 2-17 name of hair style
    //uint32  name_flags;                                   // 18
    //uint32  unk_name[16];                                 // 19-34, all empty
    //uint32  unk_flags;                                    // 35
    //float   CostMultiplier;                               // 36 values 1 and 0.75
    uint32  race;                                           // 37 race
    uint32  gender;                                         // 38 0 -> male, 1 -> female
    uint32  hair_id;                                        // 39 real ID to hair/facial hair
};

struct BattlemasterListEntry
{
    uint32  id;                                             // 0
    int32   mapid[8];                                       // 1-8 mapid
    uint32  type;                                           // 9 (3 - BG, 4 - arena)
    //uint32 canJoinAsGroup;                                // 10 (0 or 1)
    char*   name[16];                                       // 11-26
    //uint32 nameFlags                                      // 27 string flag, unused
    uint32 maxGroupSize;                                    // 28 maxGroupSize, used for checking if queue as group
    uint32 HolidayWorldStateId;                             // 29 new 3.1
    uint32 minLevel;                                        // 30, min level (sync with PvPDifficulty.dbc content)
    uint32 maxLevel;                                        // 31, max level (sync with PvPDifficulty.dbc content)
};

/*struct Cfg_CategoriesEntry
{
    uint32 Index;                                           // categoryId, sent in RealmList packet
    uint32 Unk1;
    uint32 Unk2;
    uint32 IsTournamentRealm;
    char *categoryName[16];
    uint32 categoryNameFlags;
}*/

/*struct Cfg_ConfigsEntry
{
    uint32 Id;
    uint32 Type;                                            // sent in RealmList packet
    uint32 IsPvp;
    uint32 IsRp;
};*/

#define MAX_OUTFIT_ITEMS 24

struct CharStartOutfitEntry
{
    //uint32 Id;                                            // 0
    uint32 RaceClassGender;                                 // 1 (UNIT_FIELD_BYTES_0 & 0x00FFFFFF) comparable (0 byte = race, 1 byte = class, 2 byte = gender)
    int32 ItemId[MAX_OUTFIT_ITEMS];                         // 2-25
    //int32 ItemDisplayId[MAX_OUTFIT_ITEMS];                // 26-29 not required at server side
    //int32 ItemInventorySlot[MAX_OUTFIT_ITEMS];            // 50-73 not required at server side
    //uint32 Unknown1;                                      // 74, unique values (index-like with gaps ordered in other way as ids)
    //uint32 Unknown2;                                      // 75
    //uint32 Unknown3;                                      // 76
};

struct CharTitlesEntry
{
    uint32  ID;                                             // 0, title ids, for example in Quest::GetCharTitleId()
    //uint32      unk1;                                     // 1 flags?
    char*   name[16];                                       // 2-17
                                                            // 18 string flag, unused
    //char*       name2[16];                                // 19-34, unused
                                                            // 35 string flag, unused
    uint32  bit_index;                                      // 36 used in PLAYER_CHOSEN_TITLE and 1<<index in PLAYER__FIELD_KNOWN_TITLES
};

struct ChatChannelsEntry
{
    uint32  ChannelID;                                      // 0
    uint32  flags;                                          // 1
    char*   pattern[16];                                    // 3-18
                                                            // 19 string flags, unused
    //char*       name[16];                                 // 20-35 unused
                                                            // 36 string flag, unused
};

struct ChrClassesEntry
{
    uint32  ClassID;                                        // 0
    //uint32 flags;                                         // 1, unused
    uint32  powerType;                                      // 2
                                                            // 3, unused
    char const* name[16];                                   // 4-19 unused
                                                            // 20 string flag, unused
    //char*       nameFemale[16];                           // 21-36 unused, if different from base (male) case
                                                            // 37 string flag, unused
    //char*       nameNeutralGender[16];                    // 38-53 unused, if different from base (male) case
                                                            // 54 string flag, unused
                                                            // 55, unused capitalized name
    uint32  spellfamily;                                    // 56
    //uint32 flags2;                                        // 57, unused 0x08 HasRelicSlot
    uint32  CinematicSequence;                              // 58 id from CinematicSequences.dbc
    uint32  expansion;                                      // 59 (0 - original race, 1 - tbc addon, ...)
};

struct ChrRacesEntry
{
    uint32      RaceID;                                     // 0
                                                            // 1 unused
    uint32      FactionID;                                  // 2 facton template id
                                                            // 3 unused
    uint32      model_m;                                    // 4
    uint32      model_f;                                    // 5
                                                            // 6 unused
    uint32      TeamID;                                     // 7 (7-Alliance 1-Horde)
                                                            // 8-11 unused
    uint32      CinematicSequence;                          // 12 id from CinematicSequences.dbc
    //uint32    unk_322;                                    // 13 faction (0 alliance, 1 horde, 2 not available?)
    char*       name[16];                                   // 14-29 used for DBC language detection/selection
                                                            // 30 string flags, unused
    //char*       nameFemale[16];                           // 31-46, if different from base (male) case
                                                            // 47 string flags, unused
    //char*       nameNeutralGender[16];                    // 48-63, if different from base (male) case
                                                            // 64 string flags, unused
                                                            // 65-67 unused
    uint32      expansion;                                  // 68 (0 - original race, 1 - tbc addon, ...)
};

/*struct CinematicCameraEntry
{
    uint32      id;                                         // 0 index
    char*       filename;                                   // 1
    uint32      soundid;                                    // 2 in SoundEntries.dbc or 0
    float       start_x;                                    // 3
    float       start_y;                                    // 4
    float       start_z;                                    // 5
    float       unk6;                                       // 6 speed?
};*/

struct CinematicSequencesEntry
{
    uint32      Id;                                         // 0 index
    //uint32      unk1;                                     // 1 always 0
    //uint32      cinematicCamera;                          // 2 id in CinematicCamera.dbc
                                                            // 3-9 always 0
};

struct CreatureDisplayInfoEntry
{
    uint32      Displayid;                                  // 0        m_ID
                                                            // 1        m_modelID
                                                            // 2        m_soundID
                                                            // 3        m_extendedDisplayInfoID
    float       scale;                                      // 4        m_creatureModelScale
                                                            // 5        m_creatureModelAlpha
                                                            // 6-8      m_textureVariation[3]
                                                            // 9        m_portraitTextureName
                                                            // 10       m_sizeClass
                                                            // 11       m_bloodID
                                                            // 12       m_NPCSoundID
                                                            // 13       m_particleColorID
                                                            // 14       m_creatureGeosetData
                                                            // 15       m_objectEffectPackageID
};

struct CreatureFamilyEntry
{
    uint32  ID;                                             // 0        m_ID
    float   minScale;                                       // 1        m_minScale
    uint32  minScaleLevel;                                  // 2        m_minScaleLevel
    float   maxScale;                                       // 3        m_maxScale
    uint32  maxScaleLevel;                                  // 4        m_maxScaleLevel
    uint32  skillLine[2];                                   // 5-6      m_skillLine
    uint32  petFoodMask;                                    // 7        m_petFoodMask
    int32   petTalentType;                                  // 8        m_petTalentType
                                                            // 9        m_categoryEnumID
    char*   Name[16];                                       // 10-25    m_name_lang
                                                            // 26 string flags
                                                            // 27       m_iconFile
};

#define MAX_CREATURE_SPELL_DATA_SLOT 4

struct CreatureSpellDataEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    spellId[MAX_CREATURE_SPELL_DATA_SLOT];        // 1-4      m_spells[4]
    //uint32    availability[MAX_CREATURE_SPELL_DATA_SLOT]; // 4-7      m_availability[4]
};

struct CreatureTypeEntry
{
    uint32    ID;                                           // 0        m_ID
    //char*   Name[16];                                     // 1-16     name
                                                            // 17       string flags
    //uint32    no_expirience;                              // 18 no exp? critters, non-combat pets, gas cloud.
};

/*struct CurrencyCategoryEntry
{
    uint32    ID;                                           // 0
    uint32    Unk1;                                         // 1        0 for known categories and 3 for unknown one (3.0.9)
    char*   Name[16];                                       // 2-17     name
    //                                                      // 18       string flags
};*/

struct CurrencyTypesEntry
{
    //uint32    ID;                                         // 0        not used
    uint32    ItemId;                                       // 1        used as real index
    //uint32    Category;                                   // 2        may be category
    uint32    BitIndex;                                     // 3        bit index in PLAYER_FIELD_KNOWN_CURRENCIES (1 << (index-1))
};

struct DurabilityCostsEntry
{
    uint32    Itemlvl;                                      // 0
    uint32    multiplier[29];                               // 1-29
};

struct DurabilityQualityEntry
{
    uint32    Id;                                           // 0
    float     quality_mod;                                  // 1
};

struct EmotesEntry
{
    uint32  Id;                                             // 0
    //char*   Name;                                         // 1, internal name
    //uint32  AnimationId;                                  // 2, ref to animationData
    uint32  Flags;                                          // 3, bitmask, may be unit_flags
    uint32  EmoteType;                                      // 4, Can be 0, 1 or 2 (determine how emote are shown)
    uint32  UnitStandState;                                 // 5, uncomfirmed, may be enum UnitStandStateType
    //uint32  SoundId;                                      // 6, ref to soundEntries
};

struct EmotesTextEntry
{
    uint32  Id;
    uint32  textid;
};

struct FactionEntry
{
    uint32      ID;                                         // 0        m_ID
    int32       reputationListID;                           // 1        m_reputationIndex
    uint32      BaseRepRaceMask[4];                         // 2-5      m_reputationRaceMask
    uint32      BaseRepClassMask[4];                        // 6-9      m_reputationClassMask
    int32       BaseRepValue[4];                            // 10-13    m_reputationBase
    uint32      ReputationFlags[4];                         // 14-17    m_reputationFlags
    uint32      team;                                       // 18       m_parentFactionID
    //float     unk1;                                       // 19
    //float     unk2;                                       // 20
    //uint32    unk3                                        // 21
    //uint32    unk4;                                       // 22
    char*       name[16];                                   // 23-38    m_name_lang
                                                            // 39 string flags
    //char*     description[16];                            // 40-55    m_description_lang
                                                            // 56 string flags
};

struct FactionTemplateEntry
{
    uint32      ID;                                         // 0        m_ID
    uint32      faction;                                    // 1        m_faction
    uint32      factionFlags;                               // 2        m_flags
    uint32      ourMask;                                    // 3        m_factionGroup
    uint32      friendlyMask;                               // 4        m_friendGroup
    uint32      hostileMask;                                // 5        m_enemyGroup
    uint32      enemyFaction[4];                            // 6        m_enemies[4]
    uint32      friendFaction[4];                           // 10       m_friend[4]
    //-------------------------------------------------------  end structure

    // helpers
    bool IsFriendlyTo(FactionTemplateEntry const& entry) const
    {
        if(entry.faction)
        {
            for(int i = 0; i < 4; ++i)
                if (enemyFaction[i]  == entry.faction)
                    return false;
            for(int i = 0; i < 4; ++i)
                if (friendFaction[i] == entry.faction)
                    return true;
        }
        return (friendlyMask & entry.ourMask) || (ourMask & entry.friendlyMask);
    }
    bool IsHostileTo(FactionTemplateEntry const& entry) const
    {
        if(entry.faction)
        {
            for(int i = 0; i < 4; ++i)
                if (enemyFaction[i]  == entry.faction)
                    return true;
            for(int i = 0; i < 4; ++i)
                if (friendFaction[i] == entry.faction)
                    return false;
        }
        return (hostileMask & entry.ourMask) != 0;
    }
    bool IsHostileToPlayers() const { return (hostileMask & FACTION_MASK_PLAYER) !=0; }
    bool IsNeutralToAll() const
    {
        for(int i = 0; i < 4; ++i)
            if (enemyFaction[i] != 0)
                return false;
        return hostileMask == 0 && friendlyMask == 0;
    }
    bool IsContestedGuardFaction() const { return (factionFlags & FACTION_TEMPLATE_FLAG_CONTESTED_GUARD)!=0; }
};

struct GameObjectDisplayInfoEntry
{
    uint32      Displayid;                                  // 0        m_ID
    //char* filename;                                       // 1
    //uint32 unknown2[10];                                  // 2-11     unknown data
    float  unknown12;                                       // 12-17    unknown size data, use first value as interact dist, mostly in hacks way
    //float  unknown13[5];                                  // 12-17    unknown size data
    //uint32 unknown18;                                     // 18       unknown data
};

struct GemPropertiesEntry
{
    uint32      ID;
    uint32      spellitemenchantement;
    uint32      color;
};

struct GlyphPropertiesEntry
{
    uint32  Id;
    uint32  SpellId;
    uint32  TypeFlags;
    uint32  Unk1;                                           // GlyphIconId (SpellIcon.dbc)
};

struct GlyphSlotEntry
{
    uint32  Id;
    uint32  TypeFlags;
    uint32  Order;
};

// All Gt* DBC store data for 100 levels, some by 100 per class/race
#define GT_MAX_LEVEL    100
// gtOCTClassCombatRatingScalar.dbc stores data for 32 ratings, look at MAX_COMBAT_RATING for real used amount
#define GT_MAX_RATING   32

struct GtBarberShopCostBaseEntry
{
    float   cost;
};

struct GtCombatRatingsEntry
{
    float    ratio;
};

struct GtChanceToMeleeCritBaseEntry
{
    float    base;
};

struct GtChanceToMeleeCritEntry
{
    float    ratio;
};

struct GtChanceToSpellCritBaseEntry
{
    float    base;
};

struct GtChanceToSpellCritEntry
{
    float    ratio;
};

struct GtOCTClassCombatRatingScalarEntry
{
    uint32   Id;
    float    ratio;
};

struct GtOCTRegenHPEntry
{
    float    ratio;
};

//struct GtOCTRegenMPEntry
//{
//    float    ratio;
//};

struct GtRegenHPPerSptEntry
{
    float    ratio;
};

struct GtRegenMPPerSptEntry
{
    float    ratio;
};

/*struct HolidayDescriptionsEntry
{
    uint32 ID;                                              // 0, this is NOT holiday id
    //char*     name[16]                                    // 1-16 m_name_lang
                                                            // 17 name flags
};*/

/*struct HolidayNamesEntry
{
    uint32 ID;                                              // 0, this is NOT holiday id
    //char*     name[16]                                    // 1-16 m_name_lang
    // 17 name flags
};*/

struct HolidaysEntry
{
    uint32 ID;                                              // 0, holiday id
    //uint32 unk1;                                          // 1
    //uint32 unk2;                                          // 2
    //uint32 unk3[8]                                        // 3-10, empty fields
    //uint32 unk11[13]                                      // 11-23, some unknown data (bit strings?)
    //uint32 unk11[13]                                      // 24-36, some empty fields (continue prev?)
    //uint32 unk11[12]                                      // 37-48, counters?
    //uint32 holidayNameId;                                 // 49, id for HolidayNames.dbc
    //uint32 holidayDescriptionId;                          // 50, id for HolidayDescriptions.dbc
    //uint32 unk51;                                         // 51
    //uint32 unk52;                                         // 52
    //uint32 unk53;                                         // 53
    //uint32 unk54;                                         // 54
};

struct ItemEntry
{
   uint32   ID;                                             // 0
   uint32   Class;                                          // 1
   uint32   SubClass;                                       // 2 some items have strange subclasses
   int32    Unk0;                                           // 3
   int32    Material;                                       // 4
   uint32   DisplayId;                                      // 5
   uint32   InventoryType;                                  // 6
   uint32   Sheath;                                         // 7
};

struct ItemBagFamilyEntry
{
    uint32   ID;                                            // 0
    //char*     name[16]                                    // 1-16     m_name_lang
    //                                                      // 17       name flags
};

struct ItemDisplayInfoEntry
{
    uint32      ID;                                         // 0        m_ID
                                                            // 1        m_modelName[2]
                                                            // 2        m_modelTexture[2]
                                                            // 3        m_inventoryIcon
                                                            // 4        m_geosetGroup[3]
                                                            // 5        m_flags
                                                            // 6        m_spellVisualID
                                                            // 7        m_groupSoundIndex
                                                            // 8        m_helmetGeosetVis[2]
                                                            // 9        m_texture[2]
                                                            // 10       m_itemVisual[8]
                                                            // 11       m_particleColorID
};

//struct ItemCondExtCostsEntry
//{
//    uint32      ID;
//    uint32      condExtendedCost;                         // ItemPrototype::CondExtendedCost
//    uint32      itemextendedcostentry;                    // ItemPrototype::ExtendedCost
//    uint32      arenaseason;                              // arena season number(1-4)
//};

struct ItemExtendedCostEntry
{
    uint32      ID;                                         // 0 extended-cost entry id
    uint32      reqhonorpoints;                             // 1 required honor points
    uint32      reqarenapoints;                             // 2 required arena points
    uint32      reqarenaslot;                               // 4 arena slot restrctions (min slot value)
    uint32      reqitem[5];                                 // 5-8 required item id
    uint32      reqitemcount[5];                            // 9-13 required count of 1st item
    uint32      reqpersonalarenarating;                     // 14 required personal arena rating
};

struct ItemLimitCategoryEntry
{
    uint32      ID;                                         // 0 Id
    //char*     name[16]                                    // 1-16     m_name_lang
                                                            // 17 name flags
    uint32      maxCount;                                   // 18, max allowed equipped as item or in gem slot
    uint32      mode;                                       // 19, 0 = have, 1 = equip (enum ItemLimitCategoryMode)
};

struct ItemRandomPropertiesEntry
{
    uint32    ID;                                           // 0        m_ID
    //char*     internalName                                // 1        m_Name
    uint32    enchant_id[5];                                // 2-6      m_Enchantment
    char*     nameSuffix[16];                               // 7-22     m_name_lang
                                                            // 23 name flags
};

struct ItemRandomSuffixEntry
{
    uint32    ID;                                           // 0        m_ID
    char*     nameSuffix[16];                               // 1-16     m_name_lang
                                                            // 17, name flags
                                                            // 18       m_internalName
    uint32    enchant_id[5];                                // 19-21    m_enchantment
    uint32    prefix[5];                                    // 22-24    m_allocationPct
};

struct ItemSetEntry
{
    uint32    id;                                           // 0        m_ID
    char*     name[16];                                     // 1-16     m_name_lang
                                                            // 17 string flags, unused
    uint32    itemId[17];                                   // 18-34    m_itemID
    uint32    spells[8];                                    // 35-42    m_setSpellID
    uint32    items_to_triggerspell[8];                     // 43-50    m_setThreshold
    uint32    required_skill_id;                            // 51       m_requiredSkill
    uint32    required_skill_value;                         // 52       m_requiredSkillRank
};

#define MAX_LOCK_CASE 8

struct LockEntry
{
    uint32      ID;                                         // 0        m_ID
    uint32      Type[MAX_LOCK_CASE];                        // 1-8      m_Type
    uint32      Index[MAX_LOCK_CASE];                       // 9-16     m_Index
    uint32      Skill[MAX_LOCK_CASE];                       // 17-24    m_Skill
    //uint32      Action[MAX_LOCK_CASE];                    // 25-32    m_Action
};

struct MailTemplateEntry
{
    uint32      ID;                                         // 0
    //char*       subject[16];                              // 1-16
                                                            // 17 name flags, unused
    char*       content[16];                                // 18-33
};

struct MapEntry
{
    uint32  MapID;                                          // 0
    //char*       internalname;                             // 1 unused
    uint32  map_type;                                       // 2
    //uint32 mapFlags;                                      // 3 some kind of flags (0x100 - CAN_CHANGE_PLAYER_DIFFICULTY)
    //uint32 isPvP;                                         // 4 0 or 1 for battlegrounds (not arenas)
    char*   name[16];                                       // 5-20
                                                            // 21 name flags, unused
    uint32  linked_zone;                                    // 22 common zone for instance and continent map
    //char*     hordeIntro[16];                             // 23-38 text for PvP Zones
                                                            // 39 intro text flags
    //char*     allianceIntro[16];                          // 40-55 text for PvP Zones
                                                            // 56 intro text flags
    uint32  multimap_id;                                    // 57 index in  LoadingScreens.dbc
    //float   BattlefieldMapIconScale;                      // 58 BattlefieldMapIconScale
    int32   ghost_entrance_map;                             // 59 map_id of entrance map in ghost mode (continent always and in most cases = normal entrance)
    float   ghost_entrance_x;                               // 60 entrance x coordinate in ghost mode  (in most cases = normal entrance)
    float   ghost_entrance_y;                               // 61 entrance y coordinate in ghost mode  (in most cases = normal entrance)
    //uint32  timeOfDayOverride;                            // 62 time of day override
    uint32  addon;                                          // 63 expansion
                                                            // 64 some kind of time?
    //uint32 maxPlayers;                                    // 65 max players

    // Helpers
    uint32 Expansion() const { return addon; }

    bool IsDungeon() const { return map_type == MAP_INSTANCE || map_type == MAP_RAID; }
    bool IsNonRaidDungeon() const { return map_type == MAP_INSTANCE; }
    bool Instanceable() const { return map_type == MAP_INSTANCE || map_type == MAP_RAID || map_type == MAP_BATTLEGROUND || map_type == MAP_ARENA; }
    bool IsRaid() const { return map_type == MAP_RAID; }
    bool IsBattleGround() const { return map_type == MAP_BATTLEGROUND; }
    bool IsBattleArena() const { return map_type == MAP_ARENA; }
    bool IsBattleGroundOrArena() const { return map_type == MAP_BATTLEGROUND || map_type == MAP_ARENA; }

    bool IsMountAllowed() const
    {
        return !IsDungeon() ||
            MapID==209 || MapID==269 || MapID==309 ||       // TanarisInstance, CavernsOfTime, Zul'gurub
            MapID==509 || MapID==534 || MapID==560 ||       // AhnQiraj, HyjalPast, HillsbradPast
            MapID==568 || MapID==580 || MapID==595 ||       // ZulAman, Sunwell Plateau, Culling of Stratholme
            MapID==615 || MapID==616;                       // Obsidian Sanctum, Eye Of Eternity
    }

    bool IsContinent() const
    {
        return MapID == 0 || MapID == 1 || MapID == 530 || MapID == 571;
    }
};

struct MapDifficultyEntry
{
    //uint32      Id;                                       // 0
    uint32      MapId;                                      // 1
    uint32      Difficulty;                                 // 2 (for arenas: arena slot)
    //char*       areaTriggerText[16];                      // 3-18 text showed when transfer to map failed (missing requirements)
    //uint32      textFlags;                                // 19
    uint32      resetTime;                                  // 20
    uint32      maxPlayers;                                 // 21
    //char*       difficultyString;                         // 22
};

struct MovieEntry
{
    uint32      Id;                                         // 0 index
    //char*       filename;                                 // 1
    //uint32      unk2;                                     // 2 always 100
};

struct PvPDifficultyEntry
{
    //uint32      id;                                       // 0        m_ID
    uint32      mapId;                                      // 1
    uint32      bracketId;                                  // 2
    uint32      minLevel;                                   // 3
    uint32      maxLevel;                                   // 4
    uint32      difficulty;                                 // 5

    // helpers
    BattleGroundBracketId GetBracketId() const { return BattleGroundBracketId(bracketId); }
};

struct QuestFactionRewardEntry
{
    uint32      id;                                         // 0
    int32       rewardValue[10];                            // 1-10
};

struct QuestSortEntry
{
    uint32      id;                                         // 0        m_ID
    //char*       name[16];                                 // 1-16     m_SortName_lang
                                                            // 17 name flags
};

struct QuestXPLevel
{
    uint32      questLevel;                                 // 0
    uint32      xpIndex[9];                                 // 1-9
    //unk                                                   // 10
};

struct RandomPropertiesPointsEntry
{
    //uint32  Id;                                           // 0 hidden key
    uint32    itemLevel;                                    // 1
    uint32    EpicPropertiesPoints[5];                      // 2-6
    uint32    RarePropertiesPoints[5];                      // 7-11
    uint32    UncommonPropertiesPoints[5];                  // 12-16
};

struct ScalingStatDistributionEntry
{
    uint32  Id;                                             // 0
    int32   StatMod[10];                                    // 1-10
    uint32  Modifier[10];                                   // 11-20
    uint32  MaxLevel;                                       // 21
};

struct ScalingStatValuesEntry
{
    uint32  Id;                                             // 0
    uint32  Level;                                          // 1
    uint32  ssdMultiplier[4];                               // 2-5 Multiplier for ScalingStatDistribution
    uint32  armorMod[4];                                    // 6-9 Armor for level
    uint32  dpsMod[6];                                      // 10-15 DPS mod for level
    uint32  spellBonus;                                     // 16 spell power for level
    uint32  ssdMultiplier2;                                 // 17 there's data from 3.1 dbc ssdMultiplier[3]
    uint32  ssdMultiplier3;                                 // 18 3.3
    //uint32 unk2;                                          // 19 unk, probably also Armor for level (flag 0x80000?)
    uint32  armorMod2[4];                                   // 20-23 Armor for level

    uint32  getssdMultiplier(uint32 mask) const
    {
        if (mask & 0x4001F)
        {
            if(mask & 0x00000001) return ssdMultiplier[0];
            if(mask & 0x00000002) return ssdMultiplier[1];
            if(mask & 0x00000004) return ssdMultiplier[2];
            if(mask & 0x00000008) return ssdMultiplier2;
            if(mask & 0x00000010) return ssdMultiplier[3];
            if(mask & 0x00040000) return ssdMultiplier3;
        }
        return 0;
    }

    uint32  getArmorMod(uint32 mask) const
    {
        if (mask & 0x00F001E0)
        {
            if(mask & 0x00000020) return armorMod[0];
            if(mask & 0x00000040) return armorMod[1];
            if(mask & 0x00000080) return armorMod[2];
            if(mask & 0x00000100) return armorMod[3];

            if(mask & 0x00100000) return armorMod2[0];      // cloth
            if(mask & 0x00200000) return armorMod2[1];      // leather
            if(mask & 0x00400000) return armorMod2[2];      // mail
            if(mask & 0x00800000) return armorMod2[3];      // plate
        }
        return 0;
    }

    uint32 getDPSMod(uint32 mask) const
    {
        if (mask & 0x7E00)
        {
            if(mask & 0x00000200) return dpsMod[0];
            if(mask & 0x00000400) return dpsMod[1];
            if(mask & 0x00000800) return dpsMod[2];
            if(mask & 0x00001000) return dpsMod[3];
            if(mask & 0x00002000) return dpsMod[4];
            if(mask & 0x00004000) return dpsMod[5];         // not used?
        }
        return 0;
    }

    uint32 getSpellBonus(uint32 mask) const
    {
        if (mask & 0x00008000)
            return spellBonus;
        return 0;
    }

    uint32 getFeralBonus(uint32 mask) const                 // removed in 3.2.x?
    {
        if (mask & 0x00010000)                              // not used?
            return 0;
        return 0;
    }
};

//struct SkillLineCategoryEntry{
//    uint32    id;                                         // 0      m_ID
//    char*     name[16];                                   // 1-17   m_name_lang
//                                                          // 18 string flag
//    uint32    displayOrder;                               // 19     m_sortIndex
//};

//struct SkillRaceClassInfoEntry{
//    uint32    id;                                         // 0      m_ID
//    uint32    skillId;                                    // 1      m_skillID
//    uint32    raceMask;                                   // 2      m_raceMask
//    uint32    classMask;                                  // 3      m_classMask
//    uint32    flags;                                      // 4      m_flags
//    uint32    reqLevel;                                   // 5      m_minLevel
//    uint32    skillTierId;                                // 6      m_skillTierID
//    uint32    skillCostID;                                // 7      m_skillCostIndex
//};

//struct SkillTiersEntry{
//    uint32    id;                                         // 0      m_ID
//    uint32    skillValue[16];                             // 1-17   m_cost
//    uint32    maxSkillValue[16];                          // 18-32  m_valueMax
//};

struct SkillLineEntry
{
    uint32    id;                                           // 0        m_ID
    int32     categoryId;                                   // 1        m_categoryID
    //uint32    skillCostID;                                // 2        m_skillCostsID
    char*     name[16];                                     // 3-18     m_displayName_lang
                                                            // 19 string flags
    //char*     description[16];                            // 20-35    m_description_lang
                                                            // 36 string flags
    uint32    spellIcon;                                    // 37       m_spellIconID
    //char*     alternateVerb[16];                          // 38-53    m_alternateVerb_lang
                                                            // 54 string flags
    uint32    canLink;                                      // 55       m_canLink (prof. with recipes
};

struct SkillLineAbilityEntry
{
    uint32    id;                                           // 0        m_ID
    uint32    skillId;                                      // 1        m_skillLine
    uint32    spellId;                                      // 2        m_spell
    uint32    racemask;                                     // 3        m_raceMask
    uint32    classmask;                                    // 4        m_classMask
    //uint32    racemaskNot;                                // 5        m_excludeRace
    //uint32    classmaskNot;                               // 6        m_excludeClass
    uint32    req_skill_value;                              // 7        m_minSkillLineRank
    uint32    forward_spellid;                              // 8        m_supercededBySpell
    uint32    learnOnGetSkill;                              // 9        m_acquireMethod
    uint32    max_value;                                    // 10       m_trivialSkillLineRankHigh
    uint32    min_value;                                    // 11       m_trivialSkillLineRankLow
    //uint32    characterPoints[2];                         // 12-13    m_characterPoints[2]
};

struct SoundEntriesEntry
{
    uint32    Id;                                           // 0        m_ID
    //uint32    Type;                                       // 1        m_soundType
    //char*     InternalName;                               // 2        m_name
    //char*     FileName[10];                               // 3-12     m_File[10]
    //uint32    Unk13[10];                                  // 13-22    m_Freq[10]
    //char*     Path;                                       // 23       m_DirectoryBase
                                                            // 24       m_volumeFloat
                                                            // 25       m_flags
                                                            // 26       m_minDistance
                                                            // 27       m_distanceCutoff
                                                            // 28       m_EAXDef
                                                            // 29       new in 3.1
};

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2
#define MAX_SPELL_TOTEM_CATEGORIES 2

struct SpellEntry
{
    uint32    Id;                                           // 0        m_ID
    uint32    Category;                                     // 1        m_category
    uint32    Dispel;                                       // 2        m_dispelType
    uint32    Mechanic;                                     // 3        m_mechanic
    uint32    Attributes;                                   // 4        m_attribute
    uint32    AttributesEx;                                 // 5        m_attributesEx
    uint32    AttributesEx2;                                // 6        m_attributesExB
    uint32    AttributesEx3;                                // 7        m_attributesExC
    uint32    AttributesEx4;                                // 8        m_attributesExD
    uint32    AttributesEx5;                                // 9        m_attributesExE
    uint32    AttributesEx6;                                // 10       m_attributesExF
    uint32    AttributesEx7;                                // 11       3.2.0 (0x20 - totems, 0x4 - paladin auras, etc...)
    uint32    Stances;                                      // 12       m_shapeshiftMask
    uint32    unk_320_2;                                    // 13       3.2.0
    uint32    StancesNot;                                   // 14       m_shapeshiftExclude
    uint32    unk_320_3;                                    // 15       3.2.0
    uint32    Targets;                                      // 16       m_targets
    uint32    TargetCreatureType;                           // 17       m_targetCreatureType
    uint32    RequiresSpellFocus;                           // 18       m_requiresSpellFocus
    uint32    FacingCasterFlags;                            // 19       m_facingCasterFlags
    uint32    CasterAuraState;                              // 20       m_casterAuraState
    uint32    TargetAuraState;                              // 21       m_targetAuraState
    uint32    CasterAuraStateNot;                           // 22       m_excludeCasterAuraState
    uint32    TargetAuraStateNot;                           // 23       m_excludeTargetAuraState
    uint32    casterAuraSpell;                              // 24       m_casterAuraSpell
    uint32    targetAuraSpell;                              // 25       m_targetAuraSpell
    uint32    excludeCasterAuraSpell;                       // 26       m_excludeCasterAuraSpell
    uint32    excludeTargetAuraSpell;                       // 27       m_excludeTargetAuraSpell
    uint32    CastingTimeIndex;                             // 28       m_castingTimeIndex
    uint32    RecoveryTime;                                 // 29       m_recoveryTime
    uint32    CategoryRecoveryTime;                         // 30       m_categoryRecoveryTime
    uint32    InterruptFlags;                               // 31       m_interruptFlags
    uint32    AuraInterruptFlags;                           // 32       m_auraInterruptFlags
    uint32    ChannelInterruptFlags;                        // 33       m_channelInterruptFlags
    uint32    procFlags;                                    // 34       m_procTypeMask
    uint32    procChance;                                   // 35       m_procChance
    uint32    procCharges;                                  // 36       m_procCharges
    uint32    maxLevel;                                     // 37       m_maxLevel
    uint32    baseLevel;                                    // 38       m_baseLevel
    uint32    spellLevel;                                   // 39       m_spellLevel
    uint32    DurationIndex;                                // 40       m_durationIndex
    uint32    powerType;                                    // 41       m_powerType
    uint32    manaCost;                                     // 42       m_manaCost
    uint32    manaCostPerlevel;                             // 43       m_manaCostPerLevel
    uint32    manaPerSecond;                                // 44       m_manaPerSecond
    uint32    manaPerSecondPerLevel;                        // 45       m_manaPerSecondPerLeve
    uint32    rangeIndex;                                   // 46       m_rangeIndex
    float     speed;                                        // 47       m_speed
    uint32    modalNextSpell;                               // 48       m_modalNextSpell not used
    uint32    StackAmount;                                  // 49       m_cumulativeAura
    uint32    Totem[MAX_SPELL_TOTEMS];                      // 50-51    m_totem
    int32     Reagent[MAX_SPELL_REAGENTS];                  // 52-59    m_reagent
    uint32    ReagentCount[MAX_SPELL_REAGENTS];             // 60-67    m_reagentCount
    int32     EquippedItemClass;                            // 68       m_equippedItemClass (value)
    int32     EquippedItemSubClassMask;                     // 69       m_equippedItemSubclass (mask)
    int32     EquippedItemInventoryTypeMask;                // 70       m_equippedItemInvTypes (mask)
    uint32    Effect[MAX_EFFECT_INDEX];                     // 71-73    m_effect
    int32     EffectDieSides[MAX_EFFECT_INDEX];             // 74-76    m_effectDieSides
    float     EffectRealPointsPerLevel[MAX_EFFECT_INDEX];   // 77-79    m_effectRealPointsPerLevel
    int32     EffectBasePoints[MAX_EFFECT_INDEX];           // 80-82    m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    uint32    EffectMechanic[MAX_EFFECT_INDEX];             // 83-85    m_effectMechanic
    uint32    EffectImplicitTargetA[MAX_EFFECT_INDEX];      // 86-88    m_implicitTargetA
    uint32    EffectImplicitTargetB[MAX_EFFECT_INDEX];      // 89-91    m_implicitTargetB
    uint32    EffectRadiusIndex[MAX_EFFECT_INDEX];          // 92-94    m_effectRadiusIndex - spellradius.dbc
    uint32    EffectApplyAuraName[MAX_EFFECT_INDEX];        // 95-97    m_effectAura
    uint32    EffectAmplitude[MAX_EFFECT_INDEX];            // 98-100   m_effectAuraPeriod
    float     EffectMultipleValue[MAX_EFFECT_INDEX];        // 101-103  m_effectAmplitude
    uint32    EffectChainTarget[MAX_EFFECT_INDEX];          // 104-106  m_effectChainTargets
    uint32    EffectItemType[MAX_EFFECT_INDEX];             // 107-109  m_effectItemType
    int32     EffectMiscValue[MAX_EFFECT_INDEX];            // 110-112  m_effectMiscValue
    int32     EffectMiscValueB[MAX_EFFECT_INDEX];           // 113-115  m_effectMiscValueB
    uint32    EffectTriggerSpell[MAX_EFFECT_INDEX];         // 116-118  m_effectTriggerSpell
    float     EffectPointsPerComboPoint[MAX_EFFECT_INDEX];  // 119-121  m_effectPointsPerCombo
    uint32    EffectSpellClassMaskA[3];                     // 122-124  m_effectSpellClassMaskA, effect 0
    uint32    EffectSpellClassMaskB[3];                     // 125-127  m_effectSpellClassMaskB, effect 1
    uint32    EffectSpellClassMaskC[3];                     // 128-130  m_effectSpellClassMaskC, effect 2
    uint32    SpellVisual[2];                               // 131-132  m_spellVisualID
    uint32    SpellIconID;                                  // 133      m_spellIconID
    uint32    activeIconID;                                 // 134      m_activeIconID
    uint32    spellPriority;                                // 135      m_spellPriority not used
    char*     SpellName[16];                                // 136-151  m_name_lang
    //uint32    SpellNameFlag;                              // 152 not used
    char*     Rank[16];                                     // 153-168  m_nameSubtext_lang
    //uint32    RankFlags;                                  // 169 not used
    char*     Description[16];                              // 170-185  m_description_lang not used
    //uint32    DescriptionFlags;                           // 186 not used
    char*     ToolTip[16];                                  // 187-202  m_auraDescription_lang not used
    //uint32    ToolTipFlags;                               // 203 not used
    uint32    ManaCostPercentage;                           // 204      m_manaCostPct
    uint32    StartRecoveryCategory;                        // 205      m_startRecoveryCategory
    uint32    StartRecoveryTime;                            // 206      m_startRecoveryTime
    uint32    MaxTargetLevel;                               // 207      m_maxTargetLevel
    uint32    SpellFamilyName;                              // 208      m_spellClassSet
    uint32    SpellFamilyFlags[3];                          // 209-211  m_spellClassMask NOTE: size is 12 bytes!!!
    uint32    MaxAffectedTargets;                           // 212      m_maxTargets
    uint32    DmgClass;                                     // 213      m_defenseType
    uint32    PreventionType;                               // 214      m_preventionType
    uint32    StanceBarOrder;                               // 215      m_stanceBarOrder not used
    float     DmgMultiplier[MAX_EFFECT_INDEX];              // 216-218  m_effectChainAmplitude
    uint32    MinFactionId;                                 // 219      m_minFactionID not used
    uint32    MinReputation;                                // 220      m_minReputation not used
    uint32    RequiredAuraVision;                           // 221      m_requiredAuraVision not used
    uint32    TotemCategory[MAX_SPELL_TOTEM_CATEGORIES];    // 222-223  m_requiredTotemCategoryID
    int32     AreaGroupId;                                  // 224      m_requiredAreaGroupId
    uint32    SchoolMask;                                   // 225      m_schoolMask
    uint32    runeCostID;                                   // 226      m_runeCostID
    uint32    spellMissileID;                               // 227      m_spellMissileID not used
    uint32  PowerDisplayId;                                 // 228 PowerDisplay.dbc, new in 3.1
    float   EffectSpellBonus[MAX_EFFECT_INDEX];             // 229-231  3.2.0
    uint32  spellDescriptionVariableID;                     // 232      3.2.0
    uint32  SpellDifficultyId;                              // 233      m_spellDifficultyID - id from SpellDifficulty.dbc

    // helpers
    int32 CalculateSimpleValue(SpellEffectIndex eff) const { return EffectBasePoints[eff] + int32(1); }
    uint32 const* GetEffectSpellClassMask(SpellEffectIndex effect) const
    {
        return EffectSpellClassMaskA + effect * 3;
    }

    private:
        // prevent creating custom entries (copy data from original in fact)
        SpellEntry(SpellEntry const&);                      // DON'T must have implementation
};

typedef std::set<uint32> SpellCategorySet;
typedef std::map<uint32,SpellCategorySet > SpellCategoryStore;
typedef std::set<uint32> PetFamilySpellsSet;
typedef std::map<uint32,PetFamilySpellsSet > PetFamilySpellsStore;

struct SpellCastTimesEntry
{
    uint32    ID;                                           // 0
    int32     CastTime;                                     // 1
    //float     CastTimePerLevel;                           // 2 unsure / per skill?
    int32     MinCastTime;                                  // 3 unsure
};

struct SpellFocusObjectEntry
{
    uint32    ID;                                           // 0
    //char*     Name[16];                                   // 1-15 unused
                                                            // 16 string flags, unused
};

struct SpellRadiusEntry
{
    uint32    ID;
    float     Radius;
    float     Radius2;
};

struct SpellRangeEntry
{
    uint32    ID;                                           // 0
    float     minRange;                                     // 1
    float     minRangeFriendly;                             // 2
    float     maxRange;                                     // 3
    float     maxRangeFriendly;                             // 4
    uint32  Flags;                                          // 5
    char*   Name[16];                                       // 6-21 unused
    //uint32  NameFlags;                                    // 22 unused
    char*   ShortName[16];                                  // 23-38 unused
    //uint32  NameFlags;                                    // 39 unused
};

struct SpellRuneCostEntry
{
    uint32  ID;                                             // 0
    uint32  RuneCost[3];                                    // 1-3 (0=blood, 1=frost, 2=unholy)
    uint32  runePowerGain;                                  // 4

    bool NoRuneCost() const { return RuneCost[0] == 0 && RuneCost[1] == 0 && RuneCost[2] == 0; }
    bool NoRunicPowerGain() const { return runePowerGain == 0; }
};

struct SpellShapeshiftEntry
{
    uint32 ID;                                              // 0
    //uint32 buttonPosition;                                // 1 unused
    char*  Name[16];                                        // 2-17 unused
    //uint32 NameFlags;                                     // 18 unused
    uint32 flags1;                                          // 19
    int32  creatureType;                                    // 20 <=0 humanoid, other normal creature types
    uint32 unk1;                                            // 21 unused, related to next field
    uint32 attackSpeed;                                     // 22
    uint32 modelID_A;                                       // 23 alliance modelid (0 means no model)
    uint32 modelID_H;                                       // 24 horde modelid (but only for one form)
    uint32 unk3;                                            // 25 unused always 0
    uint32 unk4;                                            // 26 unused always 0
    uint32 spellId[8];                                      // 27-34 spells which appear in the bar after shapeshifting
};

struct SpellDifficultyEntry
{
    uint32 ID;                                              // 0        m_ID
    uint32 spellId[MAX_DIFFICULTY];                         // 1-4      m_spellId[4]
};

struct SpellDurationEntry
{
    uint32    ID;
    int32     Duration[3];
};

struct SpellItemEnchantmentEntry
{
    uint32      ID;                                         // 0        m_ID
    uint32      charges;                                    // 1        m_charges
    uint32      type[3];                                    // 2-4      m_effect[3]
    uint32      amount[3];                                  // 5-7      m_effectPointsMin[3]
    uint32      amount_max[3];                              // 8-10     m_effectPointsMax[3]
    uint32      spellid[3];                                 // 11-13    m_effectArg[3]
    char*       description[16];                            // 14-29    m_name_lang[16]
    //uint32      descriptionFlags;                         // 30 name flags
    uint32      aura_id;                                    // 31       m_itemVisual
    uint32      slot;                                       // 32       m_flags
    uint32      GemID;                                      // 33       m_src_itemID
    uint32      EnchantmentCondition;                       // 34       m_condition_id
    //uint32      requiredSkill;                            // 35       m_requiredSkillID
    //uint32      requiredSkillValue;                       // 36       m_requiredSkillRank
                                                            // 37       new in 3.1
};

struct SpellItemEnchantmentConditionEntry
{
    uint32  ID;                                             // 0        m_ID
    uint8   Color[5];                                       // 1-5      m_lt_operandType[5]
    //uint32  LT_Operand[5];                                // 6-10     m_lt_operand[5]
    uint8   Comparator[5];                                  // 11-15    m_operator[5]
    uint8   CompareColor[5];                                // 15-20    m_rt_operandType[5]
    uint32  Value[5];                                       // 21-25    m_rt_operand[5]
    //uint8   Logic[5]                                      // 25-30    m_logic[5]
};

struct StableSlotPricesEntry
{
    uint32 Slot;
    uint32 Price;
};

struct SummonPropertiesEntry
{
    uint32  Id;                                             // 0
    uint32  Group;                                          // 1, enum SummonPropGroup
    uint32  FactionId;                                      // 2,                        14 rows > 0
    uint32  Type;                                           // 3, enum SummonPropType
    uint32  Slot;                                           // 4,   if type = SUMMON_PROP_TYPE_TOTEM, its actual slot    0-6
    uint32  Flags;                                          // 5, enum SummonPropFlags
};

#define MAX_TALENT_RANK 5
#define MAX_PET_TALENT_RANK 3                               // use in calculations, expected <= MAX_TALENT_RANK

struct TalentEntry
{
    uint32    TalentID;                                     // 0
    uint32    TalentTab;                                    // 1 index in TalentTab.dbc (TalentTabEntry)
    uint32    Row;                                          // 2
    uint32    Col;                                          // 3
    uint32    RankID[MAX_TALENT_RANK];                      // 4-8
                                                            // 9-12 not used, always 0, maybe not used high ranks
    uint32    DependsOn;                                    // 13 index in Talent.dbc (TalentEntry)
                                                            // 14-15 not used
    uint32    DependsOnRank;                                // 16
                                                            // 17-18 not used
    //uint32  needAddInSpellBook;                           // 19  also need disable higest ranks on reset talent tree
    //uint32  unk2;                                         // 20, all 0
    //uint64  allowForPet;                                  // 21 its a 64 bit mask for pet 1<<m_categoryEnumID in CreatureFamily.dbc
};

struct TalentTabEntry
{
    uint32  TalentTabID;                                    // 0
    //char* name[16];                                       // 1-16, unused
    //uint32  nameFlags;                                    // 17, unused
    //unit32  spellicon;                                    // 18
                                                            // 19 not used
    uint32  ClassMask;                                      // 20
    uint32  petTalentMask;                                  // 21
    uint32  tabpage;                                        // 22
    //char* internalname;                                   // 23
};

struct TaxiNodesEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    map_id;                                       // 1        m_ContinentID
    float     x;                                            // 2        m_x
    float     y;                                            // 3        m_y
    float     z;                                            // 4        m_z
    char*     name[16];                                     // 5-21     m_Name_lang
                                                            // 22 string flags
    uint32    MountCreatureID[2];                           // 23-24    m_MountCreatureID[2]
};

struct TaxiPathEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    from;                                         // 1        m_FromTaxiNode
    uint32    to;                                           // 2        m_ToTaxiNode
    uint32    price;                                        // 3        m_Cost
};

struct TaxiPathNodeEntry
{
                                                            // 0        m_ID
    uint32    path;                                         // 1        m_PathID
    uint32    index;                                        // 2        m_NodeIndex
    uint32    mapid;                                        // 3        m_ContinentID
    float     x;                                            // 4        m_LocX
    float     y;                                            // 5        m_LocY
    float     z;                                            // 6        m_LocZ
    uint32    actionFlag;                                   // 7        m_flags
    uint32    delay;                                        // 8        m_delay
    uint32    arrivalEventID;                               // 9        m_arrivalEventID
    uint32    departureEventID;                             // 10       m_departureEventID
};

struct TotemCategoryEntry
{
    uint32    ID;                                           // 0
    //char*   name[16];                                     // 1-16
                                                            // 17 string flags, unused
    uint32    categoryType;                                 // 18 (one for specialization)
    uint32    categoryMask;                                 // 19 (compatibility mask for same type: different for totems, compatible from high to low for rods)
};

struct VehicleEntry
{
    uint32  ID;                                           // 0
    uint32  flags;                                        // 1
    float   turnSpeed;                                    // 2
    float   pitchSpeed;                                   // 3
    float   pitchMin;                                     // 4
    float   pitchMax;                                     // 5
    uint32  seatID[8];                                    // 6-13
    float   mouseLookOffsetPitch;                         // 14
    float   cameraFadeDistScalarMin;                      // 15
    float   cameraFadeDistScalarMax;                      // 16
    float   cameraPitchOffset;                            // 17
    //int     powerType[3];                               //       removed in 3.1
    //int     powerToken[3];                              //       removed in 3.1
    float   facingLimitRight;                             // 18
    float   facingLimitLeft;                              // 19
    float   msslTrgtTurnLingering;                        // 20
    float   msslTrgtPitchLingering;                       // 21
    float   msslTrgtMouseLingering;                       // 22
    float   msslTrgtEndOpacity;                           // 23
    float   msslTrgtArcSpeed;                             // 24
    float   msslTrgtArcRepeat;                            // 25
    float   msslTrgtArcWidth;                             // 26
    float   msslTrgtImpactRadius[2];                      // 27-28
    char*   msslTrgtArcTexture;                           // 29
    char*   msslTrgtImpactTexture;                        // 30
    char*   msslTrgtImpactModel[2];                       // 31-32
    float   cameraYawOffset;                              // 33
    uint32  uiLocomotionType;                             // 34
    float   msslTrgtImpactTexRadius;                      // 35
    uint32  uiSeatIndicatorType;                          // 36
                                                            // 37, new in 3.1
                                                            // 38, new in 3.1
                                                            // 39, new in 3.1
};

struct VehicleSeatEntry
{
    uint32  ID;                                           // 0
    uint32  flags;                                        // 1
    int32   attachmentID;                                 // 2
    float   attachmentOffsetX;                            // 3
    float   attachmentOffsetY;                            // 4
    float   attachmentOffsetZ;                            // 5
    float   enterPreDelay;                                // 6
    float   enterSpeed;                                   // 7
    float   enterGravity;                                 // 8
    float   enterMinDuration;                             // 9
    float   enterMaxDuration;                             // 10
    float   enterMinArcHeight;                            // 11
    float   enterMaxArcHeight;                            // 12
    int32   enterAnimStart;                               // 13
    int32   enterAnimLoop;                                // 14
    int32   rideAnimStart;                                // 15
    int32   rideAnimLoop;                                 // 16
    int32   rideUpperAnimStart;                           // 17
    int32   rideUpperAnimLoop;                            // 18
    float   exitPreDelay;                                 // 19
    float   exitSpeed;                                    // 20
    float   exitGravity;                                  // 21
    float   exitMinDuration;                              // 22
    float   exitMaxDuration;                              // 23
    float   exitMinArcHeight;                             // 24
    float   exitMaxArcHeight;                             // 25
    int32   exitAnimStart;                                // 26
    int32   exitAnimLoop;                                 // 27
    int32   exitAnimEnd;                                  // 28
    float   passengerYaw;                                 // 29
    float   passengerPitch;                               // 30
    float   passengerRoll;                                // 31
    int32   passengerAttachmentID;                        // 32
    int32   vehicleEnterAnim;                             // 33
    int32   vehicleExitAnim;                              // 34
    int32   vehicleRideAnimLoop;                          // 35
    int32   vehicleEnterAnimBone;                         // 36
    int32   vehicleExitAnimBone;                          // 37
    int32   vehicleRideAnimLoopBone;                      // 38
    float   vehicleEnterAnimDelay;                        // 39
    float   vehicleExitAnimDelay;                         // 40
    uint32  vehicleAbilityDisplay;                        // 41
    uint32  enterUISoundID;                               // 42
    uint32  exitUISoundID;                                // 43
    int32   uiSkin;                                       // 44
    uint32  flagsB;                                       // 45
                                                            // 46-57 added in 3.1, floats mostly
};

struct WorldMapAreaEntry
{
    //uint32  ID;                                           // 0
    uint32  map_id;                                         // 1
    uint32  area_id;                                        // 2 index (continent 0 areas ignored)
    //char* internal_name                                   // 3
    float   y1;                                             // 4
    float   y2;                                             // 5
    float   x1;                                             // 6
    float   x2;                                             // 7
    int32   virtual_map_id;                                 // 8 -1 (map_id have correct map) other: virtual map where zone show (map_id - where zone in fact internally)
    //int32   dungeonMap_id;                                // 9 pointer to DungeonMap.dbc (owerride x1,x2,y1,y2 coordinates)
    //uint32  someMapID;                                    // 10
};

#define MAX_WORLD_MAP_OVERLAY_AREA_IDX 4

struct WorldMapOverlayEntry
{
    uint32    ID;                                           // 0
    //uint32    worldMapAreaId;                             // 1 idx in WorldMapArea.dbc
    uint32    areatableID[MAX_WORLD_MAP_OVERLAY_AREA_IDX];  // 2-5
                                                            // 6-7 always 0, possible part of areatableID[]
    //char* internal_name                                   // 8
                                                            // 9-16 some ints
};

struct WorldSafeLocsEntry
{
    uint32    ID;                                           // 0
    uint32    map_id;                                       // 1
    float     x;                                            // 2
    float     y;                                            // 3
    float     z;                                            // 4
    //char*   name[16]                                      // 5-20 name, unused
                                                            // 21 name flags, unused
};

// GCC have alternative #pragma pack() syntax and old gcc version not support pack(pop), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

// Structures not used for casting to loaded DBC data and not required then packing
struct MapDifficulty
{
    MapDifficulty() : resetTime(0), maxPlayers(0) {}
    MapDifficulty(uint32 _resetTime, uint32 _maxPlayers) : resetTime(_resetTime), maxPlayers(_maxPlayers) {}

    uint32 resetTime;
    uint32 maxPlayers;                                      // some heroic dungeons have 0 when expect same value as in normal dificulty case
};

struct TalentSpellPos
{
    TalentSpellPos() : talent_id(0), rank(0) {}
    TalentSpellPos(uint16 _talent_id, uint8 _rank) : talent_id(_talent_id), rank(_rank) {}

    uint16 talent_id;
    uint8  rank;
};

typedef std::map<uint32,TalentSpellPos> TalentSpellPosMap;

#endif

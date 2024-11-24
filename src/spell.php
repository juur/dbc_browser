<?php
if (!isset($_GET['id'])) die("Missing parameter 'id'");
require('database.php');
require('spell_desc.php');

$spell_id = (int)$_GET['id'];
list ($result, $num_rows) = query_dbc("Spell", $spell_id);
?>
<html>
<head>
<title>Spell <?php echo $spell_id; ?></title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<p><a href=".">Index</a> / <a href="spell.php?id=<?php echo $spell_id; ?>">Spell</a></p>
<?php
require('form_findid.html');
echo "<script language=\"JavaScript\">document.formid.id.value=$spell_id;</script>\n";
if ($num_rows == 0)
    echo "Spell $spell_id not found.\n";
else
{
    $spell_info = mysqli_fetch_object($result);
    echo "<h2>Spell $spell_id: $spell_info->SpellName";
    if ($spell_info->Rank != "") echo " ($spell_info->Rank)";
    echo "</h2>\n";
    echo "<p>$spell_info->Description</p>\n";
    echo "<p><i>$spell_info->ToolTip</i></p>\n";
    echo "<table class=\"main\">\n";
    $is_modifier = array(false, false, false);
    $is_summon = array(false, false, false);
    $is_mechanic = array(false, false, false);
    $misc_school_mask = array(false, false, false);
    $row = 0;
    foreach ($spell_info as $field => $value)
    {
        // skip text fields (already displayed)
        if ($field == "SpellName" || $field == "Rank" || $field == "Description" || $field == "ToolTip")
            continue;
        // strip numeric index in effect fields
        $name = substr($field, 0, -1);
        // index for effect/attribute fields
        $eff_idx = (int)substr($field, -1, 1);
        echo "<tr class=\"row".($row%2)."\"><td class=\"field\">$field</td><td class=\"value\">";
        // links for fields with spell ids
        if ($value != 0 && ($name == "EffectTriggerSpell" || $field == "casterAuraSpell" || $field == "targetAuraSpell" || $field == "excludeCasterAuraSpell" || $field == "excludeTargetAuraSpell"))
            echo "<a href=\"spell.php?id=$value\">$value</a>";
        // search links for category fields
        else if ($value != 0 && ($field == "Category" || $name == "SpellVisual" || $field == "SpellIconID" || $field == "StartRecoveryCategory" || $field == "SpellDifficultyId"))
            echo "<a href=\"search.php?$field=$value\">$value</a>";
        // print bitmask fields as hex
        else if ($value != 0 && ($field == "Attributes" || $field == "AttributesEx" || $name == "AttributesEx" || $name == "SpellFamilyFlags"))
            echo "0x" . dechex($value);
        else
            echo $value;
        echo "</td><td class=\"desc\">";
        // describe dispel field
        if ($value != 0 && $field == "Dispel")
            echo $spell_dispel[$value];
        // describe mechanic
        else if ($value != 0 && $field == "Mechanic")
            echo $spell_mechanic[$value];
        // describe Attributes field
        else if ($field == "Attributes")
            echo get_attribute_desc(0, $value);
        // describe AttributesEx fields
        else if ($field == "AttributesEx")
            echo get_attribute_desc(1, $value);
        // describe AttributesExN fields
        else if ($name == "AttributesEx")
            echo get_attribute_desc($eff_idx, $value);
        // describe stance fields
        else if ($value != 0 && ($field == "Stances" || $field == "StancesNot"))
            echo get_stance_desc($value);
        // describe aura state fields
        else if ($value != 0 && ($field == "CasterAuraState" || $field == "TargetAuraState" || $field == "CasterAuraStateNot" || $field == "TargetAuraStateNot"))
            echo $aura_state[$value];
        // describe casting time field
        else if ($field == "CastingTimeIndex")
            print_dbc_for_entry("SpellCastTimes", $value);
        // describe interrupt flags field
        else if ($field == "InterruptFlags")
            print get_spell_int_desc($value);
        // describe aura interrupt flags field
        else if ($field == "AuraInterruptFlags")
            print get_aura_int_desc($value);
        // describe channel interrupt flags field
        else if ($field == "ChannelInterruptFlags")
            print get_channel_int_desc($value);
        // describe proc field
        else if ($field == "procFlags")
            echo get_proc_desc($value);
        // describe duration field
        else if ($field == "DurationIndex")
            print_dbc_for_entry("SpellDuration", $value);
        // describe power type field
        else if ($field == "powerType")
            echo $power_type[$value];
        // describe range field
        else if ($field == "rangeIndex")
            print_dbc_for_entry("SpellRange", $value);
        // describe reagent/item fields
        else if ($value != 0 && ($name == "Reagent" || $name == "EffectItemType"))
        {
            list ($res, $nr) = query_world("item_template", $value);
            if ($nr)
            {
                $item_template = mysql_fetch_assoc($res);
                echo "<a href=\"http://www.wowhead.com/item=$value\">$item_template[name]</a>";
            }
        }
        // describe effect fields
        else if ($value !=0 && $name == "Effect")
        {
            echo $spell_effect[$value];
            if ($value == 28)
                $is_summon[$eff_idx] = true;
        }
        else if ($name == "EffectBasePoints")
        {
            //TODO: set level and combo points as parameter elsewhere
            list($min, $max) = calc_basepoints($spell_info, $eff_idx, 80, 5);
            echo $min == $max ? "value: $min" : "min: $min, max: $max";
        }
        // describe target fields
        else if ($value != 0 && ($name == "EffectImplicitTargetA" || $name == "EffectImplicitTargetB"))
            echo $spell_target[$value];
        // describe radius fields
        else if ($value != 0 && $name == "EffectRadiusIndex")
            print_dbc_for_entry("SpellRadius", $value);
        // describe aura name fields
        else if ($value !=0 && $name == "EffectApplyAuraName")
        {
            echo $spell_aura[$value];
            switch ($value)
            {
                case 107:
                case 108:
                    $is_modifier[$eff_idx] = true;
                    break;
                case 14:
                case 71:
                case 123:
                case 163:
                case 179:
                case 186:
                case 199:
                case 269:
                case 87:
                case 183:
                case 229:
                case 310:
                    $misc_school_mask[$eff_idx] = true;
                    break;
                case 77:
                case 117:
                case 232:
                case 234:
                case 255:
                    $is_mechanic[$eff_idx] = true;
                    break;
                default:
                    break;
            }
        }
        // describe misc value fields
        else if ($name == "EffectMiscValue")
        {
            if ($is_modifier[$eff_idx])
                echo $spell_mod[$value];
            else if ($misc_school_mask[$eff_idx])
                echo get_school_desc($value);
            else if ($is_summon[$eff_idx])
            {
                list ($res, $nr) = query_world("creature_template", $value);
                if ($nr)
                {
                    $creature_template = mysql_fetch_assoc($res);
                    echo "<a href=\"http://www.wowhead.com/npc=$value\">$creature_template[name]</a>";
                }
            }
            else if ($is_mechanic[$eff_idx])
                echo $spell_mechanic[$value];
        }
        // describe misc value B fields
        else if ($name == "EffectMiscValueB")
        {
            if ($is_summon[$eff_idx])
                echo $summon_type[$value];  //TODO: use SummonProperties table
        }
        // describe trigger spell fields
        else if ($value != 0 && ($name == "EffectTriggerSpell" || $field == "casterAuraSpell" || $field == "targetAuraSpell" || $field == "excludeCasterAuraSpell" || $field == "excludeTargetAuraSpell"))
        {
            list ($res, $nr) = query_dbc("Spell", $value);
            if ($nr)
            {
                $sp_info = mysql_fetch_assoc($res);
                echo $sp_info['SpellName'];
                if ($sp_info['Rank'] != '')
                    echo "($sp_info[Rank])";
            }
        }
        // describe spell family field
        else if ($field == "SpellFamilyName")
            echo $spell_family[$value];
        // describe damage class field
        else if ($field == "DmgClass")
            echo $damage_class[$value];
        // describe prevention type field
        else if ($field == "PreventionType")
            echo $prevention_type[$value];
        // describe school field
        else if ($field == "SchoolMask")
            echo get_school_desc($value);
        // describe spell difficulty field
        else if ($field == "SpellDifficultyId")
            print_dbc_for_entry("SpellDifficulty", $value);
        echo "</td></tr>\n";
        $row++;
    }
    echo "</table>\n";
}
?>
</body>
</html>

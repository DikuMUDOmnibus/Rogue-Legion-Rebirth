#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merc.h"



void do_armorcraft( CHAR_DATA *ch, char *argument )
{

  OBJ_DATA *obj;
  OBJ_DATA *obj2;
  OBJ_DATA *obj3;
  OBJ_INDEX_DATA *pObjIndex;
  char name[MSL];
  char buf[MSL];
  char slabname[MSL];
  char slabnamecolor[MSL];
  char runename[MSL];
  char runenamecolor[MSL];
  int hitroll = 0;
  int damroll = 0;
  int hp      = 0;
  int mana    = 0;
  int move    = 0;
  int wear    = 0;
  int armor   = 0;
  int rnum    = 30037;


  char arg1[MAX_STRING_LENGTH];
  char arg2[MAX_STRING_LENGTH];
  char arg3[MAX_STRING_LENGTH];

  argument = one_argument( argument, arg1 );
  argument = one_argument( argument, arg2 );
  argument = one_argument( argument, arg3 );


  if ( arg1[0] == '\0' || arg2[0] == '\0' || arg3[0] == '\0')
  {

    send_to_char( "slab: copper, iron, steel, adamantite, mithril \n\r", ch );
    send_to_char( "runestone: fire, air, earth, water\n\r", ch );
    send_to_char( "item: bracer, greaves, collar, plate, ring, helmet \n\r", ch );
    send_to_char( "      boots, sleeves, gauntlets, cloak, belt, mask \n\r", ch );
    send_to_char( "Syntax: armorcraft <slab> <runestone> <item>.\n\r", ch );
    return;
  }

  if ( ( obj2 =  get_obj_carry( ch, arg1, ch ) )  == NULL )
  {
    sprintf( buf, "You must be holding the slab.\n\r" );
    send_to_char( buf, ch );
    return;
  }
  if ( ( obj3 =  get_obj_carry( ch, arg2, ch ) )  == NULL )
  {
    sprintf( buf, "You must be holding the rune.\n\r" );
    send_to_char( buf, ch );
    return;
  }


  if (obj2->item_type != ITEM_COPPER && obj2->item_type != ITEM_IRON
      && obj2->item_type != ITEM_STEEL && obj2->item_type != ITEM_ADAMANTITE
      && obj2->item_type != ITEM_MITHRIL)
  {
  send_to_char( "You are not using a valid slab. \n\r", ch);
  return;
  }

  if (obj3->item_type != ITEM_AIRSTONE && obj3->item_type != ITEM_FIRESTONE
      && obj3->item_type != ITEM_EARTHSTONE && obj3->item_type != ITEM_WATERSTONE)
  {
  send_to_char( "You are not using a valid RuneStone. \n\r", ch);
  return;
  } 


  if (str_prefix(arg3, "bracer") && str_prefix(arg3, "greaves")
      && str_prefix(arg3, "collar") && str_prefix(arg3, "plate")
      && str_prefix(arg3, "ring") && str_prefix(arg3, "helmet")
      && str_prefix(arg3, "boots") && str_prefix(arg3, "sleeves")
      && str_prefix(arg3, "gauntlets") && str_prefix(arg3, "cloak")
      && str_prefix(arg3, "belt") && str_prefix(arg3, "mask"))
  {
  send_to_char( "That is not the name of a valid piece of Armor. \n\r", ch);
  return;
  } 

        if ( rnum == 0 || ( pObjIndex = get_obj_index( rnum ) ) == NULL )
        {
        stc( "Missing object, please notify a member of the staff.\n\r", ch );
        return;
        }

    obj     = create_object(pObjIndex, 52);


  if (!str_prefix(arg1, "copper"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL )
    {
      send_to_char( "You require a copper forging slab.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_COPPER)
    {
      send_to_char("That thing isn't copper!\n\r",ch);
      return;
    }
    extract_obj( obj2 );

    hp      = 300;
    mana    = 300;
    move    = 300;
    add_affect( obj, APPLY_HIT, hp );
    add_affect( obj, APPLY_MANA, mana );
    add_affect( obj, APPLY_MOVE, move );
    obj->value[0] = 30;
    sprintf( slabname, "Copper" );
    sprintf( slabnamecolor, "#YC#yo#7pp#ye#Yr#n" );
  }
  if (!str_prefix(arg1, "iron"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL )
    {
      send_to_char( "You require an iron forging slab.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_IRON)
    {
      send_to_char("That thing isn't iron!\n\r",ch);
      return;
    }
    extract_obj( obj2 );

    hp      = 325;
    mana    = 325;
    move    = 325;
    add_affect( obj, APPLY_HIT, hp );
    add_affect( obj, APPLY_MANA, mana );
    add_affect( obj, APPLY_MOVE, move );
    obj->value[0] = 30;
    sprintf( slabname, "Iron" );
    sprintf( slabnamecolor, "#7I#0r#7o#0n#n" );

  }
  if (!str_prefix(arg1, "steel"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL )
    {
      send_to_char( "You require a steel forging slab.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_STEEL)
    {
      send_to_char("That thing isn't steel!\n\r",ch);
      return;
    }
    extract_obj( obj2 );

    hp      = 350;
    mana    = 350;
    move    = 350;
    add_affect( obj, APPLY_HIT, hp );
    add_affect( obj, APPLY_MANA, mana );
    add_affect( obj, APPLY_MOVE, move );
    obj->value[0] = 30;
    sprintf( slabname, "Steel" );
    sprintf( slabnamecolor, "#RSteel#n" );

  }

  if (!str_prefix(arg1, "adamantite"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL )
    {
      send_to_char( "You require an adamantite forging slab.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_ADAMANTITE)
    {
      send_to_char("That thing isn't adamantite!\n\r",ch);
      return;
    }
    extract_obj( obj2 );

    hp      = 450;
    mana    = 450;
    move    = 450;
    add_affect( obj, APPLY_HIT, hp );
    add_affect( obj, APPLY_MANA, mana );
    add_affect( obj, APPLY_MOVE, move );
    obj->value[0] = 30;
    sprintf( slabname, "Adamantite" );
    sprintf( slabnamecolor, "#gAd#Gam#gan#Gti#gte#n" );

  }

  if (!str_prefix(arg1, "mithril"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL )
    {
      send_to_char( "You require an mithril forging slab.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_MITHRIL)
    {
      send_to_char("That thing isn't mithril!\n\r",ch);
      return;
    }
    extract_obj( obj2 );

    hp      = 500;
    mana    = 500;
    move    = 500;
    add_affect( obj, APPLY_HIT, hp );
    add_affect( obj, APPLY_MANA, mana );
    add_affect( obj, APPLY_MOVE, move );
    obj->value[0] = 30;
    sprintf( slabname, "Mithril" );
    sprintf( slabnamecolor, "#7Mithril#n" );

  }





  if (!str_prefix(arg2, "fire"))
  {
    if ((obj3 = get_obj_carry( ch, (arg2),ch)) == NULL )
    {
      send_to_char( "You require a fire runestone.\n\r", ch);
      return;
    }
    if (obj3->item_type != ITEM_FIRESTONE)
    {
      send_to_char("Thats not a firestone\n\r",ch);
      return;
    }
    extract_obj( obj3 );

    hitroll = 100;
    damroll = 150;
    armor   = -100;
    add_affect( obj, APPLY_HITROLL, hitroll );
    add_affect( obj, APPLY_DAMROLL, damroll );
    add_affect( obj, APPLY_AC, armor );
    sprintf( runename, flame" );
    sprintf( runenamecolor, "#RF#Yl#ra#Rm#Ye#n" );

  }
  if (!str_prefix(arg2, "air"))
  {
    if ((obj3 = get_obj_carry( ch, (arg2),ch)) == NULL )
    {
      send_to_char( "You require a fire runestone.\n\r", ch);
      return;
    }
    if (obj3->item_type != ITEM_AIRSTONE)
    {
      send_to_char("Thats not an air rune\n\r",ch);
      return;
    }
    extract_obj( obj3 );

    hitroll = 140;
    damroll = 100;
    armor   = -325;
    add_affect( obj, APPLY_HITROLL, hitroll );
    add_affect( obj, APPLY_DAMROLL, damroll );
    add_affect( obj, APPLY_AC, armor );
    sprintf( runename, "Wind" );
    sprintf( runenamecolor, "#CW#ci#Cn#cd#n" );

  }
  if (!str_prefix(arg2, "earth"))
  {
    if ((obj3 = get_obj_carry( ch, (arg2),ch)) == NULL )
    {
      send_to_char( "You require an earth runestone.\n\r", ch);
      return;
    }
    if (obj3->item_type != ITEM_EARTHSTONE)
    {
      send_to_char("Thats not an earth rune\n\r",ch);
      return;
    }
    extract_obj( obj3 );

    hitroll = 125;
    damroll = 125;
    armor   = -100;
    add_affect( obj, APPLY_HITROLL, hitroll );
    add_affect( obj, APPLY_DAMROLL, damroll );
    add_affect( obj, APPLY_AC, armor );
    sprintf( runename, "Earth" );
    sprintf( runenamecolor, "#gE#oa#gr#ot#gh#n" );
  }
  if (!str_prefix(arg2, "water"))
  {
    if ((obj3 = get_obj_carry( ch, (arg2),ch)) == NULL )
    {
      send_to_char( "You require a water runestone.\n\r", ch);
      return;
    }
    if (obj3->item_type != ITEM_WATERSTONE)
    {
      send_to_char("Thats not a water rune\n\r",ch);
      return;
    }
    extract_obj( obj3 );

    hitroll = 120;
    damroll = 120;
    armor   = -200;
    add_affect( obj, APPLY_HITROLL, hitroll );
    add_affect( obj, APPLY_DAMROLL, damroll );
    add_affect( obj, APPLY_AC, armor );
    sprintf( runename, "Ice" );
    sprintf( runenamecolor, "#CI#7c#ce#n" );

  }

//    send_to_char( "item: bracer, greaves, collar, plate, ring, helmet \n\r", ch );


  if (!str_prefix(arg3, "bracer"))
  {
    wear = ITEM_WEAR_WRIST;
    sprintf( name, "Bracer" );
    SET_BIT( obj->wear_flags, wear );
  }
  if (!str_prefix(arg3, "greaves"))
  {
    wear = ITEM_WEAR_LEGS;
    sprintf( name, "Greaves" );
    SET_BIT( obj->wear_flags, wear );
  }
  if (!str_prefix(arg3, "collar"))
  {
    wear = ITEM_WEAR_NECK;
    sprintf( name, "Collar" );
    SET_BIT( obj->wear_flags, wear );
  }
  if (!str_prefix(arg3, "plate"))
  {
    wear = ITEM_WEAR_BODY;
    sprintf( name, "Plate" );
    SET_BIT( obj->wear_flags, wear );
  }
  if (!str_prefix(arg3, "ring"))
  {
    wear = ITEM_WEAR_FINGER;
    sprintf( name, "Ring" );
    SET_BIT( obj->wear_flags, wear );
  }
  if (!str_prefix(arg3, "helmet"))
  {
    wear = ITEM_WEAR_HEAD;
    sprintf( name, "Helmet" );
    SET_BIT( obj->wear_flags, wear );
  }

//    send_to_char( "      boots, sleeves, gauntlets, cloak, belt, mask \n\r", ch );

  if (!str_prefix(arg3, "boots"))
  {
    wear = ITEM_WEAR_FEET;
    sprintf( name, "Boots" );
    SET_BIT( obj->wear_flags, wear );
  }
  if (!str_prefix(arg3, "sleeves"))
  {
    wear = ITEM_WEAR_ARMS;
    sprintf( name, "Sleeves" );
    SET_BIT( obj->wear_flags, wear );
  }
  if (!str_prefix(arg3, "gauntlets"))
  {
    wear = ITEM_WEAR_HANDS;
    sprintf( name, "Gauntlets" );
    SET_BIT( obj->wear_flags, wear );
  }
  if (!str_prefix(arg3, "cloak"))
  {
    wear = ITEM_WEAR_ABOUT;
    sprintf( name, "Cloak" );
    SET_BIT( obj->wear_flags, wear );
  }
  if (!str_prefix(arg3, "belt"))
  {
    wear = ITEM_WEAR_WAIST;
    sprintf( name, "Belt" );
    SET_BIT( obj->wear_flags, wear );
  }
  if (!str_prefix(arg3, "mask"))
  {
    wear = ITEM_WEAR_FACE;
    sprintf( name, "Faceplate" );
    SET_BIT( obj->wear_flags, wear );
  }



    obj->item_type = ITEM_ARMOR;
    obj->questowner = str_dup( ch->name );

    sprintf( buf, "%s %s %s#n", slabnamecolor, runenamecolor, name );
    free_string( obj->short_descr );
    obj->short_descr = str_dup( buf );

    sprintf( buf, "%s %s %s#n lies on the ground.", slabnamecolor, runenamecolor, name );
    free_string( obj->description );
    obj->description = str_dup( buf );

    sprintf( buf, "%s %s %s ", slabname, runename, name );
    free_string( obj->name );
    obj->name = str_dup( buf );
    obj_to_char( obj, ch );


return;
}

/***************************************************************************
 *  Shadow Wars: the Revenge of Kalos                                      *
 ---------------------------------------------------------------------------
 *  You are allowd to change and modify this code, you may NOT take out    *
 *  the helpfile 'CREATORS', and you must leave in the Greeting,           *
 *  Shadow Wars: the Revenge of Kalos created by Xkilla and Sillviant      *
 *  (c)2001 Xkilla 'Ryan Waliany' (ryan@scv.net)                           *
 *  Sillviant 'Matt Burnett' (sillviant@charter.net)                       *
 ---------------------------------------------------------------------------
 *  Changes snippet by: Xkilla. This is a snippet, you may modify it, but  *
 *  you must leave in Xkilla's credit.                                     *
 ***************************************************************************/
/***************************************************************************
 *                                 _/                            _/        *
 *      _/_/_/  _/_/      _/_/_/  _/    _/_/    _/    _/    _/_/_/         *
 *     _/    _/    _/  _/        _/  _/    _/  _/    _/  _/    _/          *
 *    _/    _/    _/  _/        _/  _/    _/  _/    _/  _/    _/           *
 *   _/    _/    _/    _/_/_/  _/    _/_/      _/_/_/    _/_/_/            *
 ***************************************************************************
 * Mindcloud Copyright 2001-2003 by Jeff Boschee (Zarius),                 *
 * Additional credits are in the help file CODECREDITS                     *
 * All Rights Reserved.                                                    *
 ***************************************************************************/
typedef struct  changes_data             CHANGE_DATA;

void load_changes args( (void) );
void save_changes args( (void) );
void delete_change args( (int num) );
 
struct changes_data
{

    char *         change;
    char *         coder;
    char *         date;
    time_t         mudtime;
};

extern struct  changes_data * changes_table;

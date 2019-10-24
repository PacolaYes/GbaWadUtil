#ifndef DOOMTYPES_H
#define DOOMTYPES_H

#include <QtCore>


typedef qint32 fixed_t;

#define FRACBITS 16
#define FRACUNIT (1<<FRACBITS)

inline static int D_abs(fixed_t x)
{
  fixed_t _t = (x),_s;
  _s = _t >> (8*sizeof _t-1);
  return (_t^_s)-_s;
}

inline static fixed_t FixedDiv(fixed_t a, fixed_t b)
{
  return ((unsigned)D_abs(a)>>14) >= (unsigned)D_abs(b) ? ((a^b)>>31) ^ INT_MAX :
    (fixed_t)(((__int64) a << FRACBITS) / b);
}

//*************************************************************************************
//WAD file structs from Doom sources.
//*************************************************************************************

#pragma pack(push,1)

typedef struct
{
    char identification[4];                  // Should be "IWAD" or "PWAD".
    qint32  numlumps;
    qint32  infotableofs;
} wadinfo_t;

typedef struct
{
    qint32  filepos;
    qint32  size;
    char name[8];
} filelump_t;



//
// Map level types.
// The following data structures define the persistent format
// used in the lumps of the WAD files.
//

// Lump order in a map WAD: each map needs a couple of lumps
// to provide a complete scene geometry description.
enum {
  ML_LABEL,             // A separator, name, ExMx or MAPxx
  ML_THINGS,            // Monsters, items..
  ML_LINEDEFS,          // LineDefs, from editing
  ML_SIDEDEFS,          // SideDefs, from editing
  ML_VERTEXES,          // Vertices, edited and BSP splits generated
  ML_SEGS,              // LineSegs, from LineDefs split by BSP
  ML_SSECTORS,          // SubSectors, list of LineSegs
  ML_NODES,             // BSP nodes
  ML_SECTORS,           // Sectors, from editing
  ML_REJECT,            // LUT, sector-sector visibility
  ML_BLOCKMAP           // LUT, motion clipping, walls/grid element
};



//*************************************************************************************
//r_defs structs from Doom sources.
//*************************************************************************************

typedef struct
{
    fixed_t x, y;
} vertex_t;

// A single Vertex.
typedef struct
{
    short x,y;
} mapvertex_t;




typedef enum
{
  ST_HORIZONTAL,
  ST_VERTICAL,
  ST_POSITIVE,
  ST_NEGATIVE
} slopetype_t;

typedef enum
{                 // cph:
    RF_TOP_TILE  = 1,     // Upper texture needs tiling
    RF_MID_TILE = 2,     // Mid texture needs tiling
    RF_BOT_TILE = 4,     // Lower texture needs tiling
    RF_IGNORE   = 8,     // Renderer can skip this line
    RF_CLOSED   =16,     // Line blocks view
} r_flags;

typedef struct line_s
{
    vertex_t v1;
    vertex_t v2;            // Vertices, from v1 to v2.
    quint32 lineno;         //line number.
    fixed_t dx, dy;        // Precalculated v2 - v1 for side checking.

    quint16 sidenum[2];        // Visual appearance: SideDefs.

    quint16 flags;           // Animation related.
    qint16 special;
    qint16 tag;
    quint16 slopetype; // To aid move clipping.

} line_t;

typedef struct {
  unsigned short v1;
  unsigned short v2;
  unsigned short flags;
  short special;
  short tag;
  // proff 07/23/2006 - support more than 32768 sidedefs
  // use the unsigned value and special case the -1
  // sidenum[1] will be -1 (NO_INDEX) if one sided
  unsigned short sidenum[2];
} maplinedef_t;

#pragma pack(pop)

#endif // DOOMTYPES_H

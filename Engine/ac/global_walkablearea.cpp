
#include "ac/global_walkablearea.h"
#include "wgt2allg.h"
#include "ac/ac_common.h"
#include "ac/ac_defines.h"
#include "ac/draw.h"
#include "ac/roomstruct.h"
#include "ac/walkablearea.h"
#include "debug/debug.h"

extern roomstruct thisroom;
extern int offsetx, offsety;


int GetScalingAt (int x, int y) {
    int onarea = get_walkable_area_pixel(x, y);
    if (onarea < 0)
        return 100;

    return get_area_scaling (onarea, x, y);
}

void SetAreaScaling(int area, int min, int max) {
    if ((area < 0) || (area > MAX_WALK_AREAS))
        quit("!SetAreaScaling: invalid walkalbe area");

    if (min > max)
        quit("!SetAreaScaling: min > max");

    if ((min < 5) || (max < 5) || (min > 200) || (max > 200))
        quit("!SetAreaScaling: min and max must be in range 5-200");

    // the values are stored differently
    min -= 100;
    max -= 100;

    if (min == max) {
        thisroom.walk_area_zoom[area] = min;
        thisroom.walk_area_zoom2[area] = NOT_VECTOR_SCALED;
    }
    else {
        thisroom.walk_area_zoom[area] = min;
        thisroom.walk_area_zoom2[area] = max;
    }
}

void RemoveWalkableArea(int areanum) {
  if ((areanum<1) | (areanum>15))
    quit("!RemoveWalkableArea: invalid area number specified (1-15).");
  play.walkable_areas_on[areanum]=0;
  redo_walkable_areas();
  DEBUG_CONSOLE("Walkable area %d removed", areanum);
}

void RestoreWalkableArea(int areanum) {
  if ((areanum<1) | (areanum>15))
    quit("!RestoreWalkableArea: invalid area number specified (1-15).");
  play.walkable_areas_on[areanum]=1;
  redo_walkable_areas();
  DEBUG_CONSOLE("Walkable area %d restored", areanum);
}


int GetWalkableAreaAt(int xxx,int yyy) {
  xxx += divide_down_coordinate(offsetx);
  yyy += divide_down_coordinate(offsety);
  if ((xxx>=thisroom.width) | (xxx<0) | (yyy<0) | (yyy>=thisroom.height))
    return 0;
  int result = get_walkable_area_pixel(xxx, yyy);
  if (result <= 0)
    return 0;
  return result;
}

//=============================================================================

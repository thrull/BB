#include "task.h"

#include "gui/tasks/menu/settings.h"

#include "gui/gui_list.h"
#include "gui/tasks/menu/competition/competition.h"

#include "etc/format.h"

REGISTER_TASK_I(waypoints);

static lv_obj_t * waypoints_init(lv_obj_t * par)
{
	lv_obj_t * list = gui_list_create(par, "Waypoints", &gui_competition, NULL);

	return list;
}

#include "competition.h"

#include "gui/tasks/menu/settings.h"

#include "waypoints.h"
#include "task.h"

#include "gui/gui_list.h"
#include "etc/format.h"

REGISTER_TASK_I(competition_settings);

static lv_obj_t * vario_settings_init(lv_obj_t * par)
{
	lv_obj_t * list = gui_list_create(par, "Competition settings", &gui_settings, NULL);

	return list;
}


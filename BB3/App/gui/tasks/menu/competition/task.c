#include "task.h"

#include "gui/tasks/menu/settings.h"

#include "gui/gui_list.h"
#include "gui/tasks/menu/competition/competition.h"

#include "etc/format.h"

REGISTER_TASK_I(task);


static lv_obj_t * take_off_init(lv_obj_t * par)
{
	lv_obj_t * list = gui_list_create(par, "Task settings", &gui_competition, NULL);

	return list;
}

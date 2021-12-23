/*
 * widget_wind.c
 *
 *  Created on: 23. 12. 2021
 *      Author: thrull
 */


#include "gui/widgets/widget.h"

REGISTER_WIDGET_IU
(
	Wind,
    "Wind direction",
    WIDGET_MIN_W,
    WIDGET_MIN_H,
	_b(wf_label_hide),

    lv_obj_t * arrow;
	lv_obj_t * text;

    lv_point_t points[WIDGET_ARROW_POINTS];
);

static void Wind_init(lv_obj_t * base, widget_slot_t * slot)
{
    widget_create_base(base, slot);
    if (!widget_flag_is_set(slot, wf_label_hide))
    	widget_add_title(base, slot, "Wind direction");

    local->text = widget_add_value(base, slot, NULL, NULL);
    local->arrow = widget_add_arrow(base, slot, local->points, NULL, NULL);

}

static void Wind_update(widget_slot_t * slot)
{
	if (fc.wind.valid)
	{
		widget_arrow_rotate(local->arrow, local->points, fc.wind.direction);
		lv_obj_set_hidden(local->arrow, false);
		lv_obj_set_hidden(local->text, true);
	}
	else
	{
		lv_label_set_text(local->text, "---");
		widget_update_font_size(local->text);
		lv_obj_set_hidden(local->arrow, true);
		lv_obj_set_hidden(local->text, false);
	}
}

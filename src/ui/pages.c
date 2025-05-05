#include "pages.h"

#include "../ssd1306.h"
#include "font.h"
#include "utils.h"
#include <stdint.h>

void ui_page_draw_work_finished(ssd1306_t* display)
{
    uint8_t i;
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    graphic_t start_pause[] = { left_selector_8px, start_8px, pause_8px, right_selector_8px };

    /* Draw "WORK" */
    page.start = 0;
    page.end = 1;
    col.start = 0;
    col.end = col.start + ui_util_graphic_16px_pixel_width(work_16px) - 1;
    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_util_draw_graphic_16px_two_line(display, work_16px);

    /* Draw "FINISHED" */
    page.start = 0;
    page.end = 1;
    col.end = DISPLAY_WIDTH - 1;
    col.start = col.end - ui_util_graphic_16px_pixel_width(finished_16px) + 1;
    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_util_draw_graphic_16px_two_line(display, finished_16px);

    /* Draw "> START PAUSE <" */
    page.start = 2;
    page.end = 3;
    col.start = 19;
    for (i = 0; i < 4; i++) {
        col.end = col.start + ui_util_graphic_8px_pixel_width(start_pause[i]) - 1;
        ssd1306_set_column_and_page_address_boundary(display, col, page);
        ui_util_draw_graphic_8px_between_two_lines(display, start_pause[i]);
        col.start += ui_util_graphic_8px_pixel_width(start_pause[i]) + 5;
    }
}

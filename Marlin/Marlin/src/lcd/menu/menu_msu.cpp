/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../inc/MarlinConfig.h"

#if BOTH(HAS_LCD_MENU, MSU_MENU)

#include "../../feature/msu/msu.h"
#include "../../module/planner.h"
#include "menu_item.h"


void menu_msu_change_filament() {
  START_MENU();
  BACK_ITEM(MSG_MSU_MENU);
  LOOP_L_N(i, 5) ACTION_ITEM_N(i, MSG_MSU_FILAMENT_N, []{ msu.tool_change(MenuItemBase::itemIndex); });
  END_MENU();
}





void menu_msu_adjust_bowden_length(){
  START_MENU();
  BACK_ITEM(MSG_MSU_MENU);
  END_MENU();
}

void menu_msu_move_extruder()
{
  if (ui.use_click())
    ui.goto_screen(menu_msu_adjust_bowden_length);
  if (ui.encoderPosition)
  {
    if (!ui.manual_move.processing)
    {
      const float diff = float(int32_t(ui.encoderPosition)) * ui.manual_move.menu_scale;
      TERN(IS_KINEMATIC, ui.manual_move.offset, current_position.e) += diff;
      ui.manual_move.soon(E_AXIS);
      ui.refresh(LCDVIEW_REDRAW_NOW);
    }
    ui.encoderPosition = 0;
  }
  if (ui.should_draw())
  {
    MenuEditItemBase::draw_edit_screen(
        GET_TEXT(MSG_MOVE_E),
        ftostr41sign(current_position.e));
  }
  
}

void menu_msu() {
  START_MENU();
  BACK_ITEM(MSG_MAIN);
  ACTION_ITEM(MSG_MSU_IDLER_HOME, []{ msu.idler_home(); });
  SUBMENU(MSG_MSU_SELECT_FILAMENT, menu_msu_change_filament);
  END_MENU();
}

#endif // HAS_LCD_MENU && MSU_MENU

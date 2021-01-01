// Copyright (C) 2020 Brian Reading
// 
// This file is part of DragonTap.
// 
// DragonTap is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// DragonTap is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with DragonTap.  If not, see <http://www.gnu.org/licenses/>.

#ifndef DT_WINDOW_H
#define DT_WINDOW_H

#include "dt-application.h"

#include <gtk/gtk.h>

#define DT_WINDOW_TYPE dt_window_get_type ()
G_DECLARE_FINAL_TYPE (DtWindow, dt_window, DT, WINDOW, GtkApplicationWindow)

G_BEGIN_DECLS

DtWindow *dt_window_new (DtApplication *app);

G_END_DECLS

#endif /* DT_WINDOW_H */
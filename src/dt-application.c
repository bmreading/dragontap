/**
 * Copyright (C) 2020 Brian Reading
 * 
 * This file is part of DragonTap.
 * 
 * DragonTap is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DragonTap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DragonTap.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>

#include "dt-application.h"
#include "dt-window.h"

struct _DtApplication
{
    GtkApplication parent_instance;
};

G_DEFINE_TYPE (DtApplication, dt_application, GTK_TYPE_APPLICATION);

static void
dt_application_activate (GApplication *app)
{
    DtWindow *window;
    window = dt_window_new (DT_APPLICATION (app));
    gtk_window_present (GTK_WINDOW (window));
}

static void
dt_application_init (DtApplication *app)
{
}

static void
dt_application_class_init (DtApplicationClass *klass)
{
    G_APPLICATION_CLASS (klass)->activate = dt_application_activate;
}

DtApplication
*dt_application_new (void)
{
    return g_object_new (DT_APPLICATION_TYPE,
                         "application-id",
                         "com.github.bmreading.dragontap",
                         "flags",
                         G_APPLICATION_HANDLES_OPEN,
                         NULL);
}
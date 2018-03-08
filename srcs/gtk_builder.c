/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:23:33 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/08 14:23:48 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtk/gtk.h>
#include "rt.h"

GtkWidget *button;
GtkWidget *myLabel;
GtkImage	*image_rt;
GdkPixbuf	*pix_buf;

typedef struct
    {
      GtkBuilder *builder;
      gpointer user_data;
    } SGlobalData;

void on_button_clicked(GObject *object, gpointer user_data)
{
  if (object && user_data)
    gtk_label_set_text(GTK_LABEL(myLabel), "Working harder");
}

int gtk_start(int ac, char **av, t_env *e)
{
	SGlobalData data;
	GtkWidget *window;
	GError *error;

	error = NULL;
	gtk_init(&ac, &av);

	/* Construct a GtkBuilder instance and load our UI description */
	data.builder = gtk_builder_new();
	gtk_builder_add_from_file (data.builder, "test.glade", &error);

	window = GTK_WIDGET(gtk_builder_get_object(data.builder, "mainWindow"));
	button = GTK_WIDGET(gtk_builder_get_object (data.builder, "button"));
	myLabel = GTK_WIDGET(gtk_builder_get_object (data.builder, "myLabel"));
  image_rt = GTK_IMAGE(gtk_builder_get_object (data.builder, "RTimage"));
  pix_buf = (GdkPixbuf *)e->img.data;
  image_rt = GTK_IMAGE(gtk_image_set_from_pixbuf(pix_buf));

	/* Connect signal handlers to the constructed widgets. */
	gtk_builder_connect_signals(data.builder, &data);

	gtk_widget_show(window);
	gtk_main();
	return 0;
}

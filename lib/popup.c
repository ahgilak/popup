#include <gtk/gtk.h>
#include <string.h>

#include "resources.h"

static GMainLoop *loop;

static void destroy(GtkDialog *dialog)
{
    gtk_window_destroy(GTK_WINDOW(dialog));
    g_main_loop_quit(loop);
}

static GLogWriterOutput log_black_hole()
{
    return G_LOG_WRITER_HANDLED;
}

void init()
{
    gtk_init();
    loop = g_main_loop_new(NULL, FALSE);

    GResource *resources = popup_get_resource();
    g_resources_register(resources);

    //disable logger in release mode
#ifndef DEBUG
    g_log_set_writer_func(log_black_hole, NULL, NULL);
#endif

    // apply styles
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    gtk_style_context_add_provider_for_display(display,
                                               GTK_STYLE_PROVIDER(provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_resource(provider, "/theme.css");
}

void alert(gchar *message)
{
    GtkBuilder *builder = gtk_builder_new_from_resource("/alert.ui");
    GObject *alert_dialog = gtk_builder_get_object(builder, "alert_dialog");
    GObject *message_label = gtk_builder_get_object(builder, "message");

    gtk_label_set_text(GTK_LABEL(message_label), message);
    gtk_widget_show(GTK_WIDGET(alert_dialog));
    g_signal_connect(alert_dialog,
                     "response",
                     G_CALLBACK(destroy),
                     NULL);

    g_main_loop_run(loop);
    g_object_unref(builder);
}

static void confirm_callback(GtkDialog *dialog,
                             gint response_id,
                             gboolean *result)
{
    *result = (response_id == GTK_RESPONSE_OK);
    destroy(dialog);
}

gboolean confirm(gchar *message)
{
    gboolean result;

    GtkBuilder *builder = gtk_builder_new_from_resource("/confirm.ui");
    GObject *confirm_dialog = gtk_builder_get_object(builder, "confirm_dialog");
    GObject *message_label = gtk_builder_get_object(builder, "message");

    gtk_label_set_text(GTK_LABEL(message_label), message);
    gtk_widget_show(GTK_WIDGET(confirm_dialog));
    g_signal_connect(confirm_dialog,
                     "response",
                     G_CALLBACK(confirm_callback),
                     &result);

    g_main_loop_run(loop);
    g_object_unref(builder);
    return result;
}

typedef struct _PromptCallbackData PromptCallbackData;

struct _PromptCallbackData
{
    GtkEntryBuffer *buffer;
    gchar *result;
};

static void prompt_callback(GtkDialog *dialog,
                            gint response_id,
                            PromptCallbackData *data)
{
    if (response_id == GTK_RESPONSE_OK)
    {
        guint size = gtk_entry_buffer_get_length(data->buffer);
        data->result = g_malloc(size + 1);
        strcpy(data->result, gtk_entry_buffer_get_text(data->buffer));
    }

    destroy(dialog);
}

gchar *prompt(gchar *message, gchar *default_value)
{
    PromptCallbackData *cb_data = g_new0(PromptCallbackData, 1);
    GtkBuilder *builder = gtk_builder_new_from_resource("/prompt.ui");
    GObject *prompt_dialog = gtk_builder_get_object(builder, "prompt_dialog");
    GObject *message_label = gtk_builder_get_object(builder, "message");
    GObject *entry = gtk_builder_get_object(builder, "entry");

    cb_data->buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));

    gtk_entry_buffer_set_text(cb_data->buffer, default_value, -1);
    gtk_label_set_text(GTK_LABEL(message_label), message);
    gtk_widget_show(GTK_WIDGET(prompt_dialog));
    g_signal_connect(prompt_dialog,
                     "response",
                     G_CALLBACK(prompt_callback),
                     cb_data);

    g_main_loop_run(loop);
    g_object_unref(builder);
    return cb_data->result;
}
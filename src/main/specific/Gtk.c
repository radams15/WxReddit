#include <gtk/gtk.h>

#ifdef USE_HANDY
#include <handy.h>
#endif

#ifdef USE_GRANITE
#include <granite/granite.h>

GraniteSettings* granite_settings;
#endif

GtkSettings* settings;

GtkWidget* find_toolbar(GtkWidget* parent){
    if (GTK_IS_TOOLBAR(parent)) {
        return parent;
    }

    if (GTK_IS_BIN(parent)) {
        GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));

        return find_toolbar(child);
    }

    if (GTK_IS_CONTAINER(parent)) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
        do{
            GtkWidget* widget = find_toolbar(children->data);
            if (widget != NULL) {
                return widget;
            }
        }while ((children = g_list_next(children)) != NULL);
    }

    return NULL;
}

GtkWidget* find_menubar(GtkWidget* parent){
    if (GTK_IS_MENU_BAR(parent)) {
        return parent;
    }

    if (GTK_IS_BIN(parent)) {
        GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));

        return find_menubar(child);
    }

    if (GTK_IS_CONTAINER(parent)) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
        do{
            GtkWidget* widget = find_menubar(children->data);
            if (widget != NULL) {
                return widget;
            }
        }while ((children = g_list_next(children)) != NULL);
    }

    return NULL;
}

void remove_from_parent(GtkWidget* widget){
    GtkWidget* parent = gtk_widget_get_parent(widget);

    if(GTK_IS_CONTAINER(parent)){
        gtk_container_remove(GTK_CONTAINER(parent), widget);
    }
}

GtkWidget* toolbar_to_headerbar(GtkToolbar* toolbar){
    remove_from_parent(GTK_WIDGET(toolbar));

#ifdef USE_HANDY
    HdyHeaderBar* header = hdy_header_bar_new();
#else
    GtkHeaderBar* header = gtk_header_bar_new();
#endif

    GList *children = gtk_container_get_children(GTK_CONTAINER(toolbar));
    do{
        GtkWidget* child = g_object_ref(children->data);

        remove_from_parent(child);

#ifdef USE_HANDY
        hdy_header_bar_pack_start(header, child);
#else
        gtk_header_bar_pack_start(header, child);
#endif
    }while ((children = g_list_next(children)) != NULL);

#ifdef USE_HANDY
    hdy_header_bar_set_show_close_button(header, TRUE);
    hdy_header_bar_set_title(header, "WxReddit");
#else
    gtk_header_bar_set_show_close_button(header, TRUE);
    gtk_header_bar_set_title(header, "WxReddit");
#endif

    gtk_widget_set_visible(header, TRUE);

    return GTK_WIDGET(header);
}

static gint
my_popup_handler (GtkWidget *widget, GdkEvent *event)
{
    GtkMenu *menu;
    GdkEventButton *event_button;

    g_return_val_if_fail (widget != NULL, FALSE);
    g_return_val_if_fail (GTK_IS_MENU (widget), FALSE);
    g_return_val_if_fail (event != NULL, FALSE);

    // The "widget" is the menu that was supplied when
    // g_signal_connect_swapped() was called.
    menu = GTK_MENU (widget);

    if (event->type == GDK_BUTTON_PRESS)
    {
        event_button = (GdkEventButton *) event;
        if (event_button->button == GDK_BUTTON_SECONDARY)
        {
            gtk_menu_popup (menu, NULL, NULL, NULL, NULL,
                            event_button->button, event_button->time);
            return TRUE;
        }
    }

    return FALSE;
}

GtkWidget* menubar_to_hamburger(GtkWindow* win, GtkWidget* menubar){
    if(!GTK_IS_MENU_BAR(menubar)){ return NULL; }

    GtkWidget* hamburger = gtk_menu_new();
    remove_from_parent(hamburger);

    g_signal_connect_swapped(win, "button_press_event", G_CALLBACK(my_popup_handler), hamburger);

    GList *children = gtk_container_get_children(GTK_CONTAINER(menubar));
    do{
        if(GTK_IS_MENU_ITEM(children)){
            GtkMenuItem* item = (GtkMenuItem*) children;

            gtk_menu_shell_append(GTK_MENU_SHELL(hamburger), GTK_WIDGET(item));
        }
    }while ((children = g_list_next(children)) != NULL);


    gtk_widget_set_visible(hamburger, TRUE);
    return hamburger;
}

void on_color_scheme_change(){
#ifdef USE_GRANITE
    g_object_set(settings, "gtk-application-prefer-dark-theme", granite_settings_get_prefers_color_scheme(granite_settings) == GRANITE_SETTINGS_COLOR_SCHEME_DARK, NULL);
#endif
}

void tweak(void* window){
    GtkWidget* win = (GtkWidget*) window;

    GtkApplication* app = gtk_window_get_application(win);
    
    GtkToolbar* toolbar = GTK_TOOLBAR(g_object_ref(find_toolbar(win)));
    
#ifdef USE_GRANITE
    GraniteModeSwitch* mode_switch = granite_mode_switch_new_from_icon_name("display-brightness-symbolic", "weather-clear-night-symbolic");
    granite_mode_switch_set_primary_icon_tooltip_text(mode_switch, "Light Background");
    granite_mode_switch_set_secondary_icon_tooltip_text(mode_switch, "Dark Background");
    gtk_widget_set_valign(GTK_WIDGET(mode_switch), GTK_ALIGN_CENTER);
    g_object_bind_property(mode_switch, "active", settings, "gtk-application-prefer-dark-theme", G_BINDING_BIDIRECTIONAL);

    GtkToolItem* tool = gtk_tool_item_new();
    gtk_container_add(GTK_CONTAINER(tool), GTK_WIDGET(mode_switch));
    gtk_toolbar_insert(toolbar, tool, -1);
    gtk_widget_show_all(toolbar);

    g_signal_connect(granite_settings, "notify::prefers-color-scheme", G_CALLBACK(on_color_scheme_change), NULL);
    on_color_scheme_change();
#endif

#ifdef USE_HEADERBAR
    //gtk_window_set_decorated(GTK_WINDOW(win), 0);
    GtkWidget * header = toolbar_to_headerbar(toolbar);
    
#ifdef USE_GRANITE
    GtkStyleContext* style = gtk_widget_get_style_context(header);
    gtk_style_context_add_class(style, "default-decoration");
#endif

    gtk_widget_show_all(header);

    gtk_window_set_titlebar(GTK_WINDOW(win), header);

#ifdef USE_HAMBURGER
    GtkWidget* menubar = g_object_ref(find_menubar(win));

    GtkWidget* hamburger = menubar_to_hamburger(win, menubar);

#ifdef USE_HANDY
    hdy_header_bar_pack_end(HDY_HEADER_BAR(header), hamburger);
#else
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), hamburger);
#endif

#endif

#endif
}

void gtk_tweak_setup(){
    settings = gtk_settings_get_default();

#ifdef USE_HANDY
    hdy_init();
#endif
#ifdef USE_GRANITE
    granite_settings = granite_settings_get_default();
    
    on_color_scheme_change();
#endif
}

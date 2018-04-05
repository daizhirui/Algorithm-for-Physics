#include <gtk/gtk.h>

void
on_open_console_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_close_console_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);
                                        
void
on_quit_console_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_preferences_console_activate        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about_console_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_clist_console_sequencefile_select_row
                                        (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button_console_drawingpanel_histogram_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_console_drawingpanel_portrait_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_drawingarea_console_colormode_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_radiobutton_console_randomization_none_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_console_randomization_applicated_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_console_readingmethod_original_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_console_readingmethod_reverse_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_console_readingmethod_originalandreverse_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_spinbutton_console_ktuples_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_button_console_advancedsettings_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_portrait_destroy
										(GtkObject 		*window,
										gpointer 		portrait);

gboolean
on_drawingarea_portrait_drawing_motion_notify_event
                                        (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea_portrait_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea_portrait_expose_event   (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea_portrait_colormode_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_button_portrait_compare_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_portrait_export_clicked      (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_drawingarea_histogram_expose_event  (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea_histogram_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_button_histogram_export_clicked     (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_drawingarea_compresult_drawing_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea_compresult_colormode_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_button_compresult_export_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_entry_advancedsettings_random_times_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_drawingarea_advancedsettings_colormode_high_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea_advancedsettings_colormode_auto_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_radiobutton_advancedsettings_colormode_highcontrast_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_advancedsettings_colormode_autobalanced_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_advancedsettings_cmp_reduction_yes_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_advancedsettings_cmp_reduction_no_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_combo_entry_advancedsettings_cmp_DAN_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_button_advancedsettings_OK_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_advancedsettings_CANCEL_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_advancedsettings_APPLY_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_comparation_OK_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_comparation_Cancel_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_clist_comparation_destination_select_row
                                        (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button_about_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton_error_clicked              (GtkButton       *button,
                                        gpointer         user_data);
                                        
gboolean
on_drawingarea_compresult_drawing_motion_notify_event
                                        (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data);

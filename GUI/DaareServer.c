#include <gtk/gtk.h>
#include <math.h>
// Callback function for button click 
// Path: /c/Users/ruben/OneDrive/Desktop
// build: gcc -o DaareGUI DaareGUI.c `pkg-config --cflags --libs gtk+-3.0`
// Run: ./DaareGUI.exe


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
// Structure to represent a circle
typedef struct {
    int x, y, radius;
    const char *name;
    double r, g, b; // Custom color components (RGB)
} Circle;

// Array to hold circles
Circle circles[8]; // 1 center circle + 7 surrounding circles
// Array of circles
// Circle circles[] = {
//     {200, 150, 50, "Circle 1"},
//     {400, 100, 70, "Circle 2"},
//     {600, 300, 90, "Circle 3"},
//     {800, 400, 60, "Circle 4"},
//     {1000, 200, 80, "Circle 5"},
//     {300, 500, 100, "Circle 6"},
//     {700, 600, 40, "Circle 7"}
// };
// Total number of circles
#define NUM_CIRCLES (sizeof(circles) / sizeof(circles[0]))

// Function to calculate surrounding circle positions
void setup_circles() {
    // Center circle
    circles[0].x = WINDOW_WIDTH / 2;
    circles[0].y = WINDOW_HEIGHT / 2;
    circles[0].radius = 100;
    circles[0].name = "Profile";  // Custom name for center circle
    circles[0].r = 0.2; circles[0].g = 0.6; circles[0].b = 1.0;  // Custom color (light blue)

    // Surrounding circles with fixed positions and custom colors
    circles[1].x = 200;
    circles[1].y = 100;
    circles[1].radius = 50;
    circles[1].name = "Camera";  // Custom name
    circles[1].r = 1.0; circles[1].g = 0.0; circles[1].b = 0.0;  // Red

    circles[2].x = 400;
    circles[2].y = 200;
    circles[2].radius = 55;
    circles[2].name = "Settings";  // Custom name
    circles[2].r = 0.0; circles[2].g = 1.0; circles[2].b = 0.0;  // Green

    circles[3].x = 600;
    circles[3].y = 550;
    circles[3].radius = 60;
    circles[3].name = "Recent Program";  // Custom name
    circles[3].r = 0.0; circles[3].g = 0.0; circles[3].b = 1.0;  // Blue

    circles[4].x = 800;
    circles[4].y = 600;
    circles[4].radius = 65;
    circles[4].name = "Storage";  // Custom name
    circles[4].r = 1.0; circles[4].g = 1.0; circles[4].b = 0.0;  // Yellow

    circles[5].x = 1000;
    circles[5].y = 150;
    circles[5].radius = 70;
    circles[5].name = "Programs";  // Custom name
    circles[5].r = 1.0; circles[5].g = 0.5; circles[5].b = 0.0;  // Orange

    circles[6].x = 300;
    circles[6].y = 500;
    circles[6].radius = 75;
    circles[6].name = "Assets";  // Custom name
    circles[6].r = 0.5; circles[6].g = 0.0; circles[6].b = 0.5;  // Purple

    circles[7].x = 900;
    circles[7].y = 300;
    circles[7].radius = 80;
    circles[7].name = "People";  // Custom name
    circles[7].r = 0.0; circles[7].g = 1.0; circles[7].b = 1.0;  // Cyan
}

// Function to check if a point is inside a circle
static gboolean point_in_circle(int x, int y, Circle *circle) {
    int dx = x - circle->x;
    int dy = y - circle->y;
    return (dx * dx + dy * dy) <= (circle->radius * circle->radius);
}

// Draw callback function
static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // Set background color
    cairo_set_source_rgb(cr, 1, 1, 1); // White
    cairo_paint(cr);

    // Draw the circles and add text in the center
    for (int i = 0; i < NUM_CIRCLES; i++) {
        Circle *circle = &circles[i];
        
        // Set the custom color for each circle
        cairo_set_source_rgb(cr, circle->r, circle->g, circle->b);
        
        // Draw the circle
        cairo_arc(cr, circle->x, circle->y, circle->radius, 0, 2 * G_PI);
        cairo_fill(cr);

        // Draw the text in the center of the circle
        cairo_set_source_rgb(cr, 1, 1, 1); // Text color (white)
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 14);

        // Get text dimensions to center the text
        cairo_text_extents_t extents;
        cairo_text_extents(cr, circle->name, &extents);
        double text_x = circle->x - extents.width / 2 - extents.x_bearing;
        double text_y = circle->y - extents.height / 2 - extents.y_bearing;

        cairo_move_to(cr, text_x, text_y);
        cairo_show_text(cr, circle->name);
    }

    return FALSE;
}

// Mouse click callback
static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    for (int i = 0; i < NUM_CIRCLES; i++) {
        if (point_in_circle(event->x, event->y, &circles[i])) {
            g_print("You clicked %s\n", circles[i].name);
            return TRUE; // Stop after the first match
        }
    }
    return FALSE; // No circle was clicked
}

int main(int argc, char *argv[]) {
    GtkWidget *window;   // Main window
    GtkWidget *drawing_area;  // Button widget

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Set up the circle positions
    setup_circles();

    // Create a new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Light Device");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);

    // Connect the "destroy" event to gtk_main_quit to exit the app
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a drawing area
    drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Connect signals
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), NULL);
    g_signal_connect(drawing_area, "button-press-event", G_CALLBACK(on_button_press), NULL);

    // Enable event handling for mouse clicks
    gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK);

    // Show all widgets
    gtk_widget_show_all(window);

    // Main event loop
    gtk_main();

    return 0;
}

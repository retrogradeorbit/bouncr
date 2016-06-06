#define SMOOTHING_WINDOW_SIZE 15

void window_clear();
void window_move_down();
float window_sum();
float window_average();
void window_set_end(float data);

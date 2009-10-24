
typedef int FanControllerCb (const int *thermals, int thermals_size);

void controller_register_callback (FanControllerCb* cb);

void controller_loop (int delay /* in seconds! */);

#include "../include/background.h"

static char input_buffer[MAX_BUFFER_SIZE];


void
init_parallax_background(char *directory, size_t count, float normal_scroll_speed, 
                         float scroll_speeds[], bool infinite_scroll) {
  parallax_background_t *layer;
  char number_buffer[3];
  char *file_extsn = ".png";

  for (int i = 0; i < count; i++) {
    layer = malloc(sizeof(parallax_background_t));

    if (layer == NULL) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for parallax_background_t. %s.\n", SDL_GetError());
      exit(EXIT_FAILURE);      
    }

    memset(layer, 0, sizeof(parallax_background_t));

    itoa(i, number_buffer, 10);
    strcpy(input_buffer, directory);
    char *file_name               = strcat(input_buffer, number_buffer);
    char *file_name_ext           = strcat(input_buffer, file_extsn);
    layer->background             = init_background(file_name_ext);
    layer->parallax_scroll_speed  = scroll_speeds[i];
    layer->normal_scroll_speed    = normal_scroll_speed;
    layer->infinite_scroll        = infinite_scroll;

    // Display a warning message if the parallax background won't scroll
    // due to the settings the user chose.
    if ((int32_t) round((layer->normal_scroll_speed * layer->parallax_scroll_speed)) == 0) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "WARNING! Layer %d in your parallax effect will not scroll because it has 0 as a speed after normalizing it!", i);
    }  

    memset(input_buffer, '\0', sizeof(input_buffer));
    app.parallax_tail->next = layer;
    app.parallax_tail = layer;
  }
}


void 
parallax_background_update(parallax_background_t *p) {
  if (!p->infinite_scroll) {
    p->background->x = (int32_t) ((0 - app.camera.x) * (p->normal_scroll_speed * p->parallax_scroll_speed));
  } else {
    p->background->x -= (int32_t) (p->normal_scroll_speed * p->parallax_scroll_speed);
    if (p->background->x < -p->background->w) {
      p->background->x = 0;
    }
  }
}


void 
parallax_background_draw(parallax_background_t *p) {
  blit_texture_scaled(p->background->background_texture, p->background->x, p->background->y, 
                      p->background->scale_x, p->background->scale_y, 0);
  blit_texture_scaled(p->background->background_texture, p->background->x + p->background->w, 
                      p->background->y, p->background->scale_x, p->background->scale_y, 0);
}


background_t* 
init_background(char *file) {
  background_t *background;
  
  background = malloc(sizeof(background_t));

  if (background == NULL) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for background_t. %s.\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  memset(background, 0, sizeof(background_t));

  background->x = 0;
  background->y = 0;

  uint32_t w;
  uint32_t h;

  background->background_texture = load_texture(file);
  SDL_QueryTexture(background->background_texture, NULL, NULL, &w, &h);

  background->w = w;
  background->h = h;
  background->scale_x = 1.0;
  background->scale_y = 1.0;

  return background;
}


void 
background_update(background_t *background) {
  background->x = 0 - app.camera.x; 
  background->y = 0 - app.camera.y;

}


void 
background_draw(background_t *background) {
  blit_texture_scaled(background->background_texture, background->x, 
                      background->y, background->scale_x, background->scale_y, 0);
}


void 
background_die(background_t *background) {
  SDL_DestroyTexture(background->background_texture);
  free(background);
}

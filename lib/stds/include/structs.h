#ifndef STRUCTS_H
#define STRUCTS_H

#include "stds.h"

typedef struct Delegate           delegate_t;
typedef struct Entity             entity_t;
typedef struct Mouse              mouse_t;
typedef struct App                app_t;
typedef struct Animation          animation_t;
typedef struct Texture            texture_t;
typedef struct FadeColor          fade_color_t;
typedef struct Background         background_t;
typedef struct ParallaxBackground parallax_background_t;
typedef struct Font               font_t;
typedef struct Trail              trail_t;


/*
 *
 */
struct ParallaxBackground {
  float                 parallax_scroll_speed;
  float                 normal_scroll_speed;
  bool                  infinite_scroll; 

  background_t          *background;
  parallax_background_t *next;
};

/*
 *
 */
struct Trail {
  float         x;
  float         y;
  int16_t       alpha;
  int16_t       alpha_decay_rate;
  uint32_t      flags;

  SDL_Texture*  texture;

  trail_t*      next;
};

/*
 *
 */
struct Animation {
  uint16_t    x;
  uint16_t    y;
  uint32_t    w;
  uint32_t    h;
  uint16_t    start_x;
  uint16_t    start_y;
  uint32_t    sprite_sheet_width;
  uint32_t    sprite_sheet_height;
  bool        cycle_once;

  uint32_t    id_flags;
  uint32_t    flags;
  uint8_t     current_frame_id;
  size_t      number_of_frames;
  float       frame_delay;
  float       frame_timer;

  SDL_Texture *current_texture;
  SDL_Texture *default_texture;
  SDL_Texture **frames;
  SDL_Texture *sprite_sheet;

  animation_t *next;
};

/*
 *
 */
struct Background {
  int32_t     x;
  int32_t     y;
  uint32_t    w;
  uint32_t    h;

  float       scale_x;
  float       scale_y;

  SDL_Texture *background_texture;
};

/*
 *
 */
struct Texture {
  char          name[MAX_FILE_NAME_LEN];

  SDL_Texture*  texture;

  texture_t*    next;
};

/*
 *
 */
struct Font {
  char      name[MAX_FILE_NAME_LEN];
  uint16_t  size;

  TTF_Font* font;
  font_t*   next;
};

/*
 *
 */
struct Delegate {
  void (*tick)(void);
  void (*draw)(void);
};

/*
 *
 */
struct Mouse {
  int32_t x;
  int32_t y;
  uint8_t button[MAX_MOUSE_BUTTONS];
  uint8_t wheel;
};

/*
 *
 */
struct App{
  uint16_t              keyboard[MAX_KEYBOARD_KEYS];
  const char            *original_title;

  SDL_Renderer          *renderer;
  SDL_Window            *window;
  SDL_Rect              screen_bounds;
  SDL_Rect              camera;

  mouse_t               mouse;
  delegate_t            delegate;
  trail_t               trail_head, *trail_tail;
  texture_t             texture_head, *texture_tail;
  font_t                font_head, *font_tail;
  parallax_background_t parallax_head, *parallax_tail;

  enum GameState        game_state;
};

/*
 *
 */
struct FadeColor {
  bool      is_first_color;
  float     alpha;
  float     time;

  SDL_Color c1;
  SDL_Color c2;
};

/*
 *
 */
struct Entity {
  float         x;
  float         y;

  //  Miscellaneous positioning variable.
  float         variability;

  // Scales the entity in either the x or y
  // direction. This should default to 1.
  float         scale_x;
  float         scale_y;

  //  Directional velocity (yes, I know it's redundant).
  float         dx;
  float         dy;

  //  Acceleration or deceleration factors.
  float         delta_accel_x;
  float         delta_accel_y;

  // Change rate of alpha value.
  float         delta_alpha;

  // Size of entity if not defined by a rectangle. These
  // should either be set manually, or defined by a call
  // to SDL_QueryTexture(...), where you pass the addresses
  // of these variables.
  uint32_t      w;
  uint32_t      h;
  uint32_t      flags;
  uint32_t      id_flags;
  uint32_t      reload;
  uint32_t      identifier;
  
  uint16_t      angle;
  uint16_t      radius;

  // Can be used interchangably for different purposes.
  int32_t       health;
  int32_t       life;

  SDL_Color     color;
  SDL_Texture*  texture[TEXTURE_BUFFER_SIZE];
  
  animation_t   *animation;
  entity_t      *next; 

  void (*tick)(entity_t*);
  void (*draw)(entity_t*);
  void (*touch)(entity_t*);
  void (*die)(entity_t*);
};

#endif

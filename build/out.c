#include "stdarg.h"
#include "string.h"
#include "ctype.h"
#include "math.h"
#include "dirent.h"
#include "unistd.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "time.h"
#include "errno.h"
#include "zlib.h"
#include "SDL2/SDL.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "unistd.h"

/* Embed: /home/mindful-dev/ocen/std/./prelude.h */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

const char* __asan_default_options() { return "detect_leaks=0"; }

//// Backtraces

volatile static const char *__oc_bt[] = {0};
volatile u64 __oc_bt_idx = 0;

#define _WITH_BT(s, ...)      \
  __oc_bt[__oc_bt_idx++] = s; \
  __VA_ARGS__;                \
  (void)__oc_bt_idx--;

void dump_backtrace() {
  if (__oc_bt_idx == 0) {
    return;
  }
  fprintf(stderr, "--------------------------------------------------------------------------------\n");
  fprintf(stderr, "Backtrace:\n");
  for (u64 i = 0; i < __oc_bt_idx; i++) {
    fprintf(stderr, "  => %s\n", __oc_bt[i]);
  }

  fprintf(stderr, "--------------------------------------------------------------------------------\n");
}

/// End backtraces

#ifdef __APPLE__
  #define oc_trap __builtin_debugtrap
#else
  #define oc_trap __builtin_trap
#endif

void ae_assert_fail(char *dbg_msg, char *msg) {
  dump_backtrace();
  fprintf(stderr, "--------------------------------------------------------------------------------\n");
  fprintf(stderr, "%s\n", dbg_msg);
  if (msg) {
    fprintf(stderr, "  Message: %s\n", msg);
  }
  fprintf(stderr, "--------------------------------------------------------------------------------\n");
  fflush(stdout);
  oc_trap();
}


/* Constants */
#define std_math_TAU ((M_PI * 2.000000f))
#define std_video_renderer_ffmpeg_READ_END (0)
#define std_video_renderer_ffmpeg_WRITE_END (1)
#define src_core_scene_num_bounces (40)
/* Typedefs */
typedef enum std_Endian std_Endian;
typedef struct std_sv_SV std_sv_SV;
typedef struct std_sv_SVLineIterator std_sv_SVLineIterator;
typedef struct std_gc_impl_Header std_gc_impl_Header;
typedef struct std_image_Color std_image_Color;
typedef struct std_image_Image std_image_Image;
typedef struct std_image_qoi_RGBA std_image_qoi_RGBA;
typedef struct std_buffer_BytesReader std_buffer_BytesReader;
typedef struct std_image_qoi_QOIDecoder std_image_qoi_QOIDecoder;
typedef struct std_buffer_Buffer std_buffer_Buffer;
typedef struct std_image_png_Chunk std_image_png_Chunk;
typedef struct std_image_png_PNG std_image_png_PNG;
typedef struct std_vec_Vec2__1 std_vec_Vec2__1;
typedef struct std_vec_Vec2__5 std_vec_Vec2__5;
typedef struct std_vec_Vec3__0 std_vec_Vec3__0;
typedef union std_video_renderer_VideoRendererUnion std_video_renderer_VideoRendererUnion;
typedef enum std_video_renderer_VideoRendererType std_video_renderer_VideoRendererType;
typedef struct std_video_renderer_VideoRenderer std_video_renderer_VideoRenderer;
typedef struct std_video_renderer_ffmpeg_FFMPEGContext std_video_renderer_ffmpeg_FFMPEGContext;
typedef struct std_video_renderer_sdl_SDLContext std_video_renderer_sdl_SDLContext;
typedef struct std_vector_Vector__0 std_vector_Vector__0;
typedef struct std_vector_Vector__1 std_vector_Vector__1;
typedef struct std_vector_Vector__2 std_vector_Vector__2;
typedef struct std_vector_Vector__3 std_vector_Vector__3;
typedef struct std_vector_Vector__4 std_vector_Vector__4;
typedef struct std_vector_Iterator__1 std_vector_Iterator__1;
typedef struct std_random_RandomState std_random_RandomState;
typedef struct src_core_matrix_Matrix src_core_matrix_Matrix;
typedef struct src_objects_transformed_Transformed src_objects_transformed_Transformed;
typedef struct src_objects_triangle_Triangle src_objects_triangle_Triangle;
typedef struct src_objects_sphere_Sphere src_objects_sphere_Sphere;
typedef struct src_objects_mesh_Mesh src_objects_mesh_Mesh;
typedef enum src_core_texture_Texture__kind src_core_texture_Texture__kind;
typedef struct src_core_texture_Texture src_core_texture_Texture;
typedef enum src_core_materialtype_MaterialType src_core_materialtype_MaterialType;
typedef enum src_core_object_Object__kind src_core_object_Object__kind;
typedef struct src_core_object_Object src_core_object_Object;
typedef struct src_core_hitrec_HitRec src_core_hitrec_HitRec;
typedef struct src_core_bounds_Bounds src_core_bounds_Bounds;
typedef struct src_core_bvh_BVH__0 src_core_bvh_BVH__0;
typedef struct src_core_scene_Scene src_core_scene_Scene;
typedef struct src_core_camera_Camera src_core_camera_Camera;
typedef struct src_core_ray_Ray src_core_ray_Ray;
typedef struct _ClosureTy_10 _ClosureTy_10;
typedef struct src_core_bvh_create__Closure_3Ctx src_core_bvh_create__Closure_3Ctx;

/* Structs */
enum std_Endian {
  std_Endian_Little,
  std_Endian_Big,
};

char *std_Endian_dbg(std_Endian this) {
  switch (this) {
    case std_Endian_Little: return "Little";
    case std_Endian_Big: return "Big";
    default: return "<unknown>";
  }
}

struct std_sv_SV {
  char *data;
  u32 len;
};

struct std_sv_SVLineIterator {
  std_sv_SV sv;
};

struct std_gc_impl_Header {
  u32 size;
  bool marked;
  bool global;
  std_gc_impl_Header *next;
  std_gc_impl_Header *prev;
};

struct std_image_Color {
  u8 r;
  u8 g;
  u8 b;
};

struct std_image_Image {
  u32 width;
  u32 height;
  std_image_Color *data;
};

struct std_image_qoi_RGBA {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
};

struct std_buffer_BytesReader {
  u8 *data;
  u32 size;
  u32 index;
};

struct std_image_qoi_QOIDecoder {
  std_buffer_BytesReader io;
  u32 width;
  u32 height;
  u8 channels;
  u8 colorspace;
  u32 pixels_done;
  std_image_qoi_RGBA prev;
  std_image_qoi_RGBA seen[64];
  std_image_Image *img;
};

struct std_buffer_Buffer {
  u8 *data;
  u32 size;
  u32 capacity;
};

struct std_image_png_Chunk {
  std_sv_SV type;
  std_buffer_Buffer data;
  bool is_critical;
  bool is_private;
};

char *std_image_png_ColorType_dbg(int this) {
  switch (this) {
    case 0: return "Grayscale";
    case 2: return "RGB";
    case 3: return "Palette";
    case 4: return "GrayscaleAlpha";
    case 6: return "RGBA";
    default: return "<unknown>";
  }
}

char *std_image_png_InterlaceMethod_dbg(int this) {
  switch (this) {
    case 0: return "None";
    case 1: return "Adam7";
    default: return "<unknown>";
  }
}

struct std_image_png_PNG {
  u32 width;
  u32 height;
  u8 bit_depth;
  int color_type;
  int interlace_method;
  u32 S;
};

char *std_fs_SeekMode_dbg(i32 this) {
  switch (this) {
    case SEEK_SET: return "Set";
    case SEEK_CUR: return "Cur";
    case SEEK_END: return "End";
    default: return "<unknown>";
  }
}

struct std_vec_Vec2__1 {
  f32 x;
  f32 y;
};

struct std_vec_Vec2__5 {
  u32 x;
  u32 y;
};

struct std_vec_Vec3__0 {
  f32 x;
  f32 y;
  f32 z;
};

union std_video_renderer_VideoRendererUnion {
  std_video_renderer_ffmpeg_FFMPEGContext *ffmpeg;
  std_video_renderer_sdl_SDLContext *sdl;
};

enum std_video_renderer_VideoRendererType {
  std_video_renderer_VideoRendererType_FFMPEG,
  std_video_renderer_VideoRendererType_SDL,
};

char *std_video_renderer_VideoRendererType_dbg(std_video_renderer_VideoRendererType this) {
  switch (this) {
    case std_video_renderer_VideoRendererType_FFMPEG: return "FFMPEG";
    case std_video_renderer_VideoRendererType_SDL: return "SDL";
    default: return "<unknown>";
  }
}

struct std_video_renderer_VideoRenderer {
  std_video_renderer_VideoRendererType type;
  std_video_renderer_VideoRendererUnion u;
};

struct std_video_renderer_ffmpeg_FFMPEGContext {
  i32 pipe;
  i32 pid;
  u32 width;
  u32 height;
};

struct std_video_renderer_sdl_SDLContext {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *buffer;
  u32 orig_width;
  u32 orig_height;
  u32 frame_time;
  i32 last_frame;
  bool paused;
};

struct std_vector_Vector__0 {
  src_objects_triangle_Triangle *data;
  u32 size;
  u32 capacity;
};

struct std_vector_Vector__1 {
  src_core_object_Object **data;
  u32 size;
  u32 capacity;
};

struct std_vector_Vector__2 {
  char **data;
  u32 size;
  u32 capacity;
};

struct std_vector_Vector__3 {
  std_vec_Vec3__0 *data;
  u32 size;
  u32 capacity;
};

struct std_vector_Vector__4 {
  std_vec_Vec2__1 *data;
  u32 size;
  u32 capacity;
};

struct std_vector_Iterator__1 {
  std_vector_Vector__1 *vec;
  u32 index;
};

char *std_sdl_Key_dbg(SDL_Scancode this) {
  switch (this) {
    case SDL_SCANCODE_A: return "A";
    case SDL_SCANCODE_B: return "B";
    case SDL_SCANCODE_C: return "C";
    case SDL_SCANCODE_D: return "D";
    case SDL_SCANCODE_E: return "E";
    case SDL_SCANCODE_F: return "F";
    case SDL_SCANCODE_G: return "G";
    case SDL_SCANCODE_H: return "H";
    case SDL_SCANCODE_I: return "I";
    case SDL_SCANCODE_J: return "J";
    case SDL_SCANCODE_K: return "K";
    case SDL_SCANCODE_L: return "L";
    case SDL_SCANCODE_M: return "M";
    case SDL_SCANCODE_N: return "N";
    case SDL_SCANCODE_O: return "O";
    case SDL_SCANCODE_P: return "P";
    case SDL_SCANCODE_Q: return "Q";
    case SDL_SCANCODE_R: return "R";
    case SDL_SCANCODE_S: return "S";
    case SDL_SCANCODE_T: return "T";
    case SDL_SCANCODE_U: return "U";
    case SDL_SCANCODE_V: return "V";
    case SDL_SCANCODE_W: return "W";
    case SDL_SCANCODE_X: return "X";
    case SDL_SCANCODE_Y: return "Y";
    case SDL_SCANCODE_Z: return "Z";
    case SDL_SCANCODE_UP: return "Up";
    case SDL_SCANCODE_DOWN: return "Down";
    case SDL_SCANCODE_LEFT: return "Left";
    case SDL_SCANCODE_RIGHT: return "Right";
    case SDL_SCANCODE_SPACE: return "Space";
    case SDL_SCANCODE_ESCAPE: return "Escape";
    case SDL_SCANCODE_COMMA: return "Comma";
    case SDL_SCANCODE_PERIOD: return "Dot";
    default: return "<unknown>";
  }
}

char *std_sdl_MouseButton_dbg(u8 this) {
  switch (this) {
    case SDL_BUTTON_LEFT: return "Left";
    case SDL_BUTTON_MIDDLE: return "Middle";
    case SDL_BUTTON_RIGHT: return "Right";
    case SDL_BUTTON_X1: return "Forward";
    case SDL_BUTTON_X2: return "Backward";
    default: return "<unknown>";
  }
}

char *std_sdl_EventType_dbg(SDL_EventType this) {
  switch (this) {
    case SDL_QUIT: return "Quit";
    case SDL_KEYDOWN: return "KeyDown";
    case SDL_KEYUP: return "KeyUp";
    case SDL_MOUSEBUTTONDOWN: return "MouseDown";
    case SDL_MOUSEBUTTONUP: return "MouseUp";
    case SDL_MOUSEWHEEL: return "Wheel";
    case SDL_WINDOWEVENT: return "Window";
    case SDL_USEREVENT: return "User";
    default: return "<unknown>";
  }
}

struct std_random_RandomState {
  u32 x;
  u32 y;
  u32 z;
  u32 w;
};

struct src_core_matrix_Matrix {
  f32 d[4][4];
};

struct src_objects_transformed_Transformed {
  src_core_object_Object *obj;
  src_core_matrix_Matrix transform;
  src_core_matrix_Matrix inverse;
};

struct src_objects_triangle_Triangle {
  std_vec_Vec3__0 p0;
  std_vec_Vec3__0 p1;
  std_vec_Vec3__0 p2;
  std_vec_Vec3__0 n0;
  std_vec_Vec3__0 n1;
  std_vec_Vec3__0 n2;
  std_vec_Vec2__1 t0;
  std_vec_Vec2__1 t1;
  std_vec_Vec2__1 t2;
};

struct src_objects_sphere_Sphere {
  std_vec_Vec3__0 pos;
  f32 r;
};

struct src_objects_mesh_Mesh {
  std_vector_Vector__0 *triangles;
  src_core_bvh_BVH__0 *bvh;
};

enum src_core_texture_Texture__kind {
  src_core_texture_Texture_Color,
  src_core_texture_Texture_Image,
  src_core_texture_Texture_Checkerboard,
};

struct src_core_texture_Texture {
  src_core_texture_Texture__kind tag;
  union {
    struct {
      std_vec_Vec3__0 color;
    } src_core_texture_Texture_Color;
    struct {
      std_image_Image *img;
    } src_core_texture_Texture_Image;
    struct {
      f32 scale;
    } src_core_texture_Texture_Checkerboard;
  };
};

enum src_core_materialtype_MaterialType {
  src_core_materialtype_MaterialType_Diffused,
  src_core_materialtype_MaterialType_Reflective,
};

char *src_core_materialtype_MaterialType_dbg(src_core_materialtype_MaterialType this) {
  switch (this) {
    case src_core_materialtype_MaterialType_Diffused: return "Diffused";
    case src_core_materialtype_MaterialType_Reflective: return "Reflective";
    default: return "<unknown>";
  }
}

enum src_core_object_Object__kind {
  src_core_object_Object_Sphere,
  src_core_object_Object_Triangle,
  src_core_object_Object_Mesh,
  src_core_object_Object_Transformed,
};

struct src_core_object_Object {
  src_core_object_Object__kind tag;
  src_core_texture_Texture texture;
  src_core_materialtype_MaterialType mat;
  union {
    struct {
      src_objects_sphere_Sphere sphere;
    } src_core_object_Object_Sphere;
    struct {
      src_objects_triangle_Triangle tri;
    } src_core_object_Object_Triangle;
    struct {
      src_objects_mesh_Mesh mesh;
    } src_core_object_Object_Mesh;
    struct {
      src_objects_transformed_Transformed trans;
    } src_core_object_Object_Transformed;
  };
};

struct src_core_hitrec_HitRec {
  f32 t;
  src_core_object_Object *obj;
  std_vec_Vec3__0 norm;
  std_vec_Vec3__0 pos;
  std_vec_Vec2__1 uv;
};

struct src_core_bounds_Bounds {
  std_vec_Vec3__0 min;
  std_vec_Vec3__0 max;
};

struct src_core_bvh_BVH__0 {
  src_core_bounds_Bounds bounds;
  bool is_leaf;
  src_objects_triangle_Triangle obj;
  src_core_bvh_BVH__0 *l;
  src_core_bvh_BVH__0 *r;
};

struct src_core_scene_Scene {
  std_vector_Vector__1 *objects;
};

struct src_core_camera_Camera {
  std_vec_Vec3__0 pos;
  std_vec_Vec3__0 top_left;
  std_vec_Vec3__0 du;
  std_vec_Vec3__0 dv;
  u32 num_samples;
};

struct src_core_ray_Ray {
  std_vec_Vec3__0 pos;
  std_vec_Vec3__0 dir;
};

struct _ClosureTy_10 {
  void *_C;
  i8 (*fn)(void *__C, src_objects_triangle_Triangle, src_objects_triangle_Triangle);
};
struct src_core_bvh_create__Closure_3Ctx {
  u32 *dim;
};
/* function declarations */
void std_panic(char *msg) __attribute__((noreturn));
char *std_format(char *fmt, ...);
bool str_ends_with(char *this, char *suffix);
bool char_is_space(char this);
bool char_is_upper(char this);
u32 u32_min(u32 this, u32 other);
u32 u32_max(u32 this, u32 other);
void std_mem_set_allocator(void *allocator, void *(*alloc_fn)(void *, u32), void (*free_fn)(void *, void *), void *(*realloc_fn)(void *, void *, u32, u32));
char *std_mem_alloc__0(u32 count);
std_image_Image *std_mem_alloc__1(u32 count);
std_image_Color *std_mem_alloc__2(u32 count);
u8 *std_mem_alloc__3(u32 count);
std_video_renderer_VideoRenderer *std_mem_alloc__4(u32 count);
std_video_renderer_ffmpeg_FFMPEGContext *std_mem_alloc__5(u32 count);
u32 *std_mem_alloc__6(u32 count);
std_video_renderer_sdl_SDLContext *std_mem_alloc__7(u32 count);
std_vector_Vector__0 *std_mem_alloc__8(u32 count);
src_objects_triangle_Triangle *std_mem_alloc__9(u32 count);
std_vector_Vector__1 *std_mem_alloc__10(u32 count);
src_core_object_Object **std_mem_alloc__11(u32 count);
std_vector_Vector__2 *std_mem_alloc__12(u32 count);
char **std_mem_alloc__13(u32 count);
std_vector_Vector__4 *std_mem_alloc__14(u32 count);
std_vec_Vec2__1 *std_mem_alloc__15(u32 count);
std_vector_Vector__3 *std_mem_alloc__16(u32 count);
std_vec_Vec3__0 *std_mem_alloc__17(u32 count);
void std_mem_free(void *ptr);
u8 *std_mem_realloc__0(u8 *ptr, u32 old_count, u32 new_count);
src_objects_triangle_Triangle *std_mem_realloc__1(src_objects_triangle_Triangle *ptr, u32 old_count, u32 new_count);
src_core_object_Object **std_mem_realloc__2(src_core_object_Object **ptr, u32 old_count, u32 new_count);
char **std_mem_realloc__3(char **ptr, u32 old_count, u32 new_count);
std_vec_Vec2__1 *std_mem_realloc__4(std_vec_Vec2__1 *ptr, u32 old_count, u32 new_count);
std_vec_Vec3__0 *std_mem_realloc__5(std_vec_Vec3__0 *ptr, u32 old_count, u32 new_count);
void *std_mem_impl_my_calloc(void *state, u32 size);
void *std_mem_impl_my_realloc(void *state, void *ptr, u32 old_size, u32 size);
void std_mem_impl_my_free(void *state, void *ptr);
bool std_sv_SV_is_empty(std_sv_SV *this);
std_sv_SV std_sv_SV_from_str(char *s);
std_sv_SV std_sv_SV_get(std_sv_SV this, u32 n);
char std_sv_SV_at(std_sv_SV this, u32 n);
std_sv_SV std_sv_SV_chop_left(std_sv_SV *this, u32 n);
void std_sv_SV_trim_left(std_sv_SV *this);
std_sv_SV std_sv_SV_chop_by_delim(std_sv_SV *this, char delim);
std_sv_SV std_sv_SV_chop_word(std_sv_SV *this);
u64 std_sv_SV_chop_unsigned(std_sv_SV *this, char *fn_name);
u32 std_sv_SV_chop_u32(std_sv_SV *this);
f32 std_sv_SV_chop_f32(std_sv_SV *this);
std_sv_SV std_sv_SV_chop_line(std_sv_SV *this);
bool std_sv_SV_eq(std_sv_SV this, std_sv_SV other);
bool std_sv_SV_eq_str(std_sv_SV this, char *other);
void std_sv_SV_only_chop_left(std_sv_SV *this, u32 n);
std_sv_SVLineIterator std_sv_SV_lines(std_sv_SV this);
std_buffer_BytesReader std_sv_SV_reader(std_sv_SV this);
bool std_sv_SVLineIterator_has_value(std_sv_SVLineIterator *this);
std_sv_SV std_sv_SVLineIterator_cur(std_sv_SVLineIterator *this);
void std_sv_SVLineIterator_next(std_sv_SVLineIterator *this);
char *std_libc_errno_get_err(void);
void std_gc_init(void *base);
void *std_gc_alloc(u32 size);
void std_gc_collect(void);
void *std_gc_impl__alloc_fn(void *_, u32 size);
void *std_gc_impl__realloc_fn(void *_, void *ptr, u32 old_size, u32 size);
void std_gc_impl__free_fn(void *_, void *ptr);
void std_gc_impl_mark_range(void *start, void *end);
void std_gc_impl_mark_object(std_gc_impl_Header *header);
std_image_Image *std_image_Image_new(u32 width, u32 height);
std_image_Color std_image_Image_get(std_image_Image *this, u32 x, u32 y);
void std_image_Image_set(std_image_Image *this, u32 x, u32 y, std_image_Color col);
std_image_Image *std_image_Image_load(char *filename);
f32 std_image_interp(f32 t, f32 a, f32 b);
f32 std_image_bilinear_interp(f32 t0, f32 t1, f32 a, f32 b, f32 c, f32 d);
std_image_Image *std_image_ppm_decode(std_buffer_Buffer *data);
u32 std_image_qoi_RGBA_hash(std_image_qoi_RGBA this);
std_image_qoi_QOIDecoder std_image_qoi_QOIDecoder_make(std_buffer_Buffer *data);
std_image_Image *std_image_qoi_QOIDecoder_decode(std_image_qoi_QOIDecoder *this);
void std_image_qoi_QOIDecoder_handle_pixel(std_image_qoi_QOIDecoder *this, std_image_qoi_RGBA pix);
void std_image_qoi_QOIDecoder_decode_pixels(std_image_qoi_QOIDecoder *this);
void std_image_qoi_QOIDecoder_decode_op_rgb(std_image_qoi_QOIDecoder *this);
void std_image_qoi_QOIDecoder_decode_op_rgba(std_image_qoi_QOIDecoder *this);
void std_image_qoi_QOIDecoder_decode_op_luma(std_image_qoi_QOIDecoder *this, u8 first);
void std_image_qoi_QOIDecoder_decode_op_index(std_image_qoi_QOIDecoder *this, u8 first);
void std_image_qoi_QOIDecoder_decode_op_diff(std_image_qoi_QOIDecoder *this, u8 first);
void std_image_qoi_QOIDecoder_decode_op_run(std_image_qoi_QOIDecoder *this, u8 first);
std_image_Image *std_image_qoi_decode(std_buffer_Buffer *data);
std_image_png_Chunk std_image_png_Chunk_parse(std_buffer_BytesReader *io);
u8 std_image_png_paeth_predictor(u8 ua, u8 ub, u8 uc);
void std_image_png_PNG_decode_scanline(std_image_png_PNG *this, std_buffer_Buffer *out, u32 scanline, std_sv_SV sv);
std_image_Image *std_image_png_decode(std_buffer_Buffer *data);
std_buffer_Buffer std_buffer_Buffer_make(u32 capacity);
std_buffer_Buffer std_buffer_Buffer_from_sized_str(char *s, u32 size);
void std_buffer_Buffer_resize_if_necessary(std_buffer_Buffer *this, u32 new_size);
u8 std_buffer_Buffer_get_byte_at(std_buffer_Buffer this, u32 index);
void std_buffer_Buffer_write_buf(std_buffer_Buffer *this, std_buffer_Buffer *buf);
void std_buffer_Buffer_write_bytes(std_buffer_Buffer *this, void *bytes, u32 size);
void std_buffer_Buffer_write_u8(std_buffer_Buffer *this, u8 value);
std_buffer_BytesReader std_buffer_Buffer_reader(std_buffer_Buffer this);
std_sv_SV std_buffer_Buffer_sv(std_buffer_Buffer this);
void std_buffer_Buffer_free(std_buffer_Buffer *this);
std_buffer_BytesReader std_buffer_BytesReader_make(u8 *data, u32 size);
u32 std_buffer_BytesReader_read_u32(std_buffer_BytesReader *this, std_Endian endian);
u8 std_buffer_BytesReader_read_u8(std_buffer_BytesReader *this);
std_sv_SV std_buffer_BytesReader_read_bytes_sv(std_buffer_BytesReader *this, u32 count);
bool std_buffer_BytesReader_is_empty(std_buffer_BytesReader *this);
i8 f32_compare(f32 this, f32 b);
std_buffer_Buffer std_fs_read_file(char *path);
std_vec_Vec2__1 std_vec_Vec2__1_add(std_vec_Vec2__1 this, std_vec_Vec2__1 other);
std_vec_Vec2__5 std_vec_Vec2__1_to_u32(std_vec_Vec2__1 this);
std_vec_Vec2__1 std_vec_Vec2__1_mults(std_vec_Vec2__1 this, f32 val);
std_vec_Vec3__0 std_vec_Vec3__0_sub(std_vec_Vec3__0 this, std_vec_Vec3__0 other);
std_vec_Vec3__0 std_vec_Vec3__0_normalized(std_vec_Vec3__0 this);
std_vec_Vec3__0 std_vec_Vec3__0_multrs(f32 val, std_vec_Vec3__0 this);
std_vec_Vec3__0 std_vec_Vec3__0_add(std_vec_Vec3__0 this, std_vec_Vec3__0 other);
f32 std_vec_Vec3__0_length_sq(std_vec_Vec3__0 this);
std_vec_Vec3__0 std_vec_Vec3__0_mult(std_vec_Vec3__0 this, std_vec_Vec3__0 other);
std_vec_Vec3__0 std_vec_Vec3__0_reflect(std_vec_Vec3__0 this, std_vec_Vec3__0 normal);
std_vec_Vec3__0 std_vec_Vec3__0_divs(std_vec_Vec3__0 this, f32 val);
std_vec_Vec3__0 std_vec_Vec3__0_subs(std_vec_Vec3__0 this, f32 val);
std_vec_Vec3__0 std_vec_Vec3__0_mults(std_vec_Vec3__0 this, f32 val);
f32 std_vec_Vec3__0_length(std_vec_Vec3__0 this);
f32 std_vec_Vec3__0_dot(std_vec_Vec3__0 this, std_vec_Vec3__0 other);
f32 std_vec_Vec3__0_index(std_vec_Vec3__0 this, u32 idx);
std_vec_Vec3__0 std_vec_Vec3__0_cross(std_vec_Vec3__0 this, std_vec_Vec3__0 other);
std_vec_Vec3__0 std_vec_Vec3__0_divrs(f32 val, std_vec_Vec3__0 this);
f32 f32_inf(void);
f32 f32_min(f32 this, f32 b);
f32 f32_max(f32 this, f32 b);
f32 f32_clamp(f32 this, f32 min, f32 max);
f32 f32_clamp01(f32 this);
i32 i32_abs(i32 this);
std_video_renderer_VideoRenderer *std_video_renderer_VideoRenderer_create(std_video_renderer_VideoRendererType type, u32 width, u32 height, u32 fps, char *out_name, bool verbose);
void std_video_renderer_VideoRenderer_send_frame(std_video_renderer_VideoRenderer *this, std_image_Image *img);
std_video_renderer_ffmpeg_FFMPEGContext *std_video_renderer_ffmpeg_FFMPEGContext_create(u32 width, u32 height, u32 fps, char *out_name, bool verbose);
bool std_video_renderer_ffmpeg_FFMPEGContext_send_frame(std_video_renderer_ffmpeg_FFMPEGContext *this, std_image_Image *img);
std_video_renderer_sdl_SDLContext *std_video_renderer_sdl_SDLContext_create(u32 width, u32 height, u32 fps);
void std_video_renderer_sdl_SDLContext_finish(std_video_renderer_sdl_SDLContext *this);
void std_video_renderer_sdl_SDLContext_send_frame(std_video_renderer_sdl_SDLContext *this, std_image_Image *img);
std_buffer_Buffer std_zlib_decompress_bytes(u8 *data, u32 size, u32 *bytes_consumed);
std_buffer_Buffer std_zlib_decompress(std_buffer_Buffer data, u32 *bytes_consumed);
src_objects_triangle_Triangle std_vector_Vector__0_at(std_vector_Vector__0 *this, u32 i);
void std_vector_Vector__0_resize(std_vector_Vector__0 *this, u32 new_capacity);
std_vector_Vector__0 *std_vector_Vector__0_new(u32 capacity);
void std_vector_Vector__0_push(std_vector_Vector__0 *this, src_objects_triangle_Triangle value);
std_vector_Iterator__1 std_vector_Vector__1_iter(std_vector_Vector__1 *this);
src_core_object_Object *std_vector_Iterator__1_cur(std_vector_Iterator__1 *this);
void std_vector_Iterator__1_next(std_vector_Iterator__1 *this);
bool std_vector_Iterator__1_has_value(std_vector_Iterator__1 *this);
std_vector_Iterator__1 std_vector_Iterator__1_make(std_vector_Vector__1 *vec);
void std_vector_Vector__1_resize(std_vector_Vector__1 *this, u32 new_capacity);
std_vector_Vector__1 *std_vector_Vector__1_new(u32 capacity);
void std_vector_Vector__1_push(std_vector_Vector__1 *this, src_core_object_Object *value);
void std_vector_Vector__2_resize(std_vector_Vector__2 *this, u32 new_capacity);
std_vector_Vector__2 *std_vector_Vector__2_new(u32 capacity);
void std_vector_Vector__2_push(std_vector_Vector__2 *this, char *value);
std_vec_Vec3__0 std_vector_Vector__3_at(std_vector_Vector__3 *this, u32 i);
void std_vector_Vector__3_free(std_vector_Vector__3 *this);
void std_vector_Vector__3_resize(std_vector_Vector__3 *this, u32 new_capacity);
std_vector_Vector__3 *std_vector_Vector__3_new(u32 capacity);
void std_vector_Vector__3_push(std_vector_Vector__3 *this, std_vec_Vec3__0 value);
std_vec_Vec2__1 std_vector_Vector__4_at(std_vector_Vector__4 *this, u32 i);
void std_vector_Vector__4_free(std_vector_Vector__4 *this);
void std_vector_Vector__4_resize(std_vector_Vector__4 *this, u32 new_capacity);
std_vector_Vector__4 *std_vector_Vector__4_new(u32 capacity);
void std_vector_Vector__4_push(std_vector_Vector__4 *this, std_vec_Vec2__1 value);
void std_random_RandomState_seed(std_random_RandomState *this, u32 s);
std_random_RandomState std_random_RandomState_make(u32 s);
u32 std_random_randint(std_random_RandomState *state);
f32 std_random_randf32(std_random_RandomState *state);
src_objects_triangle_Triangle std_sort_nth_element_by__0(src_objects_triangle_Triangle *data, u32 size, u32 n, _ClosureTy_10 cmp);
std_vec_Vec3__0 src_utils_utils_get_interpolated(std_image_Image *img, f32 xf, f32 yf);
bool src_objects_transformed_Transformed_hit(src_objects_transformed_Transformed *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, src_core_object_Object *parent);
src_core_object_Object *src_objects_transformed_Transformed_new(src_core_object_Object *obj, src_core_matrix_Matrix transform);
bool src_objects_triangle_Triangle_hit(src_objects_triangle_Triangle *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, src_core_object_Object *parent);
src_core_bounds_Bounds src_objects_triangle_Triangle_bounds(src_objects_triangle_Triangle this);
bool src_objects_sphere_Sphere_hit(src_objects_sphere_Sphere *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, src_core_object_Object *parent);
bool src_objects_mesh_Mesh_hit(src_objects_mesh_Mesh *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, src_core_object_Object *parent);
src_objects_mesh_Mesh src_objects_mesh_Mesh_from_obj(char *filename);
bool src_core_object_Object_hit(src_core_object_Object *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec);
src_core_bounds_Bounds src_core_bounds_Bounds_empty(void);
src_core_bounds_Bounds src_core_bounds_Bounds_join(src_core_bounds_Bounds this, src_core_bounds_Bounds other);
src_core_bounds_Bounds src_core_bounds_Bounds_add_point(src_core_bounds_Bounds this, std_vec_Vec3__0 vec);
void src_core_bounds_Bounds_join_assign(src_core_bounds_Bounds *this, src_core_bounds_Bounds other);
bool src_core_bounds_Bounds_hit(src_core_bounds_Bounds *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, f32 *t1, f32 *t2, std_vec_Vec3__0 inv_d);
std_vec_Vec3__0 src_core_bounds_Bounds_centroid(src_core_bounds_Bounds this);
bool src_core_bvh_BVH__0_hit(src_core_bvh_BVH__0 *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, src_core_object_Object *parent);
src_core_bvh_BVH__0 *src_core_bvh_BVH__0_create(std_vector_Vector__0 *objects, u32 start, u32 end);
std_vec_Vec3__0 src_core_texture_Texture_get(src_core_texture_Texture this, std_vec_Vec2__1 uv);
std_vec_Vec3__0 src_core_scene_Scene_sky_color(src_core_scene_Scene *this, src_core_ray_Ray *ray);
std_vec_Vec3__0 src_core_scene_random_point_on_sphere(std_random_RandomState *rng);
std_vec_Vec3__0 src_core_scene_Scene_hit(src_core_scene_Scene *this, src_core_ray_Ray *ray, std_random_RandomState *rng);
src_core_camera_Camera src_core_camera_Camera_make(u32 width, u32 height, f32 focal_length, std_vec_Vec3__0 pos, u32 num_samples);
src_core_ray_Ray src_core_camera_Camera_create_ray(src_core_camera_Camera *this, u32 i, u32 j, std_random_RandomState *rng);
src_core_matrix_Matrix src_core_matrix_Matrix_transpose(src_core_matrix_Matrix this);
src_core_matrix_Matrix src_core_matrix_Matrix_make(f32 d00, f32 d01, f32 d02, f32 d03, f32 d10, f32 d11, f32 d12, f32 d13, f32 d20, f32 d21, f32 d22, f32 d23, f32 d30, f32 d31, f32 d32, f32 d33);
src_core_matrix_Matrix src_core_matrix_Matrix_identity(void);
src_core_matrix_Matrix src_core_matrix_Matrix_mul(src_core_matrix_Matrix this, src_core_matrix_Matrix other);
std_vec_Vec3__0 src_core_matrix_Matrix_mulv(src_core_matrix_Matrix this, std_vec_Vec3__0 v);
std_vec_Vec3__0 src_core_matrix_Matrix_mulv_no_translation(src_core_matrix_Matrix this, std_vec_Vec3__0 v);
src_core_matrix_Matrix src_core_matrix_Matrix_scale(src_core_matrix_Matrix this, f32 t);
src_core_matrix_Matrix src_core_matrix_Matrix_invert(src_core_matrix_Matrix *this);
src_core_matrix_Matrix src_core_matrix_Matrix_for_translate(std_vec_Vec3__0 v);
src_core_matrix_Matrix src_core_matrix_Matrix_for_scale(std_vec_Vec3__0 v);
src_core_matrix_Matrix src_core_matrix_Matrix_for_rotate_x(f32 a);
src_core_matrix_Matrix src_core_matrix_Matrix_for_rotate_y(f32 a);
std_vec_Vec3__0 src_core_ray_Ray_at(src_core_ray_Ray this, f32 t);
i32 main(void);
void render(std_image_Image *img, src_core_camera_Camera *camera, src_core_scene_Scene *scene);
src_core_scene_Scene make_scene(f32 time);
std_image_Color std_image_Color_from_vec(std_vec_Vec3__0 vec);
i8 src_core_bvh_create__Closure_3(void *__C, src_objects_triangle_Triangle l, src_objects_triangle_Triangle r);
void *std_mem_state_allocator = NULL;
void *(*std_mem_state_alloc_fn)(void *, u32) = std_mem_impl_my_calloc;
void *(*std_mem_state_realloc_fn)(void *, void *, u32, u32) = std_mem_impl_my_realloc;
void (*std_mem_state_free_fn)(void *, void *) = std_mem_impl_my_free;
std_gc_impl_Header *std_gc_impl_alloc_list = NULL;
void *std_gc_impl_stack_bottom = NULL;
u32 std_gc_impl_total_allocations = 0;
u32 std_gc_impl_total_alloc_bytes = 0;
u32 std_gc_impl_live_allocations = 0;
u32 std_gc_impl_live_alloc_bytes = 0;
u32 std_gc_impl_freed_allocations = 0;
u32 std_gc_impl_freed_alloc_bytes = 0;
std_random_RandomState std_random_global_random_state = (std_random_RandomState){.x=123456789, .y=362436069, .z=521288629, .w=88675123};
/* function implementations */
void std_panic(char *msg) {
  dump_backtrace();
  fprintf(stderr, "--------------------------------------------------------------------------------""\n");
  fprintf(stderr, "%s""\n", msg);
  oc_trap();
  exit(1);
}

char *std_format(char *fmt, ...) {
  va_list args = {0};
  va_start(args, fmt);
  u32 size = vsnprintf(NULL, 0, fmt, args);
  va_end(args);
  va_start(args, fmt);
  char *s = std_mem_alloc__0(((u32)(size + 1)));
  vsnprintf(s, (size + 1), fmt, args);
  s[size]='\0';
  va_end(args);
  return s;
}

bool str_ends_with(char *this, char *suffix) {
  u32 suffix_len = strlen(suffix);
  u32 len = strlen(this);
  if (suffix_len > len) {
    return false;
  }
  for (u32 i = 0; i < suffix_len; i+=1) {
    if (this[((len - suffix_len) + i)] != suffix[i]) {
      return false;
    }
  }
  return true;
}

bool char_is_space(char this) {
  return isspace(this);}

bool char_is_upper(char this) {
  return isupper(this);}

u32 u32_min(u32 this, u32 other) {
  return ((this < other) ? this : other);}

u32 u32_max(u32 this, u32 other) {
  return ((this > other) ? this : other);}

void std_mem_set_allocator(void *allocator, void *(*alloc_fn)(void *, u32), void (*free_fn)(void *, void *), void *(*realloc_fn)(void *, void *, u32, u32)) {
  std_mem_state_allocator=allocator;
  std_mem_state_alloc_fn=alloc_fn;
  std_mem_state_realloc_fn=realloc_fn;
  std_mem_state_free_fn=free_fn;
}

char *std_mem_alloc__0(u32 count) {
  return ((char *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(char)))));
}

std_image_Image *std_mem_alloc__1(u32 count) {
  return ((std_image_Image *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_image_Image)))));
}

std_image_Color *std_mem_alloc__2(u32 count) {
  return ((std_image_Color *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_image_Color)))));
}

u8 *std_mem_alloc__3(u32 count) {
  return ((u8 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(u8)))));
}

std_video_renderer_VideoRenderer *std_mem_alloc__4(u32 count) {
  return ((std_video_renderer_VideoRenderer *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_video_renderer_VideoRenderer)))));
}

std_video_renderer_ffmpeg_FFMPEGContext *std_mem_alloc__5(u32 count) {
  return ((std_video_renderer_ffmpeg_FFMPEGContext *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_video_renderer_ffmpeg_FFMPEGContext)))));
}

u32 *std_mem_alloc__6(u32 count) {
  return ((u32 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(u32)))));
}

std_video_renderer_sdl_SDLContext *std_mem_alloc__7(u32 count) {
  return ((std_video_renderer_sdl_SDLContext *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_video_renderer_sdl_SDLContext)))));
}

std_vector_Vector__0 *std_mem_alloc__8(u32 count) {
  return ((std_vector_Vector__0 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__0)))));
}

src_objects_triangle_Triangle *std_mem_alloc__9(u32 count) {
  return ((src_objects_triangle_Triangle *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(src_objects_triangle_Triangle)))));
}

std_vector_Vector__1 *std_mem_alloc__10(u32 count) {
  return ((std_vector_Vector__1 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__1)))));
}

src_core_object_Object **std_mem_alloc__11(u32 count) {
  return ((src_core_object_Object **)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(src_core_object_Object *)))));
}

std_vector_Vector__2 *std_mem_alloc__12(u32 count) {
  return ((std_vector_Vector__2 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__2)))));
}

char **std_mem_alloc__13(u32 count) {
  return ((char **)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(char *)))));
}

std_vector_Vector__4 *std_mem_alloc__14(u32 count) {
  return ((std_vector_Vector__4 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__4)))));
}

std_vec_Vec2__1 *std_mem_alloc__15(u32 count) {
  return ((std_vec_Vec2__1 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vec_Vec2__1)))));
}

std_vector_Vector__3 *std_mem_alloc__16(u32 count) {
  return ((std_vector_Vector__3 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vector_Vector__3)))));
}

std_vec_Vec3__0 *std_mem_alloc__17(u32 count) {
  return ((std_vec_Vec3__0 *)std_mem_state_alloc_fn(std_mem_state_allocator, (count * ((u32)sizeof(std_vec_Vec3__0)))));
}

void std_mem_free(void *ptr) {
  if (std_mem_state_free_fn != NULL) {
    std_mem_state_free_fn(std_mem_state_allocator, ptr);
    return;
  }
}

u8 *std_mem_realloc__0(u8 *ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(u8)));
  u32 new_size = (new_count * ((u32)sizeof(u8)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/mindful-dev/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  u8 *new_ptr = std_mem_alloc__3(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

src_objects_triangle_Triangle *std_mem_realloc__1(src_objects_triangle_Triangle *ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(src_objects_triangle_Triangle)));
  u32 new_size = (new_count * ((u32)sizeof(src_objects_triangle_Triangle)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/mindful-dev/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  src_objects_triangle_Triangle *new_ptr = std_mem_alloc__9(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

src_core_object_Object **std_mem_realloc__2(src_core_object_Object **ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(src_core_object_Object *)));
  u32 new_size = (new_count * ((u32)sizeof(src_core_object_Object *)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/mindful-dev/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  src_core_object_Object **new_ptr = std_mem_alloc__11(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

char **std_mem_realloc__3(char **ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(char *)));
  u32 new_size = (new_count * ((u32)sizeof(char *)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/mindful-dev/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  char **new_ptr = std_mem_alloc__13(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

std_vec_Vec2__1 *std_mem_realloc__4(std_vec_Vec2__1 *ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(std_vec_Vec2__1)));
  u32 new_size = (new_count * ((u32)sizeof(std_vec_Vec2__1)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/mindful-dev/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  std_vec_Vec2__1 *new_ptr = std_mem_alloc__15(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

std_vec_Vec3__0 *std_mem_realloc__5(std_vec_Vec3__0 *ptr, u32 old_count, u32 new_count) {
  u32 old_size = (old_count * ((u32)sizeof(std_vec_Vec3__0)));
  u32 new_size = (new_count * ((u32)sizeof(std_vec_Vec3__0)));
  if (std_mem_state_realloc_fn != NULL) {
    return std_mem_state_realloc_fn(std_mem_state_allocator, ptr, old_size, new_size);
  }
  if(!(new_size >= old_size)) { ae_assert_fail("/home/mindful-dev/ocen/std/mem.oc:63:12: Assertion failed: `new_size >= old_size`", "Cannot shrink memory in default allocator"); }
  std_vec_Vec3__0 *new_ptr = std_mem_alloc__17(new_count);
  memcpy(new_ptr, ptr, old_size);
  std_mem_free(ptr);
  return new_ptr;
}

void *std_mem_impl_my_calloc(void *state, u32 size) {
  return calloc(size, 1);}

void *std_mem_impl_my_realloc(void *state, void *ptr, u32 old_size, u32 size) {
  return realloc(ptr, size);}

void std_mem_impl_my_free(void *state, void *ptr) {
    free(ptr);
}

bool std_sv_SV_is_empty(std_sv_SV *this) {
  return this->len==0;}

std_sv_SV std_sv_SV_from_str(char *s) {
  return (std_sv_SV){.data=s, .len=strlen(s)};}

std_sv_SV std_sv_SV_get(std_sv_SV this, u32 n) {
  return (std_sv_SV){.data=this.data, .len=n};}

char std_sv_SV_at(std_sv_SV this, u32 n) {
  if(!(n < this.len)) { ae_assert_fail("/home/mindful-dev/ocen/std/sv.oc:30:12: Assertion failed: `n < .len`", "Index out of bounds in SV::at"); }
  return this.data[n];
}

std_sv_SV std_sv_SV_chop_left(std_sv_SV *this, u32 n) {
  std_sv_SV res = std_sv_SV_get((*this), n);
  this->data=(this->data + n);
  this->len-=n;
  return res;
}

void std_sv_SV_trim_left(std_sv_SV *this) {
  while ((this->len > 0) && char_is_space(this->data[0])) {
    this->data=(this->data + 1);
    this->len-=1;
  }
}

std_sv_SV std_sv_SV_chop_by_delim(std_sv_SV *this, char delim) {
  u32 i = 0;
  while ((i < this->len) && (this->data[i] != delim)) {
    i+=1;
  }
  std_sv_SV res = std_sv_SV_get((*this), i);
  if (i==this->len) {
    this->data=(this->data + i);
    this->len-=i;
  } else {
    this->data=((this->data + i) + 1);
    this->len-=(i + 1);
  }
  return res;
}

std_sv_SV std_sv_SV_chop_word(std_sv_SV *this) {
  std_sv_SV_trim_left(this);
  u32 i = 0;
  while ((i < this->len) && !(char_is_space(this->data[i]))) {
    i+=1;
  }
  std_sv_SV res = std_sv_SV_get((*this), i);
  if (i==this->len) {
    this->data=(this->data + i);
    this->len-=i;
  } else {
    this->data=((this->data + i) + 1);
    this->len-=(i + 1);
  }
  std_sv_SV_trim_left(this);
  return res;
}

u64 std_sv_SV_chop_unsigned(std_sv_SV *this, char *fn_name) {
  char *endptr = "";
  u64 res = strtoul(this->data, &endptr, 10);
  if(!(endptr != this->data)) { ae_assert_fail("/home/mindful-dev/ocen/std/sv.oc:140:12: Assertion failed: `endptr != .data`", std_format("Failed to parse number in %s", fn_name)); }
  std_sv_SV_only_chop_left(this, ((u32)(endptr - this->data)));
  return res;
}

u32 std_sv_SV_chop_u32(std_sv_SV *this) {
  return ((u32)std_sv_SV_chop_unsigned(this, "SV::chop_u32"));}

f32 std_sv_SV_chop_f32(std_sv_SV *this) {
  char *endptr = "";
  f64 res = strtod(this->data, &endptr);
  if(!(endptr != this->data)) { ae_assert_fail("/home/mindful-dev/ocen/std/sv.oc:163:12: Assertion failed: `endptr != .data`", "Failed to parse number in SV::chop_f32"); }
  std_sv_SV_only_chop_left(this, ((u32)(endptr - this->data)));
  return ((f32)res);
}

std_sv_SV std_sv_SV_chop_line(std_sv_SV *this) {
  return std_sv_SV_chop_by_delim(this, '\n');}

bool std_sv_SV_eq(std_sv_SV this, std_sv_SV other) {
  return (this.len==other.len && memcmp(this.data, other.data, this.len)==0);}

bool std_sv_SV_eq_str(std_sv_SV this, char *other) {
  return std_sv_SV_eq(this, std_sv_SV_from_str(other));}

void std_sv_SV_only_chop_left(std_sv_SV *this, u32 n) {
  this->data=(this->data + n);
  this->len-=n;
}

std_sv_SVLineIterator std_sv_SV_lines(std_sv_SV this) {
  return (std_sv_SVLineIterator){.sv=this};}

std_buffer_BytesReader std_sv_SV_reader(std_sv_SV this) {
  return std_buffer_BytesReader_make(((u8 *)this.data), this.len);}

bool std_sv_SVLineIterator_has_value(std_sv_SVLineIterator *this) {
  return !(std_sv_SV_is_empty(&this->sv));}

std_sv_SV std_sv_SVLineIterator_cur(std_sv_SVLineIterator *this) {
  return std_sv_SV_chop_line(&this->sv);}

void std_sv_SVLineIterator_next(std_sv_SVLineIterator *this) {
}

char *std_libc_errno_get_err(void) {
  return ((char *)strerror(errno));}

void std_gc_init(void *base) {
  std_gc_impl_stack_bottom=base;
  std_mem_set_allocator(NULL, std_gc_impl__alloc_fn, std_gc_impl__free_fn, std_gc_impl__realloc_fn);
}

void *std_gc_alloc(u32 size) {
  u32 total_size = (size + ((u32)sizeof(std_gc_impl_Header)));
  std_gc_impl_Header *header = calloc(total_size, 1);
  if (!(((bool)header))) {
    return NULL;
  }
  header->size=size;
  header->marked=false;
  header->global=false;
  header->next=std_gc_impl_alloc_list;
  header->prev=NULL;
  if (((bool)std_gc_impl_alloc_list)) {
    std_gc_impl_alloc_list->prev=header;
  }
  std_gc_impl_alloc_list=header;
  std_gc_impl_total_allocations+=1;
  std_gc_impl_total_alloc_bytes+=total_size;
  std_gc_impl_live_allocations+=1;
  std_gc_impl_live_alloc_bytes+=total_size;
  return ((void *)(header + 1));
}

void std_gc_collect(void) {
  if (!(((bool)std_gc_impl_stack_bottom))) {
    std_panic("collect called before init");
  }
  for (std_gc_impl_Header *header = std_gc_impl_alloc_list; ((bool)header); header=header->next) {
    if (header->global) {
      std_gc_impl_mark_object(header);
    }
  }
  void *dummy = NULL;
  void *stack_top = &dummy;
  void *start = stack_top;
  void *end = std_gc_impl_stack_bottom;
  if (stack_top >= end) {
    start=std_gc_impl_stack_bottom;
    end=stack_top;
  }
  std_gc_impl_mark_range(start, end);
  std_gc_impl_Header *header = std_gc_impl_alloc_list;
  while (((bool)header)) {
    std_gc_impl_Header *next = header->next;
    if (!(header->marked) && !(header->global)) {
      if (((bool)header->prev)) {
        header->prev->next=header->next;
      } else {
        std_gc_impl_alloc_list=header->next;
      }
      if (((bool)header->next)) {
        header->next->prev=header->prev;
      }
      std_gc_impl_live_allocations-=1;
      std_gc_impl_live_alloc_bytes-=(header->size + ((u32)sizeof(std_gc_impl_Header)));
      std_gc_impl_freed_allocations+=1;
      std_gc_impl_freed_alloc_bytes+=(header->size + ((u32)sizeof(std_gc_impl_Header)));
      free(header);
    } else {
      header->marked=false;
    }
    header=next;
  }
}

void *std_gc_impl__alloc_fn(void *_, u32 size) {
  return std_gc_alloc(size);
}

void *std_gc_impl__realloc_fn(void *_, void *ptr, u32 old_size, u32 size) {
  void *new_ptr = std_gc_alloc(size);
  u32 num_copy = u32_min(old_size, size);
  memcpy(new_ptr, ptr, num_copy);
  return new_ptr;
}

void std_gc_impl__free_fn(void *_, void *ptr) {
}

void std_gc_impl_mark_range(void *start, void *end) {
  u64 align = ((u64)((u32)sizeof(void *)));
  u64 ustart = (((((u64)start) + align) - ((u64)1)) & ~(align - ((u64)1)));
  u64 uend = (((u64)end) & ~(align - ((u64)1)));
  for (u64 ptr = ustart; ptr < uend; ptr+=align) {
    void *potential_ptr = (*((void **)ptr));
    for (std_gc_impl_Header *header = std_gc_impl_alloc_list; ((bool)header); header=header->next) {
      void *obj_start = ((void *)(header + 1));
      void *obj_end = ((void *)(((char *)obj_start) + header->size));
      if ((obj_start <= potential_ptr) && (potential_ptr < obj_end)) {
        std_gc_impl_mark_object(header);
      }
    }
  }
}

void std_gc_impl_mark_object(std_gc_impl_Header *header) {
  if (header->marked) {
    return;
  }
  header->marked=true;
  void *start = ((void *)(header + 1));
  void *end = ((void *)(((char *)start) + header->size));
  std_gc_impl_mark_range(start, end);
}

std_image_Image *std_image_Image_new(u32 width, u32 height) {
  std_image_Image *img = std_mem_alloc__1(1);
  (*img)=(std_image_Image){.width=width, .height=height, .data=std_mem_alloc__2((width * height))};
  return img;
}

std_image_Color std_image_Image_get(std_image_Image *this, u32 x, u32 y) {
  return this->data[((y * this->width) + x)];}

void std_image_Image_set(std_image_Image *this, u32 x, u32 y, std_image_Color col) {
  this->data[((y * this->width) + x)]=col;
}

std_image_Image *std_image_Image_load(char *filename) {
  std_buffer_Buffer data = std_fs_read_file(filename);
  std_image_Image *image = ((std_image_Image *)NULL);
  if (str_ends_with(filename, ".ppm")) {
    image=std_image_ppm_decode(&data);
  } else if (str_ends_with(filename, ".qoi")) {
    image=std_image_qoi_decode(&data);
  } else if (str_ends_with(filename, ".png")) {
    image=std_image_png_decode(&data);
  } else {
    if(!(false)) { ae_assert_fail("/home/mindful-dev/ocen/std/image/mod.oc:71:16: Assertion failed: `false`", std_format("Unknown file format for image: $%s", filename)); exit(1); }
  }
  if(!(((bool)image))) { ae_assert_fail("/home/mindful-dev/ocen/std/image/mod.oc:74:12: Assertion failed: `image?`", std_format("Failed to load image: $%s", filename)); }
  std_buffer_Buffer_free(&data);
  return image;
}

f32 std_image_interp(f32 t, f32 a, f32 b) {
  return (a * (1.000000f - t)) + (b * t);
}

f32 std_image_bilinear_interp(f32 t0, f32 t1, f32 a, f32 b, f32 c, f32 d) {
  return std_image_interp(t1, std_image_interp(t0, a, b), std_image_interp(t0, c, d));
}

std_image_Image *std_image_ppm_decode(std_buffer_Buffer *data) {
  std_sv_SV data_sv = std_buffer_Buffer_sv((*data));
  if(!(std_sv_SV_eq_str(std_sv_SV_chop_word(&data_sv), "P6"))) { ae_assert_fail("/home/mindful-dev/ocen/std/image/ppm.oc:12:12: Assertion failed: `data_sv.chop_word() == \"P6\"`", "Unsupported PPM format"); }
  u32 width = std_sv_SV_chop_u32(&data_sv);
  u32 height = std_sv_SV_chop_u32(&data_sv);
  if(!(std_sv_SV_chop_u32(&data_sv)==255)) { ae_assert_fail("/home/mindful-dev/ocen/std/image/ppm.oc:15:12: Assertion failed: `data_sv.chop_u32() == 255`", "Unsupported PPM Color depth"); }
  std_image_Image *img = std_image_Image_new(width, height);
  std_buffer_BytesReader io = std_sv_SV_reader(data_sv);
  for (u32 i = 0; i < (width * height); i++) {
    u8 r = std_buffer_BytesReader_read_u8(&io);
    u8 g = std_buffer_BytesReader_read_u8(&io);
    u8 b = std_buffer_BytesReader_read_u8(&io);
    img->data[i]=(std_image_Color){.r=r, .g=g, .b=b};
  }
  return img;
}

u32 std_image_qoi_RGBA_hash(std_image_qoi_RGBA this) {
  u32 r = ((u32)this.r);
  u32 g = ((u32)this.g);
  u32 b = ((u32)this.b);
  u32 a = ((u32)this.a);
  return ((((r * 3) + (g * 5)) + (b * 7)) + (a * 11)) % 64;
}

std_image_qoi_QOIDecoder std_image_qoi_QOIDecoder_make(std_buffer_Buffer *data) {
  std_image_qoi_QOIDecoder decoder = {0};
  memset(&decoder, ((u8)0), ((u32)sizeof(std_image_qoi_QOIDecoder)));
  decoder.io=std_buffer_Buffer_reader((*data));
  decoder.prev=(std_image_qoi_RGBA){.r=((u8)0), .g=((u8)0), .b=((u8)0), .a=((u8)255)};
  return decoder;
}

std_image_Image *std_image_qoi_QOIDecoder_decode(std_image_qoi_QOIDecoder *this) {
  u32 magic = std_buffer_BytesReader_read_u32(&this->io, std_Endian_Little);
  if(!(magic==1903126886)) { ae_assert_fail("/home/mindful-dev/ocen/std/image/qoi.oc:49:12: Assertion failed: `magic == 0x716f6966`", "Invalid magic number"); }
  this->width=std_buffer_BytesReader_read_u32(&this->io, std_Endian_Little);
  this->height=std_buffer_BytesReader_read_u32(&this->io, std_Endian_Little);
  this->channels=std_buffer_BytesReader_read_u8(&this->io);
  this->colorspace=std_buffer_BytesReader_read_u8(&this->io);
  if (this->channels==((u8)4)) {
    printf("WARNING: QOI decoder does not support alpha. Ignoring alpha channel.\n");
  }
  this->img=std_image_Image_new(this->width, this->height);
  std_image_qoi_QOIDecoder_decode_pixels(this);
  return this->img;
}

void std_image_qoi_QOIDecoder_handle_pixel(std_image_qoi_QOIDecoder *this, std_image_qoi_RGBA pix) {
  u32 hash = std_image_qoi_RGBA_hash(pix);
  std_image_qoi_RGBA seen = this->seen[hash];
  this->seen[hash]=pix;
  this->prev=pix;
  this->img->data[this->pixels_done]=(std_image_Color){.r=pix.r, .g=pix.g, .b=pix.b};
  this->pixels_done+=1;
}

void std_image_qoi_QOIDecoder_decode_pixels(std_image_qoi_QOIDecoder *this) {
  while (this->pixels_done < (this->width * this->height)) {
    u8 b = std_buffer_BytesReader_read_u8(&this->io);
    if (b==((u8)254)) {
      std_image_qoi_QOIDecoder_decode_op_rgb(this);
    } else if (b==((u8)255)) {
      std_image_qoi_QOIDecoder_decode_op_rgba(this);
    } else if ((b >> ((u8)6))==((u8)0)) {
      std_image_qoi_QOIDecoder_decode_op_index(this, b);
    } else if ((b >> ((u8)6))==((u8)1)) {
      std_image_qoi_QOIDecoder_decode_op_diff(this, b);
    } else if ((b >> ((u8)6))==((u8)2)) {
      std_image_qoi_QOIDecoder_decode_op_luma(this, b);
    } else if ((b >> ((u8)6))==((u8)3)) {
      std_image_qoi_QOIDecoder_decode_op_run(this, b);
    } else {
      if(!(false)) { ae_assert_fail("/home/mindful-dev/ocen/std/image/qoi.oc:99:20: Assertion failed: `false`", "Invalid opcode"); exit(1); }
    }
  }
}

void std_image_qoi_QOIDecoder_decode_op_rgb(std_image_qoi_QOIDecoder *this) {
  u8 r = std_buffer_BytesReader_read_u8(&this->io);
  u8 g = std_buffer_BytesReader_read_u8(&this->io);
  u8 b = std_buffer_BytesReader_read_u8(&this->io);
  std_image_qoi_RGBA pixel = (std_image_qoi_RGBA){.r=r, .g=g, .b=b, .a=((u8)255)};
  std_image_qoi_QOIDecoder_handle_pixel(this, pixel);
}

void std_image_qoi_QOIDecoder_decode_op_rgba(std_image_qoi_QOIDecoder *this) {
  printf("QOI_OP_RGBA""\n");
  u8 r = std_buffer_BytesReader_read_u8(&this->io);
  u8 g = std_buffer_BytesReader_read_u8(&this->io);
  u8 b = std_buffer_BytesReader_read_u8(&this->io);
  u8 a = std_buffer_BytesReader_read_u8(&this->io);
  std_image_qoi_RGBA pixel = (std_image_qoi_RGBA){.r=r, .g=g, .b=b, .a=a};
  std_image_qoi_QOIDecoder_handle_pixel(this, pixel);
}

void std_image_qoi_QOIDecoder_decode_op_luma(std_image_qoi_QOIDecoder *this, u8 first) {
  u8 second = std_buffer_BytesReader_read_u8(&this->io);
  u8 dg = ((u8)((first & ((u8)63)) - ((u8)32)));
  u8 dr_dg = ((u8)((second >> ((u8)4)) - ((u8)8)));
  u8 db_dg = ((u8)((second & ((u8)15)) - ((u8)8)));
  u8 dr = (dg + dr_dg);
  u8 db = (dg + db_dg);
  std_image_qoi_RGBA pixel = (std_image_qoi_RGBA){.r=(this->prev.r + dr), .g=(this->prev.g + dg), .b=(this->prev.b + db), .a=this->prev.a};
  std_image_qoi_QOIDecoder_handle_pixel(this, pixel);
}

void std_image_qoi_QOIDecoder_decode_op_index(std_image_qoi_QOIDecoder *this, u8 first) {
  u8 index = (first & ((u8)63));
  std_image_qoi_RGBA pixel = this->seen[index];
  std_image_qoi_QOIDecoder_handle_pixel(this, pixel);
}

void std_image_qoi_QOIDecoder_decode_op_diff(std_image_qoi_QOIDecoder *this, u8 first) {
  u8 r = (((first >> ((u8)4)) & ((u8)3)) - ((u8)2));
  u8 g = (((first >> ((u8)2)) & ((u8)3)) - ((u8)2));
  u8 b = (((first >> ((u8)0)) & ((u8)3)) - ((u8)2));
  std_image_qoi_RGBA pixel = (std_image_qoi_RGBA){.r=(this->prev.r + ((u8)r)), .g=(this->prev.g + ((u8)g)), .b=(this->prev.b + ((u8)b)), .a=this->prev.a};
  std_image_qoi_QOIDecoder_handle_pixel(this, pixel);
}

void std_image_qoi_QOIDecoder_decode_op_run(std_image_qoi_QOIDecoder *this, u8 first) {
  u32 run = (((u32)(first & ((u8)63))) + 1);
  for (u32 i = 0; i < run; i++) {
    std_image_qoi_QOIDecoder_handle_pixel(this, this->prev);
  }
}

std_image_Image *std_image_qoi_decode(std_buffer_Buffer *data) {
  std_image_qoi_QOIDecoder decoder = std_image_qoi_QOIDecoder_make(data);
  return std_image_qoi_QOIDecoder_decode(&decoder);
}

std_image_png_Chunk std_image_png_Chunk_parse(std_buffer_BytesReader *io) {
  u32 length = std_buffer_BytesReader_read_u32(io, std_Endian_Big);
  std_sv_SV type = std_buffer_BytesReader_read_bytes_sv(io, 4);
  std_sv_SV data_sv = std_buffer_BytesReader_read_bytes_sv(io, length);
  u32 crc = std_buffer_BytesReader_read_u32(io, std_Endian_Big);
  return (std_image_png_Chunk){.type=type, .data=std_buffer_Buffer_from_sized_str(data_sv.data, data_sv.len), .is_critical=char_is_upper(std_sv_SV_at(type, 0)), .is_private=char_is_upper(std_sv_SV_at(type, 1))};
}

u8 std_image_png_paeth_predictor(u8 ua, u8 ub, u8 uc) {
  i32 a = ((i32)((u32)ua));
  i32 b = ((i32)((u32)ub));
  i32 c = ((i32)((u32)uc));
  i32 p = ((a + b) - c);
  i32 pa = i32_abs((p - a));
  i32 pb = i32_abs((p - b));
  i32 pc = i32_abs((p - c));
  return ({u8 __yv_8;
    if ((pa <= pb) && (pa <= pc)) {
      __yv_8 = ua;
      goto _l___yv_8;
    } else if (pb <= pc) {
      __yv_8 = ub;
      goto _l___yv_8;
    } else {
      __yv_8 = uc;
      goto _l___yv_8;
    }

_l___yv_8:
  __yv_8;});
}

void std_image_png_PNG_decode_scanline(std_image_png_PNG *this, std_buffer_Buffer *out, u32 scanline, std_sv_SV sv) {
  if(!(sv.len==((this->width * this->S) + 1))) { ae_assert_fail("/home/mindful-dev/ocen/std/image/png.oc:114:12: Assertion failed: `sv.len == .width * .S + 1`", "Invalid scanline length"); }
  u32 filter = ((u32)std_sv_SV_at(std_sv_SV_chop_left(&sv, 1), 0));
  u8 *line = ((u8 *)sv.data);
  u32 size = ((u32)sv.len);
  u32 cur_scanline_idx = out->size;
  u32 prev_scanline_idx = (cur_scanline_idx - (this->width * this->S));
  switch (filter) {
    case 0: {
      std_buffer_Buffer_write_bytes(out, line, size);
    } break;
    case 1: {
      for (u32 i = 0; i < sv.len; i++) {
        u8 x = line[i];
        u8 a = ((i >= this->S) ? out->data[((cur_scanline_idx + i) - this->S)] : ((u8)0));
        std_buffer_Buffer_write_u8(out, (x + a));
      }
    } break;
    case 2: {
      for (u32 i = 0; i < sv.len; i++) {
        u8 x = line[i];
        u8 b = ((scanline > 0) ? out->data[(prev_scanline_idx + i)] : ((u8)0));
        std_buffer_Buffer_write_u8(out, (x + b));
      }
    } break;
    case 3: {
      for (u32 i = 0; i < sv.len; i++) {
        u8 x = line[i];
        u32 a = ((i >= this->S) ? ((u32)out->data[((cur_scanline_idx + i) - this->S)]) : 0);
        u32 b = ((scanline > 0) ? ((u32)out->data[(prev_scanline_idx + i)]) : 0);
        std_buffer_Buffer_write_u8(out, (x + ((u8)((a + b) / 2))));
      }
    } break;
    case 4: {
      for (u32 i = 0; i < sv.len; i++) {
        u8 x = line[i];
        u8 a = ((i >= this->S) ? out->data[((cur_scanline_idx + i) - this->S)] : ((u8)0));
        u8 b = ((scanline > 0) ? out->data[(prev_scanline_idx + i)] : ((u8)0));
        u8 c = (((scanline > 0) && (i >= this->S)) ? out->data[((prev_scanline_idx + i) - this->S)] : ((u8)0));
        std_buffer_Buffer_write_u8(out, (x + std_image_png_paeth_predictor(a, b, c)));
      }
    } break;
    default: std_panic(std_format("Unsupported filter %u", filter)); break;
  }
}

std_image_Image *std_image_png_decode(std_buffer_Buffer *data) {
  std_buffer_BytesReader io = std_buffer_Buffer_reader((*data));
  std_sv_SV header = std_buffer_BytesReader_read_bytes_sv(&io, 8);
  if (!(std_sv_SV_eq_str(header, "\x89PNG\r\n\x1a\n"))) {
    printf("Not a PNG file""\n");
    exit(1);
  }
  std_image_png_PNG png = {0};
  std_buffer_Buffer datastream = std_buffer_Buffer_make(16);
  std_buffer_Buffer out = std_buffer_Buffer_make(16);
  while (!(std_buffer_BytesReader_is_empty(&io))) {
    std_image_png_Chunk chunk = std_image_png_Chunk_parse(&io);
    {
      std_sv_SV __match_var_9 = chunk.type;
      if (std_sv_SV_eq_str(__match_var_9, "IHDR")) {
        std_buffer_BytesReader io = std_buffer_Buffer_reader(chunk.data);
        png.width=std_buffer_BytesReader_read_u32(&io, std_Endian_Big);
        png.height=std_buffer_BytesReader_read_u32(&io, std_Endian_Big);
        png.bit_depth=std_buffer_BytesReader_read_u8(&io);
        png.color_type=((int)std_buffer_BytesReader_read_u8(&io));
        u8 compression_method = std_buffer_BytesReader_read_u8(&io);
        u8 filter_method = std_buffer_BytesReader_read_u8(&io);
        if(!(compression_method==((u8)0))) { ae_assert_fail("/home/mindful-dev/ocen/std/image/png.oc:245:24: Assertion failed: `compression_method == 0`", "Unsupported compression method"); }
        if(!(filter_method==((u8)0))) { ae_assert_fail("/home/mindful-dev/ocen/std/image/png.oc:246:24: Assertion failed: `filter_method == 0`", "Unsupported filter method"); }
        png.interlace_method=((int)std_buffer_BytesReader_read_u8(&io));
        if(!(png.bit_depth==((u8)8))) { ae_assert_fail("/home/mindful-dev/ocen/std/image/png.oc:251:24: Assertion failed: `png.bit_depth == 8`", "Unsupported bit depth"); }
        if(!(png.interlace_method==0)) { ae_assert_fail("/home/mindful-dev/ocen/std/image/png.oc:252:24: Assertion failed: `png.interlace_method == None`", "Unsupported interlace method"); }
        png.S=({u32 __yv_10;
switch ((png.color_type)) {
            case 2:
            m_11_0:
              {
                __yv_10 = 3;
                goto _l___yv_10;
              } break;
            case 6:
            m_11_1:
              {
                __yv_10 = 4;
                goto _l___yv_10;
              } break;
            default:
              {
                std_panic(std_format("Unsupported color type %s", std_image_png_ColorType_dbg(png.color_type)));
                goto _l___yv_10;
              } break;
          }
_l___yv_10:
        __yv_10;});
      } else if (std_sv_SV_eq_str(__match_var_9, "IDAT")) {
        std_buffer_Buffer_write_buf(&datastream, &chunk.data);
      } else if (std_sv_SV_eq_str(__match_var_9, "IEND")) {
        std_buffer_Buffer decompressed = std_zlib_decompress(datastream, NULL);
        std_buffer_Buffer_free(&datastream);
        std_buffer_Buffer_resize_if_necessary(&out, (((png.width * png.height) * png.S) + 1));
        std_buffer_BytesReader io = std_buffer_Buffer_reader(decompressed);
        for (u32 h = 0; h < png.height; h++) {
          std_sv_SV scanline = std_buffer_BytesReader_read_bytes_sv(&io, ((png.width * png.S) + 1));
          std_image_png_PNG_decode_scanline(&png, &out, h, scanline);
        }
        std_buffer_Buffer_free(&decompressed);
      } else  {
        if (!(chunk.is_critical)) {
          continue;
        }
        std_panic(std_format("Unsupported critical chunk %.*s", (chunk.type).len, (chunk.type).data));
      }
    }
  }
  std_image_Image *img = std_image_Image_new(png.width, png.height);
  for (u32 i = 0; i < (png.width * png.height); i++) {
    u32 idx = (i * png.S);
    u8 r = std_buffer_Buffer_get_byte_at(out, (idx + 0));
    u8 g = std_buffer_Buffer_get_byte_at(out, (idx + 1));
    u8 b = std_buffer_Buffer_get_byte_at(out, (idx + 2));
    img->data[i]=(std_image_Color){.r=r, .g=g, .b=b};
  }
  std_buffer_Buffer_free(&out);
  return img;
}

std_buffer_Buffer std_buffer_Buffer_make(u32 capacity) {
  return (std_buffer_Buffer){.data=std_mem_alloc__3(capacity), .size=0, .capacity=capacity};
}

std_buffer_Buffer std_buffer_Buffer_from_sized_str(char *s, u32 size) {
  return (std_buffer_Buffer){.data=((u8 *)s), .size=((u32)size), .capacity=((u32)size)};
}

void std_buffer_Buffer_resize_if_necessary(std_buffer_Buffer *this, u32 new_size) {
  if ((new_size + 1) >= this->capacity) {
    u32 new_capacity = u32_max(((this->capacity * 3) / 2), (new_size + 1));
    this->data=std_mem_realloc__0(this->data, this->capacity, new_capacity);
    memset((this->data + this->capacity), ((u8)0), (new_capacity - this->capacity));
    this->capacity=((u32)new_capacity);
    if(!(((bool)this->data))) { ae_assert_fail("/home/mindful-dev/ocen/std/buffer.oc:65:16: Assertion failed: `.data?`", "Out of memory!"); }
  }
}

u8 std_buffer_Buffer_get_byte_at(std_buffer_Buffer this, u32 index) {
  if(!(index < this.size)) { ae_assert_fail("/home/mindful-dev/ocen/std/buffer.oc:94:12: Assertion failed: `index < .size`", "Index out of bounds"); }
  return this.data[index];
}

void std_buffer_Buffer_write_buf(std_buffer_Buffer *this, std_buffer_Buffer *buf) {
  std_buffer_Buffer_resize_if_necessary(this, (this->size + buf->size));
  memcpy((this->data + this->size), buf->data, buf->size);
  this->size+=buf->size;
}

void std_buffer_Buffer_write_bytes(std_buffer_Buffer *this, void *bytes, u32 size) {
  std_buffer_Buffer_resize_if_necessary(this, (this->size + size));
  memcpy((this->data + this->size), bytes, size);
  this->size+=size;
}

void std_buffer_Buffer_write_u8(std_buffer_Buffer *this, u8 value) {
  std_buffer_Buffer_resize_if_necessary(this, (this->size + 1));
  this->data[this->size]=value;
  this->size+=1;
}

std_buffer_BytesReader std_buffer_Buffer_reader(std_buffer_Buffer this) {
  return std_buffer_BytesReader_make(this.data, this.size);}

std_sv_SV std_buffer_Buffer_sv(std_buffer_Buffer this) {
  return (std_sv_SV){.data=((char *)this.data), .len=this.size};}

void std_buffer_Buffer_free(std_buffer_Buffer *this) {
  std_mem_free(this->data);
}

std_buffer_BytesReader std_buffer_BytesReader_make(u8 *data, u32 size) {
  return (std_buffer_BytesReader){.data=data, .size=size, .index=0};
}

u32 std_buffer_BytesReader_read_u32(std_buffer_BytesReader *this, std_Endian endian) {
  u32 value = 0;
  for (u32 i = 0; i < 4; i+=1) {
    u32 shift = (endian==std_Endian_Big ? i : (3 - i));
    value=(value | (((u32)this->data[(this->index + i)]) << (24 - (shift * 8))));
  }
  this->index+=4;
  return value;
}

u8 std_buffer_BytesReader_read_u8(std_buffer_BytesReader *this) {
  u8 value = this->data[this->index];
  this->index+=1;
  return value;
}

std_sv_SV std_buffer_BytesReader_read_bytes_sv(std_buffer_BytesReader *this, u32 count) {
  std_sv_SV sv = (std_sv_SV){.data=((char *)(this->data + this->index)), .len=count};
  this->index+=count;
  return sv;
}

bool std_buffer_BytesReader_is_empty(std_buffer_BytesReader *this) {
  return (this->index >= this->size);}

i8 f32_compare(f32 this, f32 b) {
  return (((i8)(this > b)) - ((i8)(this < b)));}

std_buffer_Buffer std_fs_read_file(char *path) {
  FILE *file = fopen(path, "r");
  if (!(((bool)file))) {
    std_panic(std_format("[-] Failed to open file: %s: %s", path, std_libc_errno_get_err()));
  }
  fseek(file, ((i64)0), SEEK_END);
  u32 size = ((u32)ftell(file));
  fseek(file, ((i64)0), SEEK_SET);
  std_buffer_Buffer data = std_buffer_Buffer_make((size + 1));
  i32 read = fread(data.data, 1, size, file);
  if (((u32)read) != size) {
    std_panic(std_format("[-] Failed to read from file: %s", path));
  }
  fclose(file);
  data.size=((u32)size);
  data.data[size]=((u8)0);
  return data;
}

std_vec_Vec2__1 std_vec_Vec2__1_add(std_vec_Vec2__1 this, std_vec_Vec2__1 other) {
  return (std_vec_Vec2__1){.x=(this.x + other.x), .y=(this.y + other.y)};}

std_vec_Vec2__5 std_vec_Vec2__1_to_u32(std_vec_Vec2__1 this) {
  return (std_vec_Vec2__5){.x=((u32)this.x), .y=((u32)this.y)};}

std_vec_Vec2__1 std_vec_Vec2__1_mults(std_vec_Vec2__1 this, f32 val) {
  return (std_vec_Vec2__1){.x=(this.x * val), .y=(this.y * val)};}

std_vec_Vec3__0 std_vec_Vec3__0_sub(std_vec_Vec3__0 this, std_vec_Vec3__0 other) {
  return (std_vec_Vec3__0){.x=(this.x - other.x), .y=(this.y - other.y), .z=(this.z - other.z)};}

std_vec_Vec3__0 std_vec_Vec3__0_normalized(std_vec_Vec3__0 this) {
  f32 len = std_vec_Vec3__0_length(this);
  return (std_vec_Vec3__0){.x=(((f32)this.x) / len), .y=(((f32)this.y) / len), .z=(((f32)this.z) / len)};
}

std_vec_Vec3__0 std_vec_Vec3__0_multrs(f32 val, std_vec_Vec3__0 this) {
  return (std_vec_Vec3__0){.x=(val * this.x), .y=(val * this.y), .z=(val * this.z)};}

std_vec_Vec3__0 std_vec_Vec3__0_add(std_vec_Vec3__0 this, std_vec_Vec3__0 other) {
  return (std_vec_Vec3__0){.x=(this.x + other.x), .y=(this.y + other.y), .z=(this.z + other.z)};}

f32 std_vec_Vec3__0_length_sq(std_vec_Vec3__0 this) {
  return (((this.x * this.x) + (this.y * this.y)) + (this.z * this.z));}

std_vec_Vec3__0 std_vec_Vec3__0_mult(std_vec_Vec3__0 this, std_vec_Vec3__0 other) {
  return (std_vec_Vec3__0){.x=(this.x * other.x), .y=(this.y * other.y), .z=(this.z * other.z)};}

std_vec_Vec3__0 std_vec_Vec3__0_reflect(std_vec_Vec3__0 this, std_vec_Vec3__0 normal) {
  return std_vec_Vec3__0_sub(this, std_vec_Vec3__0_mults(normal, (((f32)2) * std_vec_Vec3__0_dot(this, normal))));}

std_vec_Vec3__0 std_vec_Vec3__0_divs(std_vec_Vec3__0 this, f32 val) {
  return (std_vec_Vec3__0){.x=(this.x / val), .y=(this.y / val), .z=(this.z / val)};}

std_vec_Vec3__0 std_vec_Vec3__0_subs(std_vec_Vec3__0 this, f32 val) {
  return (std_vec_Vec3__0){.x=(this.x - val), .y=(this.y - val), .z=(this.z - val)};}

std_vec_Vec3__0 std_vec_Vec3__0_mults(std_vec_Vec3__0 this, f32 val) {
  return (std_vec_Vec3__0){.x=(this.x * val), .y=(this.y * val), .z=(this.z * val)};}

f32 std_vec_Vec3__0_length(std_vec_Vec3__0 this) {
  return sqrtf(((f32)(((this.x * this.x) + (this.y * this.y)) + (this.z * this.z))));}

f32 std_vec_Vec3__0_dot(std_vec_Vec3__0 this, std_vec_Vec3__0 other) {
  return (((this.x * other.x) + (this.y * other.y)) + (this.z * other.z));}

f32 std_vec_Vec3__0_index(std_vec_Vec3__0 this, u32 idx) {
  return ((f32 *)&this)[idx];}

std_vec_Vec3__0 std_vec_Vec3__0_cross(std_vec_Vec3__0 this, std_vec_Vec3__0 other) {
  return (std_vec_Vec3__0){.x=((this.y * other.z) - (this.z * other.y)), .y=((this.z * other.x) - (this.x * other.z)), .z=((this.x * other.y) - (this.y * other.x))};
}

std_vec_Vec3__0 std_vec_Vec3__0_divrs(f32 val, std_vec_Vec3__0 this) {
  return (std_vec_Vec3__0){.x=(val / this.x), .y=(val / this.y), .z=(val / this.z)};}

f32 f32_inf(void) {
  return ((f32)INFINITY);}

f32 f32_min(f32 this, f32 b) {
  return ((this < b) ? this : b);}

f32 f32_max(f32 this, f32 b) {
  return ((this > b) ? this : b);}

f32 f32_clamp(f32 this, f32 min, f32 max) {
  return f32_max(f32_min(this, max), min);}

f32 f32_clamp01(f32 this) {
  return f32_clamp(this, 0.000000f, 1.000000f);}

i32 i32_abs(i32 this) {
  return ((this < 0) ? -this : this);}

std_video_renderer_VideoRenderer *std_video_renderer_VideoRenderer_create(std_video_renderer_VideoRendererType type, u32 width, u32 height, u32 fps, char *out_name, bool verbose) {
  std_video_renderer_VideoRenderer *vr = std_mem_alloc__4(1);
  vr->type=type;
switch ((type)) {
    case std_video_renderer_VideoRendererType_FFMPEG:
    m_12_0:
      {
        vr->u.ffmpeg=std_video_renderer_ffmpeg_FFMPEGContext_create(width, height, fps, out_name, verbose);
      } break;
    case std_video_renderer_VideoRendererType_SDL:
    m_12_1:
      {
        vr->u.sdl=std_video_renderer_sdl_SDLContext_create(width, height, fps);
      } break;
  }  return vr;
}

void std_video_renderer_VideoRenderer_send_frame(std_video_renderer_VideoRenderer *this, std_image_Image *img) {
switch ((this->type)) {
    case std_video_renderer_VideoRendererType_FFMPEG:
    m_13_0:
      {
        std_video_renderer_ffmpeg_FFMPEGContext_send_frame(this->u.ffmpeg, img);
      } break;
    case std_video_renderer_VideoRendererType_SDL:
    m_13_1:
      {
        std_video_renderer_sdl_SDLContext_send_frame(this->u.sdl, img);
      } break;
  }}

std_video_renderer_ffmpeg_FFMPEGContext *std_video_renderer_ffmpeg_FFMPEGContext_create(u32 width, u32 height, u32 fps, char *out_name, bool verbose) {
  i32 pipefd[2] = {0};
  if (pipe(pipefd) < 0) {
    printf("FFMPEG: Could not create a pipe\n");
    return NULL;
  }
  i32 child = fork();
  if (child < 0) {
    printf("FFMPEG: Could not fork\n");
    return NULL;
  }
  if (child==0) {
    if (dup2(pipefd[std_video_renderer_ffmpeg_READ_END], STDIN_FILENO) < 0) {
      printf("FFMPEG CHILD: Could not dup2\n");
      exit(1);
    }
    close(pipefd[std_video_renderer_ffmpeg_WRITE_END]);
    std_vector_Vector__2 *args = std_vector_Vector__2_new(16);
    std_vector_Vector__2_push(args, "ffmpeg");
    if (verbose) {
      std_vector_Vector__2_push(args, "-loglevel");
      std_vector_Vector__2_push(args, "verbose");
    }
    std_vector_Vector__2_push(args, "-y");
    std_vector_Vector__2_push(args, "-f");
    std_vector_Vector__2_push(args, "rawvideo");
    std_vector_Vector__2_push(args, "-pix_fmt");
    std_vector_Vector__2_push(args, "rgba");
    std_vector_Vector__2_push(args, "-s");
    std_vector_Vector__2_push(args, std_format("%ux%u", width, height));
    std_vector_Vector__2_push(args, "-framerate");
    std_vector_Vector__2_push(args, std_format("%u", fps));
    std_vector_Vector__2_push(args, "-i");
    std_vector_Vector__2_push(args, "-");
    std_vector_Vector__2_push(args, "-c:v");
    std_vector_Vector__2_push(args, "libx264");
    std_vector_Vector__2_push(args, "-vb");
    std_vector_Vector__2_push(args, "2500k");
    std_vector_Vector__2_push(args, "-c:a");
    std_vector_Vector__2_push(args, "aac");
    std_vector_Vector__2_push(args, "-ab");
    std_vector_Vector__2_push(args, "200k");
    std_vector_Vector__2_push(args, "-pix_fmt");
    std_vector_Vector__2_push(args, "yuv420p");
    std_vector_Vector__2_push(args, "-r");
    std_vector_Vector__2_push(args, "60");
    std_vector_Vector__2_push(args, out_name);
    std_vector_Vector__2_push(args, NULL);
    i32 ret = execvp("ffmpeg", args->data);
    if (ret < 0) {
      printf("FFMPEG CHILD: Could not execvp\n");
      exit(1);
    }
    if(!(false)) { ae_assert_fail("/home/mindful-dev/ocen/std/video_renderer/ffmpeg.oc:68:16: Assertion failed: `false`", "unreachable"); exit(1); }
  }
  if (close(pipefd[std_video_renderer_ffmpeg_READ_END]) < 0) {
    printf("FFMPEG: Could not close pipefd[READ_END]\n");
  }
  std_video_renderer_ffmpeg_FFMPEGContext *ffmpeg = std_mem_alloc__5(1);
  ffmpeg->pid=child;
  ffmpeg->pipe=pipefd[std_video_renderer_ffmpeg_WRITE_END];
  ffmpeg->width=width;
  ffmpeg->height=height;
  return ffmpeg;
}

bool std_video_renderer_ffmpeg_FFMPEGContext_send_frame(std_video_renderer_ffmpeg_FFMPEGContext *this, std_image_Image *img) {
  u32 *data = std_mem_alloc__6((this->width * img->height));
  u32 x_padding = (this->width - img->width);
  u32 y_padding = (this->height - img->height);
  for (u32 y = 0; y < img->height; ++y) {
    u32 out_x = 0;
    for (u32 x = 0; x < (x_padding / 2); ++x) {
      data[(((y + (y_padding / 2)) * this->width) + out_x)]=0;
      ++out_x;
    }
    for (u32 x = 0; x < img->width; ++x) {
      std_image_Color col = std_image_Image_get(img, x, y);
      u32 c = ((((255 << 24) | (((u32)col.b) << 16)) | (((u32)col.g) << 8)) | ((u32)col.r));
      data[(((y + (y_padding / 2)) * this->width) + out_x)]=c;
      ++out_x;
    }
    for (u32 x = (x_padding / 2); x < x_padding; ++x) {
      data[(((y + (y_padding / 2)) * this->width) + out_x)]=0;
      ++out_x;
    }
  }
  if (write(this->pipe, data, ((this->width * img->height) * 4)) < 0) {
    printf("FFMPEG: Could not write to pipe\n");
    std_mem_free(data);
    return false;
  }
  std_mem_free(data);
  return true;
}

std_video_renderer_sdl_SDLContext *std_video_renderer_sdl_SDLContext_create(u32 width, u32 height, u32 fps) {
  std_video_renderer_sdl_SDLContext *ctx = std_mem_alloc__7(1);
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(((i32)width), ((i32)height), 0, &ctx->window, &ctx->renderer);
  if(!(((bool)ctx->window))) { ae_assert_fail("/home/mindful-dev/ocen/std/video_renderer/sdl.oc:23:12: Assertion failed: `ctx.window?`", "Failed to create window"); }
  if(!(((bool)ctx->renderer))) { ae_assert_fail("/home/mindful-dev/ocen/std/video_renderer/sdl.oc:24:12: Assertion failed: `ctx.renderer?`", "Failed to create renderer"); }
  SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
  SDL_RenderClear(ctx->renderer);
  SDL_RenderPresent(ctx->renderer);
  ctx->orig_width=width;
  ctx->orig_height=height;
  ctx->buffer=SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, ((i32)width), ((i32)height));
  if(!(((bool)ctx->buffer))) { ae_assert_fail("/home/mindful-dev/ocen/std/video_renderer/sdl.oc:38:12: Assertion failed: `ctx.buffer?`", "Failed to create buffer"); }
  ctx->frame_time=(1000 / fps);
  ctx->last_frame=SDL_GetTicks();
  ctx->paused=false;
  return ctx;
}

void std_video_renderer_sdl_SDLContext_finish(std_video_renderer_sdl_SDLContext *this) {
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
  exit(0);
}

void std_video_renderer_sdl_SDLContext_send_frame(std_video_renderer_sdl_SDLContext *this, std_image_Image *img) {
  SDL_Event e = {0};
  bool quit = false;
  bool first = true;
  while ((this->paused || first) && !(quit)) {
    first=false;
    while (SDL_PollEvent(&e)) {
switch ((e.type)) {
        case SDL_QUIT:
        m_14_0:
          {
            printf("[+] Got a quit event in SDL, exiting...""\n");
            quit=true;
          } break;
        case SDL_KEYDOWN:
        m_14_1:
          {
switch ((e.key.keysym.scancode)) {
              case SDL_SCANCODE_Q:
              case SDL_SCANCODE_ESCAPE:
              m_15_0:
                {
                  quit=true;
                } break;
              case SDL_SCANCODE_SPACE:
              m_15_1:
                {
                  this->paused=!(this->paused);
                } break;
              default:
                {
                } break;
            }          } break;
        default:
          {
          } break;
      }    }
  }
  if (quit) {
    std_video_renderer_sdl_SDLContext_finish(this);
  }
  i32 current_tick = SDL_GetTicks();
  i32 elapsed = (current_tick - this->last_frame);
  if (elapsed < ((i32)this->frame_time)) {
    SDL_Delay((((i32)this->frame_time) - elapsed));
  }
  u8 *data;
  i32 i_pitch = 0;
  SDL_LockTexture(this->buffer, NULL, ((void **)&data), &i_pitch);
  if(!(i_pitch > 0)) { ae_assert_fail("/home/mindful-dev/ocen/std/video_renderer/sdl.oc:89:12: Assertion failed: `i_pitch > 0`", NULL); }
  u32 pitch = ((u32)i_pitch);
  u32 x_padding = (this->orig_width - img->width);
  u32 y_padding = (this->orig_height - img->height);
  for (u32 y = 0; y < (y_padding / 2); ++y) {
    u32 off = (y * pitch);
    for (u32 x = 0; x < this->orig_width; ++x) {
      data[(off + 3)]=((u8)255);
      off+=4;
    }
  }
  for (u32 y = 0; y < img->height; ++y) {
    u32 out_x = (x_padding / 2);
    for (u32 x = 0; x < img->width; ++x) {
      std_image_Color col = std_image_Image_get(img, x, y);
      u32 off = (((y + (y_padding / 2)) * pitch) + (out_x * 4));
      data[(off + 0)]=col.r;
      data[(off + 1)]=col.g;
      data[(off + 2)]=col.b;
      data[(off + 3)]=((u8)255);
      ++out_x;
    }
  }
  SDL_UnlockTexture(this->buffer);
  SDL_RenderCopy(this->renderer, this->buffer, NULL, NULL);
  SDL_RenderPresent(this->renderer);
  this->last_frame=SDL_GetTicks();
}

std_buffer_Buffer std_zlib_decompress_bytes(u8 *data, u32 size, u32 *bytes_consumed) {
  z_stream stream = {0};
  stream.avail_in=size;
  stream.next_in=data;
  if (inflateInit(&stream) != Z_OK) {
    std_panic("Failed to initialize zlib stream");
  }
  std_buffer_Buffer res = std_buffer_Buffer_make((size * 2));
  stream.avail_out=res.capacity;
  stream.next_out=res.data;
  bool done = false;
  while (!(done)) {
    if (stream.avail_out==0) {
      u32 new_size = (res.capacity * 2);
      std_buffer_Buffer_resize_if_necessary(&res, new_size);
      stream.avail_out=(new_size - stream.total_out);
      stream.next_out=(res.data + stream.total_out);
    }
    i32 result = inflate(&stream, Z_NO_FLUSH);
    switch (result) {
      case Z_OK: {
      } break;
      case Z_STREAM_END: {
        res.size=stream.total_out;
        done=true;
      } break;
      default: std_panic("zlib: failed to decompress data"); break;
    }
  }
  if (((bool)bytes_consumed)) {
    (*bytes_consumed)=((u32)(stream.next_in - data));
  } else {
    if (((u32)(stream.next_in - data)) != size) {
      std_panic("zlib: not all bytes were consumed, use `bytes_consumed` to get the number of bytes consumed");
    }
  }
  inflateEnd(&stream);
  return res;
}

std_buffer_Buffer std_zlib_decompress(std_buffer_Buffer data, u32 *bytes_consumed) {
  return std_zlib_decompress_bytes(data.data, data.size, bytes_consumed);
}

src_objects_triangle_Triangle std_vector_Vector__0_at(std_vector_Vector__0 *this, u32 i) {
  if(!(i < this->size)) { ae_assert_fail("/home/mindful-dev/ocen/std/vector.oc:122:12: Assertion failed: `i < .size`", "Out of bounds in Vector::at"); }
  return this->data[i];
}

void std_vector_Vector__0_resize(std_vector_Vector__0 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__1(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__0 *std_vector_Vector__0_new(u32 capacity) {
  std_vector_Vector__0 *list = std_mem_alloc__8(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__9(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__0_push(std_vector_Vector__0 *this, src_objects_triangle_Triangle value) {
  if (this->size==this->capacity) {
    std_vector_Vector__0_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

std_vector_Iterator__1 std_vector_Vector__1_iter(std_vector_Vector__1 *this) {
  return std_vector_Iterator__1_make(this);}

src_core_object_Object *std_vector_Iterator__1_cur(std_vector_Iterator__1 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/mindful-dev/ocen/std/vector.oc:168:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::current"); }
  return this->vec->data[this->index];
}

void std_vector_Iterator__1_next(std_vector_Iterator__1 *this) {
  if(!(this->index < this->vec->size)) { ae_assert_fail("/home/mindful-dev/ocen/std/vector.oc:163:12: Assertion failed: `.index < .vec.size`", "Out of bounds in Iterator::next"); }
  this->index+=1;
}

bool std_vector_Iterator__1_has_value(std_vector_Iterator__1 *this) {
  return (this->index < this->vec->size);}

std_vector_Iterator__1 std_vector_Iterator__1_make(std_vector_Vector__1 *vec) {
  return (std_vector_Iterator__1){.vec=vec, .index=0};}

void std_vector_Vector__1_resize(std_vector_Vector__1 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__2(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__1 *std_vector_Vector__1_new(u32 capacity) {
  std_vector_Vector__1 *list = std_mem_alloc__10(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__11(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__1_push(std_vector_Vector__1 *this, src_core_object_Object *value) {
  if (this->size==this->capacity) {
    std_vector_Vector__1_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

void std_vector_Vector__2_resize(std_vector_Vector__2 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__3(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__2 *std_vector_Vector__2_new(u32 capacity) {
  std_vector_Vector__2 *list = std_mem_alloc__12(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__13(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__2_push(std_vector_Vector__2 *this, char *value) {
  if (this->size==this->capacity) {
    std_vector_Vector__2_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

std_vec_Vec3__0 std_vector_Vector__3_at(std_vector_Vector__3 *this, u32 i) {
  if(!(i < this->size)) { ae_assert_fail("/home/mindful-dev/ocen/std/vector.oc:122:12: Assertion failed: `i < .size`", "Out of bounds in Vector::at"); }
  return this->data[i];
}

void std_vector_Vector__3_free(std_vector_Vector__3 *this) {
  std_mem_free(this->data);
  std_mem_free(this);
}

void std_vector_Vector__3_resize(std_vector_Vector__3 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__5(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__3 *std_vector_Vector__3_new(u32 capacity) {
  std_vector_Vector__3 *list = std_mem_alloc__16(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__17(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__3_push(std_vector_Vector__3 *this, std_vec_Vec3__0 value) {
  if (this->size==this->capacity) {
    std_vector_Vector__3_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

std_vec_Vec2__1 std_vector_Vector__4_at(std_vector_Vector__4 *this, u32 i) {
  if(!(i < this->size)) { ae_assert_fail("/home/mindful-dev/ocen/std/vector.oc:122:12: Assertion failed: `i < .size`", "Out of bounds in Vector::at"); }
  return this->data[i];
}

void std_vector_Vector__4_free(std_vector_Vector__4 *this) {
  std_mem_free(this->data);
  std_mem_free(this);
}

void std_vector_Vector__4_resize(std_vector_Vector__4 *this, u32 new_capacity) {
  if (this->capacity >= new_capacity) {
    return;
  }
  this->data=std_mem_realloc__4(this->data, this->capacity, new_capacity);
  this->capacity=new_capacity;
}

std_vector_Vector__4 *std_vector_Vector__4_new(u32 capacity) {
  std_vector_Vector__4 *list = std_mem_alloc__14(1);
  list->capacity=capacity;
  list->data=std_mem_alloc__15(capacity);
  list->size=0;
  return list;
}

void std_vector_Vector__4_push(std_vector_Vector__4 *this, std_vec_Vec2__1 value) {
  if (this->size==this->capacity) {
    std_vector_Vector__4_resize(this, (this->capacity * 2));
  }
  this->data[this->size]=value;
  this->size+=1;
}

void std_random_RandomState_seed(std_random_RandomState *this, u32 s) {
  srand(s);
  this->x=rand();
  this->y=rand();
  this->z=rand();
  this->w=rand();
}

std_random_RandomState std_random_RandomState_make(u32 s) {
  std_random_RandomState rs = {0};
  std_random_RandomState_seed(&rs, s);
  return rs;
}

u32 std_random_randint(std_random_RandomState *state) {
  if (!(((bool)state))) {
    state=&std_random_global_random_state;
  }
  u32 t = (state->x ^ (state->x << 11));
  state->x=state->y;
  state->y=state->z;
  state->z=state->w;
  state->w=((state->w ^ (state->w >> 19)) ^ (t ^ (t >> 8)));
  return state->w;
}

f32 std_random_randf32(std_random_RandomState *state) {
  return (((f32)std_random_randint(state)) / 4294967296.000000f);}

src_objects_triangle_Triangle std_sort_nth_element_by__0(src_objects_triangle_Triangle *data, u32 size, u32 n, _ClosureTy_10 cmp) {
  if (size <= 1) {
    return data[0];
  }
  src_objects_triangle_Triangle pivot = data[(size / 2)];
  u32 i = 0;
  u32 j = (size - 1);
  while (i <= j) {
    while (cmp.fn(cmp._C, data[i], pivot) < ((i8)0)) {
      i+=1;
    }
    while (cmp.fn(cmp._C, data[j], pivot) > ((i8)0)) {
      j-=1;
    }
    if (i <= j) {
      src_objects_triangle_Triangle tmp = data[i];
      data[i]=data[j];
      data[j]=tmp;
      i+=1;
      j-=1;
    }
  }
  if (n < j) {
    return std_sort_nth_element_by__0(data, (j + 1), n, cmp);
  } else if (n >= i) {
    return std_sort_nth_element_by__0((data + i), (size - i), (n - i), cmp);
  } else {
    return pivot;
  }
}

std_vec_Vec3__0 src_utils_utils_get_interpolated(std_image_Image *img, f32 xf, f32 yf) {
  xf=(f32_clamp01(xf) * ((f32)(img->width - 1)));
  yf=(f32_clamp01(yf) * ((f32)(img->height - 1)));
  u32 x_fl = ((u32)xf);
  u32 y_fl = ((u32)yf);
  u32 x_cl = ((xf != ((f32)x_fl)) ? (x_fl + 1) : x_fl);
  u32 y_cl = ((yf != ((f32)y_fl)) ? (y_fl + 1) : y_fl);
  std_image_Color a = std_image_Image_get(img, x_fl, y_fl);
  std_image_Color b = std_image_Image_get(img, x_cl, y_fl);
  std_image_Color c = std_image_Image_get(img, x_fl, y_cl);
  std_image_Color d = std_image_Image_get(img, x_cl, y_cl);
  f32 x_ratio = (xf - ((f32)x_fl));
  f32 y_ratio = (yf - ((f32)y_fl));
  std_vec_Vec3__0 col = (std_vec_Vec3__0){.x=std_image_bilinear_interp(x_ratio, y_ratio, ((f32)a.r), ((f32)b.r), ((f32)c.r), ((f32)d.r)), .y=std_image_bilinear_interp(x_ratio, y_ratio, ((f32)a.g), ((f32)b.g), ((f32)c.g), ((f32)d.g)), .z=std_image_bilinear_interp(x_ratio, y_ratio, ((f32)a.b), ((f32)b.b), ((f32)c.b), ((f32)d.b))};
  return std_vec_Vec3__0_divs(col, 255.000000f);
}

bool src_objects_transformed_Transformed_hit(src_objects_transformed_Transformed *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, src_core_object_Object *parent) {
  src_core_ray_Ray transformed_ray = (src_core_ray_Ray){.pos=src_core_matrix_Matrix_mulv(this->inverse, ray->pos), .dir=src_core_matrix_Matrix_mulv_no_translation(this->inverse, ray->dir)};
  bool did_hit = src_core_object_Object_hit(this->obj, &transformed_ray, rec);
  if (did_hit) {
    rec->pos=src_core_ray_Ray_at((*ray), rec->t);
    rec->norm=std_vec_Vec3__0_normalized(src_core_matrix_Matrix_mulv(src_core_matrix_Matrix_transpose(this->inverse), rec->norm));
    rec->obj=this->obj;
  }
  return did_hit;
}

src_core_object_Object *src_objects_transformed_Transformed_new(src_core_object_Object *obj, src_core_matrix_Matrix transform) {
  return ({src_core_object_Object *_new_16 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_core_object_Object)); *_new_16 = (src_core_object_Object){.tag=src_core_object_Object_Transformed,.texture=(src_core_texture_Texture){.tag=src_core_texture_Texture_Color,.src_core_texture_Texture_Color={(std_vec_Vec3__0){.x=0.800000f, .y=0.700000f, .z=0.600000f}, }}, .mat=src_core_materialtype_MaterialType_Reflective, .src_core_object_Object_Transformed={(src_objects_transformed_Transformed){.obj=obj, .transform=transform, .inverse=src_core_matrix_Matrix_invert(&transform)}, }}; _new_16; });
}

bool src_objects_triangle_Triangle_hit(src_objects_triangle_Triangle *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, src_core_object_Object *parent) {
  std_vec_Vec3__0 e0 = std_vec_Vec3__0_sub(this->p1, this->p0);
  std_vec_Vec3__0 e1 = std_vec_Vec3__0_sub(this->p2, this->p0);
  std_vec_Vec3__0 h = std_vec_Vec3__0_cross(ray->dir, e1);
  f32 a1 = std_vec_Vec3__0_dot(e0, h);
  if (a1==0.000000f) {
    return false;
  }
  f32 f = (1.000000f / a1);
  std_vec_Vec3__0 s = std_vec_Vec3__0_sub(ray->pos, this->p0);
  f32 v = (f * std_vec_Vec3__0_dot(s, h));
  if ((v < 0.000000f) || (v > 1.000000f)) {
    return false;
  }
  std_vec_Vec3__0 q = std_vec_Vec3__0_cross(s, e0);
  f32 w = (f * std_vec_Vec3__0_dot(ray->dir, q));
  if ((w < 0.000000f) || ((v + w) > 1.000000f)) {
    return false;
  }
  f32 t = (f * std_vec_Vec3__0_dot(e1, q));
  if ((t < 0.000100f) || (t > rec->t)) {
    return false;
  }
  f32 u = ((1.000000f - v) - w);
  rec->t=t;
  rec->norm=std_vec_Vec3__0_add(std_vec_Vec3__0_add(std_vec_Vec3__0_multrs(u, this->n0), std_vec_Vec3__0_multrs(v, this->n1)), std_vec_Vec3__0_multrs(w, this->n2));
  rec->pos=src_core_ray_Ray_at((*ray), t);
  rec->uv=std_vec_Vec2__1_add(std_vec_Vec2__1_add(std_vec_Vec2__1_mults(this->t0, u), std_vec_Vec2__1_mults(this->t1, v)), std_vec_Vec2__1_mults(this->t2, w));
  rec->obj=parent;
  return true;
}

src_core_bounds_Bounds src_objects_triangle_Triangle_bounds(src_objects_triangle_Triangle this) {
  src_core_bounds_Bounds bounds = src_core_bounds_Bounds_empty();
  bounds=src_core_bounds_Bounds_add_point(bounds, this.p0);
  bounds=src_core_bounds_Bounds_add_point(bounds, this.p1);
  return src_core_bounds_Bounds_add_point(bounds, this.p2);
}

bool src_objects_sphere_Sphere_hit(src_objects_sphere_Sphere *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, src_core_object_Object *parent) {
  std_vec_Vec3__0 oc = std_vec_Vec3__0_sub(this->pos, ray->pos);
  f32 a = std_vec_Vec3__0_length_sq(ray->dir);
  f32 b = (-2.000000f * std_vec_Vec3__0_dot(ray->dir, oc));
  f32 c = (std_vec_Vec3__0_length_sq(oc) - (this->r * this->r));
  f32 disc = ((b * b) - ((4.000000f * a) * c));
  if (disc < 0.000000f) {
    return false;
  }
  f32 t0 = ((-b - sqrtf(disc)) / (2.000000f * a));
  if (t0 < 0.000000f) {
    t0=((-b + sqrtf(disc)) / (2.000000f * a));
  }
  if (t0 < 0.000000f) {
    return false;
  }
  if (t0 > rec->t) {
    return false;
  }
  rec->t=t0;
  rec->pos=src_core_ray_Ray_at((*ray), t0);
  rec->norm=std_vec_Vec3__0_normalized(std_vec_Vec3__0_sub(rec->pos, this->pos));
  rec->uv.x=(0.500000f + (atan2f(rec->norm.z, rec->norm.x) / -std_math_TAU));
  rec->uv.y=(0.500000f + (asin(rec->norm.y) / M_PI));
  rec->obj=parent;
  return true;
}

bool src_objects_mesh_Mesh_hit(src_objects_mesh_Mesh *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, src_core_object_Object *parent) {
  return src_core_bvh_BVH__0_hit(this->bvh, ray, rec, parent);
}

src_objects_mesh_Mesh src_objects_mesh_Mesh_from_obj(char *filename) {
  std_buffer_Buffer file = std_fs_read_file(filename);
  std_sv_SV sv = std_buffer_Buffer_sv(file);
  std_vector_Vector__3 *vectors = ({
    std_vector_Vector__3 *_vc17 = std_vector_Vector__3_new(8);
    _vc17;});
  std_vector_Vector__3 *normals = ({
    std_vector_Vector__3 *_vc18 = std_vector_Vector__3_new(8);
    _vc18;});
  std_vector_Vector__4 *textures = ({
    std_vector_Vector__4 *_vc19 = std_vector_Vector__4_new(8);
    _vc19;});
  std_vector_Vector__0 *triangles = ({
    std_vector_Vector__0 *_vc20 = std_vector_Vector__0_new(8);
    _vc20;});
  for (std_sv_SVLineIterator _i1 = std_sv_SV_lines(sv); std_sv_SVLineIterator_has_value(&_i1); std_sv_SVLineIterator_next(&_i1)) {
    std_sv_SV line = std_sv_SVLineIterator_cur(&_i1);
    {
      {
        std_sv_SV __match_var_21 = std_sv_SV_chop_word(&line);
        if (std_sv_SV_eq_str(__match_var_21, "v")) {
          std_vector_Vector__3_push(vectors, (std_vec_Vec3__0){.x=std_sv_SV_chop_f32(&line), .y=std_sv_SV_chop_f32(&line), .z=std_sv_SV_chop_f32(&line)});
        } else if (std_sv_SV_eq_str(__match_var_21, "vn")) {
          std_vector_Vector__3_push(normals, (std_vec_Vec3__0){.x=std_sv_SV_chop_f32(&line), .y=std_sv_SV_chop_f32(&line), .z=std_sv_SV_chop_f32(&line)});
        } else if (std_sv_SV_eq_str(__match_var_21, "vt")) {
          std_vector_Vector__4_push(textures, (std_vec_Vec2__1){.x=std_sv_SV_chop_f32(&line), .y=std_sv_SV_chop_f32(&line)});
        } else if (std_sv_SV_eq_str(__match_var_21, "f")) {
          std_sv_SV s0 = std_sv_SV_chop_by_delim(&line, ' ');
          std_vec_Vec3__0 v0 = std_vector_Vector__3_at(vectors, (std_sv_SV_chop_u32(&s0) - 1));
          std_sv_SV_chop_left(&s0, 1);
          std_vec_Vec2__1 t0 = std_vector_Vector__4_at(textures, (std_sv_SV_chop_u32(&s0) - 1));
          std_sv_SV_chop_left(&s0, 1);
          std_vec_Vec3__0 n0 = std_vector_Vector__3_at(normals, (std_sv_SV_chop_u32(&s0) - 1));
          std_sv_SV s1 = std_sv_SV_chop_by_delim(&line, ' ');
          std_vec_Vec3__0 v1 = std_vector_Vector__3_at(vectors, (std_sv_SV_chop_u32(&s1) - 1));
          std_sv_SV_chop_left(&s1, 1);
          std_vec_Vec2__1 t1 = std_vector_Vector__4_at(textures, (std_sv_SV_chop_u32(&s1) - 1));
          std_sv_SV_chop_left(&s1, 1);
          std_vec_Vec3__0 n1 = std_vector_Vector__3_at(normals, (std_sv_SV_chop_u32(&s1) - 1));
          std_sv_SV s2 = std_sv_SV_chop_by_delim(&line, ' ');
          std_vec_Vec3__0 v2 = std_vector_Vector__3_at(vectors, (std_sv_SV_chop_u32(&s2) - 1));
          std_sv_SV_chop_left(&s2, 1);
          std_vec_Vec2__1 t2 = std_vector_Vector__4_at(textures, (std_sv_SV_chop_u32(&s2) - 1));
          std_sv_SV_chop_left(&s2, 1);
          std_vec_Vec3__0 n2 = std_vector_Vector__3_at(normals, (std_sv_SV_chop_u32(&s2) - 1));
          std_vector_Vector__0_push(triangles, (src_objects_triangle_Triangle){.p0=v0, .p1=v1, .p2=v2, .n0=n0, .n1=n1, .n2=n2, .t0=t0, .t1=t1, .t2=t2});
        } else  {
        }
      }
    }
  }
  src_core_bvh_BVH__0 *bvh = src_core_bvh_BVH__0_create(triangles, 0, triangles->size);
  /* defers */
  std_vector_Vector__4_free(textures);
  std_vector_Vector__3_free(normals);
  std_vector_Vector__3_free(vectors);
  std_buffer_Buffer_free(&file);
  return (src_objects_mesh_Mesh){.triangles=triangles, .bvh=bvh};
}

bool src_core_object_Object_hit(src_core_object_Object *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec) {
  bool did_hit = ({bool __yv_22;
    src_core_object_Object _m23 = (*this);
    switch (_m23.tag) {
      {
        src_objects_sphere_Sphere sphere;
        case src_core_object_Object_Sphere:
          sphere = _m23.src_core_object_Object_Sphere.sphere;
          goto m_24_0;
        m_24_0:
          {
            __yv_22 = src_objects_sphere_Sphere_hit(&sphere, ray, rec, this);
            goto _l___yv_22;
          } break;
      }
      {
        src_objects_triangle_Triangle tri;
        case src_core_object_Object_Triangle:
          tri = _m23.src_core_object_Object_Triangle.tri;
          goto m_24_1;
        m_24_1:
          {
            __yv_22 = src_objects_triangle_Triangle_hit(&tri, ray, rec, this);
            goto _l___yv_22;
          } break;
      }
      {
        src_objects_mesh_Mesh mesh;
        case src_core_object_Object_Mesh:
          mesh = _m23.src_core_object_Object_Mesh.mesh;
          goto m_24_2;
        m_24_2:
          {
            __yv_22 = src_objects_mesh_Mesh_hit(&mesh, ray, rec, this);
            goto _l___yv_22;
          } break;
      }
      {
        src_objects_transformed_Transformed trans;
        case src_core_object_Object_Transformed:
          trans = _m23.src_core_object_Object_Transformed.trans;
          goto m_24_3;
        m_24_3:
          {
            __yv_22 = src_objects_transformed_Transformed_hit(&trans, ray, rec, this);
            goto _l___yv_22;
          } break;
      }
    }
_l___yv_22:
  __yv_22;});
  return did_hit;
}

src_core_bounds_Bounds src_core_bounds_Bounds_empty(void) {
  return (src_core_bounds_Bounds){.min=(std_vec_Vec3__0){.x=f32_inf(), .y=f32_inf(), .z=f32_inf()}, .max=(std_vec_Vec3__0){.x=-f32_inf(), .y=-f32_inf(), .z=-f32_inf()}};}

src_core_bounds_Bounds src_core_bounds_Bounds_join(src_core_bounds_Bounds this, src_core_bounds_Bounds other) {
  std_vec_Vec3__0 new_min = (std_vec_Vec3__0){.x=f32_min(this.min.x, other.min.x), .y=f32_min(this.min.y, other.min.y), .z=f32_min(this.min.z, other.min.z)};
  std_vec_Vec3__0 new_max = (std_vec_Vec3__0){.x=f32_max(this.max.x, other.max.x), .y=f32_max(this.max.y, other.max.y), .z=f32_max(this.max.z, other.max.z)};
  return (src_core_bounds_Bounds){.min=new_min, .max=new_max};
}

src_core_bounds_Bounds src_core_bounds_Bounds_add_point(src_core_bounds_Bounds this, std_vec_Vec3__0 vec) {
  std_vec_Vec3__0 new_min = (std_vec_Vec3__0){.x=f32_min(this.min.x, vec.x), .y=f32_min(this.min.y, vec.y), .z=f32_min(this.min.z, vec.z)};
  std_vec_Vec3__0 new_max = (std_vec_Vec3__0){.x=f32_max(this.max.x, vec.x), .y=f32_max(this.max.y, vec.y), .z=f32_max(this.max.z, vec.z)};
  return (src_core_bounds_Bounds){.min=new_min, .max=new_max};
}

void src_core_bounds_Bounds_join_assign(src_core_bounds_Bounds *this, src_core_bounds_Bounds other) {
    (*this)=src_core_bounds_Bounds_join((*this), other);
}

bool src_core_bounds_Bounds_hit(src_core_bounds_Bounds *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, f32 *t1, f32 *t2, std_vec_Vec3__0 inv_d) {
  f32 tmin = -f32_inf();
  f32 tmax = f32_inf();
  {
    f32 tmin_ = ((this->min.x - ray->pos.x) * inv_d.x);
    f32 tmax_ = ((this->max.x - ray->pos.x) * inv_d.x);
    if (tmin_ > tmax_) {
      f32 tmp = tmin_;
      tmin_=tmax_;
      tmax_=tmp;
    }
    if ((tmin > tmax_) || (tmin_ > tmax)) {
      return false;
    }
    if (tmin_ > tmin) {
      tmin=tmin_;
    }
    if (tmax_ < tmax) {
      tmax=tmax_;
    }
  }
  {
    f32 tmin_ = ((this->min.y - ray->pos.y) * inv_d.y);
    f32 tmax_ = ((this->max.y - ray->pos.y) * inv_d.y);
    if (tmin_ > tmax_) {
      f32 tmp = tmin_;
      tmin_=tmax_;
      tmax_=tmp;
    }
    if ((tmin > tmax_) || (tmin_ > tmax)) {
      return false;
    }
    if (tmin_ > tmin) {
      tmin=tmin_;
    }
    if (tmax_ < tmax) {
      tmax=tmax_;
    }
  }
  {
    f32 tmin_ = ((this->min.z - ray->pos.z) * inv_d.z);
    f32 tmax_ = ((this->max.z - ray->pos.z) * inv_d.z);
    if (tmin_ > tmax_) {
      f32 tmp = tmin_;
      tmin_=tmax_;
      tmax_=tmp;
    }
    if ((tmin > tmax_) || (tmin_ > tmax)) {
      return false;
    }
    if (tmin_ > tmin) {
      tmin=tmin_;
    }
    if (tmax_ < tmax) {
      tmax=tmax_;
    }
  }
  if (tmin > rec->t) {
    return false;
  }
  if ((tmin < 0.000100f) && (tmax < 0.000100f)) {
    return false;
  }
  if (tmin < 0.000100f) {
    tmin=0.000000f;
  }
  if (((bool)t1)) {
    (*t1)=tmin;
  }
  if (((bool)t2)) {
    (*t2)=tmax;
  }
  return true;
}

std_vec_Vec3__0 src_core_bounds_Bounds_centroid(src_core_bounds_Bounds this) {
  return std_vec_Vec3__0_divs(std_vec_Vec3__0_add(this.min, this.max), 2.000000f);}

bool src_core_bvh_BVH__0_hit(src_core_bvh_BVH__0 *this, src_core_ray_Ray *ray, src_core_hitrec_HitRec *rec, src_core_object_Object *parent) {
  if (this->is_leaf) {
    return src_objects_triangle_Triangle_hit(&this->obj, ray, rec, parent);
  } else {
    f32 t_l = 0.000000f;
    f32 t_r = 0.000000f;
    bool hit_l = src_core_bounds_Bounds_hit(&this->l->bounds, ray, rec, &t_l, NULL, std_vec_Vec3__0_divrs(1.000000f, ray->dir));
    bool hit_r = src_core_bounds_Bounds_hit(&this->r->bounds, ray, rec, &t_r, NULL, std_vec_Vec3__0_divrs(1.000000f, ray->dir));
    if (!(hit_l) && !(hit_r)) {
      return false;
    }
    if (!(hit_l)) {
      return src_core_bvh_BVH__0_hit(this->r, ray, rec, parent);
    }
    if (!(hit_r)) {
      return src_core_bvh_BVH__0_hit(this->l, ray, rec, parent);
    }
    if (t_l < t_r) {
      bool left = src_core_bvh_BVH__0_hit(this->l, ray, rec, parent);
      bool right = src_core_bvh_BVH__0_hit(this->r, ray, rec, parent);
      return left || right;
    } else {
      bool right = src_core_bvh_BVH__0_hit(this->r, ray, rec, parent);
      bool left = src_core_bvh_BVH__0_hit(this->l, ray, rec, parent);
      return right || left;
    }
  }}

src_core_bvh_BVH__0 *src_core_bvh_BVH__0_create(std_vector_Vector__0 *objects, u32 start, u32 end) {
  if ((end - start)==1) {
    src_objects_triangle_Triangle object = std_vector_Vector__0_at(objects, start);
    src_core_bounds_Bounds bounds = src_objects_triangle_Triangle_bounds(object);
    src_core_bvh_BVH__0 leaf = {0};
    leaf.is_leaf=true;
    leaf.obj=object;
    leaf.bounds=bounds;
    return ({src_core_bvh_BVH__0 *_new_25 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_core_bvh_BVH__0)); *_new_25 = leaf; _new_25; });
  } else {
    src_core_bounds_Bounds bounds = src_core_bounds_Bounds_empty();
    for (u32 i = start; i < end; i+=1) {
      src_core_bounds_Bounds_join_assign(&bounds, src_objects_triangle_Triangle_bounds(std_vector_Vector__0_at(objects, i)));
    }
    std_vec_Vec3__0 box_sizes = std_vec_Vec3__0_sub(bounds.max, bounds.min);
    u32 dim = 0;
    if (std_vec_Vec3__0_index(box_sizes, dim) < std_vec_Vec3__0_index(box_sizes, 1)) {
      dim=1;
    }
    if (std_vec_Vec3__0_index(box_sizes, dim) < std_vec_Vec3__0_index(box_sizes, 2)) {
      dim=2;
    }
    u32 mid = ((start + end) / 2);
    std_sort_nth_element_by__0((objects->data + start), (end - start), mid, ({src_core_bvh_create__Closure_3Ctx *_C26 = alloca(sizeof(src_core_bvh_create__Closure_3Ctx));_C26->dim = &dim;_ClosureTy_10 _ci27 = {._C=_C26, .fn=&src_core_bvh_create__Closure_3};_ci27;}));
    src_core_bvh_BVH__0 *l = src_core_bvh_BVH__0_create(objects, start, mid);
    src_core_bvh_BVH__0 *r = src_core_bvh_BVH__0_create(objects, mid, end);
    src_core_bvh_BVH__0 internal = {0};
    internal.is_leaf=false;
    internal.l=l;
    internal.r=r;
    internal.bounds=bounds;
    return ({src_core_bvh_BVH__0 *_new_28 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_core_bvh_BVH__0)); *_new_28 = internal; _new_28; });
  }
}

std_vec_Vec3__0 src_core_texture_Texture_get(src_core_texture_Texture this, std_vec_Vec2__1 uv) {
  return ({std_vec_Vec3__0 __yv_29;
    src_core_texture_Texture _m30 = this;
    switch (_m30.tag) {
      {
        std_vec_Vec3__0 c;
        case src_core_texture_Texture_Color:
          c = _m30.src_core_texture_Texture_Color.color;
          goto m_31_0;
        m_31_0:
          {
            __yv_29 = c;
            goto _l___yv_29;
          } break;
      }
      {
        std_image_Image *i;
        case src_core_texture_Texture_Image:
          i = _m30.src_core_texture_Texture_Image.img;
          goto m_31_1;
        m_31_1:
          {
            __yv_29 = src_utils_utils_get_interpolated(i, uv.x, (1.000000f - uv.y));
            goto _l___yv_29;
          } break;
      }
      {
        f32 s;
        case src_core_texture_Texture_Checkerboard:
          s = _m30.src_core_texture_Texture_Checkerboard.scale;
          goto m_31_2;
        m_31_2:
          {
            std_vec_Vec2__5 res = std_vec_Vec2__1_to_u32(std_vec_Vec2__1_mults(uv, s));
            __yv_29 = (((res.x + res.y) % 2)==0 ? (std_vec_Vec3__0){.x=0.000000f, .y=0.000000f, .z=0.000000f} : (std_vec_Vec3__0){.x=1.000000f, .y=1.000000f, .z=1.000000f});
            goto _l___yv_29;
          } break;
      }
    }
_l___yv_29:
  __yv_29;});
}

std_vec_Vec3__0 src_core_scene_Scene_sky_color(src_core_scene_Scene *this, src_core_ray_Ray *ray) {
  f32 a = (0.500000f * (ray->dir.y + 1.000000f));
  return std_vec_Vec3__0_add(std_vec_Vec3__0_multrs((1.000000f - a), (std_vec_Vec3__0){.x=1.000000f, .y=1.000000f, .z=1.000000f}), std_vec_Vec3__0_multrs(a, (std_vec_Vec3__0){.x=0.500000f, .y=0.700000f, .z=1.000000f}));
}

std_vec_Vec3__0 src_core_scene_random_point_on_sphere(std_random_RandomState *rng) {
  while (true) {
    std_vec_Vec3__0 p = std_vec_Vec3__0_subs(std_vec_Vec3__0_mults((std_vec_Vec3__0){.x=std_random_randf32(rng), .y=std_random_randf32(rng), .z=std_random_randf32(rng)}, 2.000000f), 1.000000f);
    f32 lensq = std_vec_Vec3__0_length_sq(p);
    if ((((f32)pow(((f64)10.000000f), ((f64)-160.000000f))) < lensq) && (lensq <= 1.000000f)) {
      return std_vec_Vec3__0_divs(p, sqrtf(lensq));
    }
  }
  if(!(false)) { ae_assert_fail("/home/mindful-dev/code/ocen-light-bouncy-bounce/src/core/scene.oc:29:12: Assertion failed: `false`", NULL); exit(1); }
}

std_vec_Vec3__0 src_core_scene_Scene_hit(src_core_scene_Scene *this, src_core_ray_Ray *ray, std_random_RandomState *rng) {
  std_vec_Vec3__0 accum = (std_vec_Vec3__0){.x=1.000000f, .y=1.000000f, .z=1.000000f};
  src_core_ray_Ray current_ray = (*ray);
  for (u32 i = 0; i < src_core_scene_num_bounces; i+=1) {
    bool hit = false;
    src_core_hitrec_HitRec hit_rec = {0};
    hit_rec.t=f32_inf();
    for (std_vector_Iterator__1 _i2 = std_vector_Vector__1_iter(this->objects); std_vector_Iterator__1_has_value(&_i2); std_vector_Iterator__1_next(&_i2)) {
      src_core_object_Object *obj = std_vector_Iterator__1_cur(&_i2);
      {
        hit=(src_core_object_Object_hit(obj, &current_ray, &hit_rec) || hit);
      }
    }
    if (!(hit)) {
      return std_vec_Vec3__0_mult(src_core_scene_Scene_sky_color(this, &current_ray), accum);
    }
    accum=std_vec_Vec3__0_mult(accum, src_core_texture_Texture_get(hit_rec.obj->texture, hit_rec.uv));
    current_ray.dir=({std_vec_Vec3__0 __yv_32;
switch ((hit_rec.obj->mat)) {
        case src_core_materialtype_MaterialType_Diffused:
        m_33_0:
          {
            std_vec_Vec3__0 s = std_vec_Vec3__0_add(std_vec_Vec3__0_add(hit_rec.pos, hit_rec.norm), src_core_scene_random_point_on_sphere(rng));
            __yv_32 = std_vec_Vec3__0_normalized(std_vec_Vec3__0_sub(s, hit_rec.pos));
            goto _l___yv_32;
          } break;
        case src_core_materialtype_MaterialType_Reflective:
        m_33_1:
          {
            __yv_32 = std_vec_Vec3__0_reflect(current_ray.dir, hit_rec.norm);
            goto _l___yv_32;
          } break;
      }
_l___yv_32:
    __yv_32;});
    current_ray.pos=std_vec_Vec3__0_add(hit_rec.pos, std_vec_Vec3__0_mults(current_ray.dir, 0.001000f));
  }
  return (std_vec_Vec3__0){.x=0.000000f, .y=0.000000f, .z=0.000000f};
}

src_core_camera_Camera src_core_camera_Camera_make(u32 width, u32 height, f32 focal_length, std_vec_Vec3__0 pos, u32 num_samples) {
  f32 aspect_ratio = (((f32)width) / ((f32)height));
  f32 viewport_height = 2.000000f;
  f32 viewport_width = (viewport_height * aspect_ratio);
  std_vec_Vec3__0 viewport_u = (std_vec_Vec3__0){.x=viewport_width, .y=0.000000f, .z=0.000000f};
  std_vec_Vec3__0 viewport_v = (std_vec_Vec3__0){.x=0.000000f, .y=-viewport_height, .z=0.000000f};
  std_vec_Vec3__0 du = std_vec_Vec3__0_divs(viewport_u, ((f32)width));
  std_vec_Vec3__0 dv = std_vec_Vec3__0_divs(viewport_v, ((f32)height));
  std_vec_Vec3__0 camera_center = pos;
  std_vec_Vec3__0 upper_left = std_vec_Vec3__0_sub(std_vec_Vec3__0_sub(std_vec_Vec3__0_sub(camera_center, (std_vec_Vec3__0){.x=0.000000f, .y=0.000000f, .z=focal_length}), std_vec_Vec3__0_divs(viewport_u, 2.000000f)), std_vec_Vec3__0_divs(viewport_v, 2.000000f));
  std_vec_Vec3__0 pixel00_pos = std_vec_Vec3__0_add(upper_left, std_vec_Vec3__0_multrs(0.500000f, std_vec_Vec3__0_add(du, dv)));
  return (src_core_camera_Camera){.pos=camera_center, .top_left=pixel00_pos, .du=du, .dv=dv, .num_samples=num_samples};
}

src_core_ray_Ray src_core_camera_Camera_create_ray(src_core_camera_Camera *this, u32 i, u32 j, std_random_RandomState *rng) {
  std_vec_Vec3__0 pixel = std_vec_Vec3__0_add(std_vec_Vec3__0_add(this->top_left, std_vec_Vec3__0_multrs((((f32)i) + std_random_randf32(rng)), this->du)), std_vec_Vec3__0_multrs((((f32)j) + std_random_randf32(rng)), this->dv));
  return (src_core_ray_Ray){.pos=this->pos, .dir=std_vec_Vec3__0_normalized(std_vec_Vec3__0_sub(pixel, this->pos))};
}

src_core_matrix_Matrix src_core_matrix_Matrix_transpose(src_core_matrix_Matrix this) {
  src_core_matrix_Matrix m = {0};
  for (u32 i = 0; i < 4; i+=1) {
    for (u32 j = 0; j < 4; j+=1) {
      m.d[i][j]=this.d[j][i];
    }
  }
  return m;
}

src_core_matrix_Matrix src_core_matrix_Matrix_make(f32 d00, f32 d01, f32 d02, f32 d03, f32 d10, f32 d11, f32 d12, f32 d13, f32 d20, f32 d21, f32 d22, f32 d23, f32 d30, f32 d31, f32 d32, f32 d33) {
  src_core_matrix_Matrix m = {0};
  m.d[0][0]=d00;
  m.d[0][1]=d01;
  m.d[0][2]=d02;
  m.d[0][3]=d03;
  m.d[1][0]=d10;
  m.d[1][1]=d11;
  m.d[1][2]=d12;
  m.d[1][3]=d13;
  m.d[2][0]=d20;
  m.d[2][1]=d21;
  m.d[2][2]=d22;
  m.d[2][3]=d23;
  m.d[3][0]=d30;
  m.d[3][1]=d31;
  m.d[3][2]=d32;
  m.d[3][3]=d33;
  return m;
}

src_core_matrix_Matrix src_core_matrix_Matrix_identity(void) {
  return src_core_matrix_Matrix_make(1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f);}

src_core_matrix_Matrix src_core_matrix_Matrix_mul(src_core_matrix_Matrix this, src_core_matrix_Matrix other) {
  src_core_matrix_Matrix m = {0};
  for (u32 i = 0; i < 4; i+=1) {
    for (u32 j = 0; j < 4; j+=1) {
      m.d[i][j]=0.000000f;
      for (u32 k = 0; k < 4; k+=1) {
        m.d[i][j]+=(this.d[i][k] * other.d[k][j]);
      }
    }
  }
  return m;
}

std_vec_Vec3__0 src_core_matrix_Matrix_mulv(src_core_matrix_Matrix this, std_vec_Vec3__0 v) {
  f32 x = ((((v.x * this.d[0][0]) + (v.y * this.d[0][1])) + (v.z * this.d[0][2])) + this.d[0][3]);
  f32 y = ((((v.x * this.d[1][0]) + (v.y * this.d[1][1])) + (v.z * this.d[1][2])) + this.d[1][3]);
  f32 z = ((((v.x * this.d[2][0]) + (v.y * this.d[2][1])) + (v.z * this.d[2][2])) + this.d[2][3]);
  return (std_vec_Vec3__0){.x=x, .y=y, .z=z};
}

std_vec_Vec3__0 src_core_matrix_Matrix_mulv_no_translation(src_core_matrix_Matrix this, std_vec_Vec3__0 v) {
  f32 x = (((v.x * this.d[0][0]) + (v.y * this.d[0][1])) + (v.z * this.d[0][2]));
  f32 y = (((v.x * this.d[1][0]) + (v.y * this.d[1][1])) + (v.z * this.d[1][2]));
  f32 z = (((v.x * this.d[2][0]) + (v.y * this.d[2][1])) + (v.z * this.d[2][2]));
  return (std_vec_Vec3__0){.x=x, .y=y, .z=z};
}

src_core_matrix_Matrix src_core_matrix_Matrix_scale(src_core_matrix_Matrix this, f32 t) {
  src_core_matrix_Matrix m = {0};
  for (u32 i = 0; i < 4; i+=1) {
    for (u32 j = 0; j < 4; j+=1) {
      m.d[i][j]=(this.d[i][j] * t);
    }
  }
  return m;
}

src_core_matrix_Matrix src_core_matrix_Matrix_invert(src_core_matrix_Matrix *this) {
  src_core_matrix_Matrix inv = {0};
  inv.d[0][0]=(((((((this->d[1][1] * this->d[2][2]) * this->d[3][3]) - ((this->d[1][1] * this->d[2][3]) * this->d[3][2])) - ((this->d[2][1] * this->d[1][2]) * this->d[3][3])) + ((this->d[2][1] * this->d[1][3]) * this->d[3][2])) + ((this->d[3][1] * this->d[1][2]) * this->d[2][3])) - ((this->d[3][1] * this->d[1][3]) * this->d[2][2]));
  inv.d[1][0]=(((((((-this->d[1][0] * this->d[2][2]) * this->d[3][3]) + ((this->d[1][0] * this->d[2][3]) * this->d[3][2])) + ((this->d[2][0] * this->d[1][2]) * this->d[3][3])) - ((this->d[2][0] * this->d[1][3]) * this->d[3][2])) - ((this->d[3][0] * this->d[1][2]) * this->d[2][3])) + ((this->d[3][0] * this->d[1][3]) * this->d[2][2]));
  inv.d[2][0]=(((((((this->d[1][0] * this->d[2][1]) * this->d[3][3]) - ((this->d[1][0] * this->d[2][3]) * this->d[3][1])) - ((this->d[2][0] * this->d[1][1]) * this->d[3][3])) + ((this->d[2][0] * this->d[1][3]) * this->d[3][1])) + ((this->d[3][0] * this->d[1][1]) * this->d[2][3])) - ((this->d[3][0] * this->d[1][3]) * this->d[2][1]));
  inv.d[3][0]=(((((((-this->d[1][0] * this->d[2][1]) * this->d[3][2]) + ((this->d[1][0] * this->d[2][2]) * this->d[3][1])) + ((this->d[2][0] * this->d[1][1]) * this->d[3][2])) - ((this->d[2][0] * this->d[1][2]) * this->d[3][1])) - ((this->d[3][0] * this->d[1][1]) * this->d[2][2])) + ((this->d[3][0] * this->d[1][2]) * this->d[2][1]));
  inv.d[0][1]=(((((((-this->d[0][1] * this->d[2][2]) * this->d[3][3]) + ((this->d[0][1] * this->d[2][3]) * this->d[3][2])) + ((this->d[2][1] * this->d[0][2]) * this->d[3][3])) - ((this->d[2][1] * this->d[0][3]) * this->d[3][2])) - ((this->d[3][1] * this->d[0][2]) * this->d[2][3])) + ((this->d[3][1] * this->d[0][3]) * this->d[2][2]));
  inv.d[1][1]=(((((((this->d[0][0] * this->d[2][2]) * this->d[3][3]) - ((this->d[0][0] * this->d[2][3]) * this->d[3][2])) - ((this->d[2][0] * this->d[0][2]) * this->d[3][3])) + ((this->d[2][0] * this->d[0][3]) * this->d[3][2])) + ((this->d[3][0] * this->d[0][2]) * this->d[2][3])) - ((this->d[3][0] * this->d[0][3]) * this->d[2][2]));
  inv.d[2][1]=(((((((-this->d[0][0] * this->d[2][1]) * this->d[3][3]) + ((this->d[0][0] * this->d[2][3]) * this->d[3][1])) + ((this->d[2][0] * this->d[0][1]) * this->d[3][3])) - ((this->d[2][0] * this->d[0][3]) * this->d[3][1])) - ((this->d[3][0] * this->d[0][1]) * this->d[2][3])) + ((this->d[3][0] * this->d[0][3]) * this->d[2][1]));
  inv.d[3][1]=(((((((this->d[0][0] * this->d[2][1]) * this->d[3][2]) - ((this->d[0][0] * this->d[2][2]) * this->d[3][1])) - ((this->d[2][0] * this->d[0][1]) * this->d[3][2])) + ((this->d[2][0] * this->d[0][2]) * this->d[3][1])) + ((this->d[3][0] * this->d[0][1]) * this->d[2][2])) - ((this->d[3][0] * this->d[0][2]) * this->d[2][1]));
  inv.d[0][2]=(((((((this->d[0][1] * this->d[1][2]) * this->d[3][3]) - ((this->d[0][1] * this->d[1][3]) * this->d[3][2])) - ((this->d[1][1] * this->d[0][2]) * this->d[3][3])) + ((this->d[1][1] * this->d[0][3]) * this->d[3][2])) + ((this->d[3][1] * this->d[0][2]) * this->d[1][3])) - ((this->d[3][1] * this->d[0][3]) * this->d[1][2]));
  inv.d[1][2]=(((((((-this->d[0][0] * this->d[1][2]) * this->d[3][3]) + ((this->d[0][0] * this->d[1][3]) * this->d[3][2])) + ((this->d[1][0] * this->d[0][2]) * this->d[3][3])) - ((this->d[1][0] * this->d[0][3]) * this->d[3][2])) - ((this->d[3][0] * this->d[0][2]) * this->d[1][3])) + ((this->d[3][0] * this->d[0][3]) * this->d[1][2]));
  inv.d[2][2]=(((((((this->d[0][0] * this->d[1][1]) * this->d[3][3]) - ((this->d[0][0] * this->d[1][3]) * this->d[3][1])) - ((this->d[1][0] * this->d[0][1]) * this->d[3][3])) + ((this->d[1][0] * this->d[0][3]) * this->d[3][1])) + ((this->d[3][0] * this->d[0][1]) * this->d[1][3])) - ((this->d[3][0] * this->d[0][3]) * this->d[1][1]));
  inv.d[3][2]=(((((((-this->d[0][0] * this->d[1][1]) * this->d[3][2]) + ((this->d[0][0] * this->d[1][2]) * this->d[3][1])) + ((this->d[1][0] * this->d[0][1]) * this->d[3][2])) - ((this->d[1][0] * this->d[0][2]) * this->d[3][1])) - ((this->d[3][0] * this->d[0][1]) * this->d[1][2])) + ((this->d[3][0] * this->d[0][2]) * this->d[1][1]));
  inv.d[0][3]=(((((((-this->d[0][1] * this->d[1][2]) * this->d[2][3]) + ((this->d[0][1] * this->d[1][3]) * this->d[2][2])) + ((this->d[1][1] * this->d[0][2]) * this->d[2][3])) - ((this->d[1][1] * this->d[0][3]) * this->d[2][2])) - ((this->d[2][1] * this->d[0][2]) * this->d[1][3])) + ((this->d[2][1] * this->d[0][3]) * this->d[1][2]));
  inv.d[1][3]=(((((((this->d[0][0] * this->d[1][2]) * this->d[2][3]) - ((this->d[0][0] * this->d[1][3]) * this->d[2][2])) - ((this->d[1][0] * this->d[0][2]) * this->d[2][3])) + ((this->d[1][0] * this->d[0][3]) * this->d[2][2])) + ((this->d[2][0] * this->d[0][2]) * this->d[1][3])) - ((this->d[2][0] * this->d[0][3]) * this->d[1][2]));
  inv.d[2][3]=(((((((-this->d[0][0] * this->d[1][1]) * this->d[2][3]) + ((this->d[0][0] * this->d[1][3]) * this->d[2][1])) + ((this->d[1][0] * this->d[0][1]) * this->d[2][3])) - ((this->d[1][0] * this->d[0][3]) * this->d[2][1])) - ((this->d[2][0] * this->d[0][1]) * this->d[1][3])) + ((this->d[2][0] * this->d[0][3]) * this->d[1][1]));
  inv.d[3][3]=(((((((this->d[0][0] * this->d[1][1]) * this->d[2][2]) - ((this->d[0][0] * this->d[1][2]) * this->d[2][1])) - ((this->d[1][0] * this->d[0][1]) * this->d[2][2])) + ((this->d[1][0] * this->d[0][2]) * this->d[2][1])) + ((this->d[2][0] * this->d[0][1]) * this->d[1][2])) - ((this->d[2][0] * this->d[0][2]) * this->d[1][1]));
  f32 det = ((((this->d[0][0] * inv.d[0][0]) + (this->d[0][1] * inv.d[1][0])) + (this->d[0][2] * inv.d[2][0])) + (this->d[0][3] * inv.d[3][0]));
  if (fabsf(det) <= 0.000000f) {
    return src_core_matrix_Matrix_identity();
  }
  return src_core_matrix_Matrix_scale(inv, (1.000000f / det));
}

src_core_matrix_Matrix src_core_matrix_Matrix_for_translate(std_vec_Vec3__0 v) {
  return src_core_matrix_Matrix_make(1.000000f, 0.000000f, 0.000000f, v.x, 0.000000f, 1.000000f, 0.000000f, v.y, 0.000000f, 0.000000f, 1.000000f, v.z, 0.000000f, 0.000000f, 0.000000f, 1.000000f);}

src_core_matrix_Matrix src_core_matrix_Matrix_for_scale(std_vec_Vec3__0 v) {
  return src_core_matrix_Matrix_make(v.x, 0.000000f, 0.000000f, 0.000000f, 0.000000f, v.y, 0.000000f, 0.000000f, 0.000000f, 0.000000f, v.z, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f);}

src_core_matrix_Matrix src_core_matrix_Matrix_for_rotate_x(f32 a) {
  return src_core_matrix_Matrix_make(1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, cosf(a), -sinf(a), 0.000000f, 0.000000f, sinf(a), cosf(a), 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f);}

src_core_matrix_Matrix src_core_matrix_Matrix_for_rotate_y(f32 a) {
  return src_core_matrix_Matrix_make(cosf(a), 0.000000f, sinf(a), 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, -sinf(a), 0.000000f, cosf(a), 0.000000f, 0.000000f, 0.000000f, 0.000000f, 1.000000f);}

std_vec_Vec3__0 src_core_ray_Ray_at(src_core_ray_Ray this, f32 t) {
  return std_vec_Vec3__0_add(this.pos, std_vec_Vec3__0_multrs(t, this.dir));
}

i32 main(void) {
  u32 image_width = 1280;
  u32 image_height = 720;
  std_video_renderer_VideoRenderer *vr = std_video_renderer_VideoRenderer_create(std_video_renderer_VideoRendererType_SDL, image_width, image_height, 30, "out.mp4", false);
  u32 num_samples = 8;
  f32 focal_length = 4.500000f;
  std_vec_Vec3__0 camera_pos = (std_vec_Vec3__0){.x=0.120000f, .y=0.000000f, .z=6.000000f};
  std_image_Image *image = std_image_Image_new(image_width, image_height);
  src_core_camera_Camera camera = src_core_camera_Camera_make(image_width, image_height, focal_length, camera_pos, num_samples);
  src_core_matrix_Matrix transformation = src_core_matrix_Matrix_mul(src_core_matrix_Matrix_for_rotate_x((M_PI / 4.000000f)), src_core_matrix_Matrix_for_scale((std_vec_Vec3__0){.x=0.250000f, .y=1.000000f, .z=0.250000f}));
  u32 x = 0;
  std_gc_init(&x);
  for (u32 i = 0; true; i+=1) {
    f32 time = (((f32)i) / 30.000000f);
    src_core_scene_Scene scene = make_scene(time);
    render(image, &camera, &scene);
    std_video_renderer_VideoRenderer_send_frame(vr, image);
    std_gc_collect();
  }
}

void render(std_image_Image *img, src_core_camera_Camera *camera, src_core_scene_Scene *scene) {
  u32 completed = 0;
  #pragma omp parallel for schedule(dynamic, 32);
  for (u32 j = 0; j < img->height; j+=1) {
    std_random_RandomState rng = std_random_RandomState_make(j);
    for (u32 i = 0; i < img->width; i+=1) {
      std_vec_Vec3__0 color = (std_vec_Vec3__0){.x=0.000000f, .y=0.000000f, .z=0.000000f};
      for (u32 s = 0; s < camera->num_samples; s+=1) {
        src_core_ray_Ray ray = src_core_camera_Camera_create_ray(camera, i, j, &rng);
        color=std_vec_Vec3__0_add(color, src_core_scene_Scene_hit(scene, &ray, &rng));
      }
      std_image_Image_set(img, i, j, std_image_Color_from_vec(std_vec_Vec3__0_divs(color, ((f32)camera->num_samples))));
    }
    completed+=1;
  }
}

src_core_scene_Scene make_scene(f32 time) {
  return (src_core_scene_Scene){.objects=({
    std_vector_Vector__1 *_vc34 = std_vector_Vector__1_new(5);
    std_vector_Vector__1_push(_vc34, ({src_core_object_Object *_new_35 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_core_object_Object)); *_new_35 = (src_core_object_Object){.tag=src_core_object_Object_Sphere,.texture=(src_core_texture_Texture){.tag=src_core_texture_Texture_Color,.src_core_texture_Texture_Color={(std_vec_Vec3__0){.x=0.800000f, .y=0.700000f, .z=0.600000f}, }}, .mat=src_core_materialtype_MaterialType_Reflective, .src_core_object_Object_Sphere={(src_objects_sphere_Sphere){.pos=(std_vec_Vec3__0){.x=-1.000000f, .y=-0.210000f, .z=-1.000000f}, .r=0.300000f}, }}; _new_35; }));
    std_vector_Vector__1_push(_vc34, src_objects_transformed_Transformed_new(({src_core_object_Object *_new_36 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_core_object_Object)); *_new_36 = (src_core_object_Object){.tag=src_core_object_Object_Sphere,.texture=(src_core_texture_Texture){.tag=src_core_texture_Texture_Color,.src_core_texture_Texture_Color={(std_vec_Vec3__0){.x=0.330000f, .y=0.400000f, .z=0.700000f}, }}, .mat=src_core_materialtype_MaterialType_Diffused, .src_core_object_Object_Sphere={(src_objects_sphere_Sphere){.pos=(std_vec_Vec3__0){.x=-2.000000f, .y=-0.110000f, .z=-2.000000f}, .r=0.400000f}, }}; _new_36; }), src_core_matrix_Matrix_for_scale((std_vec_Vec3__0){.x=1.000000f, .y=0.500000f, .z=1.000000f})));
    std_vector_Vector__1_push(_vc34, src_objects_transformed_Transformed_new(({src_core_object_Object *_new_37 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_core_object_Object)); *_new_37 = (src_core_object_Object){.tag=src_core_object_Object_Sphere,.texture=(src_core_texture_Texture){.tag=src_core_texture_Texture_Image,.src_core_texture_Texture_Image={std_image_Image_load("src/earth.png"), }}, .mat=src_core_materialtype_MaterialType_Diffused, .src_core_object_Object_Sphere={(src_objects_sphere_Sphere){.pos=(std_vec_Vec3__0){.x=0.000000f, .y=0.000000f, .z=0.000000f}, .r=0.500000f}, }}; _new_37; }), src_core_matrix_Matrix_mul(src_core_matrix_Matrix_for_translate((std_vec_Vec3__0){.x=1.000000f, .y=-0.010000f, .z=-1.000000f}), src_core_matrix_Matrix_for_rotate_y(time))));
    std_vector_Vector__1_push(_vc34, ({src_core_object_Object *_new_38 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_core_object_Object)); *_new_38 = (src_core_object_Object){.tag=src_core_object_Object_Mesh,.texture=(src_core_texture_Texture){.tag=src_core_texture_Texture_Checkerboard,.src_core_texture_Texture_Checkerboard={20.000000f, }}, .mat=src_core_materialtype_MaterialType_Diffused, .src_core_object_Object_Mesh={src_objects_mesh_Mesh_from_obj("src/cube.obj"), }}; _new_38; }));
    std_vector_Vector__1_push(_vc34, src_objects_transformed_Transformed_new(({src_core_object_Object *_new_39 = std_mem_state_alloc_fn(std_mem_state_allocator, sizeof(src_core_object_Object)); *_new_39 = (src_core_object_Object){.tag=src_core_object_Object_Mesh,.texture=(src_core_texture_Texture){.tag=src_core_texture_Texture_Image,.src_core_texture_Texture_Image={std_image_Image_load("src/bouncy.png"), }}, .mat=src_core_materialtype_MaterialType_Diffused, .src_core_object_Object_Mesh={src_objects_mesh_Mesh_from_obj("src/teapot.obj"), }}; _new_39; }), src_core_matrix_Matrix_for_rotate_y((-time * 1.500000f))));
    _vc34;})};
}

std_image_Color std_image_Color_from_vec(std_vec_Vec3__0 vec) {
  u8 ir = ((u8)(vec.x * 255.999000f));
  u8 ig = ((u8)(vec.y * 255.999000f));
  u8 ib = ((u8)(vec.z * 255.999000f));
  return (std_image_Color){.r=ir, .g=ig, .b=ib};
}

i8 src_core_bvh_create__Closure_3(void *__C, src_objects_triangle_Triangle l, src_objects_triangle_Triangle r) {
  src_core_bvh_create__Closure_3Ctx *_C = (src_core_bvh_create__Closure_3Ctx *)__C;
{
  std_vec_Vec3__0 left = src_core_bounds_Bounds_centroid(src_objects_triangle_Triangle_bounds(l));
  std_vec_Vec3__0 right = src_core_bounds_Bounds_centroid(src_objects_triangle_Triangle_bounds(r));
  return f32_compare(std_vec_Vec3__0_index(left, (*_C->dim)), std_vec_Vec3__0_index(right, (*_C->dim)));
}
}


#pragma once
/*
 * File:   gl_font.h
 * Author: TeslaRus
 *
 * Created on January 16, 2015, 10:46 PM
 */

#include <cstdint>

#include <ft2build.h>
#include <freetype.h>
#include <GL/glew.h>


typedef struct char_info_s
{
    GLuint          tex_index;
    GLint           width;
    GLint           height;
    GLint           left;
    GLint           top;

    GLfloat         tex_x0;
    GLfloat         tex_y0;
    GLfloat         tex_x1;
    GLfloat         tex_y1;

    GLfloat         advance_x;
    GLfloat         advance_y;
}char_info_t, *char_info_p;

typedef struct gl_tex_font_s
{
    FT_Library               ft_library;
    FT_Face                  ft_face;
    uint16_t                 font_size;

    struct char_info_s      *glyphs;
    uint16_t                 glyphs_count;

    uint16_t                 gl_tex_indexes_count;
    uint16_t                 gl_real_tex_indexes_count;
    GLuint                  *gl_tex_indexes;
    GLint                    gl_max_tex_width;
    GLint                    gl_tex_width;
    GLfloat                  gl_font_color[4];
}gl_tex_font_t, *gl_tex_font_p;


gl_tex_font_p glf_create_font(FT_Library ft_library, const char *file_name, uint16_t font_size);
gl_tex_font_p glf_create_font_mem(FT_Library ft_library, void *face_data, size_t face_data_size, uint16_t font_size);
void glf_free_font(gl_tex_font_p glf);
void glf_resize(gl_tex_font_p glf, uint16_t font_size);
void glf_reface(gl_tex_font_p glf, const char *file_name, uint16_t font_size);

float    glf_get_string_len(gl_tex_font_p glf, const char *text, int n);
float    glf_get_ascender(gl_tex_font_p glf);
uint16_t glf_get_font_size(gl_tex_font_p glf);
void     glf_get_string_bb(gl_tex_font_p glf, const char *text, int n, GLfloat *x0, GLfloat *y0, GLfloat *x1, GLfloat *y1);

void     glf_render_str(gl_tex_font_p glf, GLfloat x, GLfloat y, const char *text);     // UTF-8

uint32_t utf8_strlen(const char *str);
uint8_t* utf8_to_utf32(uint8_t *utf8, uint32_t *utf32);

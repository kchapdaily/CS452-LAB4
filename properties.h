//properties.h
//Kevin Chapman
//use to manage the material and light properties for OpenGL applications

#ifndef __PROPS_CHAPMAN__
#define __PROPS_CHAPMAN__

#include "Angel.h"

typedef struct matProps{
  color4 ambient;
  color4 diffuse;
  color4 specular;
  float shininess;
} matProps;

typedef struct lightProps{
  point4 position;
  color4 ambient;
  color4 diffuse;
  color4 specular;
} lightProps;


void setPosition(lightProps *light, float r, float g, float b, float a);

void setShininess(matProps *mat, float s);

void setAmbient(lightProps *light, float r, float g, float b, float a);

void setAmbient(matProps *mat, float r, float g, float b, float a);

void setDiffuse(lightProps *light, float r, float g, float b, float a);

void setDiffuse(matProps *mat, float r, float g, float b, float a);

void setSpecular(lightProps *light, float r, float g, float b, float a);

void setSpecular(matProps *mat, float r, float g, float b, float a);

#endif //__PROPS_CHAPMAN__

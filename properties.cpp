#include "Angel.h"
#include "properties.h"

void setPosition(lightProps *light, float r, float g, float b, float a){
  light->ambient[0] = r;
  light->ambient[1] = g;
  light->ambient[2] = b;
  light->ambient[3] = a;
}

void setShininess(matProps *mat, float s){
	mat->shininess = s;
}

void setAmbient(lightProps *light, float r, float g, float b, float a){
  light->ambient[0] = r;
  light->ambient[1] = g;
  light->ambient[2] = b;
  light->ambient[3] = a;
}

void setAmbient(matProps *mat, float r, float g, float b, float a){
  mat->ambient[0] = r;
  mat->ambient[1] = g;
  mat->ambient[2] = b;
  mat->ambient[3] = a;
}

void setDiffuse(lightProps *light, float r, float g, float b, float a){
  light->diffuse[0] = r;
  light->diffuse[1] = g;
  light->diffuse[2] = b;
  light->diffuse[3] = a;
}

void setDiffuse(matProps *mat, float r, float g, float b, float a){
  mat->diffuse[0] = r;
  mat->diffuse[1] = g;
  mat->diffuse[2] = b;
  mat->diffuse[3] = a;
}

void setSpecular(lightProps *light, float r, float g, float b, float a){
  light->specular[0] = r;
  light->specular[1] = g;
  light->specular[2] = b;
  light->specular[3] = a;
}

void setSpecular(matProps *mat, float r, float g, float b, float a){
  mat->specular[0] = r;
  mat->specular[1] = g;
  mat->specular[2] = b;
  mat->specular[3] = a;
}

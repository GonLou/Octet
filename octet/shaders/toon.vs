//////////////////////////////////////////////////////////////////////////////////////////
//
// Default vertex shader for materials. Extend this to deal with bump mapping, defered rendering, shadows etc.
//

// matrices
uniform mat4 modelToProjection;
uniform mat4 modelToCamera;
uniform vec3 LightColor;

// attributes from vertex buffer
attribute vec4 pos;
attribute vec2 uv;
attribute vec3 normal;
attribute vec4 color;

// outputs
varying vec3 normal_;
varying vec3 camera_pos_;
varying vec2 uv_;
varying vec4 color_;
varying vec3 model_pos_;
varying vec3 diffuse_color;
varying vec3 specular_color;

void main() {
  gl_Position = modelToProjection * pos;
  vec3 tnormal = (modelToCamera * vec4(normal, 0.0)).xyz;
  vec3 tpos = (modelToCamera * pos).xyz;
  normal_ = tnormal;
  camera_pos_ = tpos;
  uv_ = uv;
  color_ = color;
  model_pos_ = pos.xyz;
  vec3 diffuse_color = LightColor * (camera_pos * color_);
  vec3 specular_color = (color_ * pos, 0.0, 1.0);
}


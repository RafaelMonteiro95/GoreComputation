
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

using namespace glm;

mat4 Camera(float Translate, vec2 const & Rotate) {

    mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
    mat4 View = translate(mat4(1.0f), vec3(0.0f, 0.0f, -Translate));
    
    View = rotate(View, Rotate.y, vec3(-1.0f, 0.0f, 0.0f));
    View = rotate(View, Rotate.x, vec3(0.0f, 1.0f, 0.0f));
    
    mat4 Model = scale(mat4(1.0f), vec3(0.5f));
    
    return Projection * View * Model;
} 
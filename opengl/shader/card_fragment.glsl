#version 330 core

out vec4 FragColor;

in vec2 textCord;
in vec3 normal;
in vec3 frag_pos;

uniform sampler2D texture1;
uniform vec3 side_color;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main() {
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light_color;

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    float specular_strength = 0.5;
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strength * spec * light_color;

    vec3 result = ambient + diffuse + specular;
    if(textCord.x < 0 && textCord.y < 0) {
        result = result * side_color;
    } else {
        result = result * texture(texture1, textCord).xyz;
    }

    FragColor = vec4(result, 1.f);
}
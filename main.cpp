#include "glm/glm.hpp"
#include "game_object.hpp"
#include <functional>
#include <cmath>

using namespace OpenGL;

struct Movement {
    /**
     * @param t the current time
     * @return whether this Movement is finished
    */
    virtual bool update(float t);
};

std::function<glm::mat3(float)> gen_y_negative(float degree) {
    return [=](float t)->glm::mat3 {
        const float theta = glm::radians(t * degree);
        return glm::mat3{
            std::cos(theta), 0, std::sin(theta), 
            0, 1, 0, 
            -std::sin(theta), 0, std::cos(theta)
        };
    };
}
    

struct Rotation : public Movement{
        Rotation(std::shared_ptr<GameObject> object, float curr_t, float t_scale, std::function<glm::mat3(float)> update_f) : 
            _object{object}, _last_t{curr_t}, _residue_t{1}, _t_scale{t_scale}, _update{update_f} {}

        bool update(float t) override {
            const float delta_t = t - _last_t;
            _last_t = t;
            const float normalize_t = delta_t * _t_scale;
            const float update_t = std::min(_residue_t, normalize_t);
            _residue_t -= update_t;
            _object->set_rot(_object->get_rot() * _update(update_t));
            return _residue_t <= 0;
        }
    private:
        std::shared_ptr<GameObject> _object;
        float _last_t;
        float _residue_t;
        float _t_scale;
        std::function<glm::mat3(float)> _update;
};



int main() {
    return 0;
}
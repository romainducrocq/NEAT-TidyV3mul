#include "utils/nintaco/action.hpp"

void nintaco::Action::init()
{
    for(size_t i = 0; i < this->actions.size(); i++){
        switch(this->actions[i]){
            case CONF::Action::UP:
                this->noops[0].act1 = std::make_unique<size_t>(i);
                break;

            case CONF::Action::DOWN:
                this->noops[0].act2 = std::make_unique<size_t>(i);
                break;

            case CONF::Action::LEFT:
                this->noops[1].act1 = std::make_unique<size_t>(i);
                break;

            case CONF::Action::RIGHT:
                this->noops[1].act2 = std::make_unique<size_t>(i);
                break;

            default:
                break;
        }
    }
}

void nintaco::Action::act_func(std::array<float, CONF::OUTPUTS>& act) const
{
    for(const auto& noop : noops){
        if(noop.is()){
            if(nintaco::Action::Output::activate(act[*noop.act1]) &&
               nintaco::Action::Output::activate(act[*noop.act2])){
                act[*noop.act1] = -1.f;
                act[*noop.act2] = -1.f;
            }
        }
    }

    for(size_t i = 0; i < act.size(); i++){
        nintaco_writeGamepad(nintaco::Api::API().get_api(), 0, this->buttons.at(this->actions[i]),
                             nintaco::Action::Output::activate(act[i]));
    }
}

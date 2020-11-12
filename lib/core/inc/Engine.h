//
// Created by rogan2 on 15/10/2020.
//

#ifndef HEADERTECH_ENGINE_H
#define HEADERTECH_ENGINE_H

#include <memory>

namespace HeaderTech::Core {
    template<class CallbackImpl>
    class Engine {
        using CallbackClass = CallbackImpl;

    public:
        Engine() : m_callback()
        {};

        ~Engine()
        {};

        void Launch()
        {
            m_callback->BeforeLaunch();

            uint16_t count = 0;
            while (true) {
                m_callback->LoopTick();
                ++count;
                if (count > 0xfffe) {
                    break;
                }
            }

            m_callback->AfterLaunch();
        }

    private:
        std::unique_ptr<CallbackClass> m_callback;
    };
}


#endif //HEADERTECH_ENGINE_H

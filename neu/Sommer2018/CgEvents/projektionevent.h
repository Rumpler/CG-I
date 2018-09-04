#ifndef PROJEKTIONEVENT_H
#define PROJEKTIONEVENT_H
#include "CgBase/CgEnums.h"
#include <glm/glm.hpp>
#include <CgBase/CgBaseEvent.h>
class ProjektionEvent: public CgBaseEvent
        {
        private:

            enum Cg::EventType type;
            /**
              x = art projektion
              y = rltbfn
              z = wert
             * @brief value
             */
            glm::vec3 value;

        public:
            ProjektionEvent();
            ProjektionEvent(enum Cg::EventType type);
            ProjektionEvent(enum Cg::EventType type, const glm::vec3 &vec);
            ~ProjektionEvent();
            void setType(Cg::EventType &value);

            enum Cg::EventType getType();
            CgBaseEvent* clone();
            glm::vec3 getValue() const;
            void setValue(const glm::vec3 &value);

};

#endif // PROJEKTIONEVENT_H

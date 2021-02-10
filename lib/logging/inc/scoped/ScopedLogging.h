//
// Created by rogan2 on 12/11/2020.
//

#ifndef HEADERTECH_SCOPEDLOGGING_H
#define HEADERTECH_SCOPEDLOGGING_H

namespace HeaderTech::Logging::Scoped {
    class ScopedLogging {
    public:
        inline ScopedLogging(int argc, const char **argv);

        inline ~ScopedLogging();
    };
}

#endif //HEADERTECH_SCOPEDLOGGING_H

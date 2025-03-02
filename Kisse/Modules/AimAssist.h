#pragma once

#include "Modules.h" // Assurez-vous d'inclure le fichier correct

namespace Kisse {
    namespace Modules {
        class AimAssist : public IModule {
        public:
            AimAssist();
            void run() override;
            void renderGUI() override;
            void render() override;
            void disable() override;

        private:
            double SNAPFORCE = 0.5; // Déclaration de snapForce
        };
    }
}

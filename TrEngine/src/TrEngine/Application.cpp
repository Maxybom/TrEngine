#include "Tepch.h"
#include "Application.h"
#include "TrEngine/Event/ApplicationEvent.h"
#include "TrEngine/Log.h"

namespace TrEngine {

    Application::Application() {}

    Application::~Application() {}

    void Application::Run() {
        WindowResizeEvent e(1280, 720); // Correzione dell'errore di battitura
        TE_TRACE(e.ToString()); // Usa ToString() per il logging
        while (true);
    }

}

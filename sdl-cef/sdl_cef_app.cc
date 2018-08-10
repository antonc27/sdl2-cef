
#include <iostream>
#include "sdl_cef_app.h"

class SdlCefRenderProcessHandler : public CefRenderProcessHandler {
public:

    explicit SdlCefRenderProcessHandler(const CefMessageRouterConfig &config) : config(config) {}

    // CefRenderProcessHandler methods
    void OnWebKitInitialized() override {
        messageRouterRenderSide = CefMessageRouterRendererSide::Create(config);
    }

    void OnContextCreated(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefFrame> frame,
                          CefRefPtr<CefV8Context> context) override {
        messageRouterRenderSide->OnContextCreated(browser, frame, context);
    }

    void OnContextReleased(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           CefRefPtr<CefV8Context> context) override {
        messageRouterRenderSide->OnContextReleased(browser, frame, context);
    }

    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                  CefProcessId source_process,
                                  CefRefPtr<CefProcessMessage> message) override {
        return messageRouterRenderSide->OnProcessMessageReceived(browser, source_process, message);
    }

private:

    const CefMessageRouterConfig &config;
    CefRefPtr<CefMessageRouterRendererSide> messageRouterRenderSide;

IMPLEMENT_REFCOUNTING(SdlCefRenderProcessHandler);
};

// SdlCefApp impl
SdlCefApp::SdlCefApp(const CefMessageRouterConfig &config)
        : renderProcessHandler(new SdlCefRenderProcessHandler(config)) {}

CefRefPtr<CefRenderProcessHandler> SdlCefApp::GetRenderProcessHandler() {
    return renderProcessHandler;
}

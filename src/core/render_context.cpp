#include <core/render_context.hpp>

RenderContext::RenderContext(const sk_sp<const GrGLInterface>& interface) {
  m_context = GrDirectContexts::MakeGL(interface);
  if (m_context == nullptr) {
    throw std::runtime_error("Failed to create context.");
    return;
  }
}

RenderContext::~RenderContext() {
  if (m_context != nullptr) {
    m_context->abandonContext();
  }
}

sk_sp<GrDirectContext> RenderContext::getContext() const {
  return m_context;
}
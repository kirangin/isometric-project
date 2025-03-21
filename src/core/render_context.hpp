#ifndef RENDER_CONTEXT_HPP
#define RENDER_CONTEXT_HPP
#include <gpu/ganesh/gl/GrGLInterface.h>
#include <gpu/ganesh/GrDirectContext.h>
#include <gpu/ganesh/gl/GrGLDirectContext.h>
#include <stdexcept>

class RenderContext {
  public:
    RenderContext(const sk_sp<const GrGLInterface>& interface);
    ~RenderContext();

    sk_sp<GrDirectContext> getContext() const;

  private:
    sk_sp<GrDirectContext> m_context;
};

#endif
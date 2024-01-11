//
// Created by Ivan Ugryumov on 03.01.2024.
//

#include "ViewDelegate.h"

ViewDelegate::ViewDelegate(MTL::Device *pDevice)
        : MTK::ViewDelegate(), m_renderer(new Renderer(pDevice)) {
}

ViewDelegate::~ViewDelegate() {
    delete m_renderer;
}

void ViewDelegate::drawInMTKView(MTK::View *pView) {
    m_renderer->draw(pView);
}

//
// Created by Ivan Ugryumov on 03.01.2024.
//
#pragma once

#include "Renderer.h"
#include <MetalKit/MetalKit.hpp>

class ViewDelegate : public MTK::ViewDelegate {
public:
    explicit ViewDelegate(MTL::Device *pDevice);

    ~ViewDelegate() override;

    void drawInMTKView(MTK::View *pView) override;

private:
    Renderer *m_renderer;
};

//
// Created by Ivan Ugryumov on 01.01.2024.
//
#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

class Renderer {
public:
    explicit Renderer(MTL::Device *device);

    ~Renderer();

    void buildShaders();

    void buildBuffers();

    void draw(MTK::View *view);

private:
    MTL::Device *m_device;
    MTL::CommandQueue *m_commandQueue;
    MTL::RenderPipelineState *m_pso;
    MTL::Buffer *m_vertexBuffer;
    MTL::Buffer *m_colorsBuffer;
};
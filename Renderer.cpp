//
// Created by Ivan Ugryumov on 01.01.2024.
//
#include "Renderer.h"
#include <simd/simd.h>
#include <QtCore>

Renderer::Renderer(MTL::Device *device) : m_device(device->retain()) {
    m_commandQueue = m_device->newCommandQueue();
    buildShaders();
    buildBuffers();
}

Renderer::~Renderer() {
    m_vertexBuffer->release();
    m_colorsBuffer->release();
    m_pso->release();
    m_commandQueue->release();
    m_device->release();
}

void Renderer::buildShaders() {
    using NS::StringEncoding::UTF8StringEncoding;
    const char *shaderSrc = R"(
        #include <metal_stdlib>
        using namespace metal;

        struct v2f
        {
            float4 position [[position]];
            half3 color;
        };

        v2f vertex vertexMain( uint vertexId [[vertex_id]],
                               device const float3* positions [[buffer(0)]],
                               device const float3* colors [[buffer(1)]] )
        {
            v2f o;
            o.position = float4( positions[ vertexId ], 1.0 );
            o.color = half3 ( colors[ vertexId ] );
            return o;
        }

        half4 fragment fragmentMain( v2f in [[stage_in]] )
        {
            return half4( in.color, 1.0 );
        }
    )";

    NS::Error *pError = nullptr;
    MTL::Library *pLibrary = m_device->newLibrary(NS::String::string(shaderSrc, UTF8StringEncoding), nullptr, &pError);
    if (!pLibrary) {
        __builtin_printf("%s", pError->localizedDescription()->utf8String());
        assert(false);
    }

    MTL::Function *pVertexFn = pLibrary->newFunction(NS::String::string("vertexMain", UTF8StringEncoding));
    MTL::Function *pFragFn = pLibrary->newFunction(NS::String::string("fragmentMain", UTF8StringEncoding));

    MTL::RenderPipelineDescriptor *pDesc = MTL::RenderPipelineDescriptor::alloc()->init();
    pDesc->setVertexFunction(pVertexFn);
    pDesc->setFragmentFunction(pFragFn);
    pDesc->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);

    m_pso = m_device->newRenderPipelineState(pDesc, &pError);
    if (!m_pso) {
        __builtin_printf("%s", pError->localizedDescription()->utf8String());
        assert(false);
    }

    pVertexFn->release();
    pFragFn->release();
    pDesc->release();
    pLibrary->release();
}

void Renderer::buildBuffers() {
    const size_t NumVertices = 3;

    simd::float3 positions[NumVertices] =
            {
                    {-0.8f, 0.8f,  0.0f},
                    {0.0f,  -0.8f, 0.0f},
                    {+0.8f, 0.8f,  0.0f}
            };

    simd::float3 colors[NumVertices] =
            {
                    {1.0,  0.3f, 0.2f},
                    {0.8f, 1.0,  0.0f},
                    {0.8f, 0.0f, 1.0}
            };

    const size_t positionsDataSize = NumVertices * sizeof(simd::float3);
    const size_t colorDataSize = NumVertices * sizeof(simd::float3);

    MTL::Buffer *pVertexPositionsBuffer = m_device->newBuffer(positionsDataSize, MTL::ResourceStorageModeManaged);
    MTL::Buffer *pVertexColorsBuffer = m_device->newBuffer(colorDataSize, MTL::ResourceStorageModeManaged);

    m_vertexBuffer = pVertexPositionsBuffer;
    m_colorsBuffer = pVertexColorsBuffer;

    memcpy(m_vertexBuffer->contents(), positions, positionsDataSize);
    memcpy(m_colorsBuffer->contents(), colors, colorDataSize);

    m_vertexBuffer->didModifyRange(NS::Range::Make(0, m_vertexBuffer->length()));
    m_colorsBuffer->didModifyRange(NS::Range::Make(0, m_colorsBuffer->length()));
}

void Renderer::draw(MTK::View *view) {
    NS::AutoreleasePool *pPool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer *pCmd = m_commandQueue->commandBuffer();
    MTL::RenderPassDescriptor *pRpd = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder *pEnc = pCmd->renderCommandEncoder(pRpd);

    pEnc->setRenderPipelineState(m_pso);

    pEnc->setVertexBuffer(m_vertexBuffer, 0, 0);
    pEnc->setVertexBuffer(m_colorsBuffer, 0, 1);
    pEnc->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));

    pEnc->endEncoding();
    pCmd->presentDrawable(view->currentDrawable());
    pCmd->commit();

    pPool->release();
}
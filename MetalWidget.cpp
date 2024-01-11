//
// Created by Ivan Ugryumov on 02.01.2024.
//

#include "MetalWidget.h"
#include "MetalHelper.h"
#include <QEvent>
#include <QWindow>

MetalWidget::MetalWidget(QWidget *parent) : QWidget(parent) {
    setUpdatesEnabled(false);
    m_device = nullptr;
    createWinId();
    initMetal();
}

MetalWidget::~MetalWidget() {
    m_device->release();
    m_view->release();
    delete m_delegate;
}

void MetalWidget::initMetal() {
    CGRect frame = (CGRect) {{0.0,                0.0},
                             {float(width()) * 2, float(height()) * 2}};

    m_device = MTL::CreateSystemDefaultDevice();

    m_view = MTK::View::alloc()->init(frame, m_device);
    m_view->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    m_view->setClearColor(MTL::ClearColor::Make(0.0, 0.0, 0.0, 1.0));

    m_delegate = new ViewDelegate(m_device);
    m_view->setDelegate(m_delegate);
}

void MetalWidget::initView() {
    replaceNSView(m_view, winId());
}
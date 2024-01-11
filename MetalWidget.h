//
// Created by Ivan Ugryumov on 02.01.2024.
//
#pragma once

#include <QWidget>
#include "ViewDelegate.h"
#include <MetalKit/MetalKit.hpp>

class MetalWidget : public QWidget {
public:
    MetalWidget(QWidget *parent = nullptr);

    ~MetalWidget();

    void initView();

private:
    void initMetal();

    ViewDelegate *m_delegate;
    MTL::Device *m_device;
    MTK::View *m_view;
};

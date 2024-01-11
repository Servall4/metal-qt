//
// Created by Ivan Ugryumov on 01.01.2024.
//
#include "MetalHelper.h"
#import <MetalKit/MetalKit.h>

NSView *getNSView(WId winId) {
    return reinterpret_cast<NSView *>(winId);
}

void replaceNSView(MTK::View *view, WId winIdWidget) {
    [getNSView(winIdWidget).window.contentView addSubview:(__bridge MTKView *)(view)];

    [((__bridge MTKView *) (view)) setFrame:getNSView(winIdWidget).frame];
    [((__bridge MTKView *) (view)) setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
}


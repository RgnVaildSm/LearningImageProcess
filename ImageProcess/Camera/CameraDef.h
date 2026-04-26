#pragma once
#ifndef _CAMERA_DEF_
#define _CAMERA_DEF_

#include <QObject>
#include <QImage>
#include <QScopedPointer>
#include <QThreadPool>
#include <memory>
#include <qcamera.h>
#include <qmediacapturesession.h>
#include <qmediadevices.h>
#include <qmediaformat.h>
#include <qmediarecorder.h>
#include <qimagecapture.h>
#include <qvideosink.h>
#include <qvideoframe.h>
#include <qvideoframeformat.h>

constexpr auto MAX_CAMERA_THREAD = 5;

#endif // !_CAMERA_DEF_

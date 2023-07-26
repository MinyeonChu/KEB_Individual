// pch.h: �̸� �����ϵ� ��� �����Դϴ�.
// �Ʒ� ������ ������ �� ���� �����ϵǾ�����, ���� ���忡 ���� ���� ������ ����մϴ�.
// �ڵ� ������ �� ���� �ڵ� �˻� ����� �����Ͽ� IntelliSense ���ɿ��� ������ ��Ĩ�ϴ�.
// �׷��� ���⿡ ������ ������ ���� �� ������Ʈ�Ǵ� ��� ��� �ٽ� �����ϵ˴ϴ�.
// ���⿡ ���� ������Ʈ�� ������ �߰����� ������. �׷��� ������ ���ϵ˴ϴ�.

#ifndef PCH_H
#define PCH_H

// ���⿡ �̸� �������Ϸ��� ��� �߰�
#include "framework.h"

/*
* opencv
*/
#pragma warning(disable: 4819)

#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "../3rdparty/opencv-4.6.0/x64/lib/opencv_world460d.lib")
#else
#pragma comment(lib, "../3rdparty/opencv-4.6.0/x64/lib/opencv_world460.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "../3rdparty/opencv-3.3.1/x86/libd/opencv_world331d.lib")
#else
#pragma comment(lib, "../3rdparty/opencv-3.3.1/x86/lib/opencv_world331.lib")
#endif
#endif

#include <opencv2/opencv.hpp>

/*
* ffmpeg
*/
#ifdef _WIN64
#pragma comment(lib, "../3rdparty/ffmpeg-3.1.5/x64/avcodec.lib")
#pragma comment(lib, "../3rdparty/ffmpeg-3.1.5/x64/avutil.lib")
#pragma comment(lib, "../3rdparty/ffmpeg-3.1.5/x64/swscale.lib")
#else
#pragma comment(lib, "../3rdparty/ffmpeg-3.1.5/x86/avcodec.lib")
#pragma comment(lib, "../3rdparty/ffmpeg-3.1.5/x86/avutil.lib")
#pragma comment(lib, "../3rdparty/ffmpeg-3.1.5/x86/swscale.lib")
#endif

#ifdef __cplusplus
extern "C" {
#endif
#define __STDC_CONSTANT_MACROS
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "libavutil/opt.h"
#ifdef __cplusplus
}
#endif 

#pragma comment(lib, "Winmm.lib")

#include "resource.h"
#include "mmsystem.h"

#include "common.h"
#include "cmn_global.h"

#include "DxDefs.h"
#include "SockDefs.h"
#include "DialogDefs.h"

#endif //PCH_H

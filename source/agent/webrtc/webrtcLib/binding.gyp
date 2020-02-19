{
  'targets': [{
    'target_name': 'webrtc',
    'sources': [
      'addon.cc',
      'AudioFrameConstructorWrapper.cc',
      'AudioFramePacketizerWrapper.cc',
      'VideoFrameConstructorWrapper.cc',
      'VideoFramePacketizerWrapper.cc',
      'SyncGroupWrapper.cc',
      'WebRtcConnection.cc',
      'ThreadPool.cc',
      'IOThreadPool.cc',
      "MediaStream.cc",
      'conn_handler/WoogeenHandler.cpp',
      'erizo/src/erizo/DtlsTransport.cpp',
      'erizo/src/erizo/IceConnection.cpp',
      'erizo/src/erizo/LibNiceConnection.cpp',
      'erizo/src/erizo/SdpInfo.cpp',
      'erizo/src/erizo/SrtpChannel.cpp',
      'erizo/src/erizo/Stats.cpp',
      'erizo/src/erizo/StringUtil.cpp',
      'erizo/src/erizo/WebRtcConnection.cpp',
      'erizo/src/erizo/MediaStream.cpp',
      'erizo/src/erizo/lib/LibNiceInterfaceImpl.cpp',
      'erizo/src/erizo/thread/IOThreadPool.cpp',
      'erizo/src/erizo/thread/IOWorker.cpp',
      'erizo/src/erizo/thread/Scheduler.cpp',
      'erizo/src/erizo/thread/ThreadPool.cpp',
      'erizo/src/erizo/thread/Worker.cpp',
      'erizo/src/erizo/rtp/PacketBufferService.cpp',
      'erizo/src/erizo/rtp/RtcpForwarder.cpp',
      'erizo/src/erizo/rtp/RtcpProcessorHandler.cpp',
      'erizo/src/erizo/rtp/RtpUtils.cpp',
      'erizo/src/erizo/rtp/QualityManager.cpp',
      'erizo/src/erizo/rtp/RtpExtensionProcessor.cpp',
      'erizo/src/erizo/rtp/BandwidthEstimationHandler.cpp',
      '<!@(find erizo/src/erizo/dtls -name "*.cpp")',
      '<!@(find erizo/src/erizo/dtls -name "*.c")',
      '<!@(find erizo/src/erizo/pipeline -name "*.cpp")',
      '<!@(find erizo/src/erizo/stats  -name "*.cpp")',
      '../../addons/common/NodeEventRegistry.cc',
      '../../../core/owt_base/AudioFrameConstructor.cpp',
      '../../../core/owt_base/AudioFramePacketizer.cpp',
      '../../../core/owt_base/AudioUtilities.cpp',
      '../../../core/owt_base/MediaFramePipeline.cpp',
      '../../../core/owt_base/VideoFrameConstructor.cpp',
      '../../../core/owt_base/VideoFramePacketizer.cpp',
      '../../../core/owt_base/SsrcGenerator.cc',
      '../../../core/rtc_adapter/VieReceiver.cc',
      '../../../core/rtc_adapter/VieRemb.cc', #20150508
      '../../../core/owt_base/HEVCTilesMerger.cpp',
      '../../../core/owt_base/SyncGroup.cpp',
    ],
    'cflags_cc': ['-DWEBRTC_POSIX', '-DWEBRTC_LINUX', '-DLINUX', '-DNOLINUXIF', '-DNO_REG_RPC=1', '-DHAVE_VFPRINTF=1', '-DRETSIGTYPE=void', '-DNEW_STDIO', '-DHAVE_STRDUP=1', '-DHAVE_STRLCPY=1', '-DHAVE_LIBM=1', '-DHAVE_SYS_TIME_H=1', '-DTIME_WITH_SYS_TIME_H=1', '-D_ENABLE_HEVC_TILES_MERGER_'],
    'include_dirs': [
      "<!(node -e \"require('nan')\")",
      'conn_handler',
      'erizo/src/erizo',
      'erizo/src/erizo/lib',
      'erizo/src/erizo/dtls',
      'erizo/src/erizo/pipeline',
      'erizo/src/erizo/rtp',
      'erizo/src/erizo/thread',
      'erizo/src/erizo/stats',
      '../../../core/common',
      '../../../core/owt_base',
      '../../../core/rtc_adapter',
      '../../../../third_party/webrtc/src',
      '../../../../build/libdeps/build/include',
      '<!@(pkg-config glib-2.0 --cflags-only-I | sed s/-I//g)',
    ],
    'libraries': [
      '-L$(CORE_HOME)/../../build/libdeps/build/lib',
      '-lsrtp2',
      '-lssl',
      '-ldl',
      '-lcrypto',
      '-llog4cxx',
      '-lboost_thread',
      '-lboost_system',
      '-lnice',
      '-l360SCVP',
      '-L$(CORE_HOME)/../../third_party/webrtc', '-lwebrtc',
    ],
    'conditions': [
      [ 'OS=="mac"', {
        'xcode_settings': {
          'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',        # -fno-exceptions
          'MACOSX_DEPLOYMENT_TARGET':  '10.7',       # from MAC OS 10.7
          'OTHER_CFLAGS': ['-g -O$(OPTIMIZATION_LEVEL) -stdlib=libc++']
        },
      }, { # OS!="mac"
          'cflags!' : ['-fno-exceptions'],
          'cflags' : ['-D__STDC_CONSTANT_MACROS'],
          'cflags_cc' : ['-Wall', '-O3', '-g' , '-std=c++11', '-fexceptions'],
          'cflags_cc!' : ['-fno-exceptions'],
          'cflags_cc!' : ['-fno-rtti']
      }],
    ]
  }]
}

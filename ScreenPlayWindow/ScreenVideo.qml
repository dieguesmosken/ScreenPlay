import QtQuick 2.9
import QtAV 1.7

Rectangle {
    color: "black"
    id: screenVideoPlayer
    anchors.fill: parent
    property string videoPath
    property bool isPlaying: false
    Component.onCompleted: screenVideoPlayer.isPlaying = true
    onIsPlayingChanged: {
        if(isPlaying){
            player.play()
            state = "playing"
        } else {
            player.pause()
            state = ""
        }
    }

//    Connections{
//        target: wallpaper
//        onPrepareDestroy:{
//            player.stop();
//            wallpaper.destroyWindow()
//        }

//        onVolumeChanged:{
//            player.volume = wallpaper.volume
//        }
//        onIsPlayingChanged:{
//            if(wallpaper.isPlaying){
//                player.play()
//            } else {
//                player.pause()
//            }
//        }
//        onDecoderChanged:{
//            player.videoCodecPriority = [decoder]
//        }
//        onFillModeChanged:{
//            if(fillMode === "Stretch"){
//                videoOut.fillMode = VideoOutput2.Stretch
//            } else if(fillMode === "PreserveAspectFit"){
//                videoOut.fillMode = VideoOutput2.PreserveAspectFit
//            }else if(fillMode === "PreserveAspectCrop"){
//                videoOut.fillMode = VideoOutput2.PreserveAspectCrop
//            }
//        }
//    }


    VideoOutput2 {
        id: videoOut
        anchors.fill: parent
        source: player
        opacity: 0
        opengl: true
        fillMode: VideoOutput.Stretch
    }

    MediaPlayer {
        id: player
        videoCodecPriority: ["CUDA", "VAAPI", "D3D11", "DXVA", "FFmpeg"]
        loops: MediaPlayer.Infinite
        volume: 0
        source: "d:/672870/860170953/horde_1980.mp4"
    }

    states: [
        State {
            name: "playing"
            PropertyChanges {
                target: videoOut
                opacity: 1
            }
            PropertyChanges {
                target: player
                volume: 1
            }
        }
    ]
    transitions: [
        Transition {
            from: ""
            to: "playing"
            reversible: true

            OpacityAnimator {
                target: videoOut
                duration: 300
                easing.type: Easing.InOutQuad
            }
            NumberAnimation {
                target: player
                property: "volume"
                duration: 300
            }
        }
    ]
}
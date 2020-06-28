package com.jchen.cplay.test

import android.media.AudioAttributes
import android.media.AudioAttributes.CONTENT_TYPE_MUSIC
import android.media.AudioAttributes.USAGE_MEDIA
import android.media.AudioFormat
import android.media.AudioManager
import android.media.AudioTrack
import android.os.Build
import androidx.annotation.RequiresApi

class AudioTrackTest {
    var minBufferSize : Int = 0;
    var audioTrack: AudioTrack? = null

    @RequiresApi(Build.VERSION_CODES.LOLLIPOP)
    fun test() {
        //配置AudioTrack
        val audioAttributes: AudioAttributes = AudioAttributes.Builder()
                .setUsage(USAGE_MEDIA)
                .setContentType(CONTENT_TYPE_MUSIC)
                .build()
        val audioFormat: AudioFormat = AudioFormat.Builder()
                .setSampleRate(44100)
                .setEncoding(AudioFormat.ENCODING_PCM_16BIT)
                .setChannelMask(AudioFormat.CHANNEL_OUT_STEREO)
                .build();
        minBufferSize = AudioTrack.getMinBufferSize(44100, AudioFormat.CHANNEL_OUT_STEREO, AudioFormat.ENCODING_PCM_16BIT);
        audioTrack = AudioTrack(audioAttributes, audioFormat, minBufferSize, AudioTrack.MODE_STREAM, AudioManager.AUDIO_SESSION_ID_GENERATE)

        //切换到播放状态
        if (audioTrack!!.state != AudioTrack.STATE_UNINITIALIZED) {
            audioTrack!!.play()
        }

        val playerThread = Thread()


    }

    inner class PlayerRunnable : Runnable {
        private var samples: ShortArray? = null
        override fun run() {
//            samples = ShortArray(minBufferSize)
//            while (true) {
//                val actualSize: Int = decoder.readSamples(samples)
//                audioTrack.write(samples, actualSize)
//            }
        }

    }
}
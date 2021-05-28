package com.sensiml.knowledgepack

import android.app.Service
import android.content.Intent
import android.os.IBinder

class KnowledgePackKotlinService : Service() {

    override fun onBind(intent: Intent): IBinder {
        TODO("Return the communication channel to the service.")
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun initKnowledgePackModels()
    external fun runKnowledgePackModel(model: Int, data: ShortArray): Int
    external fun getFeatureVector(model: Int): ByteArray

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("sensiml-knowledgepack")
        }
    }
}

package com.sensiml.knowledgepack;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;



public class KnowledgePackJavaService extends Service {
    static {
        System.loadLibrary("sensiml-knowledgepack");
    }
    public KnowledgePackJavaService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }

    public native void initKnowledgePackModels();
    public native int runKnowledgePackModel(int model, short[] data );
    public native short[] getFeatureVector(int model);

}
// Used to load the 'native-lib' library on application startup.


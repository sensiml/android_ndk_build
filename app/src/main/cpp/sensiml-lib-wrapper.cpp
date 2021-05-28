#include <jni.h>
#include <string>
#include "kb.h"
//#include "testdata.h"

extern "C" JNIEXPORT jint JNICALL
runKnowledgePackModel(JNIEnv *env,
                      jobject thiz, jint model,
                      jshortArray data) {
#if defined(USE_TEST_RAW_SAMPLES)
    static int last_index;
    int ret = 0;
    int index;
    int num_sensors = 0;
    SENSOR_DATA_T *pData;

    if(last_index >= TD_NUMROWS){
        last_index = 0;
    }

    for (index = last_index; index < TD_NUMROWS; index++) {
        pData = (SENSOR_DATA_T *) &testdata[index];
        ret = kb_run_model((SENSOR_DATA_T *) pData, num_sensors, KB_MODEL_0_INDEX);
        if (ret >= 0) {
            kb_print_model_result(KB_MODEL_0_INDEX, ret);
            //sml_output_results(KB_MODEL_0_INDEX, ret);
            kb_reset_model(0);
            last_index = index;
            return ret;
        }
    }
    return ret;

#else
    return -1;
#endif //USE_TEST_RAW_SAMPLES
}

extern "C" JNIEXPORT jobject JNICALL
getFeatureVector(JNIEnv *env, jobject thiz,
                 jint model) {
    jbyteArray result;

    uint8_t tempData[MAX_VECTOR_SIZE];
    uint8_t tempSz;
    kb_get_feature_vector(model, tempData, &tempSz);
    result = env->NewByteArray(tempSz);
    env->SetByteArrayRegion(result, 0, tempSz, reinterpret_cast<const jbyte *>(tempData));
    return result;
}
extern "C" JNIEXPORT void JNICALL
Java_com_sensiml_knowledgepack_KnowledgePackJavaService_initKnowledgePackModels(JNIEnv *env,
                                                                                jobject thiz) {
    kb_model_init();
}

extern "C" JNIEXPORT jint JNICALL
Java_com_sensiml_knowledgepack_KnowledgePackKotlinService_runKnowledgePackModel(JNIEnv *env,
                                                                                jobject thiz,
                                                                                jint model,
                                                                                jshortArray data) {
    return runKnowledgePackModel(env, thiz, model, data);
}

extern "C" JNIEXPORT void JNICALL
Java_com_sensiml_knowledgepack_KnowledgePackKotlinService_initKnowledgePackModels(JNIEnv *env,
                                                                                  jobject thiz) {
    kb_model_init();
}

extern "C" JNIEXPORT jint JNICALL
Java_com_sensiml_knowledgepack_KnowledgePackJavaService_runKnowledgePackModel(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jint model,
                                                                              jshortArray data) {
    return runKnowledgePackModel(env, thiz, model, data);
}

extern "C"
JNIEXPORT jshortArray JNICALL
Java_com_sensiml_knowledgepack_KnowledgePackJavaService_getFeatureVector(JNIEnv *env, jobject thiz,
                                                                         jint model) {
    return (jshortArray) getFeatureVector(env, thiz, model);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_sensiml_knowledgepack_KnowledgePackKotlinService_getFeatureVector(JNIEnv *env,
                                                                           jobject thiz,
                                                                           jint model) {
    return getFeatureVector(env, thiz, model);
}
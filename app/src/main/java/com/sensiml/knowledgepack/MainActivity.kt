package com.sensiml.knowledgepack

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import kotlinx.android.synthetic.main.activity_main.*

import java.lang.StringBuilder

class MainActivity : AppCompatActivity(), View.OnClickListener {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        var kpService = KnowledgePackKotlinService()

        kpService.initKnowledgePackModels()

        classificationButton.setOnClickListener {
            var dummyarray = ShortArray(3)
            var k = kpService.runKnowledgePackModel(0, dummyarray)
            if (k >= 0) {
                var fv = kpService.getFeatureVector(0);
                var output = StringBuilder("Model 0 Class ")
                output.append(k);
                output.append("\n")
                output.append(fv.toUByteArray().joinToString(prefix = "Features: [", postfix = "]"))
                sample_text.text = output.toString();
            } else{
                var output = StringBuilder("Model 0 Class Unknown ")
                output.append(k);
                var fv = kpService.getFeatureVector(0);
                output.append("\n")
                output.append(fv.toUByteArray().joinToString(prefix = "Features: [", postfix = "]"))

                sample_text.text = output.toString();
            }
        }

        // Example of a call to a native method

        Thread.sleep(1000L)
    }

    override fun onClick(v: View?) {
        TODO("Not yet implemented")
    }

}

package com.example.drone_controller

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import androidx.lifecycle.lifecycleScope
import com.example.drone_controller.databinding.ActivityMainBinding
import kotlinx.coroutines.*

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        lifecycleScope.launch {
            while (true) {
                binding.sampleText.text = stringFromJNI()
                delay(1000)
            }
        }

    }

    /**
     * A native method that is implemented by the 'drone_controller' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'drone_controller' library on application startup.
        init {
            System.loadLibrary("drone_controller")
        }
    }
}
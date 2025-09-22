package com.example.drone_controller

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import androidx.lifecycle.lifecycleScope
import com.example.drone_controller.databinding.ActivityMainBinding
import kotlinx.coroutines.*
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.widget.ImageView
import android.widget.Toast
import android.os.Handler
import android.os.Looper

class MainActivity : AppCompatActivity() {

    external fun start_UDP_receiver(port: Int): Boolean
    external fun close_UDP_receiver(): Boolean
    external fun get_frame(): ByteArray?

    companion object {
        // Used to load the 'drone_controller' library on application startup.
        init {
            System.loadLibrary("drone_controller")
        }
    }
    private lateinit var binding: ActivityMainBinding

    private lateinit var imageView: ImageView
    private val handler = Handler(Looper.getMainLooper())

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        imageView = findViewById(R.id.imageView)

        // Calculate delay for target frame rate
        val target_fps = 30
        val delay_fps = 1000f / target_fps

        val started = start_UDP_receiver(5000) // Open socket to receive stream from drone

        // If failed to open video stream close
        if (!started) {
            Toast.makeText(this, "Failed to open socket and start UDP receiver!", Toast.LENGTH_SHORT).show()
            return
        }

        start_video_stream(delay_fps.toLong()) // Start receiving video from drone

    }

    // Function which handels receving video stream from drone and displaying on screen
    private fun start_video_stream(delay: Long) {
        lifecycleScope.launch(Dispatchers.IO) {
            while (isActive) {
                val data = get_frame()

                if (data != null) {
                    val bitmap = BitmapFactory.decodeByteArray(data, 0, data.size)
                    withContext(Dispatchers.Main) {
                        imageView.setImageBitmap(bitmap)
                    }
                }

                delay(delay)
            }
        }
    }

    // When app is closed, close socket and stop receiving video stream from drone
    override fun onDestroy() {
        super.onDestroy()
        close_UDP_receiver()
    }

}
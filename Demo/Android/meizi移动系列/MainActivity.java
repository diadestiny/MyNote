package com.example.day01;


import android.annotation.SuppressLint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.FrameLayout;


public class MainActivity extends AppCompatActivity {

    private FrameLayout frame;
    private MeiziView mezi;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        frame = findViewById(R.id.mylayout);
        mezi = new MeiziView(this);
        //为我们的萌妹子添加触摸事件监听器
        mezi.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                //设置妹子显示的位置
               mezi.bitmapX= event.getX()-150;
               mezi.bitmapY= event.getY()-150;
               mezi.invalidate();
               return true;
            }
        });
        frame.addView(mezi);
    }
}


package com.example.day01;


import android.graphics.drawable.Drawable;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.FrameLayout;
import java.util.Timer;
import java.util.TimerTask;


public class MainActivity extends AppCompatActivity {

    private FrameLayout frame;
    private MeiziView mezi;
    Handler handler =new Handler(){
        int i=0;
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            if(msg.what==0x123){
                i++;
                move(i%2);
            }
        }
    };

    private void move(int i) {
        Drawable a =getResources().getDrawable(R.mipmap.meizi);
        Drawable b =getResources().getDrawable(R.mipmap.pic);
        switch (i){
            case 0:
                frame.setForeground(a);
                break;
            case 1:
                frame.setForeground(b);
                break;
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        frame = findViewById(R.id.myframe);
        new Timer().schedule(new TimerTask() {
            @Override
            public void run() {
                handler.sendEmptyMessage(0x123);
            }
        },0,100);
    }
}


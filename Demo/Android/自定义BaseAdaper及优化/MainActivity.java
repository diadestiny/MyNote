package com.example.day01;


import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.SimpleAdapter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;


public class MainActivity extends AppCompatActivity {

    private ListView listView=null;
    private AnimalAdapter animalAdapter=null;
    private List<Animal> mData;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mData = new LinkedList<>();
        mData.add(new Animal("狗说", "你是狗么?", R.mipmap.pic));
        mData.add(new Animal("牛说", "你是牛么?", R.mipmap.pic1));
        mData.add(new Animal("鸭说", "你是鸭么?", R.mipmap.pic2));
        mData.add(new Animal("鱼说", "你是鱼么?", R.mipmap.pic3));

        animalAdapter=new AnimalAdapter((LinkedList<Animal>)mData,this);

        listView = findViewById(R.id.mylistview);
        listView.setAdapter(animalAdapter);

    }
}


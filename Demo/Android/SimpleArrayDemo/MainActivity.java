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
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;


public class MainActivity extends AppCompatActivity {

    private String[] names= {"林xx","李xx","赵xx","王xx"};
    private String[] says ={"无形被黑，最为致命", "大神好厉害~", "我将带头冲锋~","楼上最强~~"};
    private int[] imgids = {R.mipmap.pic,R.mipmap.pic1,R.mipmap.pic2,R.mipmap.pic3};
    private ListView listView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        List<Map<String,Object>> listitem = new ArrayList<>();
        for(int i=0;i<names.length;i++){
            Map<String,Object> showitem =new HashMap<String, Object>();
            showitem.put("img",imgids[i]);
            showitem.put("title",names[i]);
            showitem.put("info",says[i]);
            listitem.add(showitem);
        }

        listView = findViewById(R.id.mylistview);
        SimpleAdapter adapter =new SimpleAdapter(this,listitem,R.layout.list_item,new String[]{"img","title","info"},new int[]{R.id.tupian,R.id.name,R.id.says});
        listView.setAdapter(adapter);

    }
}


package com.example.day08;

import android.app.Activity;
import android.nfc.Tag;
import android.os.Bundle;
import android.os.Environment;
import android.text.format.Formatter;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;

import static android.os.Environment.getExternalStorageDirectory;

public class SDCardDemoActivity extends Activity implements View.OnClickListener {

    private Button mwriteDataBtn;
    private Button checkSdCardBtn;
    private static final String TAG ="test001";
    private Button getFreeSizeBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //设置布局
        setContentView(R.layout.activity_sd_card);
        initView();
        initListener();
    }

    private void initListener() {
        mwriteDataBtn.setOnClickListener(this);
        checkSdCardBtn.setOnClickListener(this);
        getFreeSizeBtn.setOnClickListener(this);

    }

    private void initView() {
        mwriteDataBtn = findViewById(R.id.write_data_sd_data_btn);
        checkSdCardBtn = findViewById(R.id.sd_cast_check_btn);
        getFreeSizeBtn = findViewById(R.id.get_sd_card_free_size);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.write_data_sd_data_btn:
                //写数据到sd卡

                //Log.d(TAG,exFile+"");

                File file = new File(Environment.getExternalStorageDirectory(),"info.txt");
                FileOutputStream fos = null;
                try {
                    fos = new FileOutputStream(file);
                    fos.write("bos.fas.com".getBytes());
                    fos.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                break;
            case R.id.sd_cast_check_btn:
                //判断sd卡是否挂载
                String state = Environment.getExternalStorageState();
                if(state.equals(Environment.MEDIA_MOUNTED)){
                    Log.d(TAG,"sd卡已经挂载");
                }else if(state.equals(Environment.MEDIA_UNMOUNTED)){
                    Log.d(TAG,"sd卡已经删除");
                }
                break;
            case  R.id.get_sd_card_free_size:
                File  exFile =Environment.getExternalStorageDirectory();
                Log.d(TAG,exFile+"");
                long freeSpace = exFile.getFreeSpace();
                String sizeText = Formatter.formatFileSize(this,freeSpace);
                Log.d(TAG,"free size=="+sizeText);
                break;
        }
    }
}

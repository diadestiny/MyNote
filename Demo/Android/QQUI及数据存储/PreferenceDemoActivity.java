package com.example.day08;

import android.app.Activity;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.util.Log;
import android.widget.CompoundButton;
import android.widget.Switch;

public class PreferenceDemoActivity extends Activity implements CompoundButton.OnCheckedChangeListener {

    private Switch mIsAllowUNknownSource;
    private static final String TAG="test002";
    private SharedPreferences mSharedPreferences;

    @Override
    protected void onCreate( Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_preference_demo);

        //找到控件
        mIsAllowUNknownSource = findViewById(R.id.is_unknown_apps_sources);
        mIsAllowUNknownSource.setOnCheckedChangeListener(this);
        //第一步拿到这个SharedPreferences
        mSharedPreferences = this.getSharedPreferences("setting_info", MODE_PRIVATE);
        boolean state=mSharedPreferences.getBoolean("state",false);
        mIsAllowUNknownSource.setChecked(state);
    }

    @Override
    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        //我们在这里需要对数据进行保存
        Log.d(TAG,"the current state is"+isChecked);
        //第二步进入编辑模式
        SharedPreferences.Editor edit = mSharedPreferences.edit();
        //第三步保存数据
        //保存的数据类型有boolean,有String,float,StringSet,int
        edit.putBoolean("state",isChecked);
        //第四步提交编辑器
        edit.apply();
    }
}

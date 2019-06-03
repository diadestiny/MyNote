package com.example.day08;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * 为什么我们直接写一个文件名的时候，去写文件，报出的异常是read-only,
 * 其实呢，在Android系统中，每一个应用就是一个用户，每个用户他的权限是特定的，不可操作其他应用的内容。
 *
 * 以'/'为根目录的，区别于windows
 */

public class MainActivity extends AppCompatActivity {

    private EditText mAccount;
    private EditText mPassword;
    private Button mLogin;
    private String TAG="Test001";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();//第一步 找到控件
        initListener();
    }
    /**
     *这个方法就是给我们的按钮设置点击的监听
     */
    private void initListener() {
        mLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d(TAG,"点击了登录按钮");
                handlerLoginEvent(v);
            }
        });
    }

    /**
     * 处理登录事件
     */
    private void handlerLoginEvent(View v) {
        //第三步，我们要拿到界面上的内容,包括账号和密码
        //账号和密码
        String accountTest = mAccount.getText().toString();
        String passwordTest = mPassword.getText().toString();

        //对帐号进行检查/在实际开发中需要对用户的帐号进行合法性检查

//        if(accountTest.length()==0){
//            //账号长度为空...
//            Toast.makeText(this,"账号不可以为空",Toast.LENGTH_SHORT).show();
//            return;
//        }
//        if(passwordTest.length()==0){
//            //账号长度为空...
//
//            Toast.makeText(this,"密码不可以为空",Toast.LENGTH_SHORT).show();
//            return;
//        }

        if(TextUtils.isEmpty(accountTest)){
        //账号长度为空...
            Toast.makeText(this,"账号不可以为空",Toast.LENGTH_SHORT).show();
            return;
        }
        if(TextUtils.isEmpty(passwordTest)){
            //密码长度为空...
            Toast.makeText(this,"密码不可以为空",Toast.LENGTH_SHORT).show();
            return;
        }
        //把账号和密码保存起来
        saveUserInfo(accountTest,passwordTest);


    }

    private void saveUserInfo(String accountTest, String passwordTest) {
        Log.d(TAG,"保存用户信息");

        File cacheDir = this.getCacheDir();
        Log.d(TAG,"file dir == "+cacheDir.toString());
        //怎么获取到文件保存的路径呢
        //学会this.getFileDir()方法
        File fileDir = this.getFilesDir();

        File saveFile = new File(fileDir,"info.text");

        Log.d(TAG,"file dir == "+fileDir.toString());

        if(!saveFile.exists()){
            try {
                saveFile.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        try {
            FileOutputStream fos = new FileOutputStream(saveFile);
            //以特定的形式存储
            //我们的账号***我们的密码
            fos.write((accountTest+"***"+passwordTest).getBytes());
            Log.d(TAG,"写进用户信息");
            fos.close();
            Toast.makeText(this,"数据保存成功",Toast.LENGTH_SHORT).show();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        File fileDir = this.getFilesDir();
        File saveFile = new File(fileDir,"info.text");
        try {
            FileInputStream fileInputStream = this.openFileInput("info.text");
            BufferedReader bufferedReader =new BufferedReader(new InputStreamReader(fileInputStream));
            String info = bufferedReader.readLine();

            //fos.write((accountTest+"***"+passwordTest).getBytes());
            //保存的形式
            String [] splits = info.split("\\*\\*\\*");
            String accout = splits[0];
            String password = splits[1];

            //回显数据
            mAccount.setText(accout);
            mPassword.setText(password);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 这个方法,我们用来找到对应的控件
     */
    private void initView() {
        mAccount = findViewById(R.id.et_account);
        mPassword = findViewById(R.id.et_password);
        mLogin = findViewById(R.id.bt_login);
    }
}

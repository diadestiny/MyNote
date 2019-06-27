package com.example.myapplication;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.ImageView;

import java.io.IOException;
import java.util.List;

public class CameraActivity extends AppCompatActivity {

    private SurfaceView surfaceView = null;
    private Button camera_but = null;
    private Button flash=null;
    private Button change=null;
    private ImageView iv = null;
    private SurfaceHolder holder;
    private Camera camera=null;
    private Camera.Parameters parameters=null;
    private static final String TAG ="CameraActivity001";
    private boolean isOpenLightSign=false;
    int postion = 0;//1表示前头 0表示后头

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera);
        if (getSupportActionBar() != null){
            getSupportActionBar().hide();
        }
        surfaceView = findViewById(R.id.sv_camera_surface);
        camera_but = findViewById(R.id.camera_but);
        change = findViewById(R.id.change);
        iv = findViewById(R.id.iv);
        flash = findViewById(R.id.flash);

        holder = surfaceView.getHolder();
        holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
        holder.setFixedSize(177,144);
        holder.setKeepScreenOn(true);
        holder.addCallback(new MySufaceCallBack());

        camera_but.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                camera.takePicture(null,null,new TabkePic());
            }
        });
        flash.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                isOpenLightSign = !isOpenLightSign;
                changeLight();
            }
        });
        change.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                changeCamera();
            }
        });

    }

    @Override
    protected void onPause() {
        super.onPause();
        if(camera!=null){
            camera.stopPreview();
        }
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        if(camera!=null){
            camera.startPreview();
        }else{
            try{
                camera = Camera.open();
                camera.setDisplayOrientation(90);
                camera.setPreviewDisplay(holder);
                camera.startPreview();
            }catch (IOException e){
                e.printStackTrace();
            }
        }
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
    }

    private void changeLight(){
        Camera.Parameters parameters = camera.getParameters();
        if(isOpenLightSign){
            parameters.setFlashMode(Camera.Parameters.FLASH_MODE_ON);
            Log.d(TAG,"1");
            flash.setText("关闭闪光灯");
        }else{
            parameters.setFlashMode(Camera.Parameters.FLASH_MODE_OFF);
            Log.d(TAG,"0");
            flash.setText("打开闪光灯");
        }
        camera.setParameters(parameters);
    }
    private void changeCamera(){
        Camera.CameraInfo cameraInfo = new Camera.CameraInfo();
        int count = Camera.getNumberOfCameras();
        for(int i=0;i<count;i++){
            Camera.getCameraInfo(i,cameraInfo);
            if(postion==1){
                if(cameraInfo.facing==Camera.CameraInfo.CAMERA_FACING_BACK){
                    try {
                        camera.stopPreview();
                        camera.release();
                        camera=null;
                        camera = Camera.open(i);
                        camera.setDisplayOrientation(90);
                        camera.setPreviewDisplay(holder);
                        camera.startPreview();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    postion=0;
                    change.setText("打开前置摄像头");
                    break;
                }
            }else{
                if(cameraInfo.facing==Camera.CameraInfo.CAMERA_FACING_FRONT){
                    try {
                        camera.stopPreview();
                        camera.release();
                        camera=null;
                        camera = Camera.open(i);
                        camera.setDisplayOrientation(90);
                        camera.setPreviewDisplay(holder);
                        camera.startPreview();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    postion=1;
                    change.setText("打开后置摄像头");
                    break;
                }
            }
        }

    }

    class TabkePic implements Camera.PictureCallback{
        @Override
        public void onPictureTaken(byte[] data, Camera camera) {
            Bitmap bit0 = BitmapFactory.decodeByteArray(data,0,data.length);
            Matrix m = new Matrix();
            m.setRotate(90,(float) bit0.getWidth() / 2, (float) bit0.getHeight() / 2);
            final Bitmap bitmap = Bitmap.createBitmap(bit0, 0, 0, bit0.getWidth(), bit0.getHeight(), m, true);
            if(data.length>0){
                iv.setImageBitmap(bitmap);
            }
        }
    }
    class MySufaceCallBack implements  SurfaceHolder.Callback{
        @Override
        public void surfaceCreated(SurfaceHolder surfaceHolder) {
            if (ContextCompat.checkSelfPermission(CameraActivity.this, Manifest.permission.CAMERA)
                    == PackageManager.PERMISSION_GRANTED) {
                Log.d(TAG,"hello1");
            }else {
                ActivityCompat.requestPermissions(CameraActivity.this,new String[]{Manifest.permission.CAMERA},1);
                Log.d(TAG,"hello2");
            }
            try{
                camera = Camera.open();
                camera.setDisplayOrientation(90);
                camera.setPreviewDisplay(holder);
                camera.startPreview();
            }catch (IOException e){
                e.printStackTrace();
            }

        }

        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
            parameters = camera.getParameters();
            List<Camera.Size> supportedPictureSizes = parameters.getSupportedPictureSizes();
            if(supportedPictureSizes.isEmpty()){
                parameters.setPreviewSize(width,height);
            }else{
                Camera.Size size = supportedPictureSizes.get(0);
                parameters.setPreviewSize(size.width,size.height);
            }
            parameters.setPictureFormat(PixelFormat.JPEG);
            parameters.setPictureSize(width,height);
            parameters.setJpegQuality(80);
            parameters.setPreviewFrameRate(5);
            Log.d(TAG,"surfaceChanged");

        }
        @Override
        public void surfaceDestroyed(SurfaceHolder holder) {
            if(camera!=null){
                camera.release();
                camera = null;
            }
        }
    }



}

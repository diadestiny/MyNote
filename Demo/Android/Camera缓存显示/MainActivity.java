 package com.example.cameraalbuntest;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Build;
import android.provider.MediaStore;
import android.support.annotation.Nullable;
import android.support.v4.content.FileProvider;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import java.io.File;
import java.io.IOException;

 public class MainActivity extends AppCompatActivity implements View.OnClickListener {

     private static final int TAKE_PHOTO = 1 ;
     private Button takePhoto;
     private ImageView picture;
     private Uri imageuri;

     @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initUI();
        takePhoto.setOnClickListener(this);
    }

    private void initUI() {
        takePhoto = findViewById(R.id.take_photo);
        picture = findViewById(R.id.picture);
     }

     @Override
     public void onClick(View v) {
         if(v.getId()==R.id.take_photo){
             File outputImage = new File(getExternalCacheDir(),"output_image.jpg");
             try {
             if(outputImage.exists()){
                 outputImage.delete();
             }
             outputImage.createNewFile();
             } catch (Exception e) {
                 e.printStackTrace();
             }
             if(Build.VERSION.SDK_INT>=24){
                 imageuri = FileProvider.getUriForFile(MainActivity.this,"com.example.cameraalbumtest.fileprovider",outputImage);
             }else{
                 imageuri = Uri.fromFile(outputImage);
             }
             //启动相机程序
             Intent intent = new Intent("android.media.action.IMAGE_CAPTURE");
             intent.putExtra(MediaStore.EXTRA_OUTPUT,imageuri);
             startActivityForResult(intent,TAKE_PHOTO);
         }
     }

     @Override
     protected void onActivityResult(int requestCode, int resultCode, Intent data) {
         switch (requestCode){
             case TAKE_PHOTO:
             if(resultCode==RESULT_OK) {
                 try {
                     Bitmap bitmap = BitmapFactory.decodeStream(getContentResolver().openInputStream(imageuri));
                     picture.setImageBitmap(bitmap);
                 } catch (Exception e) {
                     e.printStackTrace();
                 }
             }
             break;
             default:break;
         }
     }
 }

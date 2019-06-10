package com.example.day01;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.View;

public class MeiziView extends View {

    public float bitmapX ;//x坐标
    public float bitmapY ;//y坐标

    public MeiziView(Context context) {
        super(context);
        //设置妹子的起始坐标
        bitmapX=0;
        bitmapY=0;
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        //创建并实例化Paint的对象
        Paint paint = new Paint();
        //根据图片生成位图对象
        Bitmap bitmap = BitmapFactory.decodeResource(this.getResources(),R.mipmap.meizi);
        //绘画图标
        canvas.drawBitmap(bitmap,bitmapX,bitmapY,paint);
        //判断并回收图片
        if(bitmap.isRecycled()){
            bitmap.recycle();
        }
    }
}

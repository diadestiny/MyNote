package com.example.day09;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

public class DrawView extends View {
    Paint p = new Paint();
    private float currentX=100;
    private float currentY=150;

    public DrawView(Context context) {
        super(context);
    }

    public DrawView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        p.setColor(Color.RED);
        canvas.drawCircle(currentX,currentY,50,p);
    }
    //重写触摸事件

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        currentX =event.getX();
        currentY =event.getY();
        //通知组件重绘自己
        invalidate();
        //返回true表明该处理方法已经处理该事件
        return true;
    }
}
